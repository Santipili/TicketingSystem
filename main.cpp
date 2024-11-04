#include <iostream>
#include <queue>
#include <string>
#include <list>
#include <vector>
#include "./include/Ticket.h" 
#include "./include/entidades.h"
using namespace std;

struct PoolMessageSender{
    static Email emailSender;
    static Instagram instagramSender;
    static Facebook facebookSender;
    static Whatsapp whatsappSender;
};

Email PoolMessageSender::emailSender = {};
Instagram PoolMessageSender::instagramSender = {};
Facebook PoolMessageSender::facebookSender = {};
Whatsapp PoolMessageSender::whatsappSender = {};

struct PoolCuentas {
    static Cuenta cuenta1;
    static Cuenta cuenta2;
};
Cuenta PoolCuentas::cuenta1 = { "Jose@gmail.com", new Email() };
Cuenta PoolCuentas::cuenta2 = { "Gabriel@gmail.com", new Email() };

struct PoolClientes {
    static Cliente cliente1;
    static Cliente cliente2;
};
Cliente PoolClientes::cliente1 = {1001, "Jose", list<Cuenta>{ PoolCuentas::cuenta1 }};
Cliente PoolClientes::cliente2 = {1002, "Gabriel", list<Cuenta>{ PoolCuentas::cuenta2 }};

struct PoolRepresentantes {
    static Representante representante1;
    static Representante representante2;
};
Representante PoolRepresentantes::representante1 = { 1001, "Santiago" };
Representante PoolRepresentantes::representante2 = { 1002, "Mateo" };

struct Poolincidentes {
    static Incidente incidente;
};
Incidente Poolincidentes::incidente = { 1001, "Cuando uses la fuerza, acordate de limpiar el lado oscuro" };

struct PoolTickets {
    static Ticket ticket1;
};
Ticket PoolTickets::ticket1 = { Poolincidentes::incidente, &PoolClientes::cliente1, 1 };

list<Representante> representantes;
list<Cliente> clientes;
list<Ticket> ticketsAtendidos;
queue<Ticket> colaMostrador;  
queue<Ticket> colaLlamadas; 

void inicializarSistema() {
    // Inicializar representantes
    clientes.push_back(PoolClientes::cliente1);
    clientes.push_back(PoolClientes::cliente2);

    representantes.push_back(PoolRepresentantes::representante1);
    representantes.push_back(PoolRepresentantes::representante2);
    PoolTickets::ticket1.setRepresentante(&PoolRepresentantes::representante1);

    ticketsAtendidos.push_back(PoolTickets::ticket1);
}

int menuPrincipal() {
    int opcion;
    do {
        cout << "Menu de Opciones:" << endl;
        cout << "1. Ingresar como Nuevo Cliente" << endl;
        cout << "2. Ingresar como Cliente existente" << endl;
        cout << "3. Ingresar como Representante" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();
    } while (opcion < 1 || opcion > 4);
    
    return opcion;
}

int menuCliente() {
    int opcion;
    do {
        cout << "Menu Cliente:" << endl;
        cout << "1. Ver tickets" << endl;
        cout << "2. Leer mensajes de un ticket" << endl;
        cout << "3. Agregar nuevo mensaje" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();
    } while (opcion < 1 || opcion > 4);
    return opcion;
}

int menuRepresentante() {
    int opcion;
    do {
        cout << "Menu Representante:" << endl;
        cout << "1. Ver tickets atendidos" << endl;
        cout << "2. Leer mensajes de un ticket" << endl;
        cout << "3. Agregar nuevo mensaje" << endl;
        cout << "4. Ver tickets pendientes" << endl;
        cout << "5. Atender Nuevo tickets" << endl;
        cout << "6. Cambiar estado de ticket" << endl;
        cout << "7. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();
    } while (opcion < 1 || opcion > 7);
    return opcion;
}

void agregarClienteACola(queue<Ticket>& cola, Cliente* cliente) {
    Incidente incidente;
    cout <<"Ingrese el incidente: " << endl;
    getline(cin, incidente.contenido);

    Ticket nuevoTicket = Ticket(incidente, cliente, ticketsAtendidos.size() + 1); 
    cola.push(nuevoTicket);       
    cout << "Ticket creado y agregado a la cola." << endl<< endl;    
}

