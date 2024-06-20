#include"lexer.h"
#include"bcc_log.h"

#define BCC_DEBUG_LEVEL BCC_DEBUG_LEVEL_ALL

const char* tok_str[150] = {
	"Auto", "Break", "Case", "Char", "Const", "Continue", "Default", "Do", "Double", "Else", "Enum", "Extern", "Float",
	"For", "Goto", "If", "Inline", "Int", "Long", "Register", "Restrict", "Return", "Short", "Signed", "Sizeof",
	"Static", "Struct", "Switch", "Typedef", "Union", "Unsigned", "Void", "Volatile", "While", "Bool", "Complex",
	"Imaginary", "[", "]", "(", ")", "{", "}", ".", "->", "++", "--", "&", "*", "+", "-", "~", "!", "/", "%",
	"<<", ">>", "<", ">", "<=", ">=", "==", "!=", "^", "|", "&&", "||", "?", ":", ";", "...", "=", "=", "/=",
	"%=", "+=", "-=", "<<=", ">>=", "&=", "^=", "|=", ",","#", "##", "Id", "Character", "String", "Integer", "FloatNum",
	"PPDefine", "PPInclude", "PPUndef", "PPIfdef", "PPIfndef", "PPElif", "PPEndif", "PPLine", "PPError", "PPPragma", "PPIf", "PPElse"
};

