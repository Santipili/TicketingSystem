#include "../include/database.h"
#include "../include/entidades.h"
#include "../include/Ticket.h"
#include "../include/MessageSender.h"

Email PoolMessageSender::emailSender = {};
Instagram PoolMessageSender::instagramSender = {};
Facebook PoolMessageSender::facebookSender = {};
Whatsapp PoolMessageSender::whatsappSender = {};

Cuenta PoolCuentas::cuenta1 = { "Jose@gmail.com", new Email() };
Cuenta PoolCuentas::cuenta2 = { "Gabriel@gmail.com", new Email() };

Cliente PoolClientes::cliente1 = {1001, "Jose", "B7600FKA", list<Cuenta>{ PoolCuentas::cuenta1 }};
Cliente PoolClientes::cliente2 = {1002, "Gabriel", "B7600FKH", list<Cuenta>{ PoolCuentas::cuenta2 }};
Cliente PoolClientes::cliente3 = {1003, "Pimentel", "B7600FKB", list<Cuenta>{ PoolCuentas::cuenta2 }};


Representante PoolRepresentantes::representante1 = { 1001, "Santiago" };
Representante PoolRepresentantes::representante2 = { 1002, "Mateo" };

Incidente Poolincidentes::incidente = { 1001, "Cuando uses la fuerza, acordate de limpiar el lado oscuro" };

Ticket PoolTickets::ticket1 = { Poolincidentes::incidente, &PoolClientes::cliente1, 1 };