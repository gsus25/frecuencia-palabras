wordcount: main.o
	gcc -o wordcount main.o $(DFLAGS)

main.o: main.c
	gcc -c main.c $(DFLAGS)

.PHONY: debug
debug: DFLAGS = -g
debug: clean wordcount

.PHONY: sanitize
sanitize: DFLAGS = -fsanitize=address,undefined
sanitize: clean wordcount

.PHONY: clean
clean:
	rm -rf wordcount *.o

.PHONY: run
run: wordcount
	./wordcount
