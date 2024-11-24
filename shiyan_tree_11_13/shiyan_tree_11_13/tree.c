#define _CRT_SECURE_NO_WARNINGS 1
#include <stdlib.h>
#include <stdio.h>
#include "SeqStack.h"
//#include "SeqCQueue.h"

typedef char DataType;
typedef struct Node {
	DataType data;			//数据域
	struct Node* leftChild;		//左子树指针
	struct Node* rightChild;      	//右子树指针
	//struct Node *parent;
}BiTreeNode, * BiTree;

/*在curr左子树插入结点，返回插入的结点*/
BiTreeNode* InsertLeftNode(BiTreeNode* curr, DataType x) {
	BiTreeNode* s, * t;
	if (curr == NULL) return NULL;
	t = curr->leftChild; 	//保存原curr所指结点的左子树指针

	s = (BiTreeNode*)malloc(sizeof(BiTreeNode));
	s->data = x;
	s->leftChild = t;   	//原curr的左子树成为新插入结点的左子树
	s->rightChild = NULL;
	curr->leftChild = s;  	//新结点为curr的左子树
	return curr->leftChild;
}

/*右子树插入结点，与左插入类似*/
BiTreeNode* InsertRightNode(BiTreeNode* curr, DataType x) {
	BiTreeNode* s, * t;
	if (curr == NULL) return NULL;
	t = curr->rightChild;      	//保存原curr所指结点的右子树指针

	s = (BiTreeNode*)malloc(sizeof(BiTreeNode));
	s->data = x;
	s->rightChild = t;   	//新插入结点的右子树为原curr的右子树
	s->leftChild = NULL;
	curr->rightChild = s;  	//新结点为curr的右子树
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
/*删除curr的左子树,返回被删结点的双亲*/
BiTreeNode* DeleteLeftTree(BiTreeNode* curr) {
	if (curr == NULL || curr->leftChild == NULL)
		return NULL;
	Destroy(&curr->leftChild); //撤销操作
	curr->leftChild = NULL;
	return curr;
}
/*删除右子树*/
BiTreeNode* DeleteRightTree(BiTreeNode* curr) {
	if (curr == NULL || curr->rightChild == NULL)
		return NULL;
	Destroy(&curr->rightChild); //撤销操作
	curr->rightChild = NULL;
	return curr;
}
void visit(DataType item) {
	printf("%c  ", item);
}
void PreOrder(BiTreeNode* t, void (*visit)(DataType item)) {
	/*前序遍历二叉树t，访问操作为visit()函数-函数指针*/
	if (t != NULL) {
		visit(t->data); //printf(“%d”,t->data);
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
			//右子树进栈,回溯访问右子树时用
			if (q != NULL)  StackPush(&st, q);
			q = p->leftChild;
			if (q != NULL)  StackPush(&st, q);
		} while (StackNotEmpty(st));
	}
}


void InOrder(BiTreeNode* t, void (*Visit)(DataType item)) {
	/*中序遍历二叉树t */
	if (t != NULL) {
		InOrder(t->leftChild, Visit);
		visit(t->data);
		InOrder(t->rightChild, Visit);
	}
}
void PostOrder(BiTreeNode* t, void (*Visit)(DataType item)) {
	/*后序遍历二叉树t */
	if (t != NULL) {
		PostOrder(t->leftChild, Visit);
		PostOrder(t->rightChild, Visit);
		visit(t->data);
	}
}

BiTreeNode* Search(BiTreeNode* bt, DataType x) {
	BiTreeNode* p;
	if (bt == NULL) return NULL;	//递归出口
	if (bt->data == x) return bt;       //递归出口
	if (bt->leftChild != NULL) {   //查询左子树
		p = Search(bt->leftChild, x);
		if (p != NULL) return p;
	}
	if (bt->rightChild != NULL) {   //查询右子树
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
//		QueueAppend(sq, p);    /*   根结点入队  */
//		while (!isEmpty(sq)) {
//			QueueDelete(sq, p);
//			visit(p->data);
//			if (p->leftChild != NULL)
//				QueueAppend(sq, p->leftChild); /* 左结点入队 */
//			if (p->rightChild != NULL)
//				QueueAppend(sq, p->rightChild);  /*右结点入队 */
//		}
//	}
//}

// A B D # # E # # C F # # G # #
// 创建二叉树的递归函数
BiTreeNode* CreateTree(FILE* file) {
	char ch;
	// 从文件中读取一个字符
	if (fscanf(file, " %c", &ch) == EOF) {
		return NULL;  // 到达文件末尾
	}
	if (ch == '#') {
		return NULL;  // 空节点
	}
	// 创建当前节点
	BiTreeNode* node = (BiTreeNode*)malloc(sizeof(BiTreeNode));
	node->data = ch;
	// 递归创建左子树和右子树
	node->leftChild = CreateTree(file);
	node->rightChild = CreateTree(file);
	return node;
}
void PrintBiTree(BiTreeNode* bt, int n) {
	int i;
	if (bt == NULL) {
		return ;
	}
	PrintBiTree(bt->rightChild, n + 1);// 递归打印右子树
	// 打印当前节点
	for (i = 0; i < n; i++) printf("\t");  // 打印缩进
	if (n >= 0) {
		printf("---");
	}
	printf("%c\n", bt->data);
	PrintBiTree(bt->leftChild, n + 1);// 递归打印左子树
}


void main(void) {
	//用递归方式创建二叉树
	FILE* file = fopen("tree.txt", "r");
	if (file == NULL) {
		printf("无法打开文件。\n"); return 1;
	}
	BiTreeNode* root = CreateTree(file);// 创建二叉树
	BiTreeNode* p, * find;
	fclose(file);  // 关闭文件

	//查找指定元素
	char x = 'E';
	find = Search(root, x);
	if (find != NULL) printf("元素%c在二叉树中", x);
	else printf("\n元素%c不在二叉树中", x);

	// 打印二叉树
	printf("二叉树的结构：\n");
	PrintBiTree(root, 0);

	//非递归方式先序遍历
	printf("前序遍历(非递归)：");
	PreOrder2(root, visit);

	//中序或后序遍历方式输出树T的结点； 
	printf("\n中序遍历：");
	InOrder(root, visit);
	printf("\n后序遍历：");
	PostOrder(root, visit);
	
	Destroy(&root);
}
