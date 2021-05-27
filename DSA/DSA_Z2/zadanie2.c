//Marcel Valent
//FIIT STU LS 2020/2021
//DSA
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "zadanie2.h"

#define INSERT 1
#define SEARCH 0
//Zavolanie prevzateho RB stromu
void CallRB(double* timeTogether, int num, unsigned long long *RBSize, char insert)
{
	LARGE_INTEGER start, end, tmp;

	if (insert)
	{
		QueryPerformanceFrequency(&tmp);
		QueryPerformanceCounter(&start);
		*RBSize += insert_RB(num, num);
		QueryPerformanceCounter(&end);
	}
	else
	{
		QueryPerformanceFrequency(&tmp);
		QueryPerformanceCounter(&start);
		if (get_key_RB(num)) printf("not found RB\n");
		QueryPerformanceCounter(&end);
	}

	*timeTogether += (double)(end.QuadPart - start.QuadPart) / tmp.QuadPart;
}
//Zavolanie prevzatej hashovacej tabulky
void CallNotMyHT(double* timeTogether, int num, unsigned long long *NotMyHTSize, char insert)
{
	LARGE_INTEGER start, end, tmp;
	char *tmp2 = malloc(31);
	sprintf(tmp2, "%d", num);
	if (insert)
	{
		QueryPerformanceFrequency(&tmp);
		QueryPerformanceCounter(&start);
		*NotMyHTSize = hashtbl_insert_first(tmp2, tmp2);
		QueryPerformanceCounter(&end);
	}
	else
	{
		QueryPerformanceFrequency(&tmp);
		QueryPerformanceCounter(&start);
		if (hashtbl_get(tmp2)) printf("not found NMHT\n");
		QueryPerformanceCounter(&end);
	}

	*timeTogether += (double)(end.QuadPart - start.QuadPart) / tmp.QuadPart;
	free(tmp2);
}
//Zavolanie mojej implement·cie AVL bin·rneho stromu
void CallAVL(double* timeTogether, int num, unsigned long long *AVLSize, char insert)
{
	LARGE_INTEGER start, end, tmp;

	if (insert)
	{
		QueryPerformanceFrequency(&tmp);
		QueryPerformanceCounter(&start);
		*AVLSize += InsertAVL(num);
		QueryPerformanceCounter(&end);

	}
	else
	{
		QueryPerformanceFrequency(&tmp);
		QueryPerformanceCounter(&start);
		if (SearchAVL(num)) printf("not found AVL\n");
		QueryPerformanceCounter(&end);
	}

	*timeTogether += (double)(end.QuadPart - start.QuadPart) / tmp.QuadPart;
}
//Zavolanie mojej implement·cie hashovacej tabuæky
void CallMyHT(double* timeTogether, int num, unsigned long long *MyHTSize, char insert)
{
	LARGE_INTEGER start, end, tmp;

	if (insert)
	{
		QueryPerformanceFrequency(&tmp);
		QueryPerformanceCounter(&start);
		*MyHTSize = InsertMyHT(num);
		QueryPerformanceCounter(&end);

	}
	else
	{
		QueryPerformanceFrequency(&tmp);
		QueryPerformanceCounter(&start);
		//if (SearchMyHT(num)) printf("not found MyHT\n");
		QueryPerformanceCounter(&end);
	}

	*timeTogether += (double)(end.QuadPart - start.QuadPart) / tmp.QuadPart;
}
//Tento testovaË sl˙ûi na randomn˝ test vloûenia(insert) a vyhæad·vania(search) v bin·rnych stromoch a hashovacÌch tabulk·ch
void RandomTest(int max,int debugCount)
{
	unsigned long long NotMyHTSize = 0;
	unsigned long long RBSize = 0;
	unsigned long long AVLSize = 0;
	unsigned long long MyHTSize = 0;
	double timeTogetherRB = 0;
	double timeTogetherNMHT = 0;
	double timeTogetherAVL = 0;
	double timeTogetherMyHT = 0;
	srand(time(0));	
	double **timeElapsed = malloc(10 * sizeof(double*));
	for (int i = 0; i < 10; i++)
	{
		timeElapsed[i] = calloc((max + debugCount - 1) / debugCount, sizeof(double));
	}
	int averageCount = 0;
	while (averageCount < 3)
	{
		timeTogetherRB = 0;
		timeTogetherNMHT = 0;
		timeTogetherAVL = 0;
		timeTogetherMyHT = 0;
		NotMyHTSize = 0;
		RBSize = 0;
		AVLSize = 0;
		MyHTSize = 0;
		int	*arrayForSearch = malloc(max * sizeof(int));
		long long arrayCounter = 0;
		for (int i = 0; i < max; i++)
		{
			int randomNum = rand() % 1000000;
			arrayForSearch[i] = randomNum;
			CallRB(&timeTogetherRB, randomNum, &RBSize, INSERT);
			CallNotMyHT(&timeTogetherNMHT, randomNum, &NotMyHTSize, INSERT);
			CallAVL(&timeTogetherAVL, randomNum, &AVLSize, INSERT);
			CallMyHT(&timeTogetherMyHT, randomNum, &MyHTSize, INSERT);

			if (i != 0 && i%debugCount == 0)
			{
				timeElapsed[1][arrayCounter] += timeTogetherRB;
				timeElapsed[2][arrayCounter] += timeTogetherNMHT;
				timeElapsed[3][arrayCounter] += timeTogetherAVL;
				timeElapsed[4][arrayCounter] += timeTogetherMyHT;
				arrayCounter++;
			}
		}
		timeElapsed[1][arrayCounter] += timeTogetherRB;
		timeElapsed[2][arrayCounter] += timeTogetherNMHT;
		timeElapsed[3][arrayCounter] += timeTogetherAVL;
		timeElapsed[4][arrayCounter] += timeTogetherMyHT;
		timeTogetherRB = 0;
		timeTogetherNMHT = 0;
		timeTogetherAVL = 0;
		timeTogetherMyHT = 0;
		arrayCounter = 0;
		int j = 0;
		for (int i = max - 1; i >= 0; i--, j++)
		{
			CallRB(&timeTogetherRB, arrayForSearch[i], &RBSize, SEARCH);
			CallNotMyHT(&timeTogetherNMHT, arrayForSearch[i], &NotMyHTSize, SEARCH);
			CallAVL(&timeTogetherAVL, arrayForSearch[i], &AVLSize, SEARCH);
			CallMyHT(&timeTogetherMyHT, arrayForSearch[i], &MyHTSize, SEARCH);

			if (j != 0 && j%debugCount == 0)
			{
				timeElapsed[1 + 5][arrayCounter] += timeTogetherRB;
				timeElapsed[2 + 5][arrayCounter] += timeTogetherNMHT;
				timeElapsed[3 + 5][arrayCounter] += timeTogetherAVL;
				timeElapsed[4 + 5][arrayCounter] += timeTogetherMyHT;
				arrayCounter++;
			}
		}
		timeElapsed[1 + 5][arrayCounter] += timeTogetherRB;
		timeElapsed[2 + 5][arrayCounter] += timeTogetherNMHT;
		timeElapsed[3 + 5][arrayCounter] += timeTogetherAVL;
		timeElapsed[4 + 5][arrayCounter] += timeTogetherMyHT;
		EraseRBTree();
		hashtbl_destroy();
		FreeAVLTree();
		FreeMyHT();
		free(arrayForSearch);
		averageCount++;
	}
	//V˝pis Ëasovej a pam‰ùovej n·roËnosti vkladania do hashovacÌch tabuliek a bin·rnych stromov
	for (int i = 0; i < (max + debugCount - 1) / debugCount; i++)
	{
		int position = (i + 1)*debugCount;

		if (position > max)
			position = max;

		printf("[RANDOM %d] RB Insert\n", position);
		printf("Time taken: %f seconds\n", timeElapsed[1][i] / 3);
		printf("Space used: %lld Bytes\n\n", RBSize);
		printf("[RANDOM %d] AVL Insert\n", position);
		printf("Time taken: %f seconds\n", timeElapsed[3][i] / 3);
		printf("Space used: %lld Bytes\n\n", AVLSize);
		printf("[RANDOM %d] NotMyHT Insert\n", position);
		printf("Time taken: %f seconds\n", timeElapsed[2][i] / 3);
		printf("Space used: %lld Bytes\n\n", NotMyHTSize);
		printf("[RANDOM %d] MyHT Insert\n", position);
		printf("Time taken: %f seconds\n", timeElapsed[4][i] / 3);
		printf("Space used: %lld Bytes\n\n", MyHTSize);
	}
    //V˝pis Ëasu vyhæad·vania v hashovacÌch tabuæk·ch a bin·rnych stromoch
	for (int i = 0; i < (max + debugCount - 1) / debugCount; i++)
	{
		int position = (i + 1)*debugCount;

		if (position > max)
			position = max;

		printf("[RANDOM %d] RB Search\n", position);
		printf("Time taken: %f seconds\n\n", timeElapsed[1 + 5][i] / 3);
		printf("[RANDOM %d] NotMyHT Search\n", position);
		printf("Time taken: %f seconds\n\n", timeElapsed[2 + 5][i] / 3);
		printf("[RANDOM %d] AVL Search\n", position);
		printf("Time taken: %f seconds\n\n", timeElapsed[3 + 5][i] / 3);
		printf("[RANDOM %d] MyHT Search\n", position);
		printf("Time taken: %f seconds\n\n", timeElapsed[4 + 5][i] / 3);
	}
	for (int i = 0; i < 10; i++)
	{
		free(timeElapsed[i]);
	}
	free(timeElapsed);
}

int main()
{	//For testing, following arguments need to be passed: max , debugCount
	RandomTest(1000,1);
	return 0;
}