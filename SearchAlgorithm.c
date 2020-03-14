#include "SearchAlgorithm.h"

void SecondOptimal(BiTree* T, ElemType R[], float sw[], int low, int high)
{
	int i = low;
	float minP = fabsf(sw[high] - sw[low]);
	float dw = sw[low - 1] + sw[high];
	for (int j=low+1;j<=high;j++)
	{
		float temp = fabsf(dw - sw[j] - sw[j - 1]);
		if (temp<minP)
		{
			i = j;
			minP = temp;
		}
	}
	*T = (BiTree)malloc(sizeof(BiTNode));
	(*T)->data = R[i];
	if (i == low)
		(*T)->lchild = NULL;
	else
		SecondOptimal(&((*T)->lchild),R,sw,low,i-1);
	if (i == high)
		(*T)->rchild = NULL;
	else
		SecondOptimal(&((*T)->rchild), R, sw,  i + 1,high);
}
Status SearchBST(BiTree T, KeyType key, BiTree f, BiTree* p)
{
	if (!T)
	{
		*p = f;
		return FALSE;
	}
	if (T->data==key)
	{
		*p = T;
		return TRUE;
	}
	else
		return SearchBST(T->data > key ? T->lchild : T->rchild, key, T, p);

}
Status SearchBST_I(BiTree T, KeyType key, BiTree* p)
{
	while (T!=NULL)
	{
		*p = T;
		if (T->data == key)
			return TRUE;
		T = (T->data > key ? T->lchild : T->rchild);
	}
	return FALSE;
}
Status InsertBST(BiTree* T, TElemType e)
{
	BiTree p = NULL;
	if (!SearchBST_I(*T,e,&p))
	{
		BiTree temp = malloc(sizeof(BiTNode));
		temp->data = e;
		temp->lchild = NULL;
		temp->rchild = NULL;
		if (!p)
		{
			*T = temp;
		}
		else {
			if (p->data > e)
				p->lchild = temp;
			else
				p->rchild = temp;
		}
		return TRUE;
	}
	return FALSE;
}

static Status deleteElem(BiTree* T)
{
	BiTree q = *T;
	BiTree s = NULL;
	if (!((*T)->lchild))
	{
		(*T) = (*T)->rchild;
		free(q);
		return TRUE;
	}
	if (!((*T)->rchild))
	{
		(*T) = (*T)->lchild;
		free(q);
		return TRUE;
	}
	s = q->lchild;
	while (s->rchild)
	{
		q = s;
		s = s->rchild;
	}
	(*T)->data = s->data;
	if (q == (*T))
		q->lchild = s->lchild;
	else
		q->rchild = s->lchild;
	free(s);
	return TRUE;
}
Status DeleteBST(BiTree* T, TElemType e)
{
	if (!(*T))
	{
		return FALSE;
	}
	if ((*T)->data==e)
	{
		return deleteElem(T);
	}
	else
		return DeleteBST((*T)->data > e ? &((*T)->lchild ): &((*T)->rchild), e);
}


static void R_Rotate(BSTree* T)
{
	BSTree p = (*T)->lchild;
	(*T)->lchild = p->rchild;
	p->rchild = (*T);
	*T = p;
}
static void L_Rotate(BSTree* T)
{
	BSTree p = (*T)->rchild;
	(*T)->rchild = p->lchild;
	p->lchild = (*T);
	*T = p;
}

static void LeftBalance(BSTree* T)
{
	BSTree lc = (*T)->lchild;
	switch (lc->bf)
	{
	case LH:
		lc->bf = EH;
		(*T)->bf = EH;
		R_Rotate(T);
		break;
	case RH:
	{
		BSTree rd = lc->rchild;
		switch (rd->bf)
		{
		case LH:
			lc->bf = EH;
			(*T)->bf = RH;
			break;
		case EH:
			lc->bf= (*T)->bf = EH;
			break;
		case RH:
			lc->bf = LH;
			(*T)->bf = EH;
			break;
		default:
			break;
		}
		rd->bf = EH;
		L_Rotate(&((*T)->lchild));
		R_Rotate(T);
		break;
	}
	default:
		break;
	}
}
static void RightBalance(BSTree* T)
{
	BSTree rc = (*T)->rchild;
	switch (rc->bf)
	{
	case RH:
		rc->bf = EH;
		(*T)->bf = EH;
		L_Rotate(T);
		break;
	case LH:
	{
		BSTree ld = rc->lchild;
		switch (ld->bf)
		{
		case LH:
			rc->bf = RH;
			(*T)->bf = EH;
			break;
		case EH:
			rc->bf = (*T)->bf = EH;
			break;
		case RH:
			rc->bf = EH;
			(*T)->bf = LH;
			break;
		default:
			break;
		}
		ld->bf = EH;
		R_Rotate(&((*T)->rchild));
		L_Rotate(T);
		break;
	}
	default:
		break;
	}
}
static Status InsertAVL_Main(BSTree* T, ElemType e, int* taller)
{
	if (!(*T))
	{
		if (!(*T = (BSTree)malloc(sizeof(BSTNode))))
			exit(OVERFLOW);
		(*T)->data = e;
		(*T)->bf = EH; 
		(*T)->lchild = (*T)->rchild = NULL;
		*taller = TRUE;
		return TRUE;
	}
	if ((*T)->data == e)
	{
		*taller = FALSE;
		return FALSE;
	}
	if ((*T)->data>e)
	{
		if (!InsertAVL_Main(&((*T)->lchild), e, taller))
			return FALSE;
		if (*taller)
		{
			switch ((*T)->bf)
			{
			case LH:
				LeftBalance(T);
				*taller = FALSE;
				break;
			case EH:
				(*T)->bf = LH;
				*taller = TRUE;
				break;
			case RH:
				(*T)->bf = EH;
				*taller = FALSE;
				break;
			default:
				break;
			}
		}
	}
	else {
		if (!InsertAVL_Main(&((*T)->rchild), e, taller))
			return FALSE;
		if (*taller)
		{
			switch ((*T)->bf)
			{
			case LH:
				(*T)->bf = EH;
				*taller = FALSE;
				break;
			case EH:
				(*T)->bf = RH;
				*taller = TRUE;
				break;
			case RH:			
				RightBalance(T);
				*taller = FALSE;
				break;
			default:
				break;
			}
		}
	}
	return TRUE;
}
Status InsertAVL(BSTree* T, ElemType e)
{
	int taller = FALSE;
	return InsertAVL_Main(T, e, &taller);
}

