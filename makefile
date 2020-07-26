all : server client
.PHONY : all
server : server.c
	gcc -o $@ $<

client.o : client.c
	gcc -o $@ $<

.PHONY : clean
	rm -f client server server.o client.o
