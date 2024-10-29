#include "../include/MessageSender.h"
#include <iostream>
using namespace std;

void Whatsapp::sendMessage(const std::string& message){
    cout << "Send Whatsapp: " << message << endl;
}

void Facebook::sendMessage(const std::string& message){
    cout << "Send to Facebook: " << message << endl;
}

void Instagram::sendMessage(const std::string& message){
    cout << "Send to Instagram: " << message << endl;
}

void Email::sendMessage(const std::string& message){
    cout << "Send Email: " << message << endl;
}
