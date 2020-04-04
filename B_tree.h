#ifndef B_TREE_H_
#define B_TREE_H_
#include "head.h"
#define BTREE_M 6  //B���Ľף�����Ϊ3
typedef int KeyType;
typedef char Record;

typedef struct BTNode
{
	int				keynum;//����йؼ��ֵĸ����������Ĵ�С
	struct BTNode	*parent;//ָ��˫�׽��
	KeyType			key[BTREE_M + 1];//�ؼ�������,0�ŵ�Ԫδʹ��
	struct BTNode	*ptr[BTREE_M + 1];//����ָ������
	Record			*recptr[BTREE_M + 1];//��¼ָ������//0�ŵ�Ԫδʹ��
}BTNode,*BTree;

typedef struct {
	BTNode* pt;	//ָ���ҵ��Ľ��
	int		index;//��Χ(1��m),�ڽ���еĹؼ������
	int		tag;//���ҳɹ�1,ʧ��0
}Result;//B���Ĳ��ҽ������

/*
��m��B��T�ϲ��ҹؼ���K�����ؽ��(pt,index,tag).�����ҳɹ�������ֵtag=1,ָ��pt��ָ�ڵ��е�i���ؼ��ֵ���K;����
����ֵtag=0������K�Ĺؼ���Ӧ������ָ��pt��ָ�ڵ��е�i��i+1���ؼ���֮��
*/
Result SearchBTree(BTree T, KeyType K);
/*
��m��B��T�Ͻ��*q��key[i]��key[i+1]֮�����ؼ���K,
���������������˫�������б�Ҫ�Ľ����ѵ�����ʹT����m��B��
*/
Status InsertBTree(BTree* T, KeyType K, Record* rec);
#endif // !1


