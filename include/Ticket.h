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
    Ticket(){};
    Ticket(Incidente incidente, Cliente* cliente, int id);
    ~Ticket();

    void crearMensajeRepresentante(string message);
    void crearMensajeCliente(string message);
    void setEstadoTicket();
    void setRepresentante(Representante* representante);
    void crearIncidente();

    void readIncidente();
    void readMensajes();    
    void getTicketData();

    string getEstado();
    int getTicketId() const;
    Cliente* getCliente();
    Representante* getRepresentante();

};

#endif
