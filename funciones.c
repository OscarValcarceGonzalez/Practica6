//
// Created by oscar on 28/04/2023.
//

#include "funciones.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int menu() {
    int opcion = 1;
    tAgenda agenda;
    inicializar_agenda(&agenda);

    while (opcion != 0) {

        printf("\n\n\n\n\n\n\n__________________________________________\n");
        printf("Bienvenido a la Agenda: \n");
        printf("1 - Listado de personas."
               "\n2 - Nueva persona."
               "\n3 - Borrar persona."
               "\n4 - Guardar agenda en fichero de texto"
               "\n5 - Leer agenda de fichero de texto"
               "\n0 - Salir.\n");

        printf("\nElige una opcion: \n");
        scanf("%i",&opcion);
        switch (opcion) {
            case 1:
                printf("Listado de personas:\n");
                mostrar_personas(&agenda);
                break;

            case 2:
                printf("Nueva persona.\n");
                nueva_persona(&agenda);
                break;

            case 3:
                printf("Borrar persona.\n");
                borrar_persona(&agenda);
                break;

            case 4:
                printf("Guardar agenda en fichero de texto.\n");
                crear_fichero(&agenda);
                break;

            case 5:
                printf("Leer agenda de fichero de texto.\n");
                leer_fichero(&agenda);
                break;

            default:
                printf("No introduciste ningun valor correcto.\n");

        }
    }
    printf("\nHas terminado la practica.");
}

void inicializar_agenda(tAgenda *agenda) {
    agenda->personas = (tPersona*)malloc(MAX_PERSONAS * sizeof(tPersona));
    agenda->num_personas = 0;
}

void mostrar_personas(tAgenda *agenda) {
    for (int i = 0; i < agenda->num_personas; i++) {
        printf("%d %s %s %s %d", i, agenda->personas[i].nombre, agenda->personas[i].apellidos, agenda->personas[i].numero, agenda->personas[i].edad);

        switch (agenda->personas[i].c) {
            case Favorito:
                printf("FAVORITO\n");
                break;
            case Conocido:
                printf("CONOCIDO\n");
                break;
            case Trabajo:
                printf("TRABAJO\n");
                break;
            default:
                printf("\n");
                break;
        }
    }
}

void nueva_persona(tAgenda *agenda) {
    if (agenda->num_personas < MAX_PERSONAS) {
        tPersona nueva;

        printf("\nIntroduzca los datos de la nueva persona:\n");
        printf("\nNombre: \n");
        scanf("%s", nueva.nombre);
        getchar();                                                      //Para vaciar el buffer
        printf("\nApellidos: \n");
        fgets(nueva.apellidos, MAX_PERSONAS, stdin);
        printf("\nNumero de telefono: \n");
        scanf("%s", nueva.numero);
        printf("\nEdad: \n");
        scanf("%hd", &nueva.edad);
        printf("\nTipo de contacto (0-FAVORITO, 1-CONOCIDO, 2-TRABAJO): \n");
        scanf("%d", &nueva.c);

        agenda->personas[agenda->num_personas] = nueva;
        agenda->num_personas++;
        printf("\nPersona metida correctamente.\n");
    } else {
        printf("\nNo se pueden meter mas personas a la agenda.\n");
    }
}

void borrar_persona(tAgenda *agenda) {
    int num_persona;

    printf("\nIndique el numero de la persona a borrar: \n");
    scanf("%d", &num_persona);

    if (num_persona >= 1 && num_persona <= agenda->num_personas) {
        tPersona *persona_a_borrar = &agenda->personas[num_persona - 1];

        printf("\nUsted desea borrar %d;%s;%s;%s;%d;", num_persona, persona_a_borrar->nombre,
               persona_a_borrar->apellidos, persona_a_borrar->numero, persona_a_borrar->edad);
        switch (persona_a_borrar->c) {
            case Favorito:
                printf("FAVORITO\n");
                break;
            case Conocido:
                printf("CONOCIDO\n");
                break;
            case Trabajo:
                printf("TRABAJO\n");
                break;
            default:
                break;
        }

        printf("\n¿Seguro? S/N: ");
        char respuesta[2];
        scanf("%s", respuesta);

        if (respuesta[0] == 'S' || respuesta[0] == 's') {
            // Borramos la persona de la agenda
            for (int i = num_persona - 1; i < agenda->num_personas - 1; i++) {
                agenda->personas[i] = agenda->personas[i + 1];
            }

            // Disminuimos el contador de personas
            agenda->num_personas--;

            printf("\nPersona borrada\n");
        }
    } else {
        printf("\nNumero de persona incorrecto\n");
    }
}

