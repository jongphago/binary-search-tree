#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100
#define IS_FULL(ptr) (!(ptr))

typedef struct treeNode* treePtr;
typedef struct treeNode {
	treePtr lchild;
	int data;
	treePtr rchild;
}treeNode;

void inorder(treePtr);
void preorder(treePtr);
void insert(treePtr*, int);
treePtr modifiedSearch(treePtr, int);

void main(void)
/* p207 program 5.1, 	p208 program 5.2, 	p235 program 5.17 insert 함수,
		강의중 제시한 Program modifiedSearch 를 참고 */
{
	int i, n, A[MAX_TERMS];
	treePtr tree = NULL;

	// 파일을 오픈한다.
	FILE* inputFile = fopen("input.txt", "r");
	// 파일을 읽어 정수의 개수는 n에, 삽입하여야할 정수들은 A에 저장한다.
	fscanf(inputFile, "%d", &n);
	for (int i = 0; i < n ; i++)
		fscanf(inputFile, "%d", &(A[i]));

	/* 순서대로 binary search tree에 삽입한다 */
	for (i = 0; i < n; i++)
		insert(&tree, A[i]);

	/* 구성된 binary search tree를 inorder와 preorder로 출력하여 올바르게 트리가 
		생성되었는지 확인한다. */
	inorder(tree);
	printf("\n");
	preorder(tree);
}

void inorder(treePtr ptr)
{
	if (ptr) {
		inorder(ptr->lchild);
		printf("%3d", ptr->data);
		inorder(ptr->rchild);
	}
}

void preorder(treePtr ptr)
{
	if (ptr) {
		printf("%3d", ptr->data);
		inorder(ptr->lchild);
		inorder(ptr->rchild);
	}
}

void insert(treePtr* node, int num)
{
	/* if num is the tree pointed at by node do nothing;
		otherwise add a new node with data = num*/
	treePtr ptr, temp = modifiedSearch(*node, num);
	if (temp || !(*node)) {
		/* num is not in the tree */
		ptr = (treePtr)malloc(sizeof(treeNode));
		if (IS_FULL(ptr)) {
			fprintf(stderr, "The memory is full");
			exit(1);
		}
		ptr->data = num;
		ptr->lchild = NULL; ptr->rchild = NULL;
		if (*node)
			if (num < temp->data)
				temp->lchild = ptr;
			else temp->rchild = ptr;
		else *node = ptr;
	}
}

treePtr modifiedSearch(treePtr tree, int key)
{
	treePtr tempTree = malloc(sizeof(treeNode));
	if (!tree) 	return NULL;
	while (tree)
	{
		if (key == tree->data) return NULL;
		tempTree = tree;
		if (key < tree->data) {
			tree = tree->lchild;
		}
		else {
			tree = tree->rchild;
		}
	}
	return tempTree;
}













