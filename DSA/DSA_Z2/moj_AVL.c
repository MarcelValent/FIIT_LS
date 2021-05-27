//Marcel Valent
//FIIT STU LS 2020/2021
//DSA
#include <stdio.h>
#include <stdlib.h>
//zadefinovanie struktury AVL stromu
typedef struct AVLTree {
	int num;
	short height;
	struct AVLTree *left;
	struct AVLTree *right;
}AVLtree;

int SearchAVL(int numInc);
int InsertAVL(int num);
void FreeAVLTree();
void FreeMyAVLTree(AVLtree *tree);
AVLtree *mainTree = NULL;
int SearchMyAVL(AVLtree *treeInc, int num);
int InsertMyAVL(int numInc, AVLtree **treeInc);
// uvolnenie AVL stromu
void FreeAVLTree()
{
	FreeMyAVLTree(mainTree);
	mainTree = NULL;
}
void FreeMyAVLTree(AVLtree *tree)
{
	if (tree == NULL)
		return;
	if (tree->left != NULL)
		FreeMyAVLTree(tree->left);
	if (tree->right != NULL)
		FreeMyAVLTree(tree->right);
	free(tree);
}
//hladanie v AVL strome
int SearchAVL(int num)
{
	return SearchMyAVL(mainTree, num);
}
int SearchMyAVL(AVLtree *treeInc, int num)
{

	if (treeInc == NULL)
		return 1;

	if (num < treeInc->num)
	{
		return SearchMyAVL(treeInc->left, num);
	}
	else
		if (num > treeInc->num)
		{
			return SearchMyAVL(treeInc->right, num);
		}
		else
			return 0;
}
int GetMax(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}
//Ziskanie vysky stromu
int GetHeight(AVLtree *treeInc)
{
	if (treeInc == NULL)
		return -1;
	else
		return treeInc->height;
}
//Nastavenie vysky stromu
void SetHeight(AVLtree *treeInc)
{
	if (treeInc != NULL)
	{
		if ((treeInc)->left != NULL || (treeInc)->right != NULL)
		{
			(treeInc)->height = GetMax(GetHeight((treeInc)->left), GetHeight((treeInc)->right)) + 1;
		}
		else
		{
			(treeInc)->height = 0;
		}
	}
}
//Nasledovne kody riesia rotáciu AVL stromu
//Lava rotacia
AVLtree* RotateLeft(AVLtree *treeInc)
{
	AVLtree *tmp = (treeInc)->right;
	(treeInc)->right = (tmp)->left;
	(tmp)->left = treeInc;
	SetHeight((tmp)->left);
	SetHeight((tmp)->right);
	SetHeight(tmp);
	return tmp;
}
//Prava rotacia
AVLtree* RotateRight(AVLtree *treeInc)
{
	AVLtree *tmp = (treeInc)->left;
	(treeInc)->left = (tmp)->right;
	(tmp)->right = treeInc;
	SetHeight((tmp)->left);
	SetHeight((tmp)->right);
	SetHeight(tmp);
	return tmp;
}
//Lavo-prava rotacia
AVLtree* RotateLeftRight(AVLtree *treeInc)
{
	(treeInc)->right = RotateRight((treeInc)->right);
	treeInc = RotateLeft(treeInc);
	return treeInc;
}
//Pravo-lava rotacia
AVLtree* RotateRightLeft(AVLtree *treeInc)
{
	(treeInc)->left = RotateLeft((treeInc)->left);
	treeInc = RotateRight(treeInc);
	return treeInc;
}
//Ziskanie vysky potrebnej na balancovanie stromu
int GetSpecialHeight(AVLtree *treeInc)
{
	if (treeInc == NULL)
		return 0;
	else
		return treeInc->height + 1;
}
//Vypocet vybalancovania stromu
int GetBalance(AVLtree *treeInc)
{
	if (treeInc == NULL)
		return 0;
	else
		return GetSpecialHeight(treeInc->left) - GetSpecialHeight(treeInc->right);
}
//Vlozenie do AVL stromu
int InsertAVL(int num)
{
	return InsertMyAVL(num, &mainTree);
}
int InsertMyAVL(int numInc, AVLtree **treeInc)
{
	int tmp;
	if (*treeInc == NULL)
	{
		(*treeInc) = malloc(sizeof(AVLtree));
		(*treeInc)->left = NULL;
		(*treeInc)->right = NULL;
		(*treeInc)->num = numInc;
		(*treeInc)->height = 0;
		return sizeof(AVLtree);
	}
	else
	{
		if (numInc > (*treeInc)->num)
		{
			tmp = InsertMyAVL(numInc, &(*treeInc)->right);
			int mainBalance = abs(GetBalance(*treeInc));
			if (mainBalance >= 2)
			{
				int balance = GetBalance((*treeInc)->right);
				if (balance < 0)
				{
					*treeInc = RotateLeft(*treeInc);
				}
				else
					if (balance > 0)
					{
						*treeInc = RotateLeftRight(*treeInc);
					}
			}
		}
		else
			if (numInc <= (*treeInc)->num)
			{
				tmp = InsertMyAVL(numInc, &(*treeInc)->left);
				int mainBalance = abs(GetBalance(*treeInc));
				if (mainBalance >= 2)
				{
					int balance = GetBalance((*treeInc)->left);
					if (balance > 0)
					{
						*treeInc = RotateRight(*treeInc);
					}
					else
						if (balance < 0)
						{
							*treeInc = RotateRightLeft(*treeInc);
						}
				}
			}
			else
				tmp = 0;
	}
	SetHeight(*treeInc);
	return tmp;
}




