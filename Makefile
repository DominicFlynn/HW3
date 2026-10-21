CC = g++
CFLAGS = -std=c++11

all: a.out

a.out: main.o address.o credit_card.o person.o product.o transaction.o store.o
	$(CC) $(CFLAGS) main.o address.o credit_card.o person.o product.o transaction.o store.o -o a.out

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

address.o: address.cpp address.h
	$(CC) $(CFLAGS) -c address.cpp

credit_card.o: credit_card.cpp credit_card.h
	$(CC) $(CFLAGS) -c credit_card.cpp

person.o: person.cpp person.h address.h credit_card.h
	$(CC) $(CFLAGS) -c person.cpp

product.o: product.cpp product.h
	$(CC) $(CFLAGS) -c product.cpp

transaction.o: transaction.cpp transaction.h person.h product.h
	$(CC) $(CFLAGS) -c transaction.cpp

store.o: store.cpp store.h person.h product.h transaction.h
	$(CC) $(CFLAGS) -c store.cpp

clean:
	rm -f *.o a.out
