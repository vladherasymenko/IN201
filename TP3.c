#include <stdio.h>
#include <stdint.h>

#define STACK_SIZE 4096

uint8_t pile1[STACK_SIZE];
uint8_t pile2[STACK_SIZE];
uint8_t pile3[STACK_SIZE];
uint8_t pile4[STACK_SIZE];

typedef void * coroutine_t;

void enter_coroutine(coroutine_t cr);

coroutine_t Test1, Test2;


void switch_coroutine(coroutine_t *p_form, coroutine_t to);


coroutine_t init_coroutine(void *stack_begin, unsigned int stack_size, void (*initial_pc)(void))
{
	char *stack_end = ((char *)stack_begin) + stack_size;
	void **ptr = stack_end;
	ptr--;
	*ptr = initial_pc;
	ptr--;
	*ptr = stack_end;
	
	for (int i = 0; i < 5; ++i)
	{	
		ptr--;	
		*ptr=0;
	}

	return ptr;
}

void funcA(void)
{
	while(1)
	{
		printf("Bonjour Thread 1\n");
		switch_coroutine(&Test1, Test2);
	}


}

void funcB(void)
{
	while(1)
	{
		printf("Bonjour Thread 2\n");
		switch_coroutine(&Test2, Test1);
	}
	

}
int main(int argc, char const *argv[])
{
	Test1 = init_coroutine(pile1, STACK_SIZE, funcA);
	Test2 = init_coroutine(pile2, STACK_SIZE, funcB);
	enter_coroutine(Test1);
	return 0;
}