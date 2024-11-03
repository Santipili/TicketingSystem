#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <string>
#include <list>
#include "./MessageSender.h"

using namespace std;

struct Cuenta
{
    MessageSender *sender;
    string direccion;

    Cuenta() : direccion("") {};
};

struct Representante
{
    int id;
    string nombre;

    Representante() : id(0), nombre("") {};
};

struct Cliente
{
    int id;
    string nombre;
    list <Cuenta> cuentas;

    Cliente() : id(0), nombre(""), cuentas() {};
};

struct Mensaje
{
    int id;
    string contenido;
    string autor;
    string destinatario;

    Mensaje() : id(0), contenido(""), autor(""), destinatario("") {}
};

struct Incidente
{
    int id;
    string contenido;

    Incidente() : id(0), contenido("") {}
};


#endif