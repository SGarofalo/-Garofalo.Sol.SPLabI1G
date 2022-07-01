#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "parser.h"
#include "miBiblio.h"
#include "miMenu.h"
#include "movie.h"

int controller_loadFromText(LinkedList *listaMovies) {

	int todoOk = 0;

	char path[20];

	utn_getString(path, 20, "Ingrese nombre del archivo (movie): ",
			"ERROR. Ingrese nuevamente nombre: ", 10);
	strcat(path, ".csv");

	FILE *fPath = fopen(path, "r");

	if (fPath != NULL && listaMovies != NULL) {
		parser_MovieFromText(fPath, listaMovies);
		fclose(fPath);
		fPath = NULL;
		todoOk = 1;

	} else {
		printf("ERROR, al abrir el archivo\n");
		todoOk = 0;
	}

	return todoOk;
}


/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char *path, LinkedList *pArrayPelis) {
	int todoOk = 0;
	int cant;

	FILE *fPath = fopen(path, "w");
	eMovie *auxMovie = NULL;

	if (pArrayPelis != NULL && fPath != NULL) {
		fprintf(fPath, "id_peli,titulo,genero,duracion\n");

		cant = ll_len(pArrayPelis);
		for (int i = 0; i < cant; i++) {
			auxMovie = (eMovie*) ll_get(pArrayPelis, i);

			if (auxMovie != NULL) {

				fprintf(fPath, "%d,%s,%s,%.1f\n", auxMovie->id,
						auxMovie->titulo, auxMovie->genero, auxMovie->duracion);
			}
		}
		todoOk = 1;
		printf("El archivo fue guardado exitosamente\n");
		fclose(fPath);
		auxMovie = NULL;
	} else {
		printf("No se pudo guardar el archivo\n");
	}

	return todoOk;
}


void controller_imprimirUnaMovie(eMovie *unaMovie) {

	int id;
	char titulo[40];
	char genero[20];
	float duracion;

	if (unaMovie != NULL && movie_getId(unaMovie, &id)
			&& movie_getTitulo(unaMovie, titulo)
			&& movie_getGenero(unaMovie, genero)
			&& movie_getD(unaMovie, &duracion)) {

		printf("%-4d      %-30s      %-15s        %.1f  \n", id, titulo, genero,
				duracion);

	}

}


int controller_imprimirMovies(LinkedList *lista) {
	int todoOk = 0;
	int tam;

	if (lista != NULL) {
		system("cls");
		printf("		** LISTA DE PELICULAS **\n");
		printf(
				"----------------------------------------------------------------------------\n");
		printf(
				"ID        TITULO                             GENERO                 DURACION\n");
		printf(
				"----------------------------------------------------------------------------\n");

		tam = ll_len(lista);

		for (int i = 0; i < tam; i++) {
			controller_imprimirUnaMovie((eMovie*) ll_get(lista, i));
		}
		todoOk = 1;
	}

	return todoOk;
}

LinkedList* controller_asignarD(LinkedList *lista) {
	LinkedList *pListaMapeada = NULL;
	void* (*funcion)(void*);

	if (lista != NULL) {
		funcion = movie_asignarDAleatorio;
		pListaMapeada = ll_map(lista, funcion);

	}

	return pListaMapeada;
}



int controller_filtrarPorGenero(LinkedList *lista) {
	int todoOk = 0;
	int (*pFiltrarGenero)(void*);
	char path[30];

	LinkedList *newList = NULL;

	int idGenero;
	int flag = 0;

	if (lista != NULL) {

		idGenero = menuGeneros();

		switch (idGenero) {
		case 1:
			pFiltrarGenero = movie_filtrarDrama;
			flag = 1;
			break;

		case 2:
			pFiltrarGenero = movie_filtrarComedia;
			flag = 1;
			break;

		case 3:
			pFiltrarGenero = movie_filtrarAccion;
			flag = 1;
			break;

		case 4:
			pFiltrarGenero = movie_filtrarTerror;
			flag = 1;
			break;
		default:
			printf("OPCION INVALIDA. REINTENTELO\n");
			break;
		}

	}

	if (flag) {

		newList = ll_filter(lista, pFiltrarGenero);
		printf("llegue");

		if (newList != NULL) {
			if (ll_len(newList) > 0) {

				controller_imprimirMovies(newList);

				utn_getString(path, 30,
						"Ingrese el nombre con el cual quiere guardar el archivo ",
						"ERROR. Por favor, ingrese el nombre con el que desea guardar el archivo: ",
						9);
				strcat(path, ".csv");
				controller_saveAsText(path, newList);

			} else {
				printf("No hay peliculas de ese genero.\n");
			}

		} else {
			printf("Algo fallo, intente nuevamente\n");
		}

		todoOk = 1;
	}

	return todoOk;
}

LinkedList* controller_ordenar(LinkedList *lista) {
	LinkedList *listaOrdenada = NULL;

	int (*pOrdenarMovies)(void*, void*);

	if (lista != NULL) {
		listaOrdenada = ll_clone(lista);

		if (lista != NULL) {

			pOrdenarMovies = movie_ordenarMovies;
			ll_sort(listaOrdenada, pOrdenarMovies, 1);

			controller_imprimirMovies(listaOrdenada);

		}

	}

	return listaOrdenada;
}


