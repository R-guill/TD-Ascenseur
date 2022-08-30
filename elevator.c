#include "elevator.h"



//Création d'un ascenseur
Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons){
    Elevator *elevator = malloc(sizeof(Elevator));
    elevator -> capacity = capacity;
    elevator -> currentFloor = currentFloor;
    elevator-> persons = persons;
    elevator->update = 0;
    

    return elevator;
}

//Création d'un immeuble
Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists){
    
    Building *building = malloc(sizeof(Building));

    building->nbFloor = nbFloor;
    building->elevator = elevator;
    building->waitingLists = waitingLists;
    return building;
}

//Renvoie la liste des personnes descendant à un étage
PersonList *exitElevator(Elevator *elevator){
    if(!(elevator->update)){
        PersonList *personsLeaving=NULL;
        PersonList *personsStaying=NULL;
        int currentFloor=elevator->currentFloor;

        while(elevator->persons){//tant que l'ascenseur n'est pas vide
            if(elevator->persons->person->dest==currentFloor){
                personsLeaving=insert(elevator->persons->person, personsLeaving);//si des personnes doivent descendre on les mets sur la liste des personnes sortantes
                
            }
            else{
                personsStaying=insert(elevator->persons->person, personsStaying);//sinon elles restent dans l'ascenseur
            }
            elevator->persons=elevator->persons->next;
        }
        //mise à jour des personnes restantes dans l'ascenseur
        elevator->persons=personsStaying;
        elevator->update=1;
        return personsLeaving;
    }
    else{
        return elevator->persons;
    }
}
//Fait entrer les personnes qui attendent si c'est possible
PersonList* enterElevator(Elevator *elevator, PersonList *waitingList){
    int currentFloor=elevator->currentFloor;
    PersonList *personsInElevator = elevator->persons;
    int numberInElevator = LengthPersonList(personsInElevator);
    while(numberInElevator!=elevator->capacity && waitingList){//tant qu'il y a de la place dans l'ascenseur on fait rentrer les gens
        personsInElevator=insert(waitingList->person, personsInElevator);
        //actualise l'ascenseur après l'appel de la fonction de sortie de l'ascenseur
        if(waitingList->person->dest==elevator->currentFloor){
            elevator->update=0;
        }
        waitingList=waitingList->next;
        numberInElevator++;
    }
    elevator->persons=personsInElevator;
    return waitingList;
}
//Déplacement de l'ascenseur

void stepElevator(Building *building){
    if(building->elevator->currentFloor == building->elevator->targetFloor){//quand l'ascenseur arrive à l'étage demandé
        exitElevator(building->elevator);//on fait sortir ceux qui sont arrivés
        *(building->waitingLists + building->elevator->currentFloor) = enterElevator(building->elevator, *(building->waitingLists + building->elevator->currentFloor));//on fait entrer ceux qui attendent à l'étage auquel on vient d'arriver
    }
    else if(building->elevator->currentFloor > building->elevator->targetFloor){//sinon tant que l'on est a un étage inférieur à celui demandé, on fait monter l'ascenseur
        building->elevator->currentFloor--;
    }
    else{
        building->elevator->currentFloor++;//sinon on le fait descendre
    }
}
