#ifndef SEARCHALGORITHM_H
#define SEARCHALGORITHM_H
#include "head.h"
#include "BiTree.h"
#include <math.h>

//次优查找树的递归构造方法
//由有序表R[low ... high]及其累计权值表sw(其中sw[0]=0)递归构造次优查找树T
void SecondOptimal(BiTree* T, ElemType R[], float sw[], int low, int high);


//二叉排序树查找数据为key的结点递归方法
/*
 * T 待比较的结点，
 * key 查找的值
 * f T的双亲结点
 * p 查找成功(返回TRUE),指向查找到的结点，若查找不成功(返回FALSE)，则指向上一个查找的结点
 */
Status SearchBST(BiTree T, KeyType key, BiTree f, BiTree* p);
//二叉排序树查找数据为key的结点非递归方法
/*
 * T 待比较的结点，
 * key 查找的值
 * p 查找成功(返回TRUE),指向查找到的结点，若查找不成功(返回FALSE)，则指向上一个查找的结点
 */
Status SearchBST_I(BiTree T, KeyType key, BiTree* p);

//二叉排序树插入数据为e的结点
Status InsertBST(BiTree *T, TElemType e);
//二叉排序树删除数据为e的结点
Status DeleteBST(BiTree* T, TElemType e);


//二叉平衡树结构(avl树)
typedef struct BSTNode{
    ElemType data;
    int bf; //节点的平衡因子
	struct BSTNode* lchild;
	struct BSTNode* rchild;
}BSTNode,*BSTree;

#define LH 1
#define EH 0
#define RH -1

//在二叉平衡树T中插入数据e的结点，插入后保证树保持平衡
//插入成功返回1，失败返回0
Status InsertAVL(BSTree* T, ElemType e);



typedef struct RBNode {
	ElemType data;
	int color; 
    struct RBNode* parent;
	struct RBNode* lchild;
	struct RBNode* rchild;
}RBNode,*PRBNode;

typedef struct RBTree
{
    struct RBNode* root;
    struct RBNode* nil;
}RBTree,*PRBTree;

#define RN 1
#define BN 0
void initRBTree(RBTree* T);
RBNode* InsertRBTree(RBTree* T, ElemType e);
PRBNode DeleteRBTree(RBTree* T, ElemType e);
Status SearchRBTree(RBTree T, ElemType key, PRBNode *p);
#endif