static void R_RotateRB(RBTree* tree, PRBNode* T)
{
	RBNode *p = (*T)->lchild;
	(*T)->lchild = p->rchild;
	if (p->rchild != tree->nil)
		p->rchild->parent = (*T);
	p->rchild = (*T);
	p->parent = (*T)->parent;
	(*T)->parent = p;
	*T = p;
}
static void L_RotateRB(RBTree* tree, PRBNode* T)
{
	RBNode *p = (*T)->rchild;
	(*T)->rchild = p->lchild;
	if (p->lchild != tree->nil)
		p->lchild->parent = (*T);
	p->lchild = (*T);
	p->parent = (*T)->parent;
	(*T)->parent = p;
	*T = p;
}
static void InsertRB_fixup(RBTree* tree, PRBNode T)
{
	PRBNode z = T,y=NULL;
	while (z->parent->color==RN)
	{
		if (z->parent==z->parent->parent->lchild)
		{
			y = z->parent->parent->rchild;
			if (y->color == RN)
			{
				z->parent->color = BN;
				y->color = BN;
				z->parent->parent->color = RN;
				z = z->parent->parent;
			}
			else 
			{
				if (z == z->parent->rchild)
				{
					z = z->parent;
					L_RotateRB(tree, &(z->parent->lchild));
				}
				z->parent->color = BN;
				z->parent->parent->color = RN;
				if (z->parent->parent== tree->root)
					R_RotateRB(tree, &(tree->root));
				else if (z->parent->parent->parent->lchild == z->parent->parent)
					R_RotateRB(tree, &(z->parent->parent->parent->lchild));
				else
					R_RotateRB(tree, &(z->parent->parent->parent->rchild));	
			}	
		}
		else {
			y = z->parent->parent->lchild;
			if (y->color == RN)
			{
				z->parent->color = BN;
				y->color = BN;
				z->parent->parent->color = RN;
				z = z->parent->parent;
			}
			else 
			{
				if (z == z->parent->lchild)
				{
					z = z->parent;
					R_RotateRB(tree, &(z->parent->rchild));
				}
				z->parent->color = BN;
				z->parent->parent->color = RN;
				if (z->parent->parent == tree->root)
					L_RotateRB(tree, &(tree->root));
				else if (z->parent->parent->parent->lchild == z->parent->parent)
					L_RotateRB(tree, &(z->parent->parent->parent->lchild));
				else
					L_RotateRB(tree, &(z->parent->parent->parent->rchild));
			}
		}
	}
	tree->root->color = BN;
}

void initRBTree(RBTree* T)
{
	if (!T)
	{
		return ;
	}
	T->root = T->nil= malloc(sizeof(RBNode));
	T->root->data = 0;
	T->root->lchild = T->root->rchild = T->root->parent = NULL;
	T->root->color= BN;
	return;
}
RBNode* InsertRBTree(RBTree* T, ElemType e)
{
	if (!T)
	{
		return NULL;
	}
	if (!T->root || !T->nil)
	{
		initRBTree(T);
	}
	if (T->root==T->nil)
	{
		T->root = malloc(sizeof(RBNode));
		T->root->data = e;	
		T->root->parent = T->nil;
		T->root->lchild = T->root->rchild = T->nil;
		T->root->color =BN;
		return T->root;
	}
	RBNode* p = T->root, *p1 = T->root->parent;
	while (p !=T->nil)
	{	
		if (p->data == e)
			return p;
		p1 = p;
		p =(p->data > e ? p->lchild : p->rchild);
	}
	if (!(p = malloc(sizeof(RBNode))))
		exit(OVERFLOW);
	p->parent = p1;
	p->color = RN;
	p->data = e;
	p->lchild = p->rchild = T->nil;
	if (e > p1->data)
	{
		p1->rchild = p;	
	}
	else {
		p1->lchild = p;
	}
	InsertRB_fixup(T, p);
	return p;
}

