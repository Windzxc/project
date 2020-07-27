all : server client
.PHONY : all
server : server.c
	gcc -g -o $@ $<
client : client.c
	gcc -g -o $@ $<
.PHONY : clean
clean :
	rm -f client server server.o client.o