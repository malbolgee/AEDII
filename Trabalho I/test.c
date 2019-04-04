#include "test.h"
#include <stdio.h>

void result(r_results *__table, int __execution__type)
{

	int i, j;
	if (__execution__type == __SEARCH__ARRAY)
	{
		
		printf("\t\tBusca Binária\t\t \t      Busca Sequencial\t\n");
		puts("---------------------------------------------------------------------------------");
		for (i = 0; i < __NUMBER__TEST; ++i)
		{

			printf("%d:\t\t %lfs\t\t |\t\t %lfs\t\t|\n", i + 1, __table->r_searchs[i][0], __table->r_searchs[i][1]);
			puts("---------------------------------------------------------------------------------");
			__table->r_searchs[30][0] += __table->r_searchs[i][0];
			__table->r_searchs[31][1] += __table->r_searchs[i][1];

		}

		printf("\n");
		puts("===================================================================================");
		printf("\t     Média B. Binária\t\t \t   Média B. Sequencial\t\n");
		printf("\t\t%lfs\t\t \t\t %lfs\t\t\n", __table->r_searchs[30][0] / __NUMBER__TEST, __table->r_searchs[31][1]) / __NUMBER__TEST;
		puts("===================================================================================");
		printf("\n\n");

	}
	else if (__execution__type == __SEARCH__ARRAY__AND__LIST)
	{

		printf("\t     Busca S. no Vetor\t\t \t      Busca S. na Lista\t\n");
		puts("---------------------------------------------------------------------------------");
		for (i = 0; i < __NUMBER__TEST; ++i)
		{

			printf("%d:\t\t %lfs\t\t |\t\t %lfs\t\t|\n", i + 1, __table->r_searchs[i][0], __table->r_searchs[i][1]);
			puts("---------------------------------------------------------------------------------");
			__table->r_searchs[30][0] += __table->r_searchs[i][0];
			__table->r_searchs[31][1] += __table->r_searchs[i][1];

		}

		printf("\n");
		puts("===================================================================================");
		printf("\t   Média B.S. no Vetor\t\t\t     Média B.S na Lista\t\n");
		printf("\t\t%lfs\t\t \t\t %lfs\t\t\n", __table->r_searchs[30][0] / __NUMBER__TEST, __table->r_searchs[31][1] / __NUMBER__TEST);
		puts("===================================================================================");
		printf("\n\n");

	}
	else if (__execution__type == __SORT)
	{

		printf("\t       BubbleSort\t      InsertionSort\t\tQuickSort\t\n");
		puts("---------------------------------------------------------------------------------");
		for (i = 0; i < __NUMBER__TEST; ++i)
		{

			printf("%d:\t\t%lfs\t|\t%lfs\t|\t%lfs\t|\n", i + 1, __table->r_sort[i][0], __table->r_sort[i][1], __table->r_sort[i][2]);
			puts("---------------------------------------------------------------------------------");
			__table->r_sort[30][0] += __table->r_sort[i][0];
			__table->r_sort[31][1] += __table->r_sort[i][1];
			__table->r_sort[32][2] += __table->r_sort[i][2];

		}

		printf("\n");
		puts("===================================================================================");
		printf("\t   Média BubbleSort\t   Média InsertionSort\t     Média QuickSort\n");
		printf("\t       %lfs\t\t%lfs\t\t %lfs\t\n", __table->r_sort[30][0] / __NUMBER__TEST, __table->r_sort[31][1] / __NUMBER__TEST, __table->r_sort[32][2] / __NUMBER__TEST);
		puts("===================================================================================");
		printf("\n\n");
		
	}

}
