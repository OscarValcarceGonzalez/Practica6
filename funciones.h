//
// Created by oscar on 28/04/2023.
//

#ifndef PRACTICA6_FUNCIONES_H
#define PRACTICA6_FUNCIONES_H

#define MAX_PERSONAS 100
#define L 100
enum contacto{
    Favorito,
    Conocido,
    Trabajo
};

typedef struct Persona {
    char nombre[MAX_PERSONAS];
    char apellidos[MAX_PERSONAS];
    char numero[MAX_PERSONAS];
    short int edad;
    enum contacto c;
} tPersona;

typedef struct Agenda {
    tPersona *personas;
    int num_personas;
} tAgenda;

void inicializar_agenda(tAgenda *agenda);
void mostrar_personas(tAgenda *agenda);
void nueva_persona(tAgenda *agenda);
void borrar_persona(tAgenda *agenda);
void crear_fichero(tAgenda * agenda);
void leer_fichero(tAgenda * agenda);

#endif //PRACTICA6_FUNCIONES_H
