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

void init(stack_t *stack) {
	stack->head = NULL;
	stack->top = NULL;
	stack->size = 0;
}

int push(stack_t *stack, uint16_t data) {
	if(stack->head == NULL) {
		stackData_t *new = (stackData_t *)malloc(sizeof(stackData_t));
		if(new != NULL) {
			new->next = NULL;
			new->data = data;
			stack->head = new;
			stack->top = new;
			++stack->size;
		} else {
			return 0;
		}
	} else {
		stackData_t *cursor = stack->head;
		while(cursor->next != NULL) {
			cursor = (stackData_t *)cursor->next;
		}
		stackData_t *new = (stackData_t *)malloc(sizeof(stackData_t));
		if(new != NULL) {
			new->next = NULL;
			new->data = data;
			cursor->next = (struct stackData_t *)new;
			stack->top = new;
			++stack->size;
		} else {
			return 0;
		}
	}
	return 1;
}

int pop(stack_t *stack) {
	if(stack->head == NULL) {
		return 0;
	} else if (stack->head->next == NULL) {
		stackData_t *cursor = stack->head;
		free(cursor);
		stack->head = NULL;
		stack->top = NULL;
		stack->size = 0;
	} else {
		stackData_t *prev = stack->head;
		stackData_t *cursor = stack->head;
		while(cursor->next != NULL) {
			prev = cursor;
			cursor = (stackData_t *)cursor->next;
		}
		free(cursor);
		prev->next = NULL;
		stack->top = prev;
		--stack->size;
	}
	return 1;
}

int peek(stack_t *stack, uint16_t *data) {
	if(stack->top != NULL) {
		*data = stack->top->data;
		return 1;
	} else {
		*data = 0;
		return 0;
	}
}

int print(stack_t *stack) {
	int i = 0;
	if(stack->head == NULL) {
		return 0;
	} else {
		stackData_t *cursor = stack->head;
		while(cursor != NULL) {
			printf("Print: Stack Value at %d: %d\n", ++i, cursor->data);
			cursor = (stackData_t *)cursor->next;
		}
	}
	return 1;
}

int peekTraverse(stack_t *stack, uint16_t *data) {
	if(stack->head == NULL) {
		*data = 0;
		return 0;
	} else {
		stackData_t *cursor = stack->head;
		while(cursor->next != NULL) {
			cursor = (stackData_t *)cursor->next;
		}
		*data = cursor->data;
	}
	return 1;
}

uint16_t getStackSize(stack_t *stack) {
	if(stack != NULL) {
		return stack->size;
	}

	return 0;
}