void atenderTicket(queue<Ticket>& cola, Representante* representante, list<Ticket>& ticketsAtendidos) {
    if (!cola.empty()) {
        Ticket ticketActual = cola.front();

        ticketActual.getTicketData();
        ticketActual.setEstadoTicket();
        ticketActual.setRepresentante(representante);

        string texto;
        cout << "Ingresar mensaje"<< endl;
        getline(std::cin, texto);
        ticketActual.crearMensajeRepresentante(texto);

        ticketsAtendidos.push_back(ticketActual);

        cout << "Ticket en proceso por el representante " << representante->nombre << endl;
        cola.pop();  
    } else {
        cout << "No hay tickets en la cola." << endl;
    }
}

void registrarNuevoCliente(queue<Ticket>& colaMostrador, queue<Ticket>& colaLlamadas, list<Cliente>& clientes ) {
    cout << "Ingrese su nombre: ";
    string nombre;
    getline(cin, nombre);

    int id = clientes.size() + 1001;

    string direccion;
    Cuenta nuevaCuenta;
    list <Cuenta> cuentasCliente;

    cout << "Email: ";
    getline(cin, direccion);
    if (!direccion.empty()) {
        nuevaCuenta.sender = &PoolMessageSender::emailSender;
        nuevaCuenta.direccion = direccion;
        cuentasCliente.push_back(nuevaCuenta);
    }

    cout << "Instagram: ";
    getline(cin, direccion);
    if (direccion != "") {
        nuevaCuenta.sender= &PoolMessageSender::instagramSender;
        nuevaCuenta.direccion = direccion;
        cuentasCliente.push_back(nuevaCuenta);
    }

    cout << "Facebook: ";
    getline(cin, direccion);
    if (direccion != "") {
        nuevaCuenta.sender= &PoolMessageSender::facebookSender;
        nuevaCuenta.direccion = direccion;
        cuentasCliente.push_back(nuevaCuenta);
    }

    cout << "Whatsapp: ";
    getline(cin, direccion);
    if (direccion != "") {
        nuevaCuenta.sender= &PoolMessageSender::whatsappSender;
        nuevaCuenta.direccion = direccion;
        cuentasCliente.push_back(nuevaCuenta);
    }

    clientes.emplace_back( id, nombre, cuentasCliente );
    cout << "Nuevo Cliente registrado." << endl;

    // Registro de cliente en cola de mostrador o llamada
    int tipoIngreso;
    cout << "Tipo de ingreso: 1 para mostrador, 2 para llamada: ";
    cin >> tipoIngreso;
    cin.ignore();
    if (tipoIngreso == 1) {
        agregarClienteACola(colaMostrador, &clientes.back());
    } else if (tipoIngreso == 2) {
        agregarClienteACola(colaLlamadas, &clientes.back());
    }
}

void gestionarClienteExistente(list<Cliente>& clientes, list<Ticket>& ticketsAtendidos) {
    int idCliente;
    cout << "Id de cliente: ";
    cin >> idCliente;

    Cliente* clienteIngresante;
    for (auto& cliente : clientes) {
        if (cliente.id == idCliente) {
            clienteIngresante = &cliente;
            break;
        }
    }

    if (clienteIngresante) {
        int idTicket;
        Ticket* ticketCliente = nullptr;

        bool salir = false;
        while (!salir) {
            int opcionCliente = menuCliente();
            switch (opcionCliente) {
                case 1:
                    // Mostrar lista de tickets
                    for (auto& ticket : ticketsAtendidos) {
                        if (ticket.getCliente()->id == clienteIngresante->id) {
                            ticket.getTicketData();
                        }
                    }
                    cin.ignore();
                    break;
                case 2:
                    // Leer mensajes de un ticket
                    cout << "Id de ticket: ";
                    cin >> idTicket;
                    cin.ignore();
                    
                    for (auto& ticket : ticketsAtendidos) {
                        if (ticket.getTicketId() == idTicket) {
                            ticketCliente = &ticket;
                            break;
                        }
                    }
                    if (ticketCliente) {
                        ticketCliente->readMensajes();
                    }
                    ticketCliente = nullptr;
                    break;
                case 3:
                    // Agregar nuevo mensaje
                    cout << "Id de ticket: ";
                    cin >> idTicket;
                    cin.ignore();

                    for (auto& ticket : ticketsAtendidos) {
                        if (ticket.getTicketId() == idTicket) {
                            ticketCliente = &ticket;
                            break;
                        }
                    }

                    if (ticketCliente) {
                        string texto;
                        cout << "Ingresar mensaje"<< endl;
                        getline(std::cin, texto);
                        ticketCliente->crearMensajeCliente(texto);
                    }
                    ticketCliente = nullptr;
                    break;
                case 4:
                    salir = true;
                    break;
            }
        }
    }
}

