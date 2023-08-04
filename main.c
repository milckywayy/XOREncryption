#include <stdio.h>
#include <unistd.h>

#include "xor.h"


// Main function that takes command line arguments.
int main(int argc, char **argv) 
{
    int opt;

    char *file_path = NULL;
    char *key = NULL;

    // Parse command line options using getopt.
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

    // Check if both file_path and key arguments have been provided.
    if (file_path == NULL || key == NULL)
    {
        fprintf(stderr, "Empty argument.\n");
        return 1;
    }

    // Call the xor function with the provided file path and key.
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

    return 0; // Return with success status if xor function completes successfully.
}

