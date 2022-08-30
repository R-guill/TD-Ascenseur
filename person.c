

#include "person.h"


//Cree une personne sachant le départ src et l'arrivée dest
Person* createPerson(int src, int dest){
    Person *person=malloc(sizeof(Person));
    person->src = src;
    person->dest = dest;
    return person;

}

//Insere une personne en debut de liste
PersonList* insert(Person *person, PersonList *list){
    PersonList *newlist=malloc(sizeof(PersonList));
    newlist->person = person;
    newlist->next = list;
    return newlist;
}

//renvoie le nombre de personnes dans une liste

int LengthPersonList(PersonList *list){
    int length = 0;
    while (list){
        length++;
        list=list->next;
    }
    return length;
}


