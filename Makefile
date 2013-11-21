main : main.c
	gcc -std=c99 -pthread -o main main.c

clean :
	rm main
