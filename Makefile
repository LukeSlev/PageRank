# ------------------------------------------------------------
# Makefile: Makefile for Lab 4
#   author: Luke Slevinsky, 1453199
#						Logan McDonald, 1401297
#
# Usage: make  // compiles the program
#        make tar   	 // create a 'tar.gz' archive of 'allFiles'
#        make clean 	 // remove unneeded files
# ------------------------------------------------------------

target := lab4
allFiles := Makefile timer.h main.c datatrim.c serialtester.c web-Stanforf.txt
objects :=
headers := timer.h Lab4_IO.h
CFLAGS :=  -Wall -lm
threadSan := -fsanitize=thread -g
LDFLAGS=
DEBUGFLAG := -ggdb
CC := mpicc
# ------------------------------------------------------------

default: $(headers) main.o Lab4_IO.o
	$(CC) $(LDFLAGS) $(DEBUGFLAG) $(CFLAGS) -o main main.o Lab4_IO.o

main1: $(headers) main1.o Lab4_IO.o
	$(CC) $(LDFLAGS) $(DEBUGFLAG) $(CFLAGS) -o main1 main1.o Lab4_IO.o

main2: $(headers) main2.o Lab4_IO.o
	$(CC) $(LDFLAGS) $(DEBUGFLAG) $(CFLAGS) -o main2 main2.o Lab4_IO.o

main3: $(headers) main3.o Lab4_IO.o
	$(CC) $(LDFLAGS) $(DEBUGFLAG) $(CFLAGS) -o main3 main3.o Lab4_IO.o

serialtester: serialtester.o Lab4_IO.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o serialtester serialtester.o Lab4_IO.o -lm

datatrim: datatrim.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o datatrim datatrim.o

main.o: main.c
	$(CC) $(LDFLAGS) $(CFLAGS) main.c -c

main1.o: main1.c
	$(CC) $(LDFLAGS) $(CFLAGS) main1.c -c

main2.o: main2.c
	$(CC) $(LDFLAGS) $(CFLAGS) main2.c -c

main3.o: main3.c
	$(CC) $(LDFLAGS) $(CFLAGS) main3.c -c

datatrim.o: datatrim.c
	$(CC) $(CFLAGS) datatrim.c -c

serialtester.o: serialtester.c
	$(CC) $(CFLAGS) serialtester.c -c

Lab4_IO.o: Lab4_IO.c
	$(CC) $(CFLAGS) Lab4_IO.c -c

tar:
	touch $(target).tar.gz
	mv $(target).tar.gz  x$(target).tar.gz
	tar -cvf $(target).tar $(allFiles)
	gzip $(target).tar

clean:
	rm *.o main serialtester datatrim
