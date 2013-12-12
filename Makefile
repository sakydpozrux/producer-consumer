main : main.c
	gcc -std=gnu99 -pthread -o main main.c -lrt

clean :
	rm main
