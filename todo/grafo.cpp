#include "../include/entidades.h"
#include "../include/Ticket.h"
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <list>
#include <iostream>
#include <string>


class ticketSystem{

private:

queue<Ticket> colaTickets;
queue<Ticket> colaTicketsEspera;
queue<Ticket> colaTicketsReabiertos;
list<Representante> RepresentantesDisponibles;
unordered_map<int,unordered_set<int>> graph;

public:

void agregarTicket(const Ticket& ticket){
    colaTickets.push(ticket);
}

void redireccionarTicket(){

    queue<Ticket> redirect;

    while (!redirect.empty()){
        redirect.push(colaTickets.front());
        colaTickets.pop();
    }

    while (!redirect.empty()){
        Ticket ticket = redirect.front();
        redirect.pop();

        if(ticket.getEstado()== "Espera"){
            colaTicketsEspera.push(ticket);
            cout << "Redirigido a cola espera" << endl;
        } else {
            colaTicketsReabiertos.push(ticket);
        }
    }
}


void representantesDisponibles(const list<Representante> representantes){

    RepresentantesDisponibles.assign(representantes.begin(),representantes.end());
}


Ticket gestorQueue(){
            
    if (RepresentantesDisponibles.empty()) {
    cout << "No hay representantes disponibles." << endl;
    return;
    }

    Ticket reabierto;
    Ticket espera;
    int opcion;

    if (!colaTicketsEspera.empty()) {
            espera = colaTicketsEspera.front();
        }
    if (!colaTicketsReabiertos.empty()) {
            reabierto = colaTicketsReabiertos.front();
        }   

    cout << "seleccionar el tipo de ticket a atender: "<< endl;
    cout << "1- Ticket en espera"<< endl;
    cout << "2- Ticket reabierto"<< endl;
    cout << "3- No atender ticket" << endl;
    cin >> opcion;

    if (opcion == 1){
        return espera;
    }
    if (opcion == 2){
        return reabierto;
    }
    else{
    return gestionarRepresentante();}
}

void crearRelacion(int idRepresentante )
{}

