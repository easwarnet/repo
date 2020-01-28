/*
 ============================================================================
 Name        : StackLinkedList.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "stack.h"

void manipulatestack() {
	stack_t stack;
	uint16_t data = 0;
	uint16_t dataTr = 0;
	init(&stack);

	print(&stack);

	push(&stack, 10);
	peek(&stack, &data); 
	peekTraverse(&stack, &dataTr); 
	printf("Stack Size: %d, Top: %d, TopTr: %d\n",getStackSize(&stack), data, dataTr);
	push(&stack, 20);
	peek(&stack, &data); 
	peekTraverse(&stack, &dataTr); 
	printf("Stack Size: %d, Top: %d, TopTr: %d\n",getStackSize(&stack), data, dataTr);
	push(&stack, 30);
	peek(&stack, &data); 
	peekTraverse(&stack, &dataTr); 
	printf("Stack Size: %d, Top: %d, TopTr: %d\n",getStackSize(&stack), data, dataTr);
	push(&stack, 40);
	peek(&stack, &data); 
	peekTraverse(&stack, &dataTr); 
	printf("Stack Size: %d, Top: %d, TopTr: %d\n",getStackSize(&stack), data, dataTr);

	print(&stack);

	pop(&stack);
	peek(&stack, &data); 
	peekTraverse(&stack, &dataTr); 
	printf("Stack Size: %d, Top: %d, TopTr: %d\n",getStackSize(&stack), data, dataTr);
	pop(&stack);
	peek(&stack, &data); 
	peekTraverse(&stack, &dataTr);
	printf("Stack Size: %d, Top: %d, TopTr: %d\n",getStackSize(&stack), data, dataTr);
	pop(&stack);
	peek(&stack, &data); 
	peekTraverse(&stack, &dataTr);
	printf("Stack Size: %d, Top: %d, TopTr: %d\n",getStackSize(&stack), data, dataTr);
	pop(&stack);
	peek(&stack, &data); 
	peekTraverse(&stack, &dataTr); 
	printf("Stack Size: %d, Top: %d, TopTr: %d\n",getStackSize(&stack), data, dataTr);

	print(&stack);
}

int main(void) {

	manipulatestack();
	return EXIT_SUCCESS;
}
