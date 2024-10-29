#ifndef TICKET_H
#define TICKET_H

#include "entidades.h"
#include <list>
#include <string>


using namespace std;


class Ticket
{
private:
    int id;
    Representante* representante;
    Cliente* cliente;
    list<Incidente> listaIncidentes;
    list<Mensaje> listaMensajes;
    string estado;

    void enviarMensaje(const Mensaje& agregarMensaje);
    
public:
    Ticket(Incidente incidente, Cliente* cliente);
    ~Ticket(){};

    void crearMensajeRepresentante();
    void crearMensajeCliente();
    void setEstadoTicket();
    void setRepresentante(Representante* representante);
    void crearIncidente();

    void getTicketData();
    void getIncidente();
    void getMensajes();
    string getEstado();
    int getTicketId();


    Cliente* getCliente();
    Representante* getRepresentante();


};

#endif
