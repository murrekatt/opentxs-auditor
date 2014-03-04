//
//  BitMessage.cpp
//  

#include "BitMessage.h"
#include <string>


bool BitMessage::verify(){
    
    std::shared_ptr<XmlRPC> m_xmllib(new XmlRPC());
    
    m_xmllib->run();
    
    return true;
    
}


