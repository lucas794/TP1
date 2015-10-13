#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "lectura.h"
#include "mesa.h"

#define MAX_COMANDOS_INGRESABLES 4

int main(void)
{
	char *comandos_ingresables[ ] = { "abrir", "ingresar", "votar", "fin" };
	mesa_t* crear_mesa = NULL;
	while( true )
	{
		/* dudo mucho que esto esté correctamente, but, works! */
		char* linea = leer_linea(stdin);
		char parametros_recibidos[MAX_COMANDOS_INGRESABLES][64]; 
							      /* max parametros */      /*len*/
		size_t i = 0;
		
		if( !(*linea) )
			return 0;
			
		char *ch;		
		ch = strtok(linea, " ");
		
		if( !(*ch) ) 
			return 0;
		
		while( ch != NULL && i < MAX_COMANDOS_INGRESABLES )
		{
			strcpy(parametros_recibidos[i], ch);
			ch = strtok(NULL, " ");
			i++;
		}
		switch( parametros_recibidos[0][0] )
		{
			case 'a': // abrir
			{
				if( strcmp(parametros_recibidos[0], comandos_ingresables[0] ) )
					continue;
				
				if( mesa_abierta(crear_mesa) ) /* ya está abierta la mesa!! */
				{
					fprintf(stderr, "ERROR2\n");
					continue;
				}
				if( i != 3 )
				{
					fprintf(stderr, "ERROR2\n");
					continue;
				}
					
				crear_mesa = abrir_mesa(parametros_recibidos[1], parametros_recibidos[2]);
				
				if( !mesa_abierta(crear_mesa) )
				{
					fprintf(stderr, "ERROR2\n");
					continue;
				}
				fprintf(stderr, "OK\n");
				break;
			}
			case 'i': /* insertar.. */
			{
				if( strcmp(parametros_recibidos[0], comandos_ingresables[1] ) )
					continue;
					
				if( !mesa_abierta(crear_mesa) )
				{
					fprintf(stderr, "ERROR3\n");
					continue;
				}
				
				if( i != 3 )
					continue;
					
				if( !agregar_votante(crear_mesa, parametros_recibidos[1], parametros_recibidos[2] ) )
					continue;
					
				fprintf(stderr, "OK\n");
				break;
			}
			case 'c': /* cerrar */
			{
				if( strcmp(parametros_recibidos[0], comandos_ingresables[3] ) )
					continue;
				
				if( !mesa_abierta(crear_mesa) )
				{
					fprintf(stderr, "ERROR3\n");
					continue;
				}
				
				destruir_mesa(crear_mesa);
				break;
			}
			case 'v': /* votar */
			{
				if( strcmp(parametros_recibidos[0], comandos_ingresables[2] ) )
					continue;
					
				if( !mesa_abierta(crear_mesa) )
				{
					fprintf(stderr, "ERROR3\n");
					continue;
				}
				
				if( !lista_largo(crear_mesa->personas_a_votar) )
				{
					fprintf(stderr, "ERROR7\n");
					continue;
				}
				
				/* realizar el proceso de votacion */
				/* utilizar primitivas de votantes.h para verificar
				 * si una persona pertenece al escrutinio */
			}
			default:
				break;
		}
	}
	return 0;
}