bool isletter(char c) {
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return 1;
	else
		return 0;
}
bool isdigits(char c) {
	if (c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}
bool isqmark(char c) {
	if (c == '\'' || c == '"')
		return 1;
	else
		return 0;
}
bool is_hex_char(char c) {
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
		return 1;
	else
		return 0;
}


DoubleLinkList NodeInit()//初始化一个节点
{
	DoubleLinkList Node = (DoubleLinkList)malloc(sizeof(DoubleListNode));
	Node->value = NULL;
	Node->prior = NULL;
	Node->next = NULL;
	return Node;
}


bool oppre(char s[], int* i, int len, DoubleLinkList *list,long int count_line) {//检查是否为关键字或标识符
	int j = *i, str_len = 0;
	DoubleLinkList node = NodeInit();
	char* tem;
	tem = (char*)malloc(sizeof(char) * id_maxlen);
	memset(tem, 0, sizeof(char) * id_maxlen);
	while (j < len) {
		if (isletter(s[j])) {
			tem[str_len++] = s[j++];
		}
		else {
			break;
		}
	}
	if (str_len == 2) {
		Marchstr(tem, "if", If);
	else {
		bcc_log_error("lex", "%d",count_line);
		free(tem);
		*i = j;
		return 0;
	}
	}
	else if (str_len == 4) {
		Marchstr(tem, "else", Else);
		Marchstr(tem, "line", PPLine);
		Marchstr(tem, "elif", PPElif);
	else {
		bcc_log_error("lex", "第%ld行 预处理出错\n", count_line);
		//printf("第%ld行 预处理出错\n", count_line);
		free(tem);
		*i = j;
		return 0;
	}
	}
	else if (str_len == 5) {
		Marchstr(tem, "undef", PPUndef);
	else Marchstr(tem, "ifdef", PPIfdef);
		else Marchstr(tem, "endif", PPEndif);
		else Marchstr(tem, "error", PPError);
		else {
			bcc_log_error("lex", "第%ld行 预处理出错\n", count_line);
			//printf("第%ld行 预处理出错\n", count_line);
			free(tem);
			*i = j;
			return 0;
		}
	}
	else if (str_len == 6) {
		Marchstr(tem, "ifndef", PPIfndef);
	else Marchstr(tem, "pragma", PPPragma);
		else Marchstr(tem, "define", PPDefine);
		else {
			bcc_log_error("lex", "第%ld行 预处理出错\n", count_line);
			//printf("第%ld行 预处理出错\n", count_line);
			free(tem);
			*i = j;
			return 0;
		}
	}
	else if (str_len == 7) {
		Marchstr(tem, "include", PPInclude);
		else {
			bcc_log_error("lex", "第%ld行 预处理出错\n", count_line);
			free(tem);
			*i = j;
			return 0;
		}
	}
	node->prior = *list;
	(*list)->next = node;
	*list = (*list)->next;
	bcc_log_info("lex", "第%ld行：%s %d\n", count_line, (*list)->value, (*list)->type);
	free(tem);
	*i = j;
	//free_assignment(i, j, tem, node);
	return 1;
}
bool opstr(char s[], int* i, int len, DoubleLinkList *list,long int count_line) {//检查是否为关键字或标识符
	int j = *i, str_len = 0;
	DoubleLinkList node = NodeInit();
	char* tem;
	tem = (char*)malloc(sizeof(char) * id_maxlen);
	memset(tem, 0, sizeof(char) * id_maxlen);
	while (j < len) {
		if (isdigits(s[j]) || isletter(s[j]) || s[j] == '_') {
			tem[str_len++] = s[j++];
		}
		else {
			break;
		}
	}
	if (str_len == 2) {
		Marchstr(tem, "do", Do);
	else Marchstr(tem, "if", If);
		else {
			node->type = Id;//这个字母开头的一串字符不是关键字，那么必为标识符
		}
	}
	else if (str_len == 3) {
		Marchstr(tem, "for", For);
		else Marchstr(tem, "int", Int);
		else {
			node->type = Id;//这个字母开头的一串字符不是关键字，那么必为标识符
		}
	}
	else if (str_len == 4) {
		Marchstr(tem, "auto", Auto);
		else Marchstr(tem, "case", Case);
		else Marchstr(tem, "char", Char);
		else Marchstr(tem, "else", Else);
		else Marchstr(tem, "enum", Enum);
		else Marchstr(tem, "goto", Goto);
		else Marchstr(tem, "long", Long);
		else Marchstr(tem, "void", Void);
		else {
			node->type = Id;//这个字母开头的一串字符不是关键字，那么必为标识符
		}
	}
	else if (str_len == 5) {
		Marchstr(tem, "break", Break);
		else Marchstr(tem, "const", Const);
		else Marchstr(tem, "float", Float);
		else Marchstr(tem, "short", Short);
		else Marchstr(tem, "union", Union);
		else Marchstr(tem, "while", While);
		else Marchstr(tem, "bool", Bool);
		else {
			node->type = Id;//这个字母开头的一串字符不是关键字，那么必为标识符
		}
	}
	else if (str_len == 6) {
		Marchstr(tem, "double", Double);
		else Marchstr(tem, "extern", Extern);
		else Marchstr(tem, "inline", Inline);
		else Marchstr(tem, "signed", Signed);
		else Marchstr(tem, "sizeof", Sizeof);
		else Marchstr(tem, "static", Static);
		else Marchstr(tem, "struct", Struct);
		else Marchstr(tem, "switch", Switch);
		else Marchstr(tem, "return", Return);
		else {
			node->type = Id;//这个字母开头的一串字符不是关键字，那么必为标识符
		}
	}
	else if (str_len == 7) {
		Marchstr(tem, "default", Default);
		else Marchstr(tem, "typedef", Typedef);
		else {
		node->type = Id;//这个字母开头的一串字符不是关键字，那么必为标识符
		}
	}
	else if (str_len == 8) {
		Marchstr(tem, "continue", Continue);
		else Marchstr(tem, "register", Register);
		else Marchstr(tem, "restrict", Restrict);
		else Marchstr(tem, "unsigned", Unsigned);
		else Marchstr(tem, "volatile", Volatile);
		else Marchstr(tem, "_Complex", Complex);
		else {
			node->type = Id;//这个字母开头的一串字符不是关键字，那么必为标识符
		}
	}
	else Marchstr(tem, "_Imaginary", Imaginary);
	else {
		node->type = Id;//这个字母开头的一串字符不是关键字，那么必为标识符
	}
	if (node->type == Id){//标识符需要存储
		node->value = (char*)malloc(sizeof(char) * str_len + 1);
		memset(node->value, 0, sizeof(char) * str_len + 1);
		strcpy_s(node->value, str_len + 1, tem);
		free(tem);
	}
	node->prior = *list;
	(*list)->next = node;
	*list = (*list)->next;
	bcc_log_info("lex", "第%ld行：%s %d\n", count_line, (*list)->value, (*list)->type);
	*i = j;
	return 1;
}
bool opqmark(char s[], int* i, int len, DoubleLinkList* list,long int *cl) {
	int j = *i, count_line = *cl, str_len = 0, tag = 0;
	DoubleLinkList node = NodeInit();
	char* tem;
	tem = (char*)malloc(sizeof(char) * str_maxlen);
	memset(tem, 0, sizeof(char) * str_maxlen);
	if (s[j] == '\"')
		tag = 1;
	j++;
	while (j < len) {
		if (s[j] == '\\'){//遇到了转义字符，那么该字符和下个字符不会是结束标志
			j++;
			if (s[j] == '\\') {
				tem[str_len++] = '\\';
				j++;
			}
			else if (s[j] == 'n') {
				tem[str_len++] = '\n';
				count_line++;
				j++;
			}
			else if (s[j] == 't') {
				tem[str_len++] = '\t';
				j++;
			}
			else if (s[j] == 'r') {
				tem[str_len++] = '\r';
				j++;
			}
			else if (s[j] == 'b') {
				tem[str_len++] = '\b';
				j++;
			}
			else if (s[j] == 'f') {
				tem[str_len++] = '\f';
				j++;
			}
			else if (s[j] == 'v') {
				tem[str_len++] = '\v';
				j++;
			}
			else if (s[j] == 'a') {
				tem[str_len++] = '\a';
				j++;
			}
			else if (s[j] == '\'') {
				tem[str_len++] = '\'';
				j++;
			}
			else if (s[j] == '\"') {
				tem[str_len++] = '\"';
				j++;
			}
			// j++;
			else if (isdigits(s[j])){//是数字，转义8进制数
				char Base_8[3];
				int k = 0;
				memset(Base_8, 0, sizeof(Base_8));
				while (isdigits(s[j]) && k < 3) {
					if (s[j] > '7' || s[j] < '0')//非法，退出
						break;
					Base_8[k++] = s[j++];
				}
				int decimal = 0, count = 0;
				for (; count < k; count++) {
					decimal = decimal * 8 + (Base_8[count] - '0');
				}
				if (decimal > 255) {
					bcc_log_error("lex", "第%ld行： 八进制转义后值大于255，非法输入\n", count_line);
					free(tem);
					free(node);
					break;
				}
				else if (decimal == 0) {
					continue;
				}
				tem[str_len++] = decimal;
			}
			else if (s[j] == 'x' || s[j] == 'X'){//转义16进制数
				char Base_16[2];
				int k = 0;
				j++;
				memset(Base_16, 0, sizeof(Base_16));
				while (k < 2) {
					if (!is_hex_char(s[j]))//不是16进制数
						break;
					Base_16[k++] = s[j++];
				}
				if (k < 1){//说明没能识别到两个16进制数
					bcc_log_error("lex", "第%ld行： 该输入非法，应输入两个16进制数\n", count_line);
					free(tem);
					free(node);
					break;
				}
				else {
					int decimal = 0, count = 0;
					for (; count < k; count++) {
						if (Base_16[count] >= '0' && Base_16[count] <= '9') {
							decimal = decimal * 16 + (Base_16[count] - '0');
						}
						else if (Base_16[count] >= 'a' && Base_16[count] <= 'f') {
							decimal = decimal * 16 + (Base_16[count] - 'a');
						}
						else {
							decimal = decimal * 16 + (Base_16[count] - 'A');
						}
					}
					tem[str_len++] = decimal;
				}
			}
		}
		else if (s[j] == '\'' || s[j] == '\"')
			//遇到结束标志
			break;
		else
			tem[str_len++] = s[j++];
	}
	if (tag == 0){//处理字符
		if (str_len != 1) {
			bcc_log_error("lex", "第%ld行： 单字符有且只能有一个字符，该输入非法\n", count_line);
			j++;
			free(tem);
			*i = j;
			return 0;
		}
		else {
			node->value = (char*)malloc(sizeof(char) * 2);
			memset(node->value, 0, sizeof(char) * 2);
			node->value[0] = tem[0];
			free(tem);
			node->type = Character;
		}
	}
	else {
		node->value = (char*)malloc(sizeof(char) * str_len + 1);
		memset(node->value, 0, sizeof(char) * str_len + 1);
		strcpy_s(node->value, str_len + 1, tem);
		free(tem);
		node->type = String;
	}
	node->prior = *list;
	(*list)->next = node;
	*list = (*list)->next;
	bcc_log_info("lex", "第%ld行：%s %d\n", count_line, (*list)->value, (*list)->type);
	*i = ++j;
	*cl = count_line;
	return 1;
}
bool opcomment(char s[], int* i, int len, DoubleLinkList* list,long int *cl) {
	int j = *i,count_line = *cl;
	if (s[j + 1] == '/')//注意，j+1可能越界
	{
		while (j < len) {
			if (s[j] == '\n' || s[j] == '\0') {
				count_line++;
				*cl = count_line;
				*i = ++j;
				return 1;
			}
			j++;
		}
	}
	else if (s[j + 1] == '*') {
		while (j < len) {
			if (s[j] == '\n') {
				count_line++;
			}
			if (s[j] == '*' && s[j + 1] == '/') {
				*i = j + 2;
				return 1;
			}
			j++;
		}
	}
	else {//不为注释，那么考虑为作为/或/=
		DoubleLinkList node = NodeInit();
		node->value = (char*)malloc(sizeof(char) * 3);
		memset(node->value, 0, sizeof(char) * 3);
		node->value[0] = '/';
		if (s[j + 1] == '=') {
			node->type = DivAss;
			node->value[1] = '=';
			j++;
		}
		else
			node->type = Division;
		node->prior = *list;
		(*list)->next = node;
		*list = (*list)->next;
		bcc_log_info("lex", "第%ld行：%s %d\n", count_line, (*list)->value, (*list)->type);
	}
	j++;
	*i = j;
	*cl = count_line;
	return 1;
}
bool op_operator(char s[], int* i, int len, DoubleLinkList* list,long int count_line) {
	int j = *i, str_len = 0;
	DoubleListNode* node = NodeInit();
	/*char tem[5];
	memset(tem, 0, sizeof(tem));
	tem[str_len++] = s[j];*/
	Matchar(s[j], '[', OpenBracket)
	else Matchar(s[j], ']', CloseBracket)
	else Matchar(s[j], '(', OpenParen)
	else Matchar(s[j], ')', CloseParen)
	else Matchar(s[j], '{', OpenBrace)
	else Matchar(s[j], '}', CloseBrace)
	else Matchar(s[j], '.', Dot)
	else Matchar(s[j], ',', Comma)
	else Matchar(s[j], '?', Condition)
	else Matchar(s[j], '~', BitNOT)
	else Matchar(s[j], ';', Semicolon)
	if (s[j] == '-') {
		j++;
		Matchar(s[j], '>', MemSelePointer)
		Matchar(s[j], '-', Decrement)
		Matchar(s[j], '=', SubAss)
		else {
			node->type = Sub;
		}
	}
	else if (s[j] == '+') {
		j++;
		Matchar(s[j], '+', Increment)
		else Matchar(s[j], '=', AddAss)
		else {
			node->type = Add;
		}
	}
	else if (s[j] == '&') {
		j++;
		Matchar(s[j], '&', LogicalAND)
		else Matchar(s[j], '=', BitANDAss)
		else {
			node->type = Address;
		}
	}
	else if (s[j] == '*') {
		j++;
		Matchar(s[j], '=', MulAss)
		else {
			node->type = Derefer_Mul;
		}
	}
	if (s[j] == '!') {
		j++;
		Matchar(s[j], '=', NotEqual)
		else {
			node->type = LogicalNOT;
		}
	}
	if (s[j] == '%') {
		j++;
		Matchar(s[j], '=', ModAss);
		Matchar(s[j], '>', CloseBrace);
		if (s[j] == ':') {
			j++;
			if (s[j] == '%') {
				j++;
				if (s[j] == ':') {
					node->type = DouPound;
				}
				else {
					bcc_log_error("lex", "第%ld行： 非法符号\n", count_line);
					// free(tem);
					//free(node);   
				}
			}
			else {
				node->type = Pound;
			}
		}
		else {
			node->type = Mod;
		}
	}
	if (s[j] == '<') {
		j++;
		Matchar(s[j], '=', LessOrEqual)
		else if (s[j] == '<') {
			j++;
			Matchar(s[j], '=', LShAss)
			else {
				node->type = LShift;
			}
		}
		else Matchar(s[j], ':', OpenBracket)
		else Matchar(s[j], '%', OpenBrace)
		else if((*list)->type==PPInclude){//说明接下来会是字符串
			node->type = Less; 
			node->prior = *list; 
			(*list)->next = node; 
			* list = (*list)->next; 
			bcc_log_info("lex", "第%ld行：%s %d\n", count_line, (*list)->value, (*list)->type);
			//DoubleListNode* node = NodeInit();
			char tem[str_maxlen];
			memset(tem, 0, sizeof(tem));
			while (s[j] != '>') {
				tem[str_len++] = s[j++];
			}

			node= NodeInit();
			node->value = (char*)malloc(sizeof(char) * str_len + 1);
			memset(node->value, 0, sizeof(char) * str_len + 1);
			strcpy_s(node->value, str_len + 1, tem);
			node->type = String;
			node->prior = *list;
			(*list)->next = node;
			*list = (*list)->next;
			bcc_log_info("lex", "第%ld行：%s %d\n", count_line, (*list)->value, (*list)->type);

			j++;
			node= NodeInit();
			node->type = Greater;
			node->prior = *list;
			(*list)->next = node;
			*list = (*list)->next;
			bcc_log_info("lex", "第%ld行：%s %d\n", count_line, (*list)->value, (*list)->type);

			* i = j; 
			return 1;
		}
		else {
			node->type = Less;
		}
	}
	if (s[j] == '>') {
		j++;
		Matchar(s[j], '=', GreaterOrEqual)
		else if (s[j] == '>') {
			j++;
			Matchar(s[j], '=', RShAss)
			else {
				
				node->type = RShift;
			}
		}
		else {
			node->type = Greater;
		}
	}
	if (s[j] == '^') {
		j++;
		Matchar(s[j], '=', BitXORAss)
		else {
			node->type = BitXOR;
		}
	}
	if (s[j] == '|') {
		j++;
		Matchar(s[j], '=', BitORAss)
		else Matchar(s[j], '|', LogicalOR)
		else {
			node->type = BitOR;
		}
	}
	if (s[j] == ':') {
		j++;
		Matchar(s[j], '>', CloseBrace)
		else {
			node->type = Colon;
		}	
	}
	else if (s[j] == '=') {
		j++;
		Matchar(s[j], '=', Equal)
		else {
			node->type = Assignment;
		}
	}
	else if (s[j] == '#') {
		j++;
		if (s[j] == '#') {
			node->type = DouPound;
	}
		else {
			node->type = Pound;
			free(node);
			oppre(s, &j, len, list, count_line);
			*i = j;
			return 1;
		}
	}
	node->prior = *list;
	(*list)->next = node;
	*list = (*list)->next;
	// free(tem);
	bcc_log_info("lex", "第%ld行：%s %d\n", count_line, (*list)->value, (*list)->type);
	*i = j;
	return 1;
}
bool opnum(char s[], int* i, int len, DoubleLinkList* list, long int count_line) {
	int j = *i, str_len = 0;
	int dot_tag = 0, base_tag = 0;
	DoubleListNode* node = NodeInit();
	char* Num_tem;
	Num_tem = (char*)malloc(sizeof(char) * num_maxlen);
	memset(Num_tem, 0, sizeof(char) * num_maxlen);
	if (s[j] == '0'){//非10进制
		j++;
		if (s[j] == 'x') {
			base_tag = 1;
			j++;
		}
		else if (s[j] <= '7' && s[j] >= '0') {
			base_tag = 2;
		}
		else{//单个0
			base_tag = 3;
			Num_tem[str_len++] = '0';
		}
	}
	for (; j < len; j++) {
		if (is_hex_char(s[j]) || s[j] == 'l' || s[j] == 'L'){//是数字或数字后缀
			Num_tem[str_len++] = s[j];
		}
		else if (s[j] == '.' && dot_tag == 0) {//遇见第一个小数点
			dot_tag = 1;
			Num_tem[str_len++] = s[j];
		}
		else if (s[j] == '.' && dot_tag >= 1){//小数点超过一个
			dot_tag = 2;
			Num_tem[str_len++] = s[j];
		}
		else//既非数字又非小数点，退出循环
			break;
	}
	if (dot_tag <= 1) {//合法的数字
		if (dot_tag == 0){//没有小数点，为整数
			if (base_tag == 3) {
				node->type = Integer;
				node->value = (char*)malloc(sizeof(char) * 2);
				memset(node->value, 0, sizeof(char) * 2);
				node->value[0] = '0';
				*i = j;
			}
			else if (base_tag == 1)//16进制数
			{
				long long ll = strtol(Num_tem, NULL, 16);
				if (errno != 0)//转换失败，该数不合法
				{
					bcc_log_error("lex", "第%ld行： 不合法的数\n", count_line);
					free(Num_tem);
					*i = j;
					return 0;
				}
				else {
					node->type = Integer;
					itoa(ll, Num_tem, 10);
					str_len = strlen(Num_tem);
					node->value = (char*)malloc(sizeof(char) * str_len + 1);
					memset(node->value, 0, sizeof(char) * str_len + 1);
					strcpy_s(node->value, str_len + 1, Num_tem);
					// free(Num_tem);
				}
			}
			else if (base_tag == 2)//8进制
			{
				long long ll = strtol(Num_tem, NULL, 8);
				if (errno != 0)//转换失败，该数不合法
				{
					bcc_log_error("lex", "第%ld行： 不合法的数\n", count_line);
					free(Num_tem);
					*i = j;
					return 0;
				}
				else {
					node->type = Integer;
					itoa(ll, Num_tem, 10);
					str_len = strlen(Num_tem);
					node->value = (char*)malloc(sizeof(char) * str_len + 1);
					memset(node->value, 0, sizeof(char) * str_len + 1);
					strcpy_s(node->value, str_len + 1, Num_tem);
				}
			}
			else//10进制数
			{
				node->type = Integer;
				node->value = (char*)malloc(sizeof(char) * str_len + 1);
				memset(node->value, 0, sizeof(char) * str_len + 1);
				strcpy_s(node->value, str_len + 1, Num_tem);
			}
		}
		else if (dot_tag == 1)//有小数点,为浮点数
		{
			strtol(Num_tem, NULL, 10);
			// printf("errno: %d\n", errno);
			if (errno == 0) {
				node->type = FloatNum;
				node->value = (char*)malloc(sizeof(char) * str_len + 1);
				memset(node->value, 0, sizeof(char) * str_len + 1);
				strcpy_s(node->value, str_len + 1, Num_tem);
			}
			else {
				bcc_log_error("lex", "第%ld行： 不合法的数\n", count_line);
				free(Num_tem);
				*i == j;
				return 0;
			}
		}
	}
	else {
		bcc_log_error("lex", "第%ld行： 不合法的数\n", count_line);
		free(Num_tem);
		*i == j;
		return 0;
	}
	*i = j;
	node->prior = *list;
	(*list)->next = node;
	*list = (*list)->next;
	bcc_log_info("lex", "第%ld行：%s %d\n", count_line, (*list)->value, (*list)->type);
	//printf("第%ld行： %s %d\n", count_line, list->value, list->type);
	free(Num_tem);
	return 1;
}

//int main() {
//	char sour[20000];
//	memset(sour, 0, 20000);//初始化数组，方便存储源代码
//	FILE* fp;
//	errno_t err = fopen_s(&fp, "parser_express.txt", "r");
//	//fp = fopen("text_01.txt", "r");//打开文件
//	if (err != 0 || fp == NULL) {
//		printf("文件打开失败\n");
//		fclose(fp);
//		return 0;
//	}
//	else {
//		printf("文件打开成功\n");
//	}
//	fseek(fp, 0, SEEK_END);
//	int file_len = ftell(fp);
//	printf("文件字符数为 %d\n", file_len);
//	fseek(fp, 0, SEEK_SET);               //重新将指针指向文件首部
//	fread(sour, sizeof(char), file_len, fp);//开始读取整个文件
//	printf("%s\n", sour);//用于调试
//	fclose(fp);//关闭文件
//	int len = strlen(sour);
//	DoubleLinkList list = NodeInit();
//	DoubleLinkList DLL_head = list;
//	int i = 0;
//	long int count_line = 1;
//	while (i < len) {
//		if (isletter(sour[i]) || sour[i] == '_')//本次接收字母，可能是关键字或标识符
//		{
//			opstr(sour, &i, len, &list, count_line);
//		}
//		else if (isdigits(sour[i]))//本次接收为数字
//		{
//			opnum(sour, &i, len, &list, count_line);
//		}
//		else if (isqmark(sour[i])) //本次接收了引号
//		{
//			opqmark(sour, &i, len, &list, &count_line);
//		}
//		else if (sour[i] == '/')//处理注释
//		{
//			opcomment(sour, &i, len, &list, &count_line);
//		}
//		else if (sour[i] == ' ')//本次空格
//		{
//			i++;
//		}
//		else if (sour[i] == '\n')//回车，行数增加
//		{
//			count_line++;
//			i++;
//		}
//		else//处理符号
//		{
//			op_operator(sour, &i, file_len, &list, count_line);
//		}
//	}
//	/*截至于此，词法分析部分结束，开始进行语法分析*/