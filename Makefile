starter : starter.c producers_supervisor.c consumers_supervisor.c shared_mem.c help.c argsinit.c producer consumer
	gcc -Wall -Wextra -std=gnu99 -pthread -o starter starter.c producers_supervisor.c shared_mem.c help.c argsinit.c consumers_supervisor.c -lrt

producer : producer.c shared_mem.c
	gcc -Wall -Wextra -std=gnu99 -pthread -o producer producer.c shared_mem.c -lrt

consumer : consumer.c shared_mem.c
	gcc -Wall -Wextra -std=gnu99 -pthread -o consumer consumer.c shared_mem.c -lrt

clean :
	rm starter producer consumer
