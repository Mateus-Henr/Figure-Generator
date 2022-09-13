all: main.o
	gcc -o all main.o

main.o: main.c
	gcc -c main.c
	
clean:
	rm all main.o