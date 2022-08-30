#ifndef PERSON_H
#define PERSON_H

#include <stdio.h>
#include <stdlib.h>

//définition de la structure des personnes
typedef struct _Person {
    int src;  //étage de depart
    int dest; //étage d'arrivee
} Person;
//définition de la structure des listes de personnes par une liste chainée
typedef struct _PersonList {
    Person *person;
    struct _PersonList *next; //pointe vers la personne suivante
} PersonList;

Person* createPerson(int src, int dest); 
PersonList* insert(Person *p, PersonList *list);
int LengthPersonList(PersonList *list);




#endif
