MY_CFLAGS = -I..
MY_LDFLAGS = -L.. -lmysac 

client: client.o
	$(CC) -o client client.o $(LDFLAGS) $(MY_LDFLAGS)

client.o: client.c
	$(CC) -c -o client.o client.c $(CFLAGS) $(MY_CFLAGS)
