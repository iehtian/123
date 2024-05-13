bool opnum(char s[], int* i, int len, DoubleLinkList& list) {
    int j = *i, strlen = 0;
    int dot_tag = 0,E_tag = 0;
    DoubleListNode* node = NodeInit();
    char* beforeE, *afterE;
    beforeE = (char*)malloc(sizeof(char) * num_maxlen);
    afterE = (char*)malloc(sizeof(char) * num_maxlen);
    for (; j < len; j++)
    {
        if (isdigit(s[j])&&E_tag==0)//是数字且没有小数点
            beforeE[strlen++] = s[j];
        else if (isdigit(s[j]) && E_tag == 1)
            afterE[strlen++] =s[j];
        else if (isdigit(s[j]) && E_tag == 1)//是数字且有小数点
            afterdot[strlen++] = s[j];
        else if (s[j] == '.' && dot_tag==0) //遇见第一个小数点
            tag = 1;
        else if (s[j]=='.' && dot_tag >=1)//小数点超过一个
            flag = 2;
        else if (s[j] == 'E' || s[j] == 'e')
            E_tag = 1;
        else//既非数字又非小数点，退出循环
            break;
    }
    if (dot_tag > 1)
    else if (dot_tag == 0 && E_tag == 0)//没有小数点和E，为普通整数
    {
        strtol(s, NULL, 10);
        if (errno == 0)
        {
            node->type = Integer;
            node.value = (char*)malloc(sizeof(char) * strlen);
            strcpy(node->value, beforeE);
        }
        else//非法
        {
            printf("非法\n");
            // free(node->value);
            free(node);
            return false;
        }
    }
    else if (dot_tag==1&&E_tag==0)//有小数点，没有E，为普通浮点数
    {
        strtol(s, NULL, 10);
        if (erron==0)
        {
            node->type = FloatNum;
            node.value = (char*)malloc(sizeof(char) * strlen);
            strcpy(node->value, beforeE);
        }
        else {
            printf("非法\n");
            // free(node->value);
            free(node);
            return false;
        }
    }
    *i = j;
    node->prior = list;
    list->next = node;
    list = list->next;
    printf("%s %d\n", list->value, list->type);
    return true;
}