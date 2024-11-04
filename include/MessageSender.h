#ifndef  MESSAGESENDER_H
#define MESSAGESENDER_H

#include <string>
class MessageSender {
public:
    virtual void sendMessage(const std::string& message, const std::string& address) = 0;
    virtual ~MessageSender() = default;
};

class Whatsapp : public MessageSender {
public:
    Whatsapp(){};
    ~Whatsapp(){};
    void sendMessage(const std::string& message, const std::string& address);
};

class Facebook : public MessageSender {
public:
    Facebook(){};
    ~Facebook(){};
    void sendMessage(const std::string& message, const std::string& address);
};

class Instagram : public MessageSender {
public:
    Instagram(){};
    ~Instagram(){};
    void sendMessage(const std::string& message, const std::string& address);
};

class Email : public MessageSender {
public:
    Email(){};
    ~Email(){};
    void sendMessage(const std::string& message, const std::string& address);
};

#endif