#ifndef DATABASE_H
#define DATABASE_H

#include "entidades.h"
#include "Ticket.h"
#include "MessageSender.h"
#include <iostream>
#include <list>

extern std::list<Cliente> clientes;
extern std::list<Representante> representantes;
extern std::list<Ticket> ticketsAtendidos;

void inicializarSistema(); // Declaración de la función para inicializar los datos

#endif // DATABASE_H
