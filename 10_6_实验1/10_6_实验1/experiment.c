#include"include.h";


void ListInitiate(LinkList* head) {
    *head = (SLNode*)malloc(sizeof(SLNode));
    if (*head == NULL) {
        printf("内存分配失败！\n");
        return;
    }
    (*head)->next = NULL;
}

int ListLength(SLNode* head) {
    SLNode* p = head->next;
    int num = 0;
    while (p != NULL) {
        num++;
        p = p->next;
    }
    return num;
}

int ListInsert(SLNode* head, int i, DataType a, DataType b) {
    SLNode* p, * q;
    p = head;
    int j = -1;
    while (p->next != NULL && j < i - 1) {
        p = p->next;
        j++;
    }
    if (j != i - 1) {
        printf("插入元素位置错误\n");
        return 0;
    }
    q = (SLNode*)malloc(sizeof(SLNode));
    if (q == NULL) {
        printf("内存分配失败！\n");
        return 0;
    }
    q->xishu = a;
    q->index = b;

    q->next = p->next;
    p->next = q;
    return 1;
}

int ListGet(SLNode* head, int i, DataType* x, DataType* y){
    SLNode* p;
    int j;
    p = head;
    j = -1;
    while (p->next != NULL && j < i) {
        p = p->next;
        j++;
    }
    if (j != i) {
        printf("取出的元素位置参数错误！\n");
        return 0;
    }
    *x = p->xishu; // 获取系数
    *y = p->index; // 获取指数
    return 1;
}

int ListDelete(SLNode* head, int i, DataType* x) {
    SLNode* p, * s;
    int j = -1;
    p = head;
    while (p->next != NULL && j < i - 1) {
        p = p->next;
        j++;
    }
    if (p->next == NULL) {
        printf("要删除的节点不存在！\n");
        return 0;
    }
    s = p->next;
    *x = s->xishu;

    p->next = s->next;
    free(s);
    return 1;
}

int CheckInputErrors(int* xishu_a, int* index_b) {
    int result = scanf("%d,%d", xishu_a, index_b);
    // 检查 scanf 的返回值，确保成功读取两个整数
    if (result != 2) {
        // 清除输入缓冲区
        while (getchar() != '\n'); // 清除输入行
        return 0; // 输入不合法
    }
    return 1; // 输入合法
}

int check_index(SLNode* head, int i, int b, DataType* num) { // 若指数相同则进行相加
    SLNode* p = head->next;
    int j = 0; // 从 0 开始，跳过头指针
    while (p != NULL) {
        if (p->index == b) { // 使用比较操作符
            ListDelete(head, j, num);//删掉之前存入指数相同的数
            return 1;
        }
        p = p->next;
        j++;
    }
    *num = 0;
    return 0;
}

// 排序链表（根据指数大小）
void SortList(SLNode* head) {
    if (head == NULL || head->next == NULL) return; //检测是否为空表

    SLNode* current, * index;
    DataType tempX, tempY;

    for (current = head->next; current != NULL; current = current->next) {
        for (index = current->next; index != NULL; index = index->next) {
            if (current->index > index->index) { // 根据指数进行比较（链表的冒泡排序）
                // 交换系数和指数
                tempX = current->xishu;
                tempY = current->index;
                current->xishu = index->xishu;
                current->index = index->index;
                index->xishu = tempX;
                index->index = tempY;
            }
        }
    }
}

