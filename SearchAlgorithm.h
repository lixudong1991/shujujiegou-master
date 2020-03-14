#ifndef SEARCHALGORITHM_H
#define SEARCHALGORITHM_H
#include "head.h"
#include "BiTree.h"
#include <math.h>

//���Ų������ĵݹ鹹�췽��
//�������R[low ... high]�����ۼ�Ȩֵ��sw(����sw[0]=0)�ݹ鹹����Ų�����T
void SecondOptimal(BiTree* T, ElemType R[], float sw[], int low, int high);


//������������������Ϊkey�Ľ��ݹ鷽��
/*
 * T ���ȽϵĽ�㣬
 * key ���ҵ�ֵ
 * f T��˫�׽��
 * p ���ҳɹ�(����TRUE),ָ����ҵ��Ľ�㣬�����Ҳ��ɹ�(����FALSE)����ָ����һ�����ҵĽ��
 */
Status SearchBST(BiTree T, KeyType key, BiTree f, BiTree* p);
//������������������Ϊkey�Ľ��ǵݹ鷽��
/*
 * T ���ȽϵĽ�㣬
 * key ���ҵ�ֵ
 * p ���ҳɹ�(����TRUE),ָ����ҵ��Ľ�㣬�����Ҳ��ɹ�(����FALSE)����ָ����һ�����ҵĽ��
 */
Status SearchBST_I(BiTree T, KeyType key, BiTree* p);

//������������������Ϊe�Ľ��
Status InsertBST(BiTree *T, TElemType e);
//����������ɾ������Ϊe�Ľ��
Status DeleteBST(BiTree* T, TElemType e);


//����ƽ�����ṹ(avl��)
typedef struct BSTNode{
    ElemType data;
    int bf; //�ڵ��ƽ������
	struct BSTNode* lchild;
	struct BSTNode* rchild;
}BSTNode,*BSTree;

#define LH 1
#define EH 0
#define RH -1

//�ڶ���ƽ����T�в�������e�Ľ�㣬�����֤������ƽ��
//����ɹ�����1��ʧ�ܷ���0
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
