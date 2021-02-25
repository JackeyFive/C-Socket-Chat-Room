do:server.c client.c
	gcc server.c -lpthread -o server
	gcc client.c -lpthread -o client

clean:
	rm server client
