#ifndef TICKETMANAGER.H
#define TICKETMANAGER.H

#include <list>
#include <queue>
#include "./Ticket.h"
#include "./entidades.h"

class TicketManager{
    private:
        list<Representante> representantes; //crear una lista predefinida de representantes
        list<Cliente> clientes; //crear una lista predefinida de clientes
        queue<Ticket> colaMostrador;  
        queue<Ticket> colaLlamadas; 
        list<Ticket> ticketsAtendidos; 
    public:
        TicketManager(){};
        ~TicketManager(){};
};


#endif