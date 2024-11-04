#include "../include/MessageSender.h"
#include <iostream>
using namespace std;

void Whatsapp::sendMessage(const std::string& message, const std::string& address){
    cout << "Send Whatsapp: " << message << endl;
    cout << "to " << address << endl;
}

void Facebook::sendMessage(const std::string& message, const std::string& address){
    cout << "Send to Facebook: " << message << endl;
    cout << "to " << address << endl;
}

void Instagram::sendMessage(const std::string& message, const std::string& address){
    cout << "Send to Instagram: " << message << endl;
    cout << "to " << address << endl;
}

void Email::sendMessage(const std::string& message, const std::string& address){
    cout << "Send Email: " << message << endl;
    cout << "to " << address << endl;
}
