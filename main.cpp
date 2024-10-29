
#include <iostream>
#include <queue>
#include <string>
#include <list>
#include "./include/Ticket.h" 
#include "./include/entidades.h"

using namespace std;

int menu() {
    int opcion;
    do {
        std::cout << "Menu de Opciones:" << endl;
        cout << "1. Ingresar como Nuevo Cliente" << endl;
        cout << "2. Ingresar como Cliente existente" << endl;
        cout << "3. Ingresar como Representante" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
    } while (opcion < 1 || opcion > 3);

    return opcion;
}

void agregarClienteACola(queue<Ticket>& cola, Cliente* cliente) {
    Incidente incidente = Incidente();

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

        cout << "Ticket en proceso por el representante " << representante->nombre << endl;
    } else {
        cout << "No hay tickets en la cola." << endl;
    }
}

int MenuCliente(){
    int opcion;
    do {
        cout << "Menu de Opciones:" << endl;
        cout << "1. Ingresar como Cliente" << endl;
        cout << "2. Ingresar como Representante" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
    } while (opcion < 1 || opcion > 3);

    return opcion;
}

int MenuRepresentante(){

}

int main() {
    //esto deberia inicializar el ticketManager
    list<Representante> representantes; //crear una lista predefinida de representantes
    list<Cliente> clientes; //crear una lista predefinida de clientes
    queue<Ticket> colaMostrador;  
    queue<Ticket> colaLlamadas; 
    list<Ticket> ticketsAtendidos; 


    bool salir = false;
    while (!salir) {
        int opcion = menu();
        switch (opcion) {
            case 1: {
                //nuevo cliente (solo puede crear nuevo incidente/ticket)
                Cliente* nuevoCliente =  new Cliente();
                cout << "ingrese su nombre: "<< endl;
                getline(std::cin, nuevoCliente->nombre);
                
                Cuenta nuevaCuenta = Cuenta();
                string direccion;
                cout << "Email: "<< endl;
                cin >> direccion;
                cin.ignore();
                if (direccion != "") {
                    nuevaCuenta.sender= new Email();
                    nuevaCuenta.direccion = direccion;
                    nuevoCliente->cuentas.push_back(nuevaCuenta);
                }
                cout << "Instagram: "<< endl;
                cin >> direccion;
                cin.ignore();
                if (direccion != "") {
                    nuevaCuenta.sender= new Instagram();
                    nuevaCuenta.direccion = direccion;
                    nuevoCliente->cuentas.push_back(nuevaCuenta);
                }
                cout << "Facebook: "<< endl;
                cin >> direccion;
                cin.ignore();
                if (direccion != "") {
                    nuevaCuenta.sender= new Facebook();
                    nuevaCuenta.direccion = direccion;
                    nuevoCliente->cuentas.push_back(nuevaCuenta);
                }
                cout << "Whatsapp: "<< endl;
                cin >> direccion;
                cin.ignore();
                if (direccion != "") {
                    nuevaCuenta.sender= new Whatsapp();
                    nuevaCuenta.direccion = direccion;
                    nuevoCliente->cuentas.push_back(nuevaCuenta);
                }


                int tipoIngreso;
                cout << "Tipo de ingreso: 1 para mostrador, 2 para llamada: ";
                cin >> tipoIngreso;

                if (tipoIngreso == 1) {
                    agregarClienteACola(colaMostrador, nuevoCliente); 
                } else if (tipoIngreso == 2) {
                    agregarClienteACola(colaLlamadas, nuevoCliente);
                }
                break;
            }
            case 2: {
                //existente
                Cliente* clienteIngresante; 
                int idCliente;
                cout << "Id de cliente: ";
                cin >> idCliente;

                for (auto& cliente : clientes) {
                    if (cliente.id == idCliente) {
                        clienteIngresante = &cliente;
                        break;
                    }
                }
                //ver tickets y mensajes
                for (auto& ticket : ticketsAtendidos) {
                    if (ticket.getCliente() == clienteIngresante) {
                        ticket.getTicketData();
                    }
                }

                //agregar nuevo mensaje
                int idticket;
                cout << "Id de ticket: ";
                cin >> idticket;
                Ticket* ticketCliente;

                for (auto& ticket : ticketsAtendidos) {
                    if (ticket.getTicketId() == idticket) {
                        ticketCliente = &ticket;
                        break;
                    }
                }
                ticketCliente->crearMensajeCliente(); // verificar si matchea un ticket o es null

                //agregar incidente 
                //crear nuevo incidente (nuevo ticket)
            }
            case 3: {
                Representante* representanteIngresante;
                // Pedir datos del representante 
                int idRepresentante;
                cout << "Id de representante: ";
                cin >> idRepresentante;

                for (auto& representante : representantes) {
                    if (representante.id == idRepresentante) {
                        representanteIngresante = &representante;
                        break;
                    }
                }

                // Ver Tickets y Mensajes
                for (auto& ticket : ticketsAtendidos) {
                    if (ticket.getRepresentante() == representanteIngresante) {
                        ticket.getTicketData();
                    }
                }

                //Enviar mensaje 
                int idticket;
                cout << "Id de ticket: ";
                cin >> idticket;
                Ticket* ticketRepresentante;

                for (auto& ticket : ticketsAtendidos) {
                    if (ticket.getTicketId() == idticket) {
                        ticketRepresentante = &ticket;
                        break;
                    }
                }
                ticketRepresentante->crearMensajeRepresentante(); 

                //Cambiar estado de ticket
                int idticket;
                cout << "Id de ticket: ";
                cin >> idticket;
                Ticket* ticketRepresentante;

                for (auto& ticket : ticketsAtendidos) {
                    if (ticket.getTicketId() == idticket) {
                        ticketRepresentante = &ticket;
                        break;
                    }
                }
                ticketRepresentante->setEstadoTicket(); 

                //Atender nuevo Ticket
                int tipoAtencion;
                cout << "Atender: 1 para mostrador, 2 para llamada: ";
                cin >> tipoAtencion;

                if (tipoAtencion == 1) {
                    atenderTicket(colaMostrador, representanteIngresante, ticketsAtendidos);
                } else if (tipoAtencion == 2) {
                    atenderTicket(colaLlamadas, representanteIngresante, ticketsAtendidos);
                }
                break;
            }
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
