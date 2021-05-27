/*----Marcel Valent----
------FIIT STU BA -----
------LS 2020/2021-----*/
#include <stdio.h>
#include <stdlib.h>

void* zaciatok;
void memory_init(void* ptr, unsigned int size)
{
	zaciatok = ptr;
	*(int*)zaciatok = size;	//Zap�sanie ve�kosti do prv�ch 4 bytov
	*(int*)((char*)zaciatok + sizeof(int)) = 3 * sizeof(int);	//Pointer na prv� vo�n� velkos�
	*(int*)((char*)zaciatok + 2 * sizeof(int)) = size - 2 * sizeof(int);	//Zap�eme ve�kos� prvej vo�nej pam�te
	*(int*)((char*)zaciatok + 3 * sizeof(int)) = -1;	//Pointer na druh� vo�n� ve�kos�
}
void* memory_alloc(unsigned int size)
{
	if (size < 4)  //Zarovnanie najmenej na 4 byt;
	{
		size = 4;
	}
	if (*(int*)((char*)zaciatok + sizeof(int)) == -1)//Ak nie je dostupn� �iadny vo�n� blok tak return
		return NULL;
	int cislo = *(int*)((char*)zaciatok + sizeof(int));
	int temp = sizeof(int); //Pointer na posledn� - next


	do
	{
		if (*(int*)((char*)zaciatok + cislo - sizeof(int)) >= (size + sizeof(int)) && *(int*)((char*)zaciatok + cislo - sizeof(int)) > 0)//Ak toto miesto vyhovuje tak
		{
			if (*(int*)((char*)zaciatok + cislo - sizeof(int)) - (size + sizeof(int)) >= 8 && (cislo + size + sizeof(int)) <= *(int*)zaciatok)//Vytvor�me nov� part�ciu ak zostalo viac ako 8 bytov a nepresahujeme dan� pam�
			{
				*(int*)((char*)zaciatok + cislo + size) = *(int*)((char*)zaciatok + cislo - sizeof(int)) - (size + sizeof(int)); //Nastav�me ve�kos� nov�ho bloku
				*(int*)((char*)zaciatok + cislo - sizeof(int)) = size + sizeof(int);//Zmen��me aktu�lnu ve�kos�
				*(int*)((char*)zaciatok + cislo + size + sizeof(int)) = *(int*)((char*)zaciatok + cislo);//Zap�eme next
				*(int*)((char*)zaciatok + temp) = cislo + size + sizeof(int);//Prep�eme next minul�ho bloku pam�te
			}
			else
			{
				*(int*)((char*)zaciatok + temp) = *(int*)((char*)zaciatok + cislo);//Prep�eme aktu�lny next na next �al�ieho vo�n�ho bloku
			}
			*(int*)((char*)zaciatok + cislo - sizeof(int)) |= 1 << 31;//Nastav�me bit na  1,�o zna�� �e je dan� pam�ov� blok je u� obsaden�
			return (void*)((char*)zaciatok + cislo);
		}
		else
		{
			if (*(int*)((char*)zaciatok + cislo) == -1)//O�etrenie pr�padu vyjdenia z pam�te
				break;
			temp = cislo;//�alej preh�ad�vame pam�
			cislo = *(int*)((char*)zaciatok + cislo);
		}
	} while (*(int*)((char*)zaciatok + cislo) != -1);
	return NULL;
}
int memory_free(void* valid_ptr)
{
	int pozicia = (char*)valid_ptr - (char*)zaciatok;
	int cislo = sizeof(int);
	int temp = cislo;
	if (*(int*)((char*)valid_ptr - sizeof(int)) >= 0)//Pokia� u� je dan� miesto uvo�nen�
	{
		return 1;
	}
	while (*(int*)((char*)zaciatok + cislo) != -1 && (cislo < pozicia || cislo == sizeof(int)))//Prijdeme na po�adovan� miesto,kde m�me uvo�ni�
	{
		temp = cislo;
		cislo = *(int*)((char*)zaciatok + cislo);
	}
	if (*(int*)((char*)zaciatok + cislo) == -1 && cislo < pozicia)//Zist�me �i vklad�me na koniec,alebo medzi dva bloky
		temp = cislo;
	*(int*)((char*)valid_ptr - sizeof(int)) ^= 1 << 31;//Prep�eme prv� bit na 0,�o zna��,�e dan� pam�ov� blok je uvo�nen�
	//Spojenie s nasleduj�cim blokom za podmienky,�e je vo�n� a nie je to koniec pam�te
	if (*(int*)((char*)valid_ptr - sizeof(int) + (*(int*)((char*)valid_ptr - sizeof(int)))) > 0 && *(int*)((char*)valid_ptr - sizeof(int) + (*(int*)((char*)valid_ptr - sizeof(int)))) < *(int*)zaciatok)
	{
		//Pozrieme ve�kos� uvo��ovan�ho bloku a n�sledne k pointeru t�to ve�kos� pri��tame. Ak je nasleduj�ci blok obsaden� tak bloky sp�ja� nebudeme.
		*(int*)(char*)valid_ptr = *(int*)((char*)valid_ptr - sizeof(int) + (*(int*)((char*)valid_ptr - sizeof(int)) + sizeof(int))); //Prepi�eme next
		*(int*)((char*)valid_ptr - sizeof(int)) += *(int*)((char*)valid_ptr - sizeof(int) + (*(int*)((char*)valid_ptr - sizeof(int)))); //Prep�eme ve�kos�
	}
	else //Ak nedok�eme dan� dva bloky spoji�
		*(int*)((char*)valid_ptr) = *(int*)((char*)zaciatok + temp);//nastav�me next
	//Spojenie s predch�dzaj�cim blokom za podmienky,�e je vo�n�
	if (temp == sizeof(int)) //AK sme na �plnom za�iatku a nem�me dostupn� previous ani ve�kos�
		{
			*(int*)((char*)zaciatok + temp) = pozicia;
		}
	else 
	{
		//Ak m�me dostupn� vo�n� predch�dzaj�ci blok tak ich spoj�me
		if ((char*)zaciatok + temp - sizeof(int) + *(int*)(((char*)zaciatok + temp - sizeof(int))) == (int*)((char*)valid_ptr - sizeof(int)))
		{
			*(int*)((char*)(char*)zaciatok + temp - sizeof(int)) += *(int*)((char*)valid_ptr - sizeof(int));//Zv���me ve�kos�
			*(int*)((char*)zaciatok + temp) = *(int*)(char*)valid_ptr;//prep�eme next
		}
		else 
		{
			*(int*)((char*)zaciatok + temp) = pozicia;//Ak ich nedok�eme spoji� tak prep�eme next
		}
	}
	return 0;
}
int memory_check(void* ptr)
{
	if (ptr == NULL)
		return 0;

	if (*(int*)zaciatok < 0)
	{
		if (*((char*)ptr - 1) < 0)
			return 0;
	}
	return 1;
}