void gestionarRepresentante(queue<Ticket>& colaMostrador, queue<Ticket>& colaLlamadas, list<Ticket>& ticketsAtendidos, list<Representante>& representantes) {
    int idRepresentante;
    cout << "Id de representante: ";
    cin >> idRepresentante;

    Representante* representanteIngresante = nullptr;
    for (auto& representante : representantes) {
        if (representante.id == idRepresentante) {
            representanteIngresante = &representante;
            break;
        }
    }

    if (representanteIngresante) {
        int idTicket;
        Ticket* ticketRepresentante = nullptr;
        std::vector<Ticket> tickets;

        bool salir = false;
        while (!salir) {
            int opcionRepresentante = menuRepresentante();
            switch (opcionRepresentante) {
                case 1:
                    // Ver Tickets y Mensajes
                    for (auto& ticket : ticketsAtendidos) {
                        if (ticket.getRepresentante()->id == representanteIngresante->id) {
                            cout <<"Tickets: "<< endl;
                            ticket.getTicketData();
                            cout << endl;
                        }
                    }
                    break;
                case 2:
                    // Leer mensajes de un ticket
                    cout << "Id de ticket: ";
                    cin >> idTicket;
                    cin.ignore();
                    
                    for (auto& ticket : ticketsAtendidos) {
                        if (ticket.getTicketId() == idTicket) {
                            ticketRepresentante = &ticket;
                            break;
                        }
                    }
                    if (ticketRepresentante) {
                        ticketRepresentante->readMensajes();
                    }
                    else {
                        cout << "Ticket no encontrado." << endl;
                    }

                    break;
                case 3:
                    // Agregar nuevo mensaje
                    cout << "Id de ticket: ";
                    cin >> idTicket;
                    cin.ignore();

                    for (auto& ticket : ticketsAtendidos) {
                        if (ticket.getTicketId() == idTicket) {
                            ticketRepresentante = &ticket;
                            break;
                        }
                    }
                    if (ticketRepresentante) {
                        string texto;
                        cout << "Ingresar mensaje"<< endl;
                        getline(std::cin, texto);
                        ticketRepresentante->crearMensajeRepresentante(texto);
                    }
                    else {
                        cout << "Ticket no encontrado." << endl;
                    }
                    break;
                case 4:
                    // Copiar los elementos de la cola de llamadas al vector

                    cout<<"Llamadas por atender: " << endl;
                    cout << colaLlamadas.size() << endl;
                    cout<< endl;
                    
                    cout <<"Tickets por Mostrador: " << endl;
                    cout << colaMostrador.size() << endl;
                    cout<< endl;


                    break;
                case 5:
                    // Atender nuevo Ticket
                    int tipoAtencion;
                    cout << "Atender: 1 para mostrador, 2 para llamada: ";
                    cin >> tipoAtencion;
                    cin.ignore();
                    if (tipoAtencion == 1) {
                        atenderTicket(colaMostrador, representanteIngresante, ticketsAtendidos);
                    } else if (tipoAtencion == 2) {
                        atenderTicket(colaLlamadas, representanteIngresante, ticketsAtendidos);
                    }
                    break;
                case 6:
                    // Cambiar estado de ticket
                    cout << "Id de ticket: ";
                    cin >> idTicket;
                    cin.ignore();

                    for (auto& ticket : ticketsAtendidos) {
                        if (ticket.getTicketId() == idTicket) {
                            ticketRepresentante = &ticket;
                            break;
                        }
                    }
                    if (ticketRepresentante) {
                        ticketRepresentante->setEstadoTicket();
                    }
                    break;
                case 7:
                    salir = true;
                    break;
            } 
        }     
       
    }
}

int main() {
    inicializarSistema();

    bool salir = false;
    while (!salir) {
        int opcion = menuPrincipal();
        switch (opcion) {
            case 1:
                registrarNuevoCliente(colaMostrador, colaLlamadas, clientes);
                break;
            case 2:
                gestionarClienteExistente(clientes, ticketsAtendidos);
                break;
            case 3:
                gestionarRepresentante(colaMostrador, colaLlamadas, ticketsAtendidos, representantes);
                break;
            case 4:
                salir = true;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    }

    cout << "Programa finalizado." << endl;
    return 0;
}
