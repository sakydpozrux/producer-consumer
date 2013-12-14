starter : starter.c additional.c producer
	gcc -std=gnu99 -pthread -o starter starter.c additional.c -lrt

producer : producer.c
	gcc -std=gnu99 -pthread -o producer producer.c additional.c -lrt

clean :
	rm starter producer consumer
