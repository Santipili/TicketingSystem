#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <string>
#include <list>
#include "./MessageSender.h"

using namespace std;

struct Cuenta
{
    Cuenta() : direccion("") {};
    Cuenta(string direccion, MessageSender *sender) : direccion(direccion), sender(sender){};
    MessageSender *sender;
    string direccion;

};

struct Representante
{
    Representante() : id(0), nombre("") {};
    Representante(int id, string nombre) : id(id), nombre(nombre) {};
    int id;
    string nombre;

};

struct Cliente
{
    Cliente() : id(0), nombre(""), cuentas() {};
    Cliente(int id, string nombre, const list <Cuenta> cuentas) : id(id), nombre(nombre), cuentas(cuentas) {};
    int id;
    string nombre;
    list <Cuenta> cuentas;

};

struct Mensaje
{
    Mensaje() : id(0), contenido(""), autor(""), destinatario("") {}
    Mensaje(int id, string contenido, string autor, string destinatario) : id(id), contenido(contenido), autor(autor), destinatario(destinatario) {}
    int id;
    string contenido;
    string autor;
    string destinatario;

};

struct Incidente
{
    Incidente() : id(0), contenido("") {}
    Incidente(int id, string contenido) : id(id), contenido(contenido) {}
    int id;
    string contenido;

};


#endif