void crear_fichero(tAgenda * agenda){

    char fichero[L];
    int escritura = 0;
    printf("Indique el nombre del fichero de texto a escribir: ");
    scanf("%s", fichero);

    FILE *f = fopen(fichero, "r");                          //Se abre el fichero en modo lectura

    if(f != NULL){                                                          //Si tiene datos se tendrá que sobreescribir

        char eleccion;

        printf("\nEl fichero %s ya existe, ¿desea sobrescribirlo? (S/N): ",fichero);
        scanf(" %c", &eleccion);
        fclose(f);

        if(eleccion == 'S'|| eleccion == 's'){
            escritura = 1;
        }else{
            printf("\nOperacion cancelada");
        }

    }else{
        escritura = 1;
    }

    if(escritura == 1){
        f = fopen(fichero, "w");
        if(f == NULL){
            perror("Error en la apertura del archivo en modo escritura");
        }
        for (int i = 0; i < agenda->num_personas; ++i) {
            fprintf(f, "%i;", i);
            fprintf(f, "%s;", agenda->personas[i].nombre);
            fprintf(f, "%s;", agenda->personas[i].apellidos);
            fprintf(f, "%i;", agenda->personas[i].edad);
            fprintf(f, "%s;", agenda->personas[i].numero);

            switch (agenda->personas[i].c) {
                case Favorito:
                    fprintf(f, "FAVORITO\n");
                    break;
                case Conocido:
                    fprintf(f, "CONOCIDO\n");
                    break;
                case Trabajo:
                    fprintf(f, "TRABAJO\n");
                    break;
                default:
                    printf("\n");
                    break;
            }
        }

        if(fclose(f) != 0){
            perror("Error en el cierre de fichero");
        }
    }
}

void leer_fichero(tAgenda * agenda){
    int escritura = 0;
    if(agenda->num_personas > 0){
        char eleccion;
        printf("Existen datos en memoria que se sobrescribirán al cargar los datos del\n"
               "fichero. ¿Desea continuar? S/N: ");
        scanf(" %c",&eleccion);

        if(eleccion == 's' || eleccion == 'S'){
            escritura = 1;
        }else{
            printf("\nOperación cancelada");
        }
    }else{
        escritura = 1;
    }

    if(escritura == 1){

        char fichero[L];

        printf("\nIndique el nombre del fichero de texto origen: ");
        scanf("%s", fichero);

        FILE *f = fopen(fichero, "r");

        if(f == NULL){
            perror("\nError en la apertura del fichero en modo escritura");
        }else{
            agenda->num_personas = 0;
            char opcion[100];
            while(!feof(f)){

                tPersona nueva;
                fscanf(f, "%*d");
                fscanf(f,"%s",nueva.nombre);
                fgets(nueva.apellidos,100,f);

                fscanf(f," %s",nueva.numero);
                fscanf(f," %hd",&nueva.edad);


                char tipo_contacto[L];
                fscanf(f, "%s", tipo_contacto);               //Se ponen los asteriscos para que se detecten pero no se guarden

                if(strcmp(tipo_contacto, "FAVORITO") == 0){
                    nueva.c = Favorito;
                }else if(strcmp(tipo_contacto, "CONOCIDO") == 0){
                    nueva.c = Conocido;
                } else if (strcmp(tipo_contacto, "TRABAJO") == 0){
                    nueva.c = Trabajo;
                }

                agenda->personas[agenda->num_personas] = nueva;
                agenda->num_personas++;
            }
            fclose(f);
        }

    }


}
