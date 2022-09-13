all:
	gcc src/main.c -o main
	./main

clean:
	rm all main