void test(char* region, char** pointer, int minBlock, int maxBlock, int minMem, int maxMem, int testdefrag) 
{
	unsigned int var = 0;
	int rand_mem = 0;
	int random = 0;
	unsigned int alloc_num = 0;
	unsigned int malloc_num = 0;
	unsigned int alloc = 0;
	unsigned int malloc = 0;
	memset(region, 0, 100000);
	rand_mem = (rand() % (maxMem - minMem + 1)) + minMem;
	memory_init(region + 500, rand_mem);
	while (alloc <= rand_mem - minBlock)
	{
		random = (rand() % (maxBlock - minBlock + 1)) + minBlock;
		if (alloc + random > rand_mem)
			continue;
		alloc_num++;
		alloc += random;
		pointer[var] = memory_alloc(random);
		if (pointer[var])
		{
			malloc_num++;
			var++;
			malloc += random;
		}
	}
	for (int j = 0; j < var; j++)
	{
		if (memory_check(pointer[j]))
		{
			memory_free(pointer[j]);
		}
		else
		{
			printf("Error: Wrong memory check.\n");
		}
	}
	if (testdefrag) {
		do {
			pointer[var] = memory_alloc(8);
			if (pointer[var])
				var++;
		} while (pointer[var]);
		for (int j = 0; j < var; j++) {
			if (memory_check(pointer[j])) {
				memory_free(pointer[j]);
			}
			else {
				printf("Memory check went wrong.\n");
			}
		}
	}
	var = 0;
	for (int j = 0; j < var; j++)
	{
		if (memory_check(pointer[j])) 
		{
			memory_free(pointer[j]);
		}
		else 
		{
			printf("Error: Wrong memory check.\n");
		}
	}
	memset(region + 500, 0, rand_mem);	
	for (int j = 0; j < 100000; j++) 
	{
		if (region[j] != 0) 
		{
			region[j] = 0;
			printf("Memory outside of region. index: %d\n", j - 500);
		}
	}
	float result_b = 100*((float)malloc / alloc);
	float result = 100*((float)malloc_num / alloc_num);
	printf("Memory size of %d bytes: allocated %.2f%% blocks (%.2f%% bytes) successfull on %d out of %d blocks.\n", rand_mem, result, result_b, malloc_num, alloc_num);
}


int main() 
{
	/*........................................................FOR TESTING.............................................................
	.................................................PARAMETERS FOR FUNCTION "test" ..................................................
	ARE IN ORDER AS FOLLOWS: minimal block size;maximal block size; minimal memory size;maximal memory size; testdefrag (either 1 or 0)*/
	char* pointer[13000];
	char memory[100000];
	test(memory, pointer, 8, 24,50,100, 0);
	test(memory, pointer, 8, 500, 20000, 99999, 0);
	test(memory, pointer, 1000,10000,80000, 999999, 0);
	return 0;
}
