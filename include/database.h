#ifndef DATABASE_H
#define DATABASE_H

#include "entidades.h"
#include "Ticket.h"
#include "MessageSender.h"
#include <iostream>
#include <list>

struct PoolMessageSender{
    static Email emailSender;
    static Instagram instagramSender;
    static Facebook facebookSender;
    static Whatsapp whatsappSender;
};


struct PoolCuentas {
    static Cuenta cuenta1;
    static Cuenta cuenta2;
};


struct PoolClientes {
    static Cliente cliente1;
    static Cliente cliente2;
    static Cliente cliente3;

};


struct PoolRepresentantes {
    static Representante representante1;
    static Representante representante2;
};


struct Poolincidentes {
    static Incidente incidente;
};


struct PoolTickets {
    static Ticket ticket1;
};

#endif 
