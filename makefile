all:
	gcc -std=c99 -Wall -o main main.c
run:
	./main
clean:
	rm main