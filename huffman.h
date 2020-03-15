#ifndef HUFFMAN_H_
#define HUFFMAN_H_


typedef struct HTN
{
	unsigned int weight;
	unsigned int parent;
	unsigned short lchild;
	unsigned short rchild;
}HTN;

typedef struct HuffmanFileHead {
	char head[7];
	char sub_zero;
	char md5[16];
	HTN tree[512];
}HuffmanFileHead;
/*
	���룺
	1���ȱ��������ļ�����ȡ0~255ÿ�����ֳ��ֵ�Ƶ�ʡ�
	2������Ƶ�ʹ������������������ÿ�����ֵĹ��������룻
	3�������ļ������ݹ���������������ݣ������ļ�ͷ��д�������������
*/

int HuffmanEnCoding(const char *filename, const char *outfile);

/*
	����
*/
int HuffmanDeCoding(const char* filename, const char* outfile);


#endif // !HUFFMAN_H_
