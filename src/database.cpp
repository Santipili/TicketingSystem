#include "../include/database.h"

std::list<Cliente> clientes;
std::list<Representante> representantes;
std::list<Ticket> ticketsAtendidos;

void inicializarSistema() {
    // Inicializar cuentas
    Cuenta cuenta1;
    cuenta1.direccion = "Jose@gmail.com";
    cuenta1.sender = new Email();

    Cuenta cuenta2;
    cuenta2.direccion = "Gabriel@gmail.com";
    cuenta2.sender = new Email();

    // Inicializar clientes
    Cliente cliente1;
    cliente1.id = 1001;
    cliente1.nombre = "Jose";
    cliente1.cuentas.push_back(cuenta1);

    Cliente cliente2;
    cliente2.id = 1002;
    cliente2.nombre = "Gabriel";
    cliente2.cuentas.push_back(cuenta2);

    clientes.push_back(cliente1);
    clientes.push_back(cliente2);

    // Inicializar representantes
    Representante representante1;
    representante1.id = 1001;
    representante1.nombre = "Santiago";

    Representante representante2;
    representante2.id = 1002;
    representante2.nombre = "Mateo";

    representantes.push_back(representante1);
    representantes.push_back(representante2);

    // Inicializar tickets
    Incidente incidente;
    incidente.id = 1001;
    incidente.contenido = "Cuando uses la fuerza, acordate de limpiar el lado oscuro";

    Ticket ticket1(incidente, &cliente1);
    ticket1.setRepresentante(&representante1);
    ticketsAtendidos.push_back(ticket1);
}
