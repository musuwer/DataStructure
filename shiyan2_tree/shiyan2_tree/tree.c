#define _CRT_SECURE_NO_WARNINGS 1
#include <stdlib.h>
#include <stdio.h>
#include "SeqStack.h"
#include "SeqCQueue.h"

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

//void visit(DataType item) {
//	printf("%c  ", item);
//}
void  LevelorderTraverse(BiTreeNode* root, void (*visit)(DataType item)) {
	SeqCQueue sq;
	QueueInitiate(&sq);
	BiTreeNode* p = root;
	if (p != NULL) {
		QueueAppend(&sq, p);    /*   ��������  */
		while (QueueNotEmpty(sq)) { 
			QueueDelete(&sq, &p);
			visit(p->data);
			if (p->leftChild != NULL)
				QueueAppend(&sq, p->leftChild); /* ������� */
			if (p->rightChild != NULL)
				QueueAppend(&sq, p->rightChild);  /*�ҽ����� */
		}
	}
}

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


// �������������Ⱥ���
int Depth(BiTreeNode* T) {
	if (T == NULL) { // ���������Ϊ0
		return 0;
	}
	else {
		// �����������������������
		int left_depth = Depth(T->leftChild);
		int right_depth = Depth(T->rightChild);

		// �������������еĽϴ���� + 1����1����Ϊ������ǰ�ڵ㣩
		return (left_depth > right_depth) ? (left_depth + 1) : (right_depth + 1);
	}
}


//��Ҷ�ӽ�㺯��
int leaf_node_function(BiTreeNode* p)
{
	if (!p)
		return 0;           //�ն����������
	else if (p->leftChild == NULL && p->rightChild == NULL)
		return  +1;
	else
	{
		return leaf_node_function(p->leftChild) + leaf_node_function(p->rightChild);
	}
} 
//��ӡҶ�ӽ��
void leaf_print(BiTreeNode* p)
{
	if (p != NULL)
	{
		if (p->leftChild == NULL && p->rightChild == NULL)
			printf("%c  ", p->data);
		leaf_print(p->leftChild);
		leaf_print(p->rightChild);
	}
}
#include <stdbool.h>

// �ж��Ƿ�Ϊ��ȫ������
bool IsCompleteBinaryTree(BiTreeNode* root) {
	if (root == NULL) {
		return true;  // ��������ȫ������
	}
	SeqCQueue queue;
	QueueInitiate(&queue);
	QueueAppend(&queue, root);
	bool foundNull = false;  // ����Ƿ��������սڵ�
	BiTreeNode* current;

	while (QueueNotEmpty(queue)) {
		QueueDelete(&queue, &current);

		if (current == NULL) {
			foundNull = true;
		}
		else {
			if (foundNull) {
				// ����������սڵ㣬���������зǿսڵ㣬������ȫ������
				return false;
			}
			// �ǿսڵ����
			QueueAppend(&queue, current->leftChild);
			QueueAppend(&queue, current->rightChild);
		}
	}
	return true;
}

void displayMenu() {
	printf("\n========== �����������˵� ==========\n");
	printf("	1. ����������\n");
	printf("	2. ��ӡ�������ṹ\n");
	printf("	3. ����ָ��Ԫ��\n");
	printf("	4. ǰ��������ǵݹ飩\n");
	printf("	5. �������\n");
	printf("	6. �������\n");
	printf("	7. ��α���\n");
	printf("	8. ������������\n");
	printf("	9. ��ӡҶ�ӽ�㼰����\n");
	printf("	10. �ж��Ƿ�Ϊ��ȫ������\n");
	printf("	0. �˳�����\n");
	printf("===================================\n");
	printf("����������ѡ��");
}

int main() {
	BiTreeNode* root = NULL; // ���������ڵ�
	int choice;
	char x;
	FILE* file;
	int depth, leafCount;

	while (1) {
		displayMenu();
		scanf("%d", &choice);
		switch (choice) {
		case 1: // ����������
			file = fopen("tree.txt", "r");
			if (file == NULL) {
				printf("�޷����ļ� tree.txt��\n");
				break;
			}
			root = CreateTree(file);
			fclose(file);
			printf("�������Ѵ�����\n");
			break;

		case 2: // ��ӡ�������ṹ
			if (root == NULL) {
				printf("������Ϊ�գ����ȴ�����������\n");
				break;
			}
			printf("�������Ľṹ��\n");
			PrintBiTree(root, 0);
			break;

		case 3: // ����ָ��Ԫ��
			if (root == NULL) {
				printf("������Ϊ�գ����ȴ�����������\n");
				break;
			}
			printf("������Ҫ���ҵ�Ԫ�أ�");
			scanf(" %c", &x);
			if (Search(root, x) != NULL)
				printf("Ԫ�� %c �ڶ������С�\n", x);
			else
				printf("Ԫ�� %c ���ڶ������С�\n", x);
			break;

		case 4: // ǰ��������ǵݹ飩
			if (root == NULL) {
				printf("������Ϊ�գ����ȴ�����������\n");
				break;
			}
			printf("ǰ��������ǵݹ飩��");
			PreOrder2(root, visit);
			printf("\n");
			break;

		case 5: // �������
			if (root == NULL) {
				printf("������Ϊ�գ����ȴ�����������\n");
				break;
			}
			printf("���������");
			InOrder(root, visit);
			printf("\n");
			break;

		case 6: // �������
			if (root == NULL) {
				printf("������Ϊ�գ����ȴ�����������\n");
				break;
			}
			printf("���������");
			PostOrder(root, visit);
			printf("\n");
			break;

		case 7: // ��α���
			if (root == NULL) {
				printf("������Ϊ�գ����ȴ�����������\n");
				break;
			}
			printf("��α�����");
			LevelorderTraverse(root, visit);
			printf("\n");
			break;

		case 8: // ������������
			if (root == NULL) {
				printf("������Ϊ�գ����ȴ�����������\n");
				break;
			}
			depth = Depth(root);
			printf("�����������Ϊ��%d\n", depth);
			break;

		case 9: // ��ӡҶ�ӽ�㼰����
			if (root == NULL) {
				printf("������Ϊ�գ����ȴ�����������\n");
				break;
			}
			leafCount = leaf_node_function(root);
			printf("Ҷ�ӽ�����Ϊ��%d\n", leafCount);
			printf("Ҷ�ӽ��Ϊ��");
			leaf_print(root);
			printf("\n");
			break;
		case 10: // �ж��Ƿ�Ϊ��ȫ������
			if (root == NULL) {
				printf("������Ϊ�գ����ȴ�����������\n");
				break;
			}
			if (IsCompleteBinaryTree(root)) {
				printf("�ö���������ȫ��������\n");
			}
			else {
				printf("�ö�����������ȫ��������\n");
			}
			break;

		case 0: // �˳�����
			if (root != NULL) {
				Destroy(&root);
			}
			printf("�������˳���\n");
			return 0;
		default:
			printf("��Ч��ѡ�������ѡ��\n");
			break;
		}
	}
	return 0;
}
