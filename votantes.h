#ifndef _VOTANTES_H
#define _VOTANTES_H

#include <stdio.h>
#include <stdbool.h>
#include "mesa.h"

typedef struct gente_a_votar votante_t;
struct gente_a_votar
{
	char *tipoDNI;
	int numeroDNI;
	bool voto_realizado;
};

/* PERSONA_VALIDA_A_VOTAR
 * Dada una persona con su DNI , numero y mesa de escrutinio se verifica
 * si está en el padron, en caso afirmativo devolvera true, en caso contrario, false */
bool persona_valida_a_votar( char *dni, char *tipoDNI, mesa_t* mesa_escrutinio );
#endif


