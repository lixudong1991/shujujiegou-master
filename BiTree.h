#ifndef BITREE_H_
#define BITREE_H_
#include "head.h"

//------�������Ĵ洢��ʾ------
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode* lchild;
	struct BiTNode* rchild;
}BiTNode,*BiTree;

typedef Status(*VISIT)(TElemType e);

/*
�������������������нڵ��ֵ(һ���ַ�),�ո��ַ���ʾ������������������ʾ�Ķ�����T
*/
Status CreateBiTree(BiTree *t);

/*
���ö�������洢�ṹ��visit �ǶԽڵ������Ӧ�ú�����
����ݹ����������t ,��ÿ�������ú���visitһ���ҽ�һ��
һ��visitʧ�ܣ������ʧ�� 
*/
Status PreOrderTraverse(BiTree t, VISIT visit);


/*
���ö�������洢�ṹ��visit �ǶԽڵ������Ӧ�ú�����
�������������t ,��ÿ�������ú���visitһ���ҽ�һ��
һ��visitʧ�ܣ������ʧ��
�ݹ鷨
*/
Status InOrderTraverse(BiTree t, VISIT visit);

/*
���ö�������洢�ṹ��visit �ǶԽڵ������Ӧ�ú�����
�������������t ,��ÿ�������ú���visitһ���ҽ�һ��
һ��visitʧ�ܣ������ʧ��
�ǵݹ�1
*/
Status InOrderTraverse_I(BiTree t, VISIT visit);
/*
���ö�������洢�ṹ��visit �ǶԽڵ������Ӧ�ú�����
�������������t ,��ÿ�������ú���visitһ���ҽ�һ��
һ��visitʧ�ܣ������ʧ��
�ǵݹ�2
*/
Status InOrderTraverse_II(BiTree t, VISIT visit);


/*
���ö�������洢�ṹ��visit �ǶԽڵ������Ӧ�ú�����
�������������t ,��ÿ�������ú���visitһ���ҽ�һ��
һ��visitʧ�ܣ������ʧ��
*/
Status PostOrderTraverse(BiTree t, VISIT visit);


/*
���ö�������洢�ṹ��visit �ǶԽڵ������Ӧ�ú�����
�������������t ,��ÿ�������ú���visitһ���ҽ�һ��
һ��visitʧ�ܣ������ʧ��
*/
Status LevelOrderTraverse(BiTree t, VISIT visit);


//------�������������洢��ʾ------
typedef enum PointerTag{
	Link,
	Thr
}PointerTag; //Link==0ָ�룬 Thr ==1����

typedef struct BiThrNode
{
	TElemType data;
	struct BiThrNode* lchild;
	struct BiThrNode* rchild;
	 PointerTag LTag;
	 PointerTag RTag;
}BiThrNode,*BiThrTree;

/*
��ͷ�ڵ��˫����������  ������
*/
Status InOrderThreading(BiThrTree *thr, BiThrTree t);

/*
��ͷ�ڵ��˫���������� ��������ǵݹ��㷨
tָ��ͷ�ڵ㣬ͷ�ڵ������lchildָ����ڵ㣬rchildָ���������ʱ�����һ���ڵ�
*/
Status InOrderTraverse_Thr(BiThrTree t, VISIT visit);



//------------���������͹���������洢��ʾ---------------
typedef struct HTNode
{
	unsigned int weight;
	unsigned int parent;
	unsigned int lchild;
	unsigned int rchild;
}HTNode,*HuffmanTree;//��̬��������洢��������

typedef char** HuffmanCode; //��̬��������洢�����������


//w ���n���ַ���Ȩֵ(����0),�����������HT�������n���ַ��Ĺ���������HC
void HuffmanCoding(HuffmanTree* HT, HuffmanCode* HC, unsigned int* w, unsigned int n);


#endif
