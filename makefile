all : server client
.PHONY : all
server : server.o
	gcc -o $@ $<

client.o : client.o
	gcc -o $@ $<

server.o : server.c
	gcc -o $@ $<

.PHONY : clean
	rm -f client server server.o client.o
	