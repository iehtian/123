#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define letter_form_len 37
#define mark_form_len 53
#define maxsize 20
char letter_form[letter_form_len][15] = { "auto","break","case","char","const","continue","default","do","double",
"else","enum","extern","float","for","goto","if","inline","int","long","register","restrict","return","short","signed",
"sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while","_Bool","_Complex","_Imaginary" };
char mark_form[mark_form_len][15] = { "[","]","(",")","{","}",".","->","++","--","&","*","+","-","~","!","/","%","<<",
">>","<<",">","<=",">=","==","!=","^","|","&&","||","?",":",";","...","=","*=","/=","%=","+=","-=","<<=",">>=","&=",
"^=","|=",",","#","##","<:",":>","<%","%>","%:" };
struct DoubleListNode
{
    int attribute=-1;//属性，即类别或编码、种别码，如100，101
    char* value;//单词本身
    struct DoubleListNode* prior; // 前驱指针
    struct DoubleListNode* next;  // 后驱指针
};
typedef DoubleListNode* DoubleLinkList;
DoubleLinkList ListInit()
{
	DoubleLinkList list = (DoubleLinkList)malloc(sizeof(DoubleListNode));
	list->prior = NULL;
	list->next = NULL;
	list->attribute = -1;
	return list;
}
bool isletter(char c) {
    if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z'))
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
bool opnum(char s[], int* i, int len, DoubleLinkList list) {
    int temlen = 0;
    int j = *i;
    char tem[maxsize];
    // memset(tem, 0, maxsize * sizeof(char));
    int flag = 0;//用于标记是整数或浮点数或非法
    for (; j < len; j++)
        {
            if (isdigit(s[j]))
            {
                tem[temlen++] = s[j];
            }
            else if (s[j]=='.')
            {
                tem[temlen++] = s[j];
                if (flag == 0)
                {
                    flag = 1;//这是第一个小数点，是合法的浮点数
                }
                else
                {
                    flag = 2;//有多个小数点，是非法的浮点数
                }
            }
            else
                break;
    }
        DoubleLinkList DLN = (DoubleLinkList)malloc(sizeof(DoubleListNode));
        // DLN->value=(char*)malloc(maxsize * sizeof(char));
        DLN->prior = list;
        list->next = DLN;
        DLN->next = NULL;
        if (flag==0&&atof(tem)<=2147483647&&atof(tem)>=-2147483648)//没有小说点，是整数。同时整数大小越界
        {
            DLN->attribute = 300;
        }
        else if (flag==1)///浮点型
        {
            DLN->attribute = 400;
        }
        else {//非法
            DLN->attribute = -1;
        }
        DLN->value = (char*)malloc(sizeof(char) * maxsize);
        memset(DLN->value, 0, maxsize);
        for (int l = 0; l < temlen; l++) {
            DLN->value[l] = tem[l];
        }
        *i = j;
        return true;
}
int find_form(char* c, char s[][15], int len) {
    for (int i = 0; i < len; i++) {
        if (strcmp(c, s[i]) == 0)
            return i;
    }
    return -1;
}
bool opstr(char s[], int* i, int len, DoubleLinkList list) {
    int j = *i;
    char* tem;
    int temlen = 0;
    tem=(char*)malloc(sizeof(char) * maxsize);
    memset(tem, 0, maxsize * sizeof(char));
    for (; j < len; j++)
    {
        if (isdigit(s[j])||isletter(s[j]))
        {
            tem[temlen++] = s[j];
        }
        else
            break;
    }
    DoubleLinkList DLN = (DoubleLinkList)malloc(sizeof(DoubleListNode));
    DLN->prior = list;
    list->next = DLN;
    DLN->next = NULL;
    int k = find_form(tem, letter_form, letter_form_len);
    if ( k != -1)
    {
        DLN->attribute = k + 100;
        DLN->value = (char*)malloc(sizeof(char) * maxsize);
        memset(DLN->value, 0, maxsize);
        for (int l = 0; l < temlen; l++) {
            DLN->value[l] = tem[l];
        }
    }
    else if (list->attribute < 200)//说明该字符串前是关键字，这个是标识符
    {
        DLN->attribute = 700;
        // DLN->value = tem;
        DLN->value = (char*)malloc(sizeof(char) * maxsize);
        memset(DLN->value, 0, maxsize);
        for (int l = 0; l < temlen; l++) {
            DLN->value[l] = tem[l];
        }
    }
    else
    {
        DLN->attribute = 600;
        DLN->value = tem;
    }
    *i = j;
    return true;
}
bool op_operator(char s[], int* i, int len, DoubleLinkList list) {
    int j = *i;
    int temlen = 0;
    char* tem;
    tem=(char*)malloc(sizeof(char) * maxsize);
    memset(tem, 0, maxsize * sizeof(char));
    for (; j < len; j++)
    {
        if ((!isdigit(s[j]))&&(!isletter(s[j]))&&s[j] != ' '&&s[j] != '\n')
        {
            tem[temlen++] = s[j];
        }
        else
            break;
    }
    DoubleLinkList DLN = (DoubleLinkList)malloc(sizeof(DoubleListNode));
    DLN->prior = list;
    list->next = DLN;
    DLN->next = NULL;
    int k = find_form(tem, mark_form, mark_form_len);
    if (k != -1)
    {
        DLN->attribute = k+200;
    }
    else
    {
        DLN->attribute = -1;
    }
    DLN->value = (char*)malloc(sizeof(char) * maxsize);
    memset(DLN->value, 0, maxsize);
    for (int l = 0; l < temlen; l++) {
        DLN->value[l] = tem[l];
    }
    *i = j;
    return true;
}
bool opqmark(char s[], int* i, int len, DoubleLinkList list) {
    int j = *i;
    int temlen = 0;
    char* tem;
    memset(tem, 0, maxsize * sizeof(char));
    if (s[j] == '\'')
    {
        DoubleLinkList DLN = (DoubleLinkList)malloc(sizeof(DoubleListNode));
        DLN->prior = list;
        list->next = DLN;
        DLN->next = NULL;
        DLN->attribute = 800;
        DLN->value = "\'";
        list = list->next;
        j++;
        for (; j < len; j++)
        {
            if (s[j] != '\'')
            {
                tem[temlen++] = s[j];
                // printf("%s",tem);
            }
            else if (s[j - 1] == '\\' && s[j - 2] == '\\')//注意，j-2可能越界，之后修改根据需要增加判断
            {
                break;
            }
            else if (s[j - 1] == '\\')
            {
                continue;
            }
        }
        if (temlen != 0)
            {
                DLN = (DoubleLinkList)malloc(sizeof(DoubleListNode));
                DLN->prior = list;
                list->next = DLN;
                DLN->next = NULL;
                DLN->attribute = 400;
                DLN->value = (char*)malloc(sizeof(char) * maxsize);
                memset(DLN->value, 0, maxsize);
                for (int l = 0; l < temlen; l++) {
                    DLN->value[l] = tem[l];
                }
                list=list->next;
        }
        DLN = (DoubleLinkList)malloc(sizeof(DoubleListNode));
        DLN->prior = list;
        list->next = DLN;
        DLN->next = NULL;
        DLN->attribute = 800;
        DLN->value = "\'";
    }
    else
    {
        DoubleLinkList DLN = (DoubleLinkList)malloc(sizeof(DoubleListNode));
        DLN->prior = list;
        list->next = DLN;
        DLN->next = NULL;
        DLN->attribute = 900;
        DLN->value = "\"";
        list = list->next;
        j++;
        for (; j < len; j++)
        {
            if (s[j] != '\"')
            {
                tem[temlen++] = s[j];
            }
            else if (s[j - 1] == '\\' && s[j - 2] == '\\')//注意，j-2可能越界，之后修改根据需要增加判断
            {
                break;
            }
            else if (s[j - 1] == '\\')
            {
                continue;
            }
            else
                break;
        }
        if (temlen != 0)
            {
                DLN = (DoubleLinkList)malloc(sizeof(DoubleListNode));
                DLN->prior = list;
                list->next = DLN;
                DLN->next = NULL;
                DLN->attribute = 500;
                DLN->value = (char*)malloc(sizeof(char) * maxsize);
                memset(DLN->value, 0, maxsize);
                for (int l = 0; l < temlen; l++) {
                    DLN->value[l] = tem[l];
                }
                list=list->next;
        }
        DLN = (DoubleLinkList)malloc(sizeof(DoubleListNode));
        DLN->prior = list;
        list->next = DLN;
        DLN->next = NULL;
        DLN->attribute = 900;
        DLN->value = "\"";
    }
    j++;
    *i = j;
    return true;
}
bool opcomment(char s[], int* i, int len, DoubleLinkList list) {
    int j = *i;
    if (s[j + 1] == '/')//注意，j+1可能越界
    {
        while (j < len && s[j] != '\n' && s[j] != '\0')
        {
            j++;
        }
    }
    else if (s[j+1]=='*') 
    {
        for (; j < len; j++)
        {
            if (s[j]=='/'&&s[j-1]=='*')
                break;
        }
    }
    else {
        DoubleLinkList DLN = (DoubleLinkList)malloc(sizeof(DoubleListNode));
        DLN->prior = list;
        list->next = DLN;
        DLN->next = NULL;
        DLN->attribute = 217;
        DLN->value = "/";
    }
    j++;
    *i = j;
    return true;
}
int main() {
    char sour[1024];
    memset(sour, 0, 1024);//初始化数组，方便存储源代码
    FILE* fp;
    fp = fopen("text.txt", "r");//打开文件
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
    DoubleLinkList list = ListInit();
    DoubleLinkList head = list;
    for (int i = 0; i < file_len; )
    {
        if (isletter(sour[i]))
        {
            opstr(sour, &i, file_len, list);
            list = list->next;
            // printf("%s\n", list->value);
        }
        else if (isdigit(sour[i])){
            opnum(sour, &i, file_len, list);
            list = list->next;
            // printf("%s\n", list->value);
        }
        else if (isqmark(sour[i])) {
            opqmark(sour, &i, file_len, list);
            while (list->next!=NULL)
            {
                list = list->next;
            }
            // printf("%s\n", list->value);
        }
        else if (sour[i]=='/')
        {
            opcomment(sour, &i, file_len, list);
            // list = list->next;
            // printf("%s\n",list->value);
        }
        else if (sour[i] == ' '||sour[i]=='\n')
            i++;
        else
        {
            op_operator(sour, &i, file_len, list);
            list = list->next;
            // printf("%s\n", list->value);
        }
    }
    list = head->next;
    while (list->next != NULL)
    {
        printf("%s %d\n", list->value, list->attribute);
        list = list->next;
    }
    printf("%s %d\n", list->value,list->attribute);
}
