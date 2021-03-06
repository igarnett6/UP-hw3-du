du: du.c
	gcc -o du -std=gnu99 -Wall du.c

	clean:
		rm -f du
