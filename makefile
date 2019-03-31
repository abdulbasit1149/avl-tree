target : avltree

avltree : avltree.o tree.o
	gcc -Wall -pedantic -std=c99 avltree.o tree.o -o avltree

avltree.o: avltree.c
	gcc -c -Wall -pedantic -std=c99 avltree.c

tree.o: tree.c
	gcc -c -Wall -pedantic -std=c99 tree.c

clean:
	rm avltree *.o