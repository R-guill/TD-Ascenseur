#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <stdio.h>
#include <stdlib.h>

#include "person.h"

//définition de la structure de l'ascenseur
typedef struct _Elevator {
    int capacity;    // capacité maximale de la cabine
    int currentFloor;// étage courant
    int targetFloor; // destination
    PersonList *persons; // personnes dans la cabine
    int update; //rajoutée pour gérer  l'affichage des entrées et des sorties sur un étage
    
} Elevator;


//définition de la structure de l'ascenseur
typedef struct _Building {
    int nbFloor; // nombre d’étage des l’immeuble
    Elevator *elevator; // la cabine d’ascenseur
    PersonList **waitingLists; // array of waiting list (one per floor)
} Building;

Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons);
Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists);

PersonList* exitElevator(Elevator *elevator);
PersonList* enterElevator(Elevator *elevator, PersonList *list);
void stepElevator(Building *b);

#endif
