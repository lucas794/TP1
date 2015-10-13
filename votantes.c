#include "mesa.h"
#include <string.h>
#include "votantes.h"

bool persona_valida_a_votar( char *dni, char *tipoDNI, mesa_t* mesa_escrutinio )
{
	bool pertenece = false;
	
	lista_iter_t* iterador = lista_iter_crear(mesa_escrutinio->personas_a_votar);
	int iDNI = atoi(dni);
	votante_t* tmp;
	
	while( !lista_iter_al_final(iterador) )
	{
		tmp = lista_iter_ver_actual(iterador);
		
		if( !strcmp(tmp->tipoDNI, tipoDNI) && (tmp->numeroDNI == iDNI) )
			pertenece = true;
			
		if( pertenece )
		{
			lista_iter_destruir(iterador);
			return true;
		}
		
		lista_iter_avanzar(iterador);
	}
	if( !pertenece )
		lista_iter_destruir(iterador);
	
	return false;
}
