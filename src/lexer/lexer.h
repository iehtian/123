#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include<limits.h>
#include<windows.h>
#include <stdbool.h>

#define id_maxlen 64//对标识符的长度做出限制
#define str_maxlen 2048//字符串长度与C语言本身无关，这里规定字符串长度
#define num_maxlen 64//限制数字长度

#define Marchstr(tem,str,Type) if(strcmp(tem,str) == 0) node->type= Type
#define Matchar(tem, c, Type) \
    if ((tem) == (c)) { \
        node->type = (Type); \
        j++; \
        node->prior = *list; \
        (*list)->next = node; \
        *list = (*list)->next; \
        /* free(tem); */ \
        bcc_log_info("lex", "第%ld行：%s %d\n", count_line, (*list)->value, (*list)->type); \
        *i = j; \
		return 1;\
    }

enum value_type {
	Auto, Break, Case, Char, Const, Continue, Default, Do, Double, Else, Enum, Extern, Float, For, Goto, If,
	Inline, Int, Long, Register, Restrict, Return, Short, Signed, Sizeof, Static, Struct, Switch, Typedef,
	Union, Unsigned, Void, Volatile, While, Bool, Complex, Imaginary, OpenBracket, CloseBracket,
	OpenParen, CloseParen, OpenBrace, CloseBrace, Dot, MemSelePointer, Increment, Decrement, Address, Derefer_Mul,
	Add, Sub, BitNOT, LogicalNOT, Division, Mod, LShift, RShift, Less, Greater, LessOrEqual, GreaterOrEqual,
	Equal, NotEqual, BitXOR, BitOR, LogicalAND, LogicalOR, Condition, Colon, Semicolon, VarArgument, Assignment,
	MulAss, DivAss, ModAss, AddAss, SubAss, LShAss, RShAss, BitANDAss, BitXORAss, BitORAss, Comma, Pound, DouPound,
	Id, Character, String, Integer, FloatNum, PPDefine, PPInclude, PPUndef, PPIfdef, PPIfndef, PPElif, PPEndif,
	PPLine, PPError, PPPragma, PPIf, PPElse
};

extern const char* tok_str[150];

typedef struct DoubleListNode
{
	enum value_type type;//属性，即类别或编码、种别码，如100，101
	char* value;//单词本身
	struct DoubleListNode* prior; // 前驱指针
	struct DoubleListNode* next;  // 后驱指针
}DoubleListNode;
typedef struct DoubleListNode* DoubleLinkList;


bool isletter(char c);
bool isdigits(char c);
bool isqmark(char c);
bool is_hex_char(char c);
DoubleLinkList NodeInit();
bool oppre(char s[], int* i, int len, DoubleLinkList* list, long int count_line);
bool opstr(char s[], int* i, int len, DoubleLinkList* list, long int count_line);
bool opqmark(char s[], int* i, int len, DoubleLinkList* list,long int *cl);
bool opcomment(char s[], int* i, int len, DoubleLinkList* list,long int *cl);
bool op_operator(char s[], int* i, int len, DoubleLinkList* list, long int count_line);
bool opnum(char s[], int* i, int len, DoubleLinkList* list, long int count_line);
