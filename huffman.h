#ifndef HUFFMAN_H_
#define HUFFMAN_H_


typedef struct HTN
{
	unsigned int weight;
	unsigned int parent;
	unsigned short lchild;
	unsigned short rchild;
}HTN;

typedef struct HCode {
	char len;
	char dat[32];
}HCode;
typedef struct HuffmanFileHead {
	char head[7];
	char sub_zero;
	char md5[16];
	HTN tree[512];
	HCode code[256];
}HuffmanFileHead;
/*
	编码：
	1，先遍历整个文件，获取0~255每个数字出现的频率。
	2，根据频率构造哈夫曼树，并构造每个数字的哈夫曼编码；
	3，遍历文件，根据哈夫曼编码编码数据，并在文件头部写入哈夫曼树数组
*/

int HuffmanEnCoding(const char *filename, const char *outfile);
int HuffmanDeCoding(const char* filename, const char* outfile);


#endif // !HUFFMAN_H_
