#define _XOPEN_SOURCE 500

#include <stdlib.h>
#include "parser.h"
#include "lectura.h"
#include "mesa.h"
#include "votantes.h"
#include <limits.h>
#include "lista.h"

bool mesa_abierta(mesa_t* mesa_v)
{
	/* una mesa está abierta cuando tiene gente a votar y tiene boletas */
	return (mesa_v && !lista_esta_vacia(mesa_v->boletas_en_mesa) &&
			!lista_esta_vacia(mesa_v->padron) );
}

bool agregar_votante( mesa_t* mesa_de_votos, char* tipo_dni, char* numero_dni )
{
	int iDNI = atoi(numero_dni);
	
	votante_t* votante_nuevo;
		
	if( (votante_nuevo = malloc(sizeof(votante_t))) == NULL )
			return false;
	
	votante_nuevo->tipoDNI = strdup(tipo_dni);
	votante_nuevo->numeroDNI = iDNI;
	votante_nuevo->voto_realizado = false;
				
	lista_insertar_ultimo(mesa_de_votos->personas_a_votar, votante_nuevo);
	return true;
}

void destruir_votante(void *dato)
{
	votante_t* tmp = dato;
	
	free(tmp->tipoDNI);
}

void destruir_boleta(void *dato)
{
	boleta_t* tmp = dato;
	
	free(tmp->nombrePartido);
	free(tmp->presidente);
	free(tmp->gobernador);
	free(tmp->intendente);
}

void destruir_mesa( mesa_t* mesa_votos )
{
	lista_destruir(mesa_votos->boletas_en_mesa, destruir_boleta);
	lista_destruir(mesa_votos->padron, destruir_votante);
	lista_destruir(mesa_votos->personas_a_votar, destruir_votante);
	free(mesa_votos);
}

mesa_t* abrir_mesa(char *mesa_electoral, char *padron)
{
	mesa_t* la_mesa;
	
	if( !(la_mesa = malloc(sizeof(mesa_t))) )
		return NULL;
	
	la_mesa->estado = false;
	la_mesa->boletas_en_mesa = lista_crear();
	la_mesa->personas_a_votar = lista_crear();
	la_mesa->padron = lista_crear();
	
	if( !la_mesa->boletas_en_mesa || !la_mesa->personas_a_votar || !la_mesa->padron )
	{
		fprintf(stderr, "ERROR1\n");
		return NULL;
	}
	
	if( mesa_electoral == NULL || padron == NULL )
	{
		fprintf(stderr, "ERROR1\n");
		lista_destruir(la_mesa->boletas_en_mesa, NULL);
		lista_destruir(la_mesa->personas_a_votar, NULL);
		lista_destruir(la_mesa->padron, NULL);
		free(la_mesa);
		return NULL;
	}
	
	FILE *postulantes, *votantes;

	if( !(postulantes = fopen(mesa_electoral, "r")) )
	{
		fprintf(stderr, "ERROR2\n");
		lista_destruir(la_mesa->personas_a_votar, NULL);
		lista_destruir(la_mesa->boletas_en_mesa, NULL);
		lista_destruir(la_mesa->padron, NULL);
		free(la_mesa);
		return NULL;
	}
		
	if( !(votantes = fopen(padron, "r")) )
	{
		fprintf(stderr, "ERROR2\n");
		fclose(postulantes);
		lista_destruir(la_mesa->personas_a_votar, NULL);
		lista_destruir(la_mesa->boletas_en_mesa, NULL);
		lista_destruir(la_mesa->padron, NULL);
		free(la_mesa);
		return NULL;
	}
	char *linea_fixeada;
	fila_csv_t* parseado;
	
	while( (linea_fixeada = leer_linea(postulantes)) != NULL )
	{
		parseado = parsear_linea_csv(linea_fixeada, 5);
		boleta_t* nueva_boleta;
		
		if( ( nueva_boleta = malloc(sizeof(boleta_t)) ) == NULL )
		{
			lista_destruir(la_mesa->boletas_en_mesa, NULL);
			lista_destruir(la_mesa->personas_a_votar, NULL);
			lista_destruir(la_mesa->padron, NULL);
			fclose(postulantes);
			fclose(votantes);
			free(la_mesa);
			return NULL;
		}
		nueva_boleta->IDpartido	= atoi(obtener_columna(parseado, 0));
		nueva_boleta->nombrePartido	= strdup(obtener_columna(parseado, 1));
		nueva_boleta->presidente = strdup(obtener_columna(parseado, 2));
		nueva_boleta->gobernador = strdup(obtener_columna(parseado, 3));
		nueva_boleta->intendente = strdup(obtener_columna(parseado, 4));
		nueva_boleta->votos_recibidos[0] = 0;
		nueva_boleta->votos_recibidos[1] = 0;
		nueva_boleta->votos_recibidos[2] = 0;
		lista_insertar_ultimo(la_mesa->boletas_en_mesa, nueva_boleta);
		destruir_fila_csv(parseado, false);
	}
	
	while( (linea_fixeada = leer_linea(votantes)) != NULL )
	{
		parseado = parsear_linea_csv(linea_fixeada, 2);
		
		votante_t* nuevo_votante;
		
		if( ( nuevo_votante = malloc(sizeof(votante_t)) ) == NULL )
		{
			lista_destruir(la_mesa->boletas_en_mesa, destruir_boleta);
			lista_destruir(la_mesa->personas_a_votar, NULL);
			lista_destruir(la_mesa->padron, NULL);
			fclose(postulantes);
			fclose(votantes);
			free(la_mesa);
			return NULL;
		}
		nuevo_votante->tipoDNI = strdup(obtener_columna(parseado, 0));
		nuevo_votante->numeroDNI = atoi((obtener_columna(parseado, 1)));
		nuevo_votante->voto_realizado = false;
		lista_insertar_ultimo(la_mesa->padron, nuevo_votante);
		destruir_fila_csv(parseado, false);
	}
	fclose(votantes);
	fclose(postulantes);
	return la_mesa;
}
