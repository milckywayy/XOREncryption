#include <stdio.h>
#include <unistd.h>

#include "xor.h"


int main(int argc, char **argv) 
{
	int opt;

	char *file_path= NULL;
	char *key = NULL;

	while ((opt = getopt(argc, argv, "f:k:")) != -1)
	{
		switch (opt)
		{
			case 'f':
				file_path = optarg;
				break;
			case 'k':
				key = optarg;
				break;
			case '?':
				if (optopt == 'f' || optopt == 'k')
				{
                    			fprintf(stderr, "Option -%c requires an argument.\n", optopt);
				}
				else
				{
			    		fprintf(stderr, "Unknown option %c.\n", optopt);
				}
				return 1;
			default:
				fprintf(stderr, "Invalid option.\n");
				return 1;
		}
	}
	
	if (file_path == NULL || key == NULL)
	{
		fprintf(stderr, "Empty argument.\n");
		return 1;
	}

	switch (xor(file_path, key)) 
	{
		case 1:
			fprintf(stderr, "Memory error.\n");
			return 2;
		case 2:
			fprintf(stderr, "Couldn't read %s file.\n", file_path);
			return 3;
		case 3:
			fprintf(stderr, "Couldn't write to %s file.\n", file_path);
			return 4;
	}

	return 0;
}
