#ifndef _MESA_H
#define _MESA_H

#include <stdio.h>
#include <stdbool.h>
#include "lista.h"

typedef struct boletas boleta_t;
typedef struct mesa mesa_t;

struct mesa
{
	bool estado;
	lista_t *boletas_en_mesa;
	lista_t *padron;
	lista_t *personas_a_votar;
};

struct boletas
{
	int IDpartido;
	char *nombrePartido;
	char *presidente;
	char *gobernador;
	char *intendente;
	size_t votos_recibidos[3];
};

/* ABRIR_MESA
 * Dado 2 rutas (candidatos y padron electoral) se procede a abrir
 * la mesa electoral, devuelve un puntero a una mesa creada */
mesa_t* abrir_mesa(char *mesa_electoral, char *padron);

/* MESA_ABIERTA
 * Dada una mesa, devolverá true si esta está abierta, en caso
 * contrario false
 * pre: La mesa fue creada
 */
bool mesa_abierta(mesa_t*);

/* AGREGAR_VOTANTE_NUEVO
 * Dado un DNI, numero de dni y una mesa electoral,
 * se procede a agregarlo al padron electoral
 * True en caso afirmativo, false en caso contrario 
 * PRE: La mesa fue creada */
bool agregar_votante( mesa_t* mesa_de_votos, char* tipo_dni, char* numero_dni );

/* DESTRUIR_MESA
 * Dada una mesa válida, se procede a borrarla */
void destruir_mesa( mesa_t* mesa_votos );

/* DESTRUIR_MESA
 * destruye a un votante de la lista de votos */
void destruir_votante(void *);

#endif
