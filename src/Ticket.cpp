#include <list>
#include <string>
#include <iostream>
#include "../include/Ticket.h"
#include "../include/entidades.h"

using namespace std;


Ticket::Ticket(Incidente incidente, Cliente* cliente, int id){
    listaIncidentes.push_back(incidente);
    this->cliente = cliente;
    this->id = id;
    this->estado = "Espera";
}

Ticket::~Ticket(){}

void Ticket::enviarMensaje(const Mensaje& agregarMensaje){
    // este metodo es privado para q al crear un mensaje el representante se envie la notificacion al cliente
    for (auto& cuenta : cliente->cuentas) {
        cuenta.sender->sendMessage(agregarMensaje.contenido, cuenta.direccion);
    }
    cout << endl;
}

void Ticket::setRepresentante(Representante* representante){
    this->representante = representante;
    this->estado="Activo";
}

void Ticket::crearMensajeRepresentante(string message){
    Mensaje mensaje;

    mensaje.autor = representante->nombre;
    mensaje.destinatario = cliente->nombre;
    mensaje.contenido = message;

    listaMensajes.push_back(mensaje);
    enviarMensaje(mensaje);
}; 

void Ticket::crearMensajeCliente(string message){
    Mensaje mensaje;
     
    mensaje.autor = cliente->nombre;
    mensaje.destinatario = representante->nombre;
    mensaje.contenido = message;
    listaMensajes.push_back(mensaje);
};

void Ticket::setEstadoTicket(){

    string estado_modificable;
    int opcion ;

    do{
        cout << "Seleccione el nuevo estado del ticket con su respectivo numero: " << endl;
        cout << " 1_ Activo " << endl;
        cout << " 2_ Espera" << endl;
        cout << " 3_ Re-Abierto " << endl;
        cout << " 4_ Cerrado " << endl;
        cin >> opcion;
    } while (opcion < 1 || opcion > 4);


    switch (opcion){
        case 1:
        estado_modificable = "Activo";
        break;

        case 2:
        estado_modificable = "Espera";
        break;

        case 3:
        estado_modificable = "Re-Abierto";
        break;

        case 4:
        estado_modificable = "Cerrado";
        break;

    };

    this->estado = estado_modificable;
};

void Ticket::crearIncidente(){

    Incidente nuevo_incidente;

    if (listaIncidentes.empty()){
        nuevo_incidente.id = 001;
    } else {
        nuevo_incidente.id = listaIncidentes.back().id + 1;
    }

    cout << "Ingrese el contenido del nuevo incidente: " << endl;
    getline(cin, nuevo_incidente.contenido);

    listaIncidentes.push_back(nuevo_incidente);

    cout << "Nuevo incidente agregado con ID: " << nuevo_incidente.id << endl;
}

void Ticket::readIncidente(){
    int count = 1;
    for (auto& Incidente : listaIncidentes) {
        cout << count<< "_ ";
        cout << Incidente.contenido << endl;
        count++;
    }
}

void Ticket::readMensajes(){
    if (listaMensajes.empty()) {
        cout << "No hay mensajes." << endl << endl;
        return;
    }

    for (auto it = listaMensajes.begin(); it != listaMensajes.end(); ++it) {
        cout << it->autor <<":"<< endl;
        cout <<"        " << it->contenido<< endl;
        }
    cout << endl;
}
void Ticket::getTicketData(){
    cout <<"Id: "<< id << endl;
    cout <<"Estado: "<< estado << endl;
    cout <<"Cliente: "<< cliente->nombre << endl;
    cout << "Incidentes: "; 
    this->readIncidente();
}

Cliente* Ticket::getCliente(){
    return this->cliente;
}

Representante* Ticket::getRepresentante(){
    return this->representante;
}

int Ticket::getTicketId() const{
    return this->id;
}
string Ticket::getEstado(){
    return this-> estado;
};








