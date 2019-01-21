<<<<<<< HEAD
square: point.c color.c frame.c square.c
	gcc -o square point.c color.c frame.c square.c -I.
=======
square: square.c point.c
	gcc -o square square.c point.c -I.
>>>>>>> parent of 3ffac8e... generate words to frame
