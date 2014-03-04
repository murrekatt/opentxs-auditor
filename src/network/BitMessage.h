//
//  BitMessage.h
//  

#include <memory>
#include <string>
#include "Network.h"
#include "XmlRPC.h"


class BitMessage : public NetworkModule {
    
    
public:
    
    BitMessage(std::string Host, int Port, std::string Pass, std::string Username) : m_host(Host), m_port(Port), m_pass(Pass), m_username(Username) {};
    
    bool verify();
    
private:
    
    std::string m_host;
    int m_port;
    std::string m_pass;
    std::string m_username;
    
    std::shared_ptr<XmlRPC> m_xmllib;
    
};