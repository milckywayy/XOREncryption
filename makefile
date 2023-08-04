main.exe: main.c xor.c xor.h queue.c queue.h
	cc main.c xor.c queue.c -o main.exe
