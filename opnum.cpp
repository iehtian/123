    *i = j;
    node->prior = list;
    list->next = node;
    list = list->next;
    printf("%s %d\n", list->value, list->type);
