#ifndef  MESSAGESENDER_H
#define MESSAGESENDER_H

#include <string>
class MessageSender {
public:
    virtual void sendMessage(const std::string& message) = 0;
    virtual ~MessageSender() = default;
};

class Whatsapp : public MessageSender {
public:
    Whatsapp(){};
    ~Whatsapp(){};
    void sendMessage(const std::string& message);
};

class Facebook : public MessageSender {
public:
    Facebook(){};
    ~Facebook(){};
    void sendMessage(const std::string& message);
};

class Instagram : public MessageSender {
public:
    Instagram(){};
    ~Instagram(){};
    void sendMessage(const std::string& message);
};

class Email : public MessageSender {
public:
    Email(){};
    ~Email(){};
    void sendMessage(const std::string& message);
};

#endif