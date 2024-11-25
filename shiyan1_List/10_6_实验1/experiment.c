#include"include.h";


void ListInitiate(LinkList* head) {
    *head = (SLNode*)malloc(sizeof(SLNode));
    if (*head == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
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
        printf("����Ԫ��λ�ô���\n");
        return 0;
    }
    q = (SLNode*)malloc(sizeof(SLNode));
    if (q == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
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
        printf("ȡ����Ԫ��λ�ò�������\n");
        return 0;
    }
    *x = p->xishu; // ��ȡϵ��
    *y = p->index; // ��ȡָ��
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
        printf("Ҫɾ���Ľڵ㲻���ڣ�\n");
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
    // ��� scanf �ķ���ֵ��ȷ���ɹ���ȡ��������
    if (result != 2) {
        // ������뻺����
        while (getchar() != '\n'); // ���������
        return 0; // ���벻�Ϸ�
    }
    return 1; // ����Ϸ�
}

int check_index(SLNode* head, int i, int b, DataType* num) { // ��ָ����ͬ��������
    SLNode* p = head->next;
    int j = 0; // �� 0 ��ʼ������ͷָ��
    while (p != NULL) {
        if (p->index == b) { // ʹ�ñȽϲ�����
            ListDelete(head, j, num);//ɾ��֮ǰ����ָ����ͬ����
            return 1;
        }
        p = p->next;
        j++;
    }
    *num = 0;
    return 0;
}

// ������������ָ����С��
void SortList(SLNode* head) {
    if (head == NULL || head->next == NULL) return; //����Ƿ�Ϊ�ձ�

    SLNode* current, * index;
    DataType tempX, tempY;

    for (current = head->next; current != NULL; current = current->next) {
        for (index = current->next; index != NULL; index = index->next) {
            if (current->index > index->index) { // ����ָ�����бȽϣ������ð������
                // ����ϵ����ָ��
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
    ListInitiate(&head3); // ��ʼ��������

    // ������һ������
    SLNode* t = head1->next; // ����ͷ�ڵ�
    while (t != NULL) {
        ListInsert(head3, ListLength(head3), t->xishu, t->index); // ���뵱ǰ�ڵ�
        t = t->next; 
    }
    // �����ڶ�������
    t = head2->next; // ����ͷ�ڵ�
    while (t != NULL) {
        ListInsert(head3, ListLength(head3), (t->xishu) * operate, t->index); // ���뵱ǰ�ڵ�
        t = t->next; 
    }

    return head3; // ���غϲ��������
}
void CombineLikeTerms(SLNode* head) {
    if (head == NULL || head->next == NULL)
        return; // ��������Ƿ�Ϊ��
    SLNode* current = head->next; // �ӵ�һ����Ч�ڵ㿪ʼ
    while (current != NULL) {
        SLNode* run = current->next; // ��鵱ǰ�ڵ����Ľڵ�
        SLNode* pre = current; // ��¼ǰһ���ڵ�

        while (run != NULL) {
            if (run->index == current->index) {
                // ����ҵ���ָͬ������ϲ�ϵ��
                current->xishu += run->xishu;

                // ����ϲ���ϵ��Ϊ�㣬ɾ���ýڵ�
                if (current->xishu == 0) {
                    pre->next = run->next; // ����Ҫɾ���Ľڵ�
                    free(run); 
                    run = pre->next; // ���� run
                }
                else {
                    // ����ֻ�����ǰ��ָ��
                    pre->next = run->next; // �� pre �� next ָ����һ��
                    free(run); 
                    run = pre->next; // ���� run
                }
            }
            else {
                // ���ָ������ͬ�����������һ���ڵ�
                pre = run; // ����ǰ��ָ��
                run = run->next; // �ƶ�����һ���ڵ�
            }
        }
        current = current->next; // �ƶ�����һ���ڵ�
    }
}
int IsZeroPolynomial(SLNode* head) {
    SLNode* p = head->next; // ����ͷ�ڵ�

    while (p != NULL) {
        if (p->xishu != 0) { // ������κη���ϵ��
            return 0; // ���������ʽ
        }
        p = p->next;
    }

    return 1; // ����ϵ�������㣬�����������ʽ
}



int main() {
    SLNode* head1, * head2, * head3, * temp_head;
    int i, j = 0;
    int xishu_a, index_b; // ����ϵ����ָ�����м���
    DataType num = 0; // ����ָ����ͬʱ���ϵ��������ӵĲ���
    ListInitiate(&head1);
    ListInitiate(&head2);
    printf("�ԣ�ϵ����ָ������ʽ����:     (ע�� , ��Ӣ��)");
    while (j < 2) {
        printf("\n�������%d������ʽ������:\n", j + 1);

        j++;
        if (j == 1)
            temp_head = head1;
        else
            temp_head = head2;
        for (i = 0; i < 5; i++) {
            printf("����� %d �", i + 1);
            if (!CheckInputErrors(&xishu_a, &index_b)) {
                printf("�����ʽ�������� (ϵ��, ָ��) ����ʽ���롣\n");
                i--; // �ظ���ǰ����
                continue; // ��������ѭ��
            }
            // ����Ƿ�������ָͬ���Ľڵ�
            if (check_index(temp_head, i, index_b, &num)) {
                //ָ����ȵĶ���ʽ���ϵ����Ϊ��������ȥ
                if (xishu_a + num != 0) {
                    ListInsert(temp_head, ListLength(temp_head), xishu_a + num, index_b); // ������ĩβ�����½ڵ�
                }
            }
            else {
                // ���û����ͬ��ָ������ֱ�Ӳ���
                ListInsert(temp_head, ListLength(temp_head), xishu_a, index_b);
            }
        }
        SortList(temp_head);
    }
    printf("��������������������������������\n");
    printf("���룺-1.��ʽ���\n");
    printf("       1.��ʽ���\n");
    int operate;
    scanf("%d", &operate); //�����û�����ѡ��ӷ������

    head3 = Twoformula(head1, head2, operate); //�µĶ���ʽ��ָ��
    SortList(head3); //��ָ����С��������
    CombineLikeTerms(head3);

   
    if (IsZeroPolynomial(head3)) {
        printf("�����0");
    }
    else {
        for (i = 0; i < ListLength(head3); i++) {
            DataType x, y;
            ListGet(head3, i, &x, &y);
            if (x != 0) {
                if (x > 0)
                    printf("%dx^%d", x, y); // ���ϵ���Ƿ���ȷ����������
                else
                    printf("(%dx)^%d", x, y); //���Ǹ������������
                if (i != ListLength(head3) - 1) printf("+");
            }
        }
    }
    return 0;
}