#include "test.h"
#include <stdio.h>

void result_kl(float __key, int __search)
{

	switch (__search)
	{

		case __LINEAR:
			printf("A busca sequencial demorou %f segundos para ser executada\n", __key);
			return;
		case __BINARIA:
			printf("A busca binaria demorou %f segundos para ser executada\n", __key);
			return;
		case __BUBBLE:
			printf("Bubble demorou %f segundos\n", __key);
			return;
		case __INSERTION:
			printf("Insertion demorou %f segundos\n", __key);
			return;
		case __QUICK:
			printf("Quick demorou %f segundos\n", __key);
			return;
		case __MEDIA__BINARIA:
			printf("Busca binária demorou %f segundos em média para ser executada\n", __key / 30);
			return;
		case __MEDIA__LINEAR:
			printf("Busca sequencial demorou %f segundos em média para ser executada\n", __key / 30);
			return;
		case __LINEAR__VETOR:
			printf("A busca sequencial demorou %f segundos para ser executada no vetor\n", __key);
			return;
		case __LINEAR__LIST:
			printf("A busca sequencial demorou %f segundos para ser executada na lista\n", __key);
			return;
		case __MEDIA__VETOR:
			printf("A busca sequencial demorou %f segundos em média para ser executada no vetor\n", __key / 30);
			return;
		case __MEDIA__LIST:
			printf("A busca sequencial demorou %f segundos em média para ser executada na lista\n", __key / 30);
			return;

	}

}