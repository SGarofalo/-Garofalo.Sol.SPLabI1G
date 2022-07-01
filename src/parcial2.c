#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "movie.h"
#include "time.h"
#include "miMenu.h"

int main(void) {




	setbuf(stdout, NULL);
	srand(time(NULL));

	LinkedList *listaPelis = ll_newLinkedList();

	if (listaPelis != NULL) {
		menuPrincipal(listaPelis);
	}





	return EXIT_SUCCESS;
}
