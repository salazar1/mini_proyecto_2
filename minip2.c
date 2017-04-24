#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Dict {
	char palIngles  [50];
	char palEspanol [50];
};
typedef struct Dict tipoDict;

struct Nodo {
	tipoDict info;
	struct Nodo *siguiente;
};

typedef struct Nodo tipoNodo;

tipoNodo *lista=NULL;

tipoNodo *crearNodo (tipoDict dict) {
	tipoNodo *nodo = (tipoNodo *)malloc (sizeof (tipoNodo));

	strcpy (nodo->info.palIngles, dict.palIngles);
	strcpy (nodo->info.palEspanol, dict.palEspanol);
	

	nodo->siguiente = NULL;
	return nodo;
}

void adicionarLista (tipoNodo *lista, tipoDict dict) {
	tipoNodo *nuevoNodo = crearNodo (dict);

	if (lista==NULL) {
		lista = nuevoNodo;
	}else {
		tipoNodo *aptNodo = lista;
		while (aptNodo != NULL) {
			aptNodo = aptNodo->siguiente;
		}
		aptNodo->siguiente = nuevoNodo;
	}
}

void imprimirLista (tipoNodo *lista) {
	tipoNodo *aptNodo = lista;
	while (aptNodo != NULL) {
		printf ("<%s>::<%s>\n", aptNodo->info.palIngles, aptNodo->info.palEspanol);
		aptNodo = aptNodo->siguiente;
	}
}

void cargarDictToLista (char *nombreArchivoBin, tipoNodo *lista) {
	FILE *manejadorBin;
	manejadorBin = fopen (nombreArchivoBin, "r"); 
	tipoDict dictTmp;
	int longitudBytes = sizeof(tipoDict);

	while (fread (&dictTmp, longitudBytes, 1, manejadorBin) == 1) {
		printf ("<%s>:<%s>\n", dictTmp.palIngles, dictTmp.palEspanol);
		adicionarLista (lista, dictTmp);
	}
	fclose (manejadorBin);
}

int main (int argc, char * argv[]){
	tipoNodo *lista=NULL;
	cargarDictToLista ("palabras.TXT", lista);
	imprimirLista (lista);
	return 0;
}
