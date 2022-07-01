#include <time.h>
#include <ctype.h>
#include "movie.h"
#include "miBiblio.h"

eMovie* movie_new() {
	eMovie *nuevaMovie = (eMovie*) malloc(sizeof(eMovie));

	if (nuevaMovie != NULL) {
		nuevaMovie->id = 0;
		strcpy(nuevaMovie->titulo, " ");
		strcpy(nuevaMovie->genero, " ");
		nuevaMovie->duracion = 0.0;
	}

	return nuevaMovie;
}


eMovie* movie_newParametros(char *idStr, char *tituloStr, char *generoStr,
		char *DStr) {
	eMovie *nuevaMovie = movie_new();

	if (nuevaMovie != NULL && idStr != NULL && tituloStr != NULL
			&& generoStr != NULL && DStr != NULL) {

		movie_setId(nuevaMovie, atoi(idStr));
		movie_setTitulo(nuevaMovie, tituloStr);
		movie_setGenero(nuevaMovie, generoStr);
		movie_setD(nuevaMovie, atof(DStr));
	}

	return nuevaMovie;
}


int movie_delete(eMovie *this) {
	int todoOk = 0;

	if (this != NULL) {
		free(this);
		todoOk = 1;
	}

	return todoOk;
}


int movie_setId(eMovie* this,int id){
	int todoOk = 0;

	if (this != NULL && id > 0){
		this->id = id;
		todoOk = 1;
	}

	return todoOk;
}

int movie_setTitulo(eMovie* this,char* titulo){
	int todoOk = 0;

	if (this != NULL && titulo != NULL){
		strcpy(this->titulo, titulo);
		todoOk = 1;
	}

	return todoOk;
}

int movie_setGenero(eMovie* this,char* genero){
	int todoOk = 0;

	if (this != NULL && genero != NULL){
		strcpy(this->genero, genero);
		todoOk = 1;
	}

	return todoOk;
}

int movie_setD(eMovie* this, float duracion)
{
	int todoOk = 0;

	if (this != NULL && duracion >= 0){
		this->duracion = duracion;

		todoOk = 1;
	}

	return todoOk;
}


int movie_getId(eMovie* this,int* id){
	int todoOk = 0;

	if (this != NULL && id != NULL){
		*id = this->id;
		todoOk = 1;
	}

	return todoOk;
}


int movie_getTitulo(eMovie* this,char* titulo){
	int todoOk = 0;

	if (this != NULL && titulo != NULL){
		strcpy(titulo, this->titulo);
		todoOk = 1;
	}

	return todoOk;
}


int movie_getGenero(eMovie* this,char* genero){
	int todoOk = 0;

	if (this != NULL && genero != NULL){
		strcpy(genero, this->genero);
		todoOk = 1;
	}

	return todoOk;
}


int movie_getD(eMovie* this, float* duracion)
{
	int todoOk = 0;

	if (this != NULL && duracion >= 0){
		*duracion = this->duracion;
		todoOk = 1;
	}

	return todoOk;
}






void* movie_asignarDAleatorio(void *unaMovie) {

	int DMax = 240;
	int DMin = 100;

	if (unaMovie != NULL) {

		movie_setD(unaMovie,floatAleatorioUnDecimal(DMin, DMax));
	}

	return unaMovie;
}






int movie_filtrarAccion(void *p) {
	int todoOk = 0;
	char auxGenero[20];
	eMovie *auxMovie = NULL;

	if (p != NULL) {
		auxMovie = (eMovie*) p;
		movie_getGenero(auxMovie, auxGenero);

		if (strcmp(auxGenero, "Accion") == 0) {
			todoOk = 1;
		}
	}

	return todoOk;
}

int movie_filtrarTerror(void *p) {
	int todoOk = 0;
	char auxGenero[20];
	eMovie *auxMovie = NULL;

	if (p != NULL) {
		auxMovie = (eMovie*) p;
		movie_getGenero(auxMovie, auxGenero);

		if (strcmp(auxGenero, "Terror") == 0) {
			todoOk = 1;
		}
	}

	return todoOk;
}

int movie_filtrarComedia(void *p) {
	int todoOk = 0;
	char auxGenero[20];
	eMovie *auxMovie = NULL;

	if (p != NULL) {
		auxMovie = (eMovie*) p;
		movie_getGenero(auxMovie, auxGenero);

		if (strcmp(auxGenero, "Comedia") == 0) {
			todoOk = 1;
		}
	}

	return todoOk;
}

int movie_filtrarDrama(void *p) {
	int todoOk = 0;
	char auxGenero[20];
	eMovie *auxMovie = NULL;

	if (p != NULL) {
		auxMovie = (eMovie*) p;
		movie_getGenero(auxMovie, auxGenero);

		if (strcmp(auxGenero, "Drama") == 0) {
			todoOk = 1;
		}
	}

	return todoOk;
}


int movie_ordenarMovies(void *peliI, void *peliJ) {
	int todoOk = -1;
	char generoI[40];
	char generoJ[40];
	float DgI;
	float DgJ;

	if (peliI != NULL && peliJ != NULL) {
		movie_getGenero(peliI, generoI);
		movie_getGenero(peliJ, generoJ);
		movie_getD(peliI, &DgI);
		movie_getD(peliJ, &DgJ);

		if (strcmp(generoI, generoJ) > 0 || (strcmp(generoI, generoJ) == 0 && DgI < DgJ)) {
			todoOk = 1;
		} else {
			todoOk = 0;
		}

	}

	return todoOk;
}





