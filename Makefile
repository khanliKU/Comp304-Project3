fs304: fs304.c
	gcc -o fs304 fs304.c -lm
clean:
	rm -f *.o fs304
	echo Clean done