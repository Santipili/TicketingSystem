#include <list>
#include <string>
#include <iostream>
#include "../include/Ticket.h"
#include "../include/entidades.h"

using namespace std;


Ticket::Ticket(Incidente incidente, Cliente* cliente){
    listaIncidentes.push_back(incidente);
    this->cliente = cliente;
    this->estado = "Espera";
}

Ticket::~Ticket(){}

void Ticket::enviarMensaje(const Mensaje& agregarMensaje){
    // este metodo es privado para q al crear un mensaje el representante se envie la notificacion al cliente
    for (auto& cuenta : cliente->cuentas) {
        cuenta.sender->sendMessage(agregarMensaje.contenido);
    }
}

void Ticket::setRepresentante(Representante* representante){
    this->representante = representante;
    this->estado="Activo";
}

void Ticket::crearMensajeRepresentante(){
    Mensaje mensaje;

    string texto;
    cout << "Ingresar mensaje"<< endl;
    getline(std::cin, texto);
     
    mensaje.autor = representante->nombre;
    mensaje.destinatario = cliente->nombre;
    mensaje.contenido = texto;

    listaMensajes.push_back(mensaje);
    enviarMensaje(mensaje);
}; 

void Ticket::crearMensajeCliente(){
    Mensaje mensaje;

    string texto;
    cout << "Ingresar mensaje"<< endl;
    getline(std::cin, texto);
     
    mensaje.autor = cliente->nombre;
    mensaje.destinatario = representante->nombre;
    mensaje.contenido = texto;
    listaMensajes.push_back(mensaje);
};

void Ticket::setEstadoTicket(){

    string estado_modificable;
    int opcion ;
    
    cout <<"Estado actual: " << this->getEstado() << endl;

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

int Ticket::getTicketId() const{
    return this->id;
}
string Ticket::getEstado(){
    return this-> estado;
};

void Ticket::getIncidente(){
    for (auto& Incidente : listaIncidentes) {
        cout << Incidente.id << endl;
    }
}

void Ticket::getMensajes(){

    for (auto it = listaMensajes.begin(); it != listaMensajes.end(); ++it) {
        cout << it->autor <<":"<< endl;
        cout <<"        " << it->contenido<< endl;
        }
}
void Ticket::getTicketData(){
    cout <<"Id: "<< id << endl;
    cout <<"Estado: "<< estado << endl;
    cout <<"Cliente: "<< cliente->nombre << endl;
    cout << "Incidentes: " << endl; 
    this->getIncidente();
}

Cliente* Ticket::getCliente(){

    cout << this->cliente->id << endl;
    cout << this->cliente->nombre << endl;
    for (const auto& cuenta : cliente->cuentas) {
        cout << "- Direccion : " << cuenta.direccion << endl;
    }

    return this->cliente;
}

Representante* Ticket::getRepresentante(){

    cout << "Identificador: " << this->representante->id << endl;
    cout << "Nombre: " << this->representante->nombre << endl;

    return this->representante;
}







