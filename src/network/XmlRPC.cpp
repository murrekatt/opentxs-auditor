//
//  XmlRPC.cpp
//  


#include "XmlRPC.h"

#include <string>


XmlRPC::XmlRPC(std::string serverurl, int port, bool authrequired, int Timeout) : m_serverurl(serverurl), m_port(port), m_authrequired(authrequired), m_timeout(Timeout) {
    
    xmlrpc_c::clientXmlTransport_curl transport(
                                                xmlrpc_c::clientXmlTransport_curl::constrOpt()
                                                .timeout(m_timeout)  // milliseconds
                                                );
    
}



bool XmlRPC::run(std::string user, std::string pass ){
    
    try {
        
        xmlrpc_c::client_xml client(&transport);
        
        std::string const method("helloWorld");
        
        xmlrpc_c::paramList params;
        params.add(xmlrpc_c::value_string("Hello"));
        params.add(xmlrpc_c::value_string("Auditor"));
        
        xmlrpc_c::rpcPtr rpc(method, params);
        
        std::string const serverUrl(m_serverurl + ":" + std::to_string(m_port));
        
        xmlrpc_c::carriageParm_http0 carriageParams(serverUrl);
        
        
        carriageParams.setUser(user, pass);
        carriageParams.allowAuthBasic();
        
        rpc->call(&client, &carriageParams);
        
        assert(rpc ->isFinished());
        
        std::string const result(xmlrpc_c::value_string(rpc->getResult()));
        
        std::cout << "\nResponse is: " << result << std::endl;
        
    } catch (std::exception const& e) {
        std::cerr << "Client threw error: " << e.what() << std::endl;
        return false;
    } catch (...) {
        std::cerr << "Client threw unexpected error." << std::endl;
        return false;
    }
    
    return true;
    
}



void XmlRPC::setTimeout(int Timeout){
    
    m_timeout = Timeout;
    
    xmlrpc_c::clientXmlTransport_curl transport(
                                                xmlrpc_c::clientXmlTransport_curl::constrOpt()
                                                .timeout(m_timeout)  // milliseconds
                                                );
}


void XmlRPC::setAuth(std::string user, std::string pass){
    
    m_authuser = user;
    m_authpass = pass;
    
}


void XmlRPC::toggleAuth(bool toggle){
    m_authrequired = toggle;
}