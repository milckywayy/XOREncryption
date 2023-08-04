#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


char * string_to_bin(char *str)
{
	int i, j;
	int str_len = 0;
	char *result;
	
	while (*str != '\0')
	{
		str++;
		str_len++;
	}
	str -= str_len;
	
	result = malloc(sizeof(char) * (str_len * 8) + 1);

	if (result == NULL)
	{
		return NULL;
	}

	for (i = 0; i < str_len; i++)
	{
		for (j = 0; j < 8; j++)
		{
			result[(i * 8) + j] = ((str[i] >> (7 - j)) & 1) + '0';
		}
	}
	result[(i * 8) + j + 1] = '\0';

	return result;
}


int xor(char *file_path, char *key)
{
	int i;
	char c;
	char byte;

	int key_shift = 0;
	char *key_bin;

	queue_t queue;

	FILE *file;

	if ((key_bin = string_to_bin(key)) == NULL)
	{
		return 1;
	}

	if (init_queue(&(queue), 8) == 1)
	{
		free(key_bin);
		return 1;
	}

	file = fopen(file_path, "r");
	if (file == NULL)
	{
		free(key_bin);
		free_queue(&(queue));
		return 2;
	}

	while ((c = getc(file)) != EOF)
	{
		byte = 0;
		for (i = 0; i < 8; i++)
		{
			if (key_bin[key_shift] == '\0')
			{
				key_shift = 0;
			}

			byte |= (((c & (1 << (7 - i))) >> (7 - i)) ^ ((key_bin[key_shift++]) - '0')) << (7 - i);
		}
		if (add_queue_element(&(queue), byte) == 1)
		{
			fclose(file);
			free(key_bin);
			free_queue(&(queue));
			return 1;
		}
	}

	fclose(file);
	
	file = fopen(file_path, "w");
	if (file == NULL)
	{
		free(key_bin);
		free_queue(&(queue));
		return 3;
	}

	while (queue.size > 0)
	{
		fprintf(file, "%c", get_queue_element(&(queue)));
	}
	fclose(file);
	
	free(key_bin);
	free_queue(&(queue));

	return 0;
}

