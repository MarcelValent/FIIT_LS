//Marcel Valent
//FIIT STU LS 2020/2021
//DSA
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define FACTOR  0.75
//zadefinovanie hashovacej tabulky
typedef struct MyTable { 
	int size;
	int usedSize;
	int *elements;
}myTable;
myTable *myHTable = NULL;
//vytvorenie hashovacej tabulky
int CreateTable(int sizeInc) 
{
	if (myHTable == NULL)
	{
		myHTable = malloc(sizeof(myTable));
		myHTable->size = sizeInc;
		myHTable->usedSize = 0;
		myHTable->elements = calloc(sizeInc, sizeof(int));
	}
	return sizeof(myHTable);
}
//hashovacia funkcia
int HashFunction(int num, unsigned long long attempt, int size)
{
	return  (unsigned long long)(num + attempt) % size;
}
//vlozenie hashovacej funkcie
myTable* InsertMyHTFunc(myTable *tmpTable, int number)
{
	unsigned long long attempt = 0;
	while (1)
	{
		int tmpEh = HashFunction(number, attempt, tmpTable->size);
		if (tmpTable->elements[tmpEh] != 0)
		{
			attempt++;
		}
		else
		{
			int tmpEh = HashFunction(number, attempt, tmpTable->size);
			tmpTable->elements[tmpEh] = number;
			tmpTable->usedSize++;
			break;
		}
	}
	return tmpTable;
}
//zvacsenie hashovacej tabulky
void ResizeTable()
{
	myTable *tmpTable = malloc(sizeof(myTable));
	tmpTable->size = 2 * (myHTable->size);
	int maxElementsLoaded = myHTable->usedSize;
	tmpTable->elements = calloc(tmpTable->size, sizeof(int));
	tmpTable->usedSize = 0;
	free(myHTable->elements);
	free(myHTable);
	myHTable = tmpTable;
}
//h¾adanie v hashovacej tabulke
int SearchMyHT(int number)
{
	int i = 0;
	while (1)
	{
		if (myHTable->elements[HashFunction(number, i, myHTable->size)] == number) {
			return 0;
		}
		else
			i++;
		if (i > myHTable->size)
			return 1;
	}
}
//Vkladanie do hashovacej tabulky
int InsertMyHT(int number)
{
	if (myHTable == NULL)
		CreateTable(1000);

	InsertMyHTFunc(myHTable, number);
	if ((double)((double)myHTable->usedSize / (double)myHTable->size) > (double)FACTOR)
		ResizeTable();

	return 8+ 8*myHTable->size;
}
//Uvolnenie hashovacej tabulky
void FreeMyHT()
{
	free(myHTable->elements);
	free(myHTable);
	myHTable = NULL;
}
