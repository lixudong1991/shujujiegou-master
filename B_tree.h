#ifndef B_TREE_H_
#define B_TREE_H_
#include "head.h"
#define BTREE_M 6  //B树的阶，暂设为3
typedef int KeyType;
typedef char Record;

typedef struct BTNode
{
	int				keynum;//结点中关键字的个数，即结点的大小
	struct BTNode	*parent;//指向双亲结点
	KeyType			key[BTREE_M + 1];//关键字向量,0号单元未使用
	struct BTNode	*ptr[BTREE_M + 1];//子树指针向量
	Record			*recptr[BTREE_M + 1];//记录指针向量//0号单元未使用
}BTNode,*BTree;

typedef struct {
	BTNode* pt;	//指向找到的结点
	int		index;//范围(1到m),在结点中的关键字序号
	int		tag;//查找成功1,失败0
}Result;//B树的查找结果类型

/*
在m阶B树T上查找关键字K，返回结果(pt,index,tag).若查找成功则特征值tag=1,指针pt所指节点中第i个关键字等于K;否则
特征值tag=0，等于K的关键字应插入在指针pt所指节点中的i和i+1个关键字之间
*/
Result SearchBTree(BTree T, KeyType K);
/*
在m阶B树T上结点*q的key[i]和key[i+1]之间插入关键字K,
若引起结点过大，则沿双亲链进行必要的结点分裂调整，使T仍是m阶B树
*/
Status InsertBTree(BTree* T, KeyType K, Record* rec);
#endif // !1