static void RBDeleteFixup(RBTree* tree, RBNode* T)
{
	RBNode* w=NULL;
	while (T!=tree->root&&T->color==BN)
	{
		if (T == T->parent->lchild)
		{
			w = T->parent->rchild;
			if (w->color==RN)
			{
				w->color = BN;
				w->parent->color = RN;
				if (T->parent == tree->root)
					L_RotateRB(tree, &(tree->root));
				else if (T->parent->parent->lchild == T->parent)
					L_RotateRB(tree, &(T->parent->parent->lchild));
				else
					L_RotateRB(tree, &(T->parent->parent->rchild));
				w = T->parent->rchild;
			}
			if (w->lchild->color == BN && w->rchild->color == BN)
			{
				w->color = RN;
				T = T->parent;
			}
			else
			{
				if (w->rchild->color == BN)
				{
					w->lchild->color = BN;
					w->color = RN;
					R_RotateRB(tree, &(T->parent->rchild));
					w = T->parent->rchild;
				}
				w->color = T->parent->color;
				T->parent->color = BN;
				w->rchild->color = BN;
				if (T->parent == tree->root)
					L_RotateRB(tree, &(tree->root));
				else if (T->parent->parent->lchild == T->parent)
					L_RotateRB(tree, &(T->parent->parent->lchild));
				else
					L_RotateRB(tree, &(T->parent->parent->rchild));
				T = tree->root;
			}
		}
		else 
		{
			w = T->parent->lchild;
			if (w->color == RN)
			{
				w->color = BN;
				w->parent->color = RN;
				if (T->parent == tree->root)
					R_RotateRB(tree, &(tree->root));
				else if (T->parent->parent->lchild == T->parent)
					R_RotateRB(tree, &(T->parent->parent->lchild));
				else
					R_RotateRB(tree, &(T->parent->parent->rchild));
				w = T->parent->lchild;
			}
			if (w->lchild->color == BN && w->rchild->color == BN)
			{
				w->color = RN;
				T = T->parent;
			}
			else
			{
				if (w->lchild->color == BN)
				{
					w->rchild->color = BN;
					w->color = RN;
					L_RotateRB(tree, &(T->parent->lchild));
					w = T->parent->lchild;
				}
				w->color = T->parent->color;
				T->parent->color = BN;
				w->lchild->color = BN;
				if (T->parent == tree->root)
					R_RotateRB(tree, &(tree->root));
				else if (T->parent->parent->lchild == T->parent)
					R_RotateRB(tree, &(T->parent->parent->lchild));
				else
					R_RotateRB(tree, &(T->parent->parent->rchild));
				T = tree->root;
			}
		}
	}
	T->color = BN;
}
static PRBNode RBdeleteElem(RBTree* tree,PRBNode* T)
{
	if (!tree)
		return;
	PRBNode q = *T,ret=q;
	PRBNode s = NULL;
	int color = q->color;
	PRBNode x = NULL;
	if (((*T)->lchild)==tree->nil)
	{
		((*T)->rchild)->parent = (*T)->parent;
		(*T) =x= (*T)->rchild;	
	//	free(q);
	}else if (((*T)->rchild)==tree->nil)
	{
		(*T)->lchild->parent = (*T)->parent;
		(*T) =x= (*T)->lchild;
		//free(q);
	}
	else {
		s = q->lchild;
		while (s->rchild != tree->nil)
		{
			q = s;
			s = s->rchild;
		}
		ElemType tem = (*T)->data;
		(*T)->data = s->data;
		s->data = tem;
		if (q == (*T))
			q->lchild = s->lchild;
		else
			q->rchild = s->lchild;
		s->lchild->parent = q;
		color = s->color;
		x = s->lchild;
		ret = s;
	//	free(s);
	}
	if (color == BN)
		RBDeleteFixup(tree,x);
	return ret;
}

PRBNode DeleteRBTree(RBTree* tree, ElemType e)
{
	if (tree ==NULL)
		return NULL;
	PRBNode p = tree->root;
	while(p!= tree->nil)
	{
		if (p->data == e)
		{
			if (p == tree->root)
				return RBdeleteElem(tree, &(tree->root));
			else if (p = p->parent->lchild)
				return RBdeleteElem(tree, &(p->parent->lchild));
			else
				return RBdeleteElem(tree, &(p->parent->rchild));
		}
		else
			p = (e > p->data ? p->rchild : p->lchild);
	}
	return NULL;
}
Status SearchRBTree(RBTree T, ElemType key, PRBNode *p)
{
	PRBNode q = T.root;
	while (q != T.nil)
	{
		*p =q;
		if (q->data == key)
			return TRUE;
		q = (q->data > key ? q->lchild : q->rchild);
	}
	return FALSE;
}