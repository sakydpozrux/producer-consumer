starter : starter.c additional.c
	gcc -std=gnu99 -pthread -o starter starter.c additional.c -lrt

clean :
	rm starter
