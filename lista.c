#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct _nodo nodo_t;

struct _nodo
{
	void *dato;
	nodo_t* siguiente;
};

struct lista
{
	nodo_t* primero;
	nodo_t* ultimo;
	size_t cant_elementos;
};

struct lista_iter
{
	nodo_t* anterior;
	nodo_t* actual;
};

lista_t *lista_crear(void) 
{
	lista_t* lista_enlazada = malloc(sizeof(lista_t));
	
	if( lista_enlazada == NULL )
		return NULL;
		
	lista_enlazada->primero = NULL;
	lista_enlazada->ultimo  = NULL;
	lista_enlazada->cant_elementos = 0;
	
	return lista_enlazada;
}
bool lista_esta_vacia(const lista_t *lista)
{
	return (lista != NULL && !lista_largo(lista));
}

bool lista_insertar_primero(lista_t *lista, void *dato)
{
	if( !lista )
		return false;
		
	nodo_t* vagon = malloc( sizeof(nodo_t) );
	
	if( !vagon )
		return false;
		
	vagon->dato = dato;
	vagon->siguiente = NULL;
	
	if(lista_esta_vacia(lista))
		lista->ultimo  = vagon;
	else
		vagon->siguiente = lista->primero;
		
	lista->primero = vagon;
	lista->cant_elementos++;
	
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato)
{
	if( !lista )
		return false;
		
	nodo_t* vagon = malloc( sizeof(nodo_t) );
	
	if( !vagon )
		return false;
		
	vagon->dato = dato;
	vagon->siguiente = NULL;
	if( lista_esta_vacia(lista) )
	{
		lista->primero = vagon;
		lista->ultimo = vagon;
	}
	else
	{
		lista->ultimo->siguiente = vagon;
		lista->ultimo = vagon;
	}
	lista->cant_elementos++;
	return true;
}

void *lista_borrar_primero(lista_t *lista)
{
	if( !lista || lista_esta_vacia(lista) )
		return NULL;
	
	nodo_t* vagon_temporal_a_borrar = lista->primero;
	void* dato = lista->primero->dato;
	
	lista->primero = lista->primero->siguiente;
	
	free(vagon_temporal_a_borrar);	
	lista->cant_elementos--;
	
	return dato;
}

void *lista_ver_primero(const lista_t *lista)
{	
	if( !lista || lista_esta_vacia(lista) )
		return NULL;
		
	return lista->primero->dato;
}

size_t lista_largo(const lista_t *lista)
{
	if( !lista )
		return 0;
		
	return lista->cant_elementos;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *))
{
	if( !lista )
		return;
		
	while( !lista_esta_vacia(lista) )
	{
		void *dato = lista_borrar_primero(lista);
		
		if( destruir_dato )
			destruir_dato(dato);
	}
	
	free(lista);
}

lista_iter_t *lista_iter_crear(const lista_t *lista)
{
	if( !lista )
		return NULL;
	
	lista_iter_t* iterador = malloc( sizeof(lista_iter_t) );
	
	if( !iterador )
		return NULL;
	
	iterador->anterior = NULL;
	iterador->actual = lista->primero;
	return iterador;
}

bool lista_iter_avanzar(lista_iter_t *iter)
{
	if( !iter || lista_iter_al_final(iter) )
		return false;
	
	nodo_t* tmp_vagon = iter->actual;
	
	iter->anterior = iter->actual;
	iter->actual = tmp_vagon->siguiente;
	
	return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter)
{
	if( !iter || lista_iter_al_final(iter) )
		return NULL;
	
	return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter)
{
	if( !iter )
		return false;

	/* Una iterador está parado en el final cuando
	 * Actualmente está parado en el final y el anterior existe.
	 * O , caso que la lista está vacia, no existe ni el anterior ni el
	 * actual */
	return ( (iter->anterior && !iter->actual) || 
			(!iter->anterior && !iter->actual) );
}

void lista_iter_destruir(lista_iter_t *iter)
{
	free(iter);
}

bool lista_insertar(lista_t *lista, lista_iter_t *iter, void *dato)
{
	if( !lista || !iter )
		return false;
	
	if( iter->actual == lista->primero )
	{
		if( lista_insertar_primero(lista, dato) )
		{
			iter->actual = lista->primero;
			iter->anterior = NULL;
			return true;
		}
		else
		{
			return false;
		}
	}
	// Revisar este if detalladamente...
	if( lista_iter_al_final(iter) )
	{
		iter->anterior = lista->ultimo;
		if( lista_insertar_ultimo(lista, dato) )
		{
			iter->actual = lista->ultimo;
			return true;
		}
		else
		{
			iter->actual = NULL;
			return false;
		}
	}
		
	nodo_t* nuevo_vagon = malloc( sizeof(nodo_t) );
		
	if( !nuevo_vagon )
		return false;
	
	nuevo_vagon->dato = dato;
	
	nuevo_vagon->siguiente = iter->actual;
	iter->anterior->siguiente = nuevo_vagon;
	
	iter->actual = nuevo_vagon;
	
	lista->cant_elementos++;
	
	return true;
}
		
void *lista_borrar(lista_t *lista, lista_iter_t *iter)
{
	if( !lista || !iter	|| lista_iter_al_final(iter) )
		return NULL;
	
	void* dato_eliminado;
	
	if( iter->actual == lista->primero )
	{
		dato_eliminado = lista_borrar_primero(lista);
		
		iter->actual = lista->primero;
		iter->anterior = NULL;
		
		return dato_eliminado;
	}
	else
	{
		dato_eliminado = iter->actual->dato;
		nodo_t* nodo_eliminado = iter->actual;
		
		iter->anterior->siguiente = iter->actual->siguiente;
		iter->actual = iter->actual->siguiente;
		
		if( iter->actual == lista->ultimo ) /* caso excepcional */
			lista->ultimo = iter->anterior;
			
		free(nodo_eliminado);
	}
	lista->cant_elementos--;
	
	return dato_eliminado;
}
	
void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra)
{
	if( !lista || lista_esta_vacia(lista) )
		return;
		
	nodo_t *prim = lista->primero;
	
	while( visitar(prim->dato, extra) && (prim = prim->siguiente) ) { }
}
