//
//  XmlRPC.cpp
//  


#include "XmlRPC.h"

#include <string>
#include <vector>
#include <utility>


XmlRPC::XmlRPC(std::string serverurl, int port, bool authrequired, int Timeout) : m_serverurl(serverurl), m_port(port), m_authrequired(authrequired), m_timeout(Timeout) {
    
    xmlrpc_c::clientXmlTransport_curl transport(
                                                xmlrpc_c::clientXmlTransport_curl::constrOpt()
                                                .timeout(m_timeout)  // milliseconds
                                                );
    
    m_authset = false;
    
}



XmlResponse XmlRPC::run(std::string methodName, std::vector<xmlrpc_c::value> parameters ){
    
    try {
        
        // Construct our client from our Transport object
        xmlrpc_c::client_xml client(&transport);
    
        std::string const method(methodName);

        // Parse through our parameters list
        
        // ** Need to debug why the add method fails when
        //      we reference i < parameters.size()
        //      instead of referencing int paramsize to parameters.size()
        
        int paramsize = parameters.size();

        xmlrpc_c::paramList params;
        for(int i; i < paramsize; i++){
            params.add(xmlrpc_c::value(parameters.at(i)));
        }
        
        // Construct the Server URL
        std::string const serverUrl(m_serverurl + ":" + std::to_string(m_port));
        xmlrpc_c::carriageParm_http0 carriageParams(serverUrl);

        // Check That Auth Requirements have been met
        if(m_authrequired){
            if(!m_authset){
                std::cout << "Error: XML-RPC Auth is required but has not been set" << std::endl;
                return std::make_pair(false,xmlrpc_c::value_string(""));
            }
            else{
                carriageParams.setUser(m_authuser, m_authpass);
                carriageParams.allowAuthBasic();
            }
        }
        
        
        // Uncomment this to expand the size limit, I will move this elsewhere later into a function
        // similar to the timeout setting one.
        //
        xmlrpc_limit_set(XMLRPC_XML_SIZE_LIMIT_ID, 5e6);

        // Run our RPC Call
        xmlrpc_c::rpcPtr rpc(method, params);
        rpc->call(&client, &carriageParams);
        assert(rpc->isFinished());
        
        xmlrpc_c::value const response(rpc->getResult());
        
        return std::make_pair(true,response);
        
    } catch (std::exception const& e) {
        std::cerr << "Client threw error: " << e.what() << std::endl;
        return std::make_pair(false,xmlrpc_c::value_string(""));
    } catch (...) {
        std::cerr << "Client threw unexpected error." << std::endl;
        return std::make_pair(false,xmlrpc_c::value_string(""));
    }
    
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
    
    m_authset = true;
    
}


void XmlRPC::toggleAuth(bool toggle){
    m_authrequired = toggle;
}


void XmlRPC::xmlrpc_millisecond_sleep(unsigned int const milliseconds) {
#if MSVCRT
    SleepEx(milliseconds, true);
#else
    usleep(milliseconds * 1000);
#endif
}