#define _CRT_SECURE_NO_WARNINGS 1
#include <stdlib.h>
#include <stdio.h>
#include "SeqStack.h"
#include "SeqCQueue.h"

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

//void visit(DataType item) {
//	printf("%c  ", item);
//}
void  LevelorderTraverse(BiTreeNode* root, void (*visit)(DataType item)) {
	SeqCQueue sq;
	QueueInitiate(&sq);
	BiTreeNode* p = root;
	if (p != NULL) {
		QueueAppend(&sq, p);    /*   根结点入队  */
		while (QueueNotEmpty(sq)) { 
			QueueDelete(&sq, &p);
			visit(p->data);
			if (p->leftChild != NULL)
				QueueAppend(&sq, p->leftChild); /* 左结点入队 */
			if (p->rightChild != NULL)
				QueueAppend(&sq, p->rightChild);  /*右结点入队 */
		}
	}
}

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


// 计算二叉树的深度函数
int Depth(BiTreeNode* T) {
	if (T == NULL) { // 空树的深度为0
		return 0;
	}
	else {
		// 计算左子树和右子树的深度
		int left_depth = Depth(T->leftChild);
		int right_depth = Depth(T->rightChild);

		// 返回左右子树中的较大深度 + 1（加1是因为包括当前节点）
		return (left_depth > right_depth) ? (left_depth + 1) : (right_depth + 1);
	}
}


//求叶子结点函数
int leaf_node_function(BiTreeNode* p)
{
	if (!p)
		return 0;           //空二叉树的情况
	else if (p->leftChild == NULL && p->rightChild == NULL)
		return  +1;
	else
	{
		return leaf_node_function(p->leftChild) + leaf_node_function(p->rightChild);
	}
} 
//打印叶子结点
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

// 判断是否为完全二叉树
bool IsCompleteBinaryTree(BiTreeNode* root) {
	if (root == NULL) {
		return true;  // 空树是完全二叉树
	}
	SeqCQueue queue;
	QueueInitiate(&queue);
	QueueAppend(&queue, root);
	bool foundNull = false;  // 标记是否已遇到空节点
	BiTreeNode* current;

	while (QueueNotEmpty(queue)) {
		QueueDelete(&queue, &current);

		if (current == NULL) {
			foundNull = true;
		}
		else {
			if (foundNull) {
				// 如果已遇到空节点，但后续还有非空节点，则不是完全二叉树
				return false;
			}
			// 非空节点入队
			QueueAppend(&queue, current->leftChild);
			QueueAppend(&queue, current->rightChild);
		}
	}
	return true;
}

void displayMenu() {
	printf("\n========== 二叉树操作菜单 ==========\n");
	printf("	1. 创建二叉树\n");
	printf("	2. 打印二叉树结构\n");
	printf("	3. 查找指定元素\n");
	printf("	4. 前序遍历（非递归）\n");
	printf("	5. 中序遍历\n");
	printf("	6. 后序遍历\n");
	printf("	7. 层次遍历\n");
	printf("	8. 计算二叉树深度\n");
	printf("	9. 打印叶子结点及个数\n");
	printf("	10. 判断是否为完全二叉树\n");
	printf("	0. 退出程序\n");
	printf("===================================\n");
	printf("请输入您的选择：");
}

int main() {
	BiTreeNode* root = NULL; // 二叉树根节点
	int choice;
	char x;
	FILE* file;
	int depth, leafCount;

	while (1) {
		displayMenu();
		scanf("%d", &choice);
		switch (choice) {
		case 1: // 创建二叉树
			file = fopen("tree.txt", "r");
			if (file == NULL) {
				printf("无法打开文件 tree.txt。\n");
				break;
			}
			root = CreateTree(file);
			fclose(file);
			printf("二叉树已创建！\n");
			break;

		case 2: // 打印二叉树结构
			if (root == NULL) {
				printf("二叉树为空，请先创建二叉树。\n");
				break;
			}
			printf("二叉树的结构：\n");
			PrintBiTree(root, 0);
			break;

		case 3: // 查找指定元素
			if (root == NULL) {
				printf("二叉树为空，请先创建二叉树。\n");
				break;
			}
			printf("请输入要查找的元素：");
			scanf(" %c", &x);
			if (Search(root, x) != NULL)
				printf("元素 %c 在二叉树中。\n", x);
			else
				printf("元素 %c 不在二叉树中。\n", x);
			break;

		case 4: // 前序遍历（非递归）
			if (root == NULL) {
				printf("二叉树为空，请先创建二叉树。\n");
				break;
			}
			printf("前序遍历（非递归）：");
			PreOrder2(root, visit);
			printf("\n");
			break;

		case 5: // 中序遍历
			if (root == NULL) {
				printf("二叉树为空，请先创建二叉树。\n");
				break;
			}
			printf("中序遍历：");
			InOrder(root, visit);
			printf("\n");
			break;

		case 6: // 后序遍历
			if (root == NULL) {
				printf("二叉树为空，请先创建二叉树。\n");
				break;
			}
			printf("后序遍历：");
			PostOrder(root, visit);
			printf("\n");
			break;

		case 7: // 层次遍历
			if (root == NULL) {
				printf("二叉树为空，请先创建二叉树。\n");
				break;
			}
			printf("层次遍历：");
			LevelorderTraverse(root, visit);
			printf("\n");
			break;

		case 8: // 计算二叉树深度
			if (root == NULL) {
				printf("二叉树为空，请先创建二叉树。\n");
				break;
			}
			depth = Depth(root);
			printf("二叉树的深度为：%d\n", depth);
			break;

		case 9: // 打印叶子结点及个数
			if (root == NULL) {
				printf("二叉树为空，请先创建二叉树。\n");
				break;
			}
			leafCount = leaf_node_function(root);
			printf("叶子结点个数为：%d\n", leafCount);
			printf("叶子结点为：");
			leaf_print(root);
			printf("\n");
			break;
		case 10: // 判断是否为完全二叉树
			if (root == NULL) {
				printf("二叉树为空，请先创建二叉树。\n");
				break;
			}
			if (IsCompleteBinaryTree(root)) {
				printf("该二叉树是完全二叉树。\n");
			}
			else {
				printf("该二叉树不是完全二叉树。\n");
			}
			break;

		case 0: // 退出程序
			if (root != NULL) {
				Destroy(&root);
			}
			printf("程序已退出。\n");
			return 0;
		default:
			printf("无效的选项，请重新选择。\n");
			break;
		}
	}
	return 0;
}
