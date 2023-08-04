#include <stdio.h>


int xor(char *file_path, char *key)
{
	int i;
	char c;
	int bit;

	FILE *file;

	file = fopen(file_path, "r");
	if (file == NULL)
	{
		fprintf(stderr, "Couldn't read %s file.\n", file_path);
		return 1;
	}

	while ((c = getc(file)) != EOF)
	{
		for (i = 0; i < 8; i++)
		{
			bit = (c & (1 << i)) >> i;

			printf("->%d\n", bit);
		}
	}

	return 0;
}

