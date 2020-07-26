all : server client
.PHONY : all
server : server.c
	gcc -shared -g -o $@ $<
client : client.c
	gcc -shared -g -o $@ $<
.PHONY : clean
clean :
	rm -f client server server.o client.o