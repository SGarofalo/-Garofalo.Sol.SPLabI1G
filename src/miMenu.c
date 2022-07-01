#include "miMenu.h"

#include <stdio.h>
#include <stdlib.h>
#include "miBiblio.h"

int elegirOpcionMenuPrincipal(){
	int opcion;

		system("cls");
		printf("-------------------------------------------\n");
		printf("		** ABM PELICULAS **     \n");
		printf("-------------------------------------------\n");
		printf("  1. Cargar archivo\n");
		printf("  2. Imprimir lista\n");
		printf("  3. Asignar tiempos\n");
		printf("  4. Filtrar por tipo\n");
		printf("  5. Mostrar duraciones.\n");
		printf("  6. Guardar peliculas.\n");
		printf("  7. Salir\n");

	getInt("Ingrese una opcion: ", "ERROR. Ingrese nuevamente: ", &opcion);

	return opcion;
}

int menuPrincipal(LinkedList *listaMovies) {
	int todoOk = 0;
	int option;
	char salir = 'n';
	char path[40];

	int flagL = 0;
	int flagMapG = 0;
	int flagMapD = 0;
	int flagSort = 0;
	int flagSave = 0;

	LinkedList *listaMapeada = ll_newLinkedList();
	LinkedList *listaClonada = ll_newLinkedList();

	if (listaMovies != NULL) {
		do {
			option = elegirOpcionMenuPrincipal();
			switch (option) {
			case 1:
				if (!flagL) {
					if (controller_loadFromText(listaMovies)) {
						flagL = 1;
						printf("Archivo cargado exitosamente!\n");
					}
				} else {
					printf("Los datos fueron cargados!\n");
				}
				break;
			case 2:

				if (flagL) {
					controller_imprimirMovies(listaMovies);
				} else {
					printf("Primero debe cargar el archivo\n");
				}
				break;
			case 3:
				if (flagMapD) {
					printf("Ya fuaron cargados!\n");
				} else {
					if (flagL) {
						listaMapeada = controller_asignarD(listaMovies);

						if (listaMapeada != NULL) {
							printf("Tiempos asignados con exito!!\n\n");

							controller_imprimirMovies(listaMovies);
							flagMapD = 1;
						}
					} else {
						printf("Primero debe cargar la lista!\n");
					}
				}

				break;
			case 4:
				if (flagMapG && flagMapD) {
					controller_filtrarPorGenero(listaMovies);
				} else {
					printf("Primero debe cargar las duraciones en la lista!\n");
				}

				break;

			case 5:

				if (flagMapG && flagMapD) {
					listaClonada = controller_ordenar(listaMapeada);

					if (listaClonada != NULL) {
						flagSort = 1;
					}

				} else {
					printf("Primero debe cargar las duraciones\n");
				}

				if (flagL) {
					controller_imprimirMovies(listaMovies);
				} else {
					printf("Primero debe cargar el archivo para poder mostrarlo.!\n");
				}



				break;
			case 6:

				if (flagSort) {
					utn_getString(path, 30,
							"Por favor, ingrese el nombre con el que desea guardar el archivo: ",
							"ERROR. Por favor, ingrese el nombre con el que desea guardar el archivo: ",
							9);
					strcat(path, ".csv");
					controller_saveAsText(path, listaClonada);
					flagSave = 1;
				}


				break;
			case 7:

				system("cls");
				if (flagSave)


					printf("No puede salir sin guardar los datos \n");

				salir = getConfirmation("Esta seguro que desea salir? (s/n): ",
						"ERROR. Esta seguro que desea salir? (s/n): ");
				break;
			default:
				printf("Ingreso una opcion invalida. Vuelva a intentarlo.\n");
				break;
			}

			printf("Presione una tecla para continuar...\n");
			fflush(stdin);
			getchar();

		} while (salir == 'n');

		todoOk = 1;
	}

	ll_deleteLinkedList(listaMapeada);

	return todoOk;
}

int menuGeneros() {
	int opcion;

	system("cls");
	printf("----------------------------------------\n");
	printf("   **   TIPOS DE GENEROS **      \n");
	printf("----------------------------------------\n");
	printf("1. Romance\n");
	printf("2. Comedy\n");
	printf("3. Documentary\n");
	printf("4. Horror\n");
	printf("5.Musicaly");
	printf("6. Drama");


	getInt("Por favor ingrese el ID del genero que desea: ",
			"Ingrese nombre valido ", &opcion);

	return opcion;
}


