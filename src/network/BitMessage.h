//
//  BitMessage.h
//  

#include <memory>
#include <string>
#include "Network.h"
#include "XmlRPC.h"


class BitMessage : public NetworkModule {
    
    
public:
    
    BitMessage(std::string Host, int Port, std::string Username, std::string Pass) : m_host(Host), m_port(Port), m_username(Username), m_pass(Pass) {};
    
    bool verify();
    void setTimeout(int timeout);
    
private:
    
    // Private member variables
    std::string m_host;
    int m_port;
    std::string m_pass;
    std::string m_username;
    
    
    // Communication Library, XmlRPC in this case
    std::shared_ptr<XmlRPC> m_xmllib;
    
    
    
};