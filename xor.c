#include <stdio.h>
#include <stdlib.h>

#include "queue.h"


// Function to convert a string to binary representation
char * string_to_bin(char *str)
{
	int i, j;
	int str_len = 0;
	char *result;
	
	// Calculate the length of the input string
	while (*str != '\0')
	{
		str++;
		str_len++;
	}
	str -= str_len;
	
	// Allocate memory for the binary representation of the string
	result = malloc(sizeof(char) * (str_len * 8) + 1);

	if (result == NULL)
	{
		return NULL;
	}

	// Convert each character in the string to its binary representation
	for (i = 0; i < str_len; i++)
	{
		for (j = 0; j < 8; j++)
		{
			// Store the binary representation of the character in the result array
			result[(i * 8) + j] = ((str[i] >> (7 - j)) & 1) + '0';
		}
	}
	result[(i * 8) + j + 1] = '\0'; // Null-terminate the binary string

	return result;
}

// Function to perform XOR encryption/decryption on a file
int xor(char *file_path, char *key)
{
	int i;
	char c;
	char byte;

	int key_shift = 0;
	char *key_bin;

	queue_t queue;

	FILE *file;

	// Convert the key to binary representation
	if ((key_bin = string_to_bin(key)) == NULL)
	{
		return 1;
	}

	// Initialize a queue to store the encrypted/decrypted bytes
	if (init_queue(&(queue), 8) == 1)
	{
		free(key_bin);
		return 1;
	}

	// Open the input file for reading
	file = fopen(file_path, "r");
	if (file == NULL)
	{
		free(key_bin);
		free_queue(&(queue));
		return 2;
	}

	// Perform XOR encryption/decryption on each byte in the file
	while ((c = getc(file)) != EOF)
	{
		byte = 0;
		for (i = 0; i < 8; i++)
		{
			// Cycle through the key binary representation if needed
			if (key_bin[key_shift] == '\0')
			{
				key_shift = 0;
			}

			// Perform XOR operation and construct the resulting byte
			byte |= (((c & (1 << (7 - i))) >> (7 - i)) ^ ((key_bin[key_shift++]) - '0')) << (7 - i);
		}
		// Add the encrypted/decrypted byte to the queue
		if (add_queue_element(&(queue), byte) == 1)
		{
			fclose(file);
			free(key_bin);
			free_queue(&(queue));
			return 1;
		}
	}

	fclose(file);
	
	// Open the file again for writing the encrypted/decrypted content
	file = fopen(file_path, "w");
	if (file == NULL)
	{
		free(key_bin);
		free_queue(&(queue));
		return 3;
	}

	// Write the encrypted/decrypted bytes from the queue to the file
	while (queue.size > 0)
	{
		fprintf(file, "%c", get_queue_element(&(queue)));
	}
	fclose(file);
	
	free(key_bin);
	free_queue(&(queue));

	return 0;
}