SLNode* Twoformula(SLNode* head1, SLNode* head2, int operate) {
    SLNode* head3;
    ListInitiate(&head3); // 初始化新链表

    // 遍历第一个链表
    SLNode* t = head1->next; // 跳过头节点
    while (t != NULL) {
        ListInsert(head3, ListLength(head3), t->xishu, t->index); // 插入当前节点
        t = t->next; 
    }
    // 遍历第二个链表
    t = head2->next; // 跳过头节点
    while (t != NULL) {
        ListInsert(head3, ListLength(head3), (t->xishu) * operate, t->index); // 插入当前节点
        t = t->next; 
    }

    return head3; // 返回合并后的链表
}
void CombineLikeTerms(SLNode* head) {
    if (head == NULL || head->next == NULL)
        return; // 检查链表是否为空
    SLNode* current = head->next; // 从第一个有效节点开始
    while (current != NULL) {
        SLNode* run = current->next; // 检查当前节点后面的节点
        SLNode* pre = current; // 记录前一个节点

        while (run != NULL) {
            if (run->index == current->index) {
                // 如果找到相同指数的项，合并系数
                current->xishu += run->xishu;

                // 如果合并后系数为零，删除该节点
                if (current->xishu == 0) {
                    pre->next = run->next; // 跳过要删除的节点
                    free(run); 
                    run = pre->next; // 更新 run
                }
                else {
                    // 否则只需更新前驱指针
                    pre->next = run->next; // 将 pre 的 next 指向下一个
                    free(run); 
                    run = pre->next; // 更新 run
                }
            }
            else {
                // 如果指数不相同，继续检查下一个节点
                pre = run; // 更新前驱指针
                run = run->next; // 移动到下一个节点
            }
        }
        current = current->next; // 移动到下一个节点
    }
}
int IsZeroPolynomial(SLNode* head) {
    SLNode* p = head->next; // 跳过头节点

    while (p != NULL) {
        if (p->xishu != 0) { // 如果有任何非零系数
            return 0; // 不是零多项式
        }
        p = p->next;
    }

    return 1; // 所有系数都是零，返回是零多项式
}



int main() {
    SLNode* head1, * head2, * head3, * temp_head;
    int i, j = 0;
    int xishu_a, index_b; // 接收系数和指数进行检验
    DataType num = 0; // 接收指数相同时候的系数进行相加的参数
    ListInitiate(&head1);
    ListInitiate(&head2);
    printf("以（系数，指数）方式输入:     (注意 , 是英文)");
    while (j < 2) {
        printf("\n请输入第%d个多项式的数据:\n", j + 1);

        j++;
        if (j == 1)
            temp_head = head1;
        else
            temp_head = head2;
        for (i = 0; i < 5; i++) {
            printf("输入第 %d 项：", i + 1);
            if (!CheckInputErrors(&xishu_a, &index_b)) {
                printf("输入格式错误，请以 (系数, 指数) 的形式输入。\n");
                i--; // 重复当前输入
                continue; // 跳过本次循环
            }
            // 检查是否已有相同指数的节点
            if (check_index(temp_head, i, index_b, &num)) {
                //指数相等的多项式相加系数不为零则插入进去
                if (xishu_a + num != 0) {
                    ListInsert(temp_head, ListLength(temp_head), xishu_a + num, index_b); // 在链表末尾插入新节点
                }
            }
            else {
                // 如果没有相同的指数，则直接插入
                ListInsert(temp_head, ListLength(temp_head), xishu_a, index_b);
            }
        }
        SortList(temp_head);
    }
    printf("————————————————\n");
    printf("输入：-1.两式相减\n");
    printf("       1.两式相加\n");
    int operate;
    scanf("%d", &operate); //根据用户输入选择加法或减法

    head3 = Twoformula(head1, head2, operate); //新的多项式的指针
    SortList(head3); //按指数大小进行排序
    CombineLikeTerms(head3);

   
    if (IsZeroPolynomial(head3)) {
        printf("结果：0");
    }
    else {
        for (i = 0; i < ListLength(head3); i++) {
            DataType x, y;
            ListGet(head3, i, &x, &y);
            if (x != 0) {
                if (x > 0)
                    printf("%dx^%d", x, y); // 检查系数是否正确存入链表中
                else
                    printf("(%dx)^%d", x, y); //若是负数则加上括号
                if (i != ListLength(head3) - 1) printf("+");
            }
        }
    }
    return 0;
}