#ifndef BITREE_H_
#define BITREE_H_
#include "head.h"

//------二叉树的存储表示------
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode* lchild;
	struct BiTNode* rchild;
}BiTNode,*BiTree;

typedef Status(*VISIT)(TElemType e);

/*
按先序次序输入二叉树中节点的值(一个字符),空格字符表示空树，构造二叉链表表示的二叉树T
*/
Status CreateBiTree(BiTree *t);

/*
采用二叉链表存储结构，visit 是对节点操作的应用函数。
先序递归遍历二叉树t ,对每个结点调用函数visit一次且仅一次
一旦visit失败，则操作失败 
*/
Status PreOrderTraverse(BiTree t, VISIT visit);


/*
采用二叉链表存储结构，visit 是对节点操作的应用函数。
中序遍历二叉树t ,对每个结点调用函数visit一次且仅一次
一旦visit失败，则操作失败
递归法
*/
Status InOrderTraverse(BiTree t, VISIT visit);

/*
采用二叉链表存储结构，visit 是对节点操作的应用函数。
中序遍历二叉树t ,对每个结点调用函数visit一次且仅一次
一旦visit失败，则操作失败
非递归1
*/
Status InOrderTraverse_I(BiTree t, VISIT visit);
/*
采用二叉链表存储结构，visit 是对节点操作的应用函数。
中序遍历二叉树t ,对每个结点调用函数visit一次且仅一次
一旦visit失败，则操作失败
非递归2
*/
Status InOrderTraverse_II(BiTree t, VISIT visit);


/*
采用二叉链表存储结构，visit 是对节点操作的应用函数。
后序遍历二叉树t ,对每个结点调用函数visit一次且仅一次
一旦visit失败，则操作失败
*/
Status PostOrderTraverse(BiTree t, VISIT visit);


/*
采用二叉链表存储结构，visit 是对节点操作的应用函数。
层序遍历二叉树t ,对每个结点调用函数visit一次且仅一次
一旦visit失败，则操作失败
*/
Status LevelOrderTraverse(BiTree t, VISIT visit);


//------二叉树的线索存储表示------
typedef enum PointerTag{
	Link,
	Thr
}PointerTag; //Link==0指针， Thr ==1线索

typedef struct BiThrNode
{
	TElemType data;
	struct BiThrNode* lchild;
	struct BiThrNode* rchild;
	 PointerTag LTag;
	 PointerTag RTag;
}BiThrNode,*BiThrTree;

/*
带头节点的双向线索链表  线索化
*/
Status InOrderThreading(BiThrTree *thr, BiThrTree t);

/*
带头节点的双向线索链表 中序遍历非递归算法
t指向头节点，头节点的左链lchild指向根节点，rchild指向中序遍历时的最后一个节点
*/
Status InOrderTraverse_Thr(BiThrTree t, VISIT visit);



//------------哈夫曼树和哈夫曼编码存储表示---------------
typedef struct HTNode
{
	unsigned int weight;
	unsigned int parent;
	unsigned int lchild;
	unsigned int rchild;
}HTNode,*HuffmanTree;//动态分配数组存储哈夫曼树

typedef char** HuffmanCode; //动态分配数组存储哈夫曼编码表


//w 存放n个字符的权值(大于0),构造哈夫曼树HT，并求出n个字符的哈夫曼编码HC
void HuffmanCoding(HuffmanTree* HT, HuffmanCode* HC, unsigned int* w, unsigned int n);


#endif
