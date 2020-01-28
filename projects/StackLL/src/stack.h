/*
 ============================================================================
 Name        : StackLinkedList.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#ifndef STACKLL
#define STACKLL
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct STACKDATA {
	uint16_t data;
	struct stackData_t *next;
}stackData_t;

typedef struct STACKINFO {
	uint16_t size;
	stackData_t *head;
	stackData_t *top;
}stack_t;

void init(stack_t *stack);
int push(stack_t *stack, uint16_t data);
int pop(stack_t *stack);
int peek(stack_t *stack, uint16_t *data);
int print(stack_t *stack);
int peekTraverse(stack_t *stack, uint16_t *data);
uint16_t getStackSize(stack_t *stack);
#endif
