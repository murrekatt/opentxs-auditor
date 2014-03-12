//
//  BitMessage.cpp
//  

#include "BitMessage.h"
#include <string>
#include <iostream>
#include <vector>
#include <utility>


bool BitMessage::testApi(){
    
    std::shared_ptr<XmlRPC> m_xmllib(new XmlRPC(m_host, m_port, true, 10000));
    
    m_xmllib->setAuth(m_username, m_pass);
    
    std::vector<xmlrpc_c::value> params;
    params.push_back(xmlrpc_c::value_string("Hello"));
    params.push_back(xmlrpc_c::value_string("Auditor"));
    
    xmlresponse result = m_xmllib->run("helloWorld", params);
    
    if(result.first == false){
        std::cout << "Error Accessing BitMessage API" << std::endl;
        return false;
    }
    else{
        std::cout << "BitMessage API Response: " << result.second << std::endl;
    }
    
    return true;
    
}


