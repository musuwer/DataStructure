#define _CRT_SECURE_NO_WARNINGS 1
#include <stdlib.h>
#include <stdio.h>
#include "SeqStack.h"
//#include "SeqCQueue.h"

typedef char DataType;
typedef struct Node {
	DataType data;			//������
	struct Node* leftChild;		//������ָ��
	struct Node* rightChild;      	//������ָ��
	//struct Node *parent;
}BiTreeNode, * BiTree;

/*��curr�����������㣬���ز���Ľ��*/
BiTreeNode* InsertLeftNode(BiTreeNode* curr, DataType x) {
	BiTreeNode* s, * t;
	if (curr == NULL) return NULL;
	t = curr->leftChild; 	//����ԭcurr��ָ����������ָ��

	s = (BiTreeNode*)malloc(sizeof(BiTreeNode));
	s->data = x;
	s->leftChild = t;   	//ԭcurr����������Ϊ�²������������
	s->rightChild = NULL;
	curr->leftChild = s;  	//�½��Ϊcurr��������
	return curr->leftChild;
}

/*�����������㣬�����������*/
BiTreeNode* InsertRightNode(BiTreeNode* curr, DataType x) {
	BiTreeNode* s, * t;
	if (curr == NULL) return NULL;
	t = curr->rightChild;      	//����ԭcurr��ָ����������ָ��

	s = (BiTreeNode*)malloc(sizeof(BiTreeNode));
	s->data = x;
	s->rightChild = t;   	//�²������������Ϊԭcurr��������
	s->leftChild = NULL;
	curr->rightChild = s;  	//�½��Ϊcurr��������
	return curr->rightChild;
}
void Destroy(BiTreeNode** root) {
	if ((*root) != NULL && (*root)->leftChild != NULL) {
		Destroy(&(*root)->leftChild);
	}
	if ((*root) != NULL && (*root)->rightChild != NULL) {
		Destroy(&(*root)->rightChild);
	}
	free(*root);
}
/*ɾ��curr��������,���ر�ɾ����˫��*/
BiTreeNode* DeleteLeftTree(BiTreeNode* curr) {
	if (curr == NULL || curr->leftChild == NULL)
		return NULL;
	Destroy(&curr->leftChild); //��������
	curr->leftChild = NULL;
	return curr;
}
/*ɾ��������*/
BiTreeNode* DeleteRightTree(BiTreeNode* curr) {
	if (curr == NULL || curr->rightChild == NULL)
		return NULL;
	Destroy(&curr->rightChild); //��������
	curr->rightChild = NULL;
	return curr;
}
void visit(DataType item) {
	printf("%c  ", item);
}
void PreOrder(BiTreeNode* t, void (*visit)(DataType item)) {
	/*ǰ�����������t�����ʲ���Ϊvisit()����-����ָ��*/
	if (t != NULL) {
		visit(t->data); //printf(��%d��,t->data);
		PreOrder(t->leftChild, visit);
		PreOrder(t->rightChild, visit);
	}
} 
void  PreOrder2(BiTreeNode* root, void (*Visit)(DataType item)) {
	BiTreeNode* p = root, * q;
	SeqStack st;
	StackInitiate(&st);
	if (root == NULL)  printf("Binary Tree is Empty!\n");
	else {
		StackPush(&st, root);
		do {
			StackPop(&st, &p);
			visit(p->data);
			q = p->rightChild;
			//��������ջ,���ݷ���������ʱ��
			if (q != NULL)  StackPush(&st, q);
			q = p->leftChild;
			if (q != NULL)  StackPush(&st, q);
		} while (StackNotEmpty(st));
	}
}


void InOrder(BiTreeNode* t, void (*Visit)(DataType item)) {
	/*�������������t */
	if (t != NULL) {
		InOrder(t->leftChild, Visit);
		visit(t->data);
		InOrder(t->rightChild, Visit);
	}
}
void PostOrder(BiTreeNode* t, void (*Visit)(DataType item)) {
	/*�������������t */
	if (t != NULL) {
		PostOrder(t->leftChild, Visit);
		PostOrder(t->rightChild, Visit);
		visit(t->data);
	}
}

BiTreeNode* Search(BiTreeNode* bt, DataType x) {
	BiTreeNode* p;
	if (bt == NULL) return NULL;	//�ݹ����
	if (bt->data == x) return bt;       //�ݹ����
	if (bt->leftChild != NULL) {   //��ѯ������
		p = Search(bt->leftChild, x);
		if (p != NULL) return p;
	}
	if (bt->rightChild != NULL) {   //��ѯ������
		p = Search(bt->rightChild, x);
		if (p != NULL) return p;
	}
	return NULL;
}
//void  LevelorderTraverse(BiTreeNode* root, void (*visit)(DataType item)) {
//	SeqCQueue* sq;
//	QueueInitiate(sq);
//	BiTreeNode* p = root;
//	if (p != NULL) {
//		QueueAppend(sq, p);    /*   ��������  */
//		while (!isEmpty(sq)) {
//			QueueDelete(sq, p);
//			visit(p->data);
//			if (p->leftChild != NULL)
//				QueueAppend(sq, p->leftChild); /* ������� */
//			if (p->rightChild != NULL)
//				QueueAppend(sq, p->rightChild);  /*�ҽ����� */
//		}
//	}
//}

// A B D # # E # # C F # # G # #
// �����������ĵݹ麯��
BiTreeNode* CreateTree(FILE* file) {
	char ch;
	// ���ļ��ж�ȡһ���ַ�
	if (fscanf(file, " %c", &ch) == EOF) {
		return NULL;  // �����ļ�ĩβ
	}
	if (ch == '#') {
		return NULL;  // �սڵ�
	}
	// ������ǰ�ڵ�
	BiTreeNode* node = (BiTreeNode*)malloc(sizeof(BiTreeNode));
	node->data = ch;
	// �ݹ鴴����������������
	node->leftChild = CreateTree(file);
	node->rightChild = CreateTree(file);
	return node;
}
void PrintBiTree(BiTreeNode* bt, int n) {
	int i;
	if (bt == NULL) {
		return ;
	}
	PrintBiTree(bt->rightChild, n + 1);// �ݹ��ӡ������
	// ��ӡ��ǰ�ڵ�
	for (i = 0; i < n; i++) printf("\t");  // ��ӡ����
	if (n >= 0) {
		printf("---");
	}
	printf("%c\n", bt->data);
	PrintBiTree(bt->leftChild, n + 1);// �ݹ��ӡ������
}


void main(void) {
	//�õݹ鷽ʽ����������
	FILE* file = fopen("tree.txt", "r");
	if (file == NULL) {
		printf("�޷����ļ���\n"); return 1;
	}
	BiTreeNode* root = CreateTree(file);// ����������
	BiTreeNode* p, * find;
	fclose(file);  // �ر��ļ�

	//����ָ��Ԫ��
	char x = 'E';
	find = Search(root, x);
	if (find != NULL) printf("Ԫ��%c�ڶ�������", x);
	else printf("\nԪ��%c���ڶ�������", x);

	// ��ӡ������
	printf("�������Ľṹ��\n");
	PrintBiTree(root, 0);

	//�ǵݹ鷽ʽ�������
	printf("ǰ�����(�ǵݹ�)��");
	PreOrder2(root, visit);

	//�������������ʽ�����T�Ľ�㣻 
	printf("\n���������");
	InOrder(root, visit);
	printf("\n���������");
	PostOrder(root, visit);
	
	Destroy(&root);
}
