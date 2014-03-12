//
//  XmlRPC.h
//  

#include <cassert>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <utility>

#include <xmlrpc-c/girerr.hpp>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client.hpp>

typedef std::pair<bool, std::string> XmlResponse;

class XmlRPC {
    
public:
    
    XmlRPC(std::string serverurl, int port=80, bool authrequired=false, int Timeout=10000);
    ~XmlRPC(){};
    
    std::pair<bool, std::string> run(std::string methodName, std::vector<xmlrpc_c::value> parameters);
    void setTimeout(int Timeout);
    void setAuth(std::string user, std::string pass);
    void toggleAuth(bool toggle);
    
private:
    
    int m_timeout;
    std::string m_serverurl;
    int m_port;
    
    bool m_authrequired;
    bool m_authset;
    
    std::string m_authuser;
    std::string m_authpass;
    
    xmlrpc_c::clientXmlTransport_curl transport;
    
    
};