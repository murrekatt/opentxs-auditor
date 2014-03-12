//
//  BitMessage.cpp
//  

#include "BitMessage.h"
#include <string>
#include <iostream>


bool BitMessage::verify(){
    
    std::shared_ptr<XmlRPC> m_xmllib(new XmlRPC(m_host, m_port, true, 10000));
    
    m_xmllib->run(m_username, m_pass);
    
    return true;
    
}


