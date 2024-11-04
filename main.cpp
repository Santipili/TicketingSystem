#include <iostream>
#include <queue>
#include <string>
#include <list>
#include "./include/Ticket.h" 
#include "./include/entidades.h"
// #include "./include/database.h"

using namespace std;


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

    Ticket nuevoTicket = Ticket(incidente, cliente); 
    cola.push(nuevoTicket);       
    cout << "Ticket creado y añadido a la cola." << endl;
}

void atenderTicket(queue<Ticket>& cola, Representante* representante, list<Ticket>& ticketsAtendidos) {
    if (!cola.empty()) {
        Ticket ticketActual = cola.front();
        cola.pop();  // Elimino el ticket de la cola en espera

        ticketActual.setRepresentante(representante);
        ticketActual.setEstadoTicket();
        ticketActual.crearMensajeRepresentante();

        ticketsAtendidos.push_back(ticketActual);

        ticketActual.getTicketData();
        cout << "Ticket en proceso por el representante " << representante->nombre << endl;
    } else {
        cout << "No hay tickets en la cola." << endl;
    }
}

// Función para agregar un nuevo cliente y crear un ticket
void registrarNuevoCliente(queue<Ticket>& colaMostrador, queue<Ticket>& colaLlamadas, list<Cliente>& clientes ) {
    Cliente nuevoCliente;
    cout << "Ingrese su nombre: ";
    getline(cin, nuevoCliente.nombre);

    nuevoCliente.id = clientes.size() + 1001;
    
    // Registro de cuentas
    string direccion;
    Cuenta nuevaCuenta;

    cout << "Email: ";
    getline(cin, direccion);
    if (!direccion.empty()) {
        nuevaCuenta.sender = new Email();
        nuevaCuenta.direccion = direccion;
        nuevoCliente.cuentas.push_back(nuevaCuenta);
    }

    cout << "Instagram: ";
    getline(cin, direccion);
    if (direccion != "") {
        nuevaCuenta.sender= new Instagram();
        nuevaCuenta.direccion = direccion;
        nuevoCliente.cuentas.push_back(nuevaCuenta);
    }

    cout << "Facebook: ";
    getline(cin, direccion);
    if (direccion != "") {
        nuevaCuenta.sender= new Facebook();
        nuevaCuenta.direccion = direccion;
        nuevoCliente.cuentas.push_back(nuevaCuenta);
    }

    cout << "Whatsapp: ";
    getline(cin, direccion);
    if (direccion != "") {
        nuevaCuenta.sender= new Whatsapp();
        nuevaCuenta.direccion = direccion;
        nuevoCliente.cuentas.push_back(nuevaCuenta);
    }

    clientes.push_back(nuevoCliente);
    cout << "Id de cliente: " << nuevoCliente.id << endl;
    cout << "Nuevo Cliente registrado." << endl;

    // Registro de cliente en cola de mostrador o llamada
    int tipoIngreso;
    cout << "Tipo de ingreso: 1 para mostrador, 2 para llamada: ";
    cin >> tipoIngreso;
    cin.ignore();
    if (tipoIngreso == 1) {
        agregarClienteACola(colaMostrador, &nuevoCliente);
    } else if (tipoIngreso == 2) {
        agregarClienteACola(colaLlamadas, &nuevoCliente);
    }
}

// Función para gestionar un cliente existente
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

        int opcionCliente = menuCliente();
        switch (opcionCliente) {
            case 1:
                // Mostrar lista de tickets
                for (auto& ticket : ticketsAtendidos) {
                    if (ticket.getCliente()->id == clienteIngresante->id) {
                        cout << "Id de ticket: " << ticket.getTicketId() << endl;
                        ticket.getTicketData();
                    }
                }
                cin.ignore();
                break;
            case 2:
                // Leer mensajes de un ticket
                cout << "Id de ticket: ";
                cin >> idTicket;
                
                for (auto& ticket : ticketsAtendidos) {
                    if (ticket.getTicketId() == idTicket) {
                        ticketCliente = &ticket;
                        break;
                    }
                }
                if (ticketCliente) {
                    ticketCliente->getMensajes();
                }
                ticketCliente = nullptr;
                break;
            case 3:
                // Agregar nuevo mensaje
                cout << "Id de ticket: ";
                cin >> idTicket;

                for (auto& ticket : ticketsAtendidos) {
                    if (ticket.getTicketId() == idTicket) {
                        ticketCliente = &ticket;
                        break;
                    }
                }

                if (ticketCliente) {
                    ticketCliente->crearMensajeCliente();
                }
                ticketCliente = nullptr;
                break;
        }
    }
}

// Función para gestionar un representante
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
        int opcionRepresentante = menuRepresentante();
        switch (opcionRepresentante) {
            case 1:
                // Ver Tickets y Mensajes
                for (auto& ticket : ticketsAtendidos) {
                    if (ticket.getRepresentante() == representanteIngresante) {
                        ticket.getTicketData();
                    }
                }
                break;
            case 2:
                // Leer mensajes de un ticket
                cout << "Id de ticket: ";
                cin >> idTicket;
                
                for (auto& ticket : ticketsAtendidos) {
                    if (ticket.getTicketId() == idTicket) {
                        ticketRepresentante = &ticket;
                        break;
                    }
                }
                if (ticketRepresentante) {
                    ticketRepresentante->getMensajes();
                }

                break;
            case 3:
                // Agregar nuevo mensaje
                cout << "Id de ticket: ";
                cin >> idTicket;

                for (auto& ticket : ticketsAtendidos) {
                    if (ticket.getTicketId() == idTicket) {
                        ticketRepresentante = &ticket;
                        break;
                    }
                }
                if (ticketRepresentante) {
                    ticketRepresentante->crearMensajeCliente();
                }
                break;
            case 4:
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
        }      
       
    }
}

    list<Representante> representantes;
    list<Cliente> clientes;
    list<Ticket> ticketsAtendidos;
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


int main() {

    queue<Ticket> colaMostrador;  
    queue<Ticket> colaLlamadas; 

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
