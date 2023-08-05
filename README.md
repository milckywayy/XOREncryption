# XOR_Encryption

Basic implementation of the XOR cipher algorithm in C that provides a command-line interface to encrypt and decrypt files using this cipher.

## Description of Files:

- main.c: The main entry point of the program. It handles command-line arguments, such as file path (-f) and key (-k), using getopt function. It then calls the xor function from xor.c with the provided file path and key.

- xor.c: Contains the implementation of the xor function, which performs the XOR encryption/decryption on a given file using the provided key. The function reads the content of the file, converts the key to its binary representation using the string_to_bin function, and then performs XOR operation on each byte in the file using the key. The encrypted/decrypted bytes are temporarily stored in a queue, and the final result is written back to the file.

- queue.c: Implements a simple queue data structure to store bytes temporarily during the encryption/decryption process. The queue supports operations such as initialization, adding elements, getting the front element, printing elements, and freeing the memory.

## Usage:
To encrypt or decrypt a file using the XOR cipher, run the program with the following command-line options:

    ./main -f <file_path> -k <key>
    
Where <file_path> is the path to the file you want to encrypt or decrypt, and <key> is the key to be used for XOR operation.

The program will then read the content of the specified file, perform the XOR operation using the provided key, and write the result back to the file.
