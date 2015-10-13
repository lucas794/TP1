#ifndef _LISTA_ENLAZADA_H

#define _LISTA_ENLAZADA_H

#include <stdlib.h>
#include <stdbool.h>

/* TIPO DE DATOS */
typedef struct lista lista_t;

/* ||-> lista *lista_crear(void)
 * 	Crea una nueva lista
 *  Post: Devuelve un puntero a una lista vacia 
*/
lista_t *lista_crear(void);

/* ||-> bool lista_esta_vacia(const lista_t *lista);
 * Devuelve verdadero o falso, según si la lista tiene o no elementos.
 * Pre: la lista fue creada. 
*/
bool lista_esta_vacia(const lista_t *lista);

/* ||-> bool lista_insertar_primero(lista_t *lista, void *dato);
 * Inserta un elemento en la primera posición
 * Devolvera false en caso de error
 * Pre: La lista fué creada
 * Post: se agregó un nuevo elemento a la lista, éste será el primero
*/
bool lista_insertar_primero(lista_t *lista, void *dato);

/* ||-> bool lista_insertar_ultimo(lista_t *lista, void *dato);
 * Inserta un elemento en la última posicion
 * Devolvera false en caso de error, trabaja en O(1)!
 * Pre: La lista fué creada
 * Post: se agregó un nuevo elemento a la lista, éste será el último
*/
bool lista_insertar_ultimo(lista_t *lista, void *dato);

/* ||-> bool void *lista_borrar_primero(lista_t *lista);
 * Elimina el primer elemento de la lista
 * Pre: La lista fué creada
 * Post: Se devuelve el dato del elemento borrado
*/
void *lista_borrar_primero(lista_t *lista);

/* ||-> void *lista_ver_primero(const lista_t *lista);
 * Devuelve el dato del primer elemento de la lista
 * Pre: La lista fué creada
 * Post: Se devuelve el dato del primer elemento
*/
void *lista_ver_primero(const lista_t *lista);

/* ||-> size_t lista_largo(const lista_t *lista);
 * Devuelve el largo de la lista , trabaja en O(1)!
 * Pre: La lista fué creada
 * Post: devuelve el largo de la lista
*/
size_t lista_largo(const lista_t *lista);

/* ||-> void lista_destruir(lista_t *lista, void destruir_dato(void *));
 * Destruye la lista, Si se recibe la función destruir_dato por parámetro,
 * para cada uno de los elementos de la lista llama a destruir_dato.
 * Pre: la lista fue creada. destruir_dato es una función capaz de destruir
 * los datos de la lista, o NULL en caso de que no se la utilice.
 * Post: se eliminaron todos los elementos de la cola.
*/
void lista_destruir(lista_t *lista, void destruir_dato(void *));

void pruebas_lista_alumno(void);
/* PRIMITIVAS DE ITERACION */

typedef struct lista_iter lista_iter_t;

/* ||-> lista_iter_t *lista_iter_crear(const lista_t *lista);
 * Crea un nuevo iterador
 * Pre: La lista fué creada
 * Post: Devuelve un iterador válido para la lista
*/
lista_iter_t *lista_iter_crear(const lista_t *lista);

/* ||-> bool lista_iter_avanzar(lista_iter_t *iter);
 * Avanza uno a uno los elementos de la lista
 * Pre: el iterador fue creado
 * Post: En caso afirmativo, avanza satisfactoriamente al prox elemento
*/
bool lista_iter_avanzar(lista_iter_t *iter);

/* ||-> void *lista_iter_ver_actual(const lista_iter_t *iter);
 * Ve el dato donde está parado el iterador
 * Pre: el iterador fue creado
 * Post: devuelve el dato donde está parado el iterador
*/
void *lista_iter_ver_actual(const lista_iter_t *iter);

/* ||-> bool lista_iter_al_final(const lista_iter_t *iter);
 * Itera hasta llegar al final, al llegar se devolverá true;
 * Pre: el iterador fue creado
*/
bool lista_iter_al_final(const lista_iter_t *iter);

/* ||-> void lista_iter_destruir(lista_iter_t *iter);
 * Destruye un iterador
 * Pre:el iterador fue creado
*/
void lista_iter_destruir(lista_iter_t *iter);

/* ||-> bool lista_insertar(lista_t *lista, lista_iter_t *iter, void *dato);
 * 	 && void *lista_borrar(lista_t *lista, lista_iter_t *iter);
 * 
 * Insertan y destruyen respectivamente!!
 * Pre: la lista y el iterador fueron creados
*/
bool lista_insertar(lista_t *lista, lista_iter_t *iter, void *dato);
void *lista_borrar(lista_t *lista, lista_iter_t *iter);

void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra);
#endif // _LISTA_ENLAZADA_H
