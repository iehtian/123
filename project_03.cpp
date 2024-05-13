#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
// #define maxsize 100
#define id_maxlen 64//对标识符的长度做出限制
#define str_maxlen 2048//字符串长度与C语言本身无关，这里规定字符串长度
#define num_maxlen 64//限制数字长度
#include<limits.h>
#include<errno.h>
enum value_type {
    Auto,Break,Case,Char,Const,Continue,Default,Do,Double,Else,Enum,Extern,Float,For,Goto,If,
    Inline, Int, Long, Register, Restrict, Return, Short, Signed, Sizeof, Static, Struct, Switch, Typedef,
    Union, Unsigned, Void, Volatile, While, Bool, Complex, Imaginary, OpenBracket, CloseBracket,
    OpenParen, CloseParen,OpenBrace, CloseBrace, Dot, MemSelePointer, Increment, Decrement, Address, Derefer_Mul,
    Add, Sub, BitNOT, LogicalNOT, Division, Mod, LShift, RShift, Less, Greater, LessOrEqual, GreaterOrEqual,
    Equal, NotEqual, BitXOR, BitOR, LogicalAND, LogicalOR, Condition, Colon, Semicolon, VarArgument, Assignment,
    MulAss, DivAss, ModAss, AddAss, SubAss, LShAss, RShAss, BitANDAss, BitXORAss, BitORAss, Pound, DouPound,
    Id, Character, String, Integer, FloatNum, Define, Include, Comma, undef,
    //某些符号暂未考虑
};
/*注意415页的宏定义*/
struct DoubleListNode
{
    enum value_type type;//属性，即类别或编码、种别码，如100，101
    char* value;//单词本身
    struct DoubleListNode* prior; // 前驱指针
    struct DoubleListNode* next;  // 后驱指针
};
typedef struct DoubleListNode* DoubleLinkList;
DoubleLinkList NodeInit()//初始化一个节点
{
	DoubleLinkList Node = (DoubleLinkList)malloc(sizeof(DoubleListNode));
	Node->prior = NULL;
	Node->next = NULL;
	return Node;
}
bool isletter(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return true;
    else
        return false;
}
bool isdigit(char c) {
    if (c >= '0'&&c <= '9')
        return true;
    else
        return false;
}
bool isqmark(char c) {
	if (c == '\''||c=='"')
        return true;
    else
        return false;
}
bool is_hex_char(char c) {
    if ((c >= '0'&&c <= '9') || (c >= 'a'&&c <= 'f') || (c >= 'A'&&c <= 'F'))
        return true;
    else
        return false;
}
bool opstr(char s[], int* i, int len, DoubleLinkList& list) {//检查是否为关键字或标识符
    int j = *i, strlen = 0;
    DoubleLinkList node = NodeInit();
    char* tem;
    tem = (char*)malloc(sizeof(char) * id_maxlen);
    memset(tem, 0, sizeof(char) * id_maxlen);
    // node->value = (char*)malloc(sizeof(char) * maxsize);
    // memset(node->value, 0, sizeof(char) * maxsize);
    while (j < len)
    {
        if (isdigit(s[j]) || isletter(s[j])||s[j] == '_')
            tem[strlen++] = s[j++];
        else
            break;
    }
    if (strlen == 2)
    {
        if (strcmp(tem, "do") == 0)
            node->type = Do;
        else if (strcmp(tem, "if") == 0)
            node->type = If;
        else
            node->type = Id;//这个字母开头的一串字符不是关键字，那么必为标识符
    }
    else if (strlen == 3)
    {
        if (strcmp(tem, "for") == 0)
            node->type = For;
        else if (strcmp(tem, "int") == 0)
            node->type = Int;
        else
            node->type = Id;//这个字母开头的一串字符不是关键字，那么必为标识符
    }
    else if (strlen == 4)
    {
        if (strcmp(tem, "auto") == 0)
            node->type = Auto;
        else if (strcmp(tem, "case") == 0)
            node->type = Case;
        else if (strcmp(tem, "char") == 0)
            node->type = Char;
        else if (strcmp(tem, "else") == 0)
            node->type = Else;
        else if (strcmp(tem, "enum") == 0)
            node->type = Enum;
        else if (strcmp(tem, "goto") == 0)
            node->type = Goto;
        else if (strcmp(tem, "long") == 0)
            node->type = Long;
        else if (strcmp(tem, "void") == 0)
            node->type = Void;
        else if (strcmp(tem, "bool") == 0)
            node->type = Bool;
        else
            node->type = Id;//这个字母开头的一串字符不是关键字，那么必为标识符
    }
    else if (strlen == 5)
    {
        if (strcmp(tem, "break") == 0)
            node->type = Break;
        else if (strcmp(tem, "const") == 0)
            node->type = Const;
        else if (strcmp(tem, "float") == 0)
            node->type = Float;
        else if (strcmp(tem, "short") == 0)
            node->type = Short;
        else if (strcmp(tem, "union") == 0)
            node->type = Union;
        else if (strcmp(tem, "while") == 0)
            node->type = While;
        else if (strcmp(tem, "_Bool") == 0)
            node->type = Bool;
        else
            node->type = Id;//这个字母开头的一串字符不是关键字，那么必为标识符
    }
    else if (strlen==6)
    {
        if (strcmp(tem, "double") == 0)
            node->type = Double;
        else if (strcmp(tem, "extern") == 0)
            node->type = Extern;
        else if (strcmp(tem, "inline") == 0)
            node->type = Inline;
        else if (strcmp(tem, "signed") == 0)
            node->type = Signed;
        else if (strcmp(tem, "sizeof") == 0)
            node->type = Sizeof;
        else if (strcmp(tem, "static") == 0)
            node->type = Static;
        else if (strcmp(tem, "struct") == 0)
            node->type = Struct;
        else if (strcmp(tem, "switch") == 0)
            node->type = Switch;
        else if (strcmp(tem, "return") == 0)
            node->type = Return;
        else
            node->type = Id;//这个字母开头的一串字符不是关键字，那么必为标识符
    }
    else if (strlen == 7)
    {
        if (strcmp(tem, "default") == 0)
            node->type = Default;
        else if (strcmp(tem, "typedef") == 0)
            node->type = Typedef;
        else if (strcmp(tem, "complex") == 0)
            node->type = Complex;
        else
            node->type = Id;//这个字母开头的一串字符不是关键字，那么必为标识符
    }
    else if (strlen == 8) {
        if (strcmp(tem, "continue") == 0)
            node->type = Continue;
        else if (strcmp(tem, "register") == 0)
            node->type = Register;
        else if (strcmp(tem, "restrict") == 0)
            node->type = Restrict;
        else if (strcmp(tem, "unsigned") == 0)
            node->type = Unsigned;
        else if (strcmp(tem, "volatile") == 0)
            node->type = Volatile;
        else if (strcmp(tem, "_Complex") == 0)
            node->type = Complex;
        else
            node->type = Id;//这个字母开头的一串字符不是关键字，那么必为标识符
    }
    else if (strcmp(tem, "_Imaginary") == 0 || strcmp(tem, "imaginary") == 0)
        node->type = Imaginary;
    else
        node->type = Id;//这个字母开头的一串字符不是关键字，那么必为标识符
    node->value = (char*)malloc(sizeof(char) * strlen);
    memset(node->value, 0, sizeof(char)* strlen);
    // printf("%s\n", tem);
    strcpy(node->value,tem);
    // for (int k = 0; k < strlen; k++)
    //     node->value[k] = tem[k];
    free(tem);
    node->prior = list;
    list->next = node;
    list = list->next;
    printf("%s %d\n", list->value, list->type);
    *i = j;
    return true;
}
bool opqmark(char s[], int* i, int len, DoubleLinkList& list) {
    int j = *i, strlen = 0, tag = 0;
    DoubleLinkList node = NodeInit();
    char* tem;
    tem = (char*)malloc(sizeof(char) * str_maxlen);
    memset(tem, 0, sizeof(char) * str_maxlen);
    // node->value = (char*)malloc(sizeof(char) * maxsize);
    // memset(node->value, 0, sizeof(char) * maxsize);
    if (s[j]=='\"')
        tag = 1;    
    j++;
    while (j < len) {
        if (s[j] == '\\')//遇到了转义字符，那么该字符和下个字符不会是结束标志
        {
            j++;
            if (s[j] == '\\')
            {
                tem[strlen++] = '\\';
                j++;
            }
                
            else if (s[j] == 'n'){
                tem[strlen++] = '\n';
                j++;
            }
            else if (s[j] == 't') {
                tem[strlen++] = '\t';
                j++;
            }
            else if (s[j] == 'r') {
                tem[strlen++] = '\r';
                j++;
            }
            else if (s[j] == 'b') {
                tem[strlen++] = '\b';
                j++;
            }
            else if (s[j] == 'f') {
                tem[strlen++] = '\f';
                j++;
            }
            else if (s[j] == 'v') {
                tem[strlen++] = '\v';
                j++;
            }
            else if (s[j] == 'a') {
                tem[strlen++] = '\a';
                j++;
            }
            else if (s[j] == '\'') {
                tem[strlen++] = '\'';
                j++;
            }
            else if (s[j] == '\"') {
                tem[strlen++] = '\"';
                j++;
            }
            // j++;
            else if (isdigit(s[j]))//是数字，转义8进制数
            {
                char Base_8[3];
                int k = 0;
                memset(Base_8, 0, sizeof(Base_8));
                while (isdigit(s[j])&&k<3)
                {
                    if (s[j] > '7' || s[j] < '0')//非法，退出
                        break;
                    Base_8[k++] = s[j++];
                }
                int decimal = 0,count=0;
                for ( ; count < k; count++)
                    decimal = decimal * 8 + (Base_8[count] - '0');
                if (decimal>256)
                {
                    printf("八进制转义后值大于256，非法输入\n");
                    free(tem);
                    free(node);
                    break;
                }
                else if (decimal == 0)
                {
                    continue;
                }
                tem[strlen++] = decimal;
            }
            else if (s[j] == 'x')//转义16进制数
            {
                char Base_16[2];
                int k = 0;
                j++;
                memset(Base_16, 0, sizeof(Base_16));
                while (k < 2)
                {
                    if (!is_hex_char(s[j]))//不是16进制数
                        break;
                    Base_16[k++] = s[j++];
                }
                if (k < 1)//说明没能识别到两个16进制数
                {
                    printf("该输入非法，应输入两个16进制数\n");
                    free(tem);
                    free(node);
                    break;
                }
                else
                {
                    int decimal = 0, count = 0;
                    for (; count < k; count++)
                        decimal = decimal * 16 + (Base_16[count] - '0');
                    if (decimal > 256)
                    {
                        printf("十六进制转义后值大于256，非法输入");
                        free(tem);
                        free(node);
                        break;
                    }
                    tem[strlen++] = decimal;
                }
            }
            
        }
        else if(s[j]=='\''||s[j]=='\"')
        //遇到结束标志
            break;
        else
        tem[strlen++] = s[j++];
    }
    if (tag == 0)//处理字符
    {
        if (strlen == 0 || strlen > 1)
        {
            printf("单字符有且只能有一个字符，该输入非法\n");
            free(tem);
            free(node);
            *i = ++j;
            return false;
        }
        else
        {
            node->value = (char*)malloc(sizeof(char));
            node->value[0] = tem[0];
            free(tem);
            node->type = Character;
        }
    }
    else
    {
        node->value = (char*)malloc(sizeof(char) * strlen);
        memset(node->value, 0, sizeof(char) * strlen);
        strcpy(node->value, tem);
        free(tem);
        node->type = String;
    }
    node->prior = list;
    list->next = node;
    list = list->next;
    printf("%s %d\n", list->value, list->type);
    *i = ++j;
    return true;
}
bool opcomment(char s[], int* i, int len, DoubleLinkList& list) {
    int j = *i;
    if (s[j + 1] == '/')//注意，j+1可能越界
    {
        while (j < len)
        {
            if (s[j] == '\n' || s[j] == '\0')
            {
                *i = ++j;
                return true;
            }
            j++;
        }
    }
    else if (s[j + 1] == '*')
    {
        while(j<len)
        {
            if (s[j] == '*' && s[j + 1] == '/')
            {
                *i = j + 2;
                return true;
            }
            j++;
        }
    }
    else {//不为注释，那么考虑为作为/或/=
        DoubleLinkList node = NodeInit();
        node->value = (char*)malloc(sizeof(char) * 2);
        memset(node->value, 0, sizeof(char) * 2);
        node->prior = list;
        list->next = node;
        node->value[0]='/';
        if (s[j + 1] == '=')
        {
            node->type = DivAss;
            node->value[1] = '=';
            j++;
        }
        else
            node->type = Division;
        list = list->next;
        printf("%s %d\n", list->value, list->type);
    }
    j++;
    *i = j;
    return true;
}
bool op_operator(char s[], int* i, int len, DoubleLinkList& list) {
    int j = *i, strlen = 0;
    DoubleListNode* node = NodeInit();
    node->value = (char*)malloc(sizeof(char) * 3);
    memset(node->value, 0, sizeof(char) * 3);
    node->value[strlen++]=s[j++];
    if (strcmp(node->value, "[") == 0)
        node->type = OpenBracket;
    else if (strcmp(node->value, "]") == 0)
        node->type = CloseBracket;
    else if (strcmp(node->value, "(") == 0)
        node->type = OpenParen;
    else if (strcmp(node->value, ")") == 0)
        node->type = CloseParen;
    else if (strcmp(node->value, "{") == 0)
        node->type = OpenBrace;
    else if (strcmp(node->value, "}") == 0)
        node->type = CloseBrace;
    else if (strcmp(node->value, ".") == 0)
        node->type = Dot;
    else if (strcmp(node->value, ",") == 0)
        node->type = Comma;
    else if (strcmp(node->value, "?") == 0)
        node->type = Condition; 
    else if (strcmp(node->value, "-") == 0)
    {
        if (s[j] == '>')
        {
            node->value[strlen++] = s[j++];
            node->type = MemSelePointer;
        }
        else if (s[j] == '-')
        {
            node->value[strlen++] = s[j++];
            node->type = Decrement;
        }
        else if (s[j] == '=')
        {
            node->value[strlen++] = s[j++];
            node->type = SubAss;
        }
        else
            node->type = Sub;
    }
    else if (strcmp(node->value, "+") == 0)
    {
        if (s[j] == '+')
        {
            node->value[strlen++] = s[j++];
            node->type = Increment;
        }
        else if (s[j] == '=')
        {
            node->value[strlen++] = s[j++];
            node->type = AddAss;
        }
        else
            node->type = Add;
    }
    else if (strcmp(node->value, "&") == 0)
    {
        if (s[j]=='&')
        {
            node->value[strlen++] = s[j++];
            node->type = LogicalAND;
        }
        else if (s[j]=='=')
        {
            node->value[strlen++] = s[j++];
            node->type = BitANDAss;
        }
        else
            node->type = Address;
    }
    else if (strcmp(node->value, "*") == 0)
    {
        if (s[j] == '=')
        {
            node->value[strlen++] = s[j++];
            node->type = MulAss;
        }
        else
            node->type = Derefer_Mul;
    }
    else if (strcmp(node->value, "~") == 0)  
        node->type = BitNOT;  
    else if (strcmp(node->value, "!") == 0)
    {
        if (s[j]=='=')
        {
            node->value[strlen++] = s[j++];
            node->type = NotEqual;
        }
        else
            node->type = LogicalNOT;
    }
    else if (strcmp(node->value, "%") == 0)    
    {
        if (s[j] == '=')
        {
            node->value[strlen++] = s[j++];
            node->type = ModAss;
        }
        else if (s[j] == '>')
        {
            node->value[strlen++] = s[j++];
            node->type = CloseBrace;
        }
        else if (s[j]==':')
        {
            node->value[strlen++] = s[j++];
            if (s[j] == '%')
            {
                node->value[strlen++] = s[j++];
                if (s[j] == ':')
                {
                    node->value[strlen++] = s[j++];
                    node->type = DouPound;
                }
                else
                {
                    printf("非法\n");
                    free(node->value);
                    free(node);
                }
            }
            else
                node->type = Pound;
        }
        else
            node->type = Mod;
    }
    else if (strcmp(node->value, "<") == 0)
    {
        if (s[j] == '=')
        {
            node->value[strlen++] = s[j++];
            node->type = LessOrEqual;
        }
        else if (s[j] == '<')
        {
            node->value[strlen++] = s[j++];
            if (s[j] == '=')
                node->type = LShAss;
            else
                node->type = LShift;
        }
        else if (s[j] == ':')
        {
            node->value[strlen++] = s[j++];
            node->type = OpenBracket;
        }
        else if (s[j]=='%')
        {
            node->value[strlen++] = s[j++];
            node->type = OpenBrace;
        }
        else
            node->type = Less;
    }
    else if (strcmp(node->value, ">") == 0)
    {
        if (s[j] == '=')
        {
            node->value[strlen++] = s[j++];
            node->type = GreaterOrEqual;
        }
        else if (s[j]=='>')
        {
            node->value[strlen++] = s[j++];
            if (s[j] == '=')
                node->type = RShAss;
            else
                node->type = RShift;
        }
        else
            node->type = Greater;
    }
    else if (strcmp(node->value, "^") == 0)
    {
        if (s[j] == '=')
        {
            node->value[strlen++] = s[j++];
            node->type = BitXORAss;
        }
        else
            node->type = BitXOR;
    }
    else if (strcmp(node->value, "|") == 0)
    {
        if (s[j] == '=')
        {
            node->value[strlen++] = s[j++];
            node->type = BitORAss;
        }
        else if (s[j]=='|')
        {
            node->value[strlen++] = s[j++];
            node->type = LogicalOR;
        }
        else
            node->type = BitOR;
    }
    else if (strcmp(node->value, ":") == 0)
    {
        if (s[j] == '>')
        {
            node->value[strlen++] = s[j++];
            node->type = CloseBrace;
        }
        else
            node->type = Colon;
    }
    else if (strcmp(node->value, ";") == 0)
    node->type = Semicolon;
    else if (strcmp(node->value, "=") == 0)
    {
        if (s[j] == '=')
        {
            node->value[strlen++] = s[j++];
            node->type = Equal;
        }
        else
            node->type = Assignment;
    }
    else if (strcmp(node->value, "#") == 0)
    {
        if (s[j] == '#')
        {
            node->value[strlen++] = s[j++];
            node->type = DouPound;
        }
        else
            node->type = Pound;
    }
    node->prior = list;
    list->next = node;
    list = list->next;
    printf("%s %d\n", list->value, list->type);
    *i = j;
    return true;
}
bool opnum(char s[], int* i, int len, DoubleLinkList& list) {
    int j = *i, strlen = 0;
    int dot_tag = 0;
    DoubleListNode* node = NodeInit();
    char* Num_tem;
    Num_tem = (char*)malloc(sizeof(char) * num_maxlen);
    memset(Num_tem, 0, sizeof(char) * num_maxlen);
    for (; j < len; j++)
    {
        if (isdigit(s[j]))//是数字且没有小数点
            Num_tem[strlen++] = s[j];
        else if (s[j] == '.' && dot_tag == 0) //遇见第一个小数点
        {
            dot_tag = 1;
            Num_tem[strlen++] = s[j];
        }
        else if (s[j] == '.' && dot_tag >= 1)//小数点超过一个
        {
            dot_tag = 2;
            Num_tem[strlen++] = s[j];
        }
        else//既非数字又非小数点，退出循环
            break;
    }
    if (dot_tag <= 1) {
        if (dot_tag == 0)//没有小数点，为整数
        {
            strtol(Num_tem, NULL, 10);
            printf("errno: %d\n", errno);
            if (errno == 0)
            {
                node->type = Integer;
                node->value = (char*)malloc(sizeof(char) * strlen);
                strcpy(node->value, Num_tem);
            }
            else//非法
            {
                printf("该数字输入非法\n");
                // free(node->value);
                free(node);
                free(Num_tem);
                *i = j;
                return false;
            }
        }
        else if (dot_tag == 1)//有小数点,为浮点数
        {
            strtol(Num_tem, NULL, 10);
            printf("errno: %d\n", errno);
            if (errno == 0)
            {
                node->type = FloatNum;
                node->value = (char*)malloc(sizeof(char) * strlen);
                strcpy(node->value, Num_tem);
            }
            else {
                printf("该数字输入非法\n");
                // free(node->value);
                free(node);
                free(Num_tem);
                *i = j;
                return false;
            }
        }
    }
    else
    {
        printf("该数字输入非法\n");
            // free(node->value);
        free(node);
        free(Num_tem);
        *i = j;
        return false;
    }
    *i = j;
    node->prior = list;
    list->next = node;
    list = list->next;
    printf("%s %d\n", list->value, list->type);
    free(Num_tem);
    return true;
}
int main() {
    char sour[20000];
    memset(sour, 0, 20000);//初始化数组，方便存储源代码
    FILE* fp;
    fp = fopen("text_01.txt", "r");//打开文件
    if (feof(fp)||fp==NULL)
	{
        printf("文件打开失败");
        fclose(fp);
        exit(0);//文件打开失败或为空文件退出
    }
    fseek(fp, 0, SEEK_END);
    int file_len = ftell(fp);
    printf("文件字符数为 %d\n",file_len);   
    fseek(fp, 0, SEEK_SET);               //重新将指针指向文件首部
    fread(sour, sizeof(char), file_len, fp);//开始读取整个文件
    printf("%s\n", sour);//用于调试
    fclose(fp);//关闭文件
    int len=strlen(sour);
    DoubleLinkList list = NodeInit();
    DoubleLinkList head = list;
    int i = 0;
    while(i < len) {
        if (isletter(sour[i]) || sour[i] == '_')//本次接收字母，可能是关键字或标识符
            opstr(sour, &i, len, list);
        else if (isdigit(sour[i]))//本次接收为数字
            opnum(sour, &i, file_len, list);
        else if (isqmark(sour[i])) //本次接收了引号
            opqmark(sour, &i, len, list);
        else if (sour[i]=='/')//处理注释
            opcomment(sour, &i, file_len, list);
        else if (sour[i] == ' '||sour[i]=='\n')//本次空格或回车
            i++;
        else
            op_operator(sour, &i, file_len, list);
    }
}