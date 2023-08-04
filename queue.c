#include <stdlib.h>
#include <stdio.h>

#include "queue.h"


// Function to initialize the queue
int init_queue(queue_t *queue, int size)
{
	queue->elements = malloc(sizeof(char) * size);

	queue->size = 0;
	queue->capacity = size;

	// Checking if memory allocation was successful
	if (queue->elements == NULL)
	{
		return 1;
	}

	return 0;
}

// Function to double the capacity of the queue
int double_queue_capacity(queue_t *queue)
{
	queue->capacity *= 2;

	// Reallocating memory for the queue elements with the new capacity
	queue->elements = realloc(queue->elements, sizeof(char) * queue->capacity);

	// Checking if memory reallocation was successful
	if (queue->elements == NULL)
	{
		return 1;
	}

	return 0;
}

// Function to add an element to the queue
int add_queue_element(queue_t *queue, char c)
{
	int result = 0;

	// Check if the queue is already full
	if (queue->size >= queue->capacity)
	{
		// Double the queue capacity and check if it was successful
		result = double_queue_capacity(queue);
		if (result == 1)
		{
			return 1;
		}
	}

	// Add the new element to the queue
	queue->elements[queue->size++] = c;

	return 0;
}

// Function to get the front element from the queue and remove it
char get_queue_element(queue_t *queue)
{
	int i;
	char element;

	// If the queue is empty, return null character '\0'
	if (queue->size < 1)
	{
		return '\0';
	}

	element = queue->elements[0];

	// Shift all elements one position to the front
	for (i = 0; i < queue->size - 1; i++)
	{
		queue->elements[i] = queue->elements[i + 1];
	}

	queue->size--;

	return element;
}

// Function to print the elements in the queue
void print_queue(queue_t *queue)
{
	int i;

	// Print each element in the queue along with its index
	for (i = 0; i < queue->size; i++)
	{
		printf("index: %d, value: %c\n", i, queue->elements[i]);
	}
}

// Function to free the memory allocated for the queue elements
void free_queue(queue_t *queue)
{
	free(queue->elements);
}

