#include <stdlib.h>
#include <stdio.h>

#include "queue.h"


int init_queue(queue_t *queue, int size)
{
	queue->elements = malloc(sizeof(char) * size);
	queue->size = 0;
	queue->capacity = size;

	if (queue->elements == NULL)
	{
		return 1;
	}

	return 0;
}

int double_queue_capacity(queue_t *queue)
{
	queue->capacity *= 2;
	queue->elements = realloc(queue->elements, sizeof(char) * queue->capacity);
	
	if (queue->elements == NULL)
	{
		return 1;
	}

	return 0;
}

int add_queue_element(queue_t *queue, char c)
{
	int result = 0;

	if (queue->size >= queue->capacity)
	{
		result = double_queue_capacity(queue);
		if (result == 1)
		{
			return 1;
		}
	}

	queue->elements[queue->size++] = c;

	return 0;
}

char get_queue_element(queue_t *queue)
{
	int i;
	char element;

	if (queue->size < 1)
	{
		return '\0';
	}

	element = queue->elements[0];

	for (i = 0; i < queue->size - 1; i++)
	{
		queue->elements[i] = queue->elements[i + 1];
	}
	queue->size--;

	return element;
}

void print_queue(queue_t *queue) 
{
	int i;

	for (i = 0; i < queue->size; i++)
	{
		printf("index: %d, value: %c\n", i, queue->elements[i]);
	}
}

void free_queue(queue_t *queue)
{
	free(queue->elements);
}
