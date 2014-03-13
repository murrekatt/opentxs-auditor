//
//  BitMessage.cpp
//  

#include "BitMessage.h"
#include "json/json.h"
#include "base64.h"

#include <string>
#include <iostream>
#include <vector>
#include <utility>


BitMessage::BitMessage(std::string Host, int Port, std::string Username, std::string Pass) : m_host(Host), m_port(Port), m_username(Username), m_pass(Pass) {
    
    m_xmllib = new XmlRPC(m_host, m_port, true, 10000);
    m_xmllib->setAuth(m_username, m_pass);

}


BitMessage::~BitMessage(){
    delete m_xmllib;
}


bool BitMessage::testApi(){
    
    std::vector<xmlrpc_c::value> params;
    params.push_back(xmlrpc_c::value_string("Hello"));
    params.push_back(xmlrpc_c::value_string("Auditor"));
    
    XmlResponse result = m_xmllib->run("helloWorld", params);
    
    if(result.first == false){
        std::cout << "Error Accessing BitMessage API" << std::endl;
        return false;
    }
    else{
        std::cout << "BitMessage API Response: " << result.second << std::endl;
    }
    
    return true;
    
}


std::vector<std::string> BitMessage::listAddresses(){
    
    std::vector<xmlrpc_c::value> params;
    std::vector<std::string> responses;
    
    XmlResponse result = m_xmllib->run("listAddresses2", params);

    if(result.first == false){
        std::cout << "Error: listAddresses2 failed" << std::endl;
        return responses;
    }
    else{
        
        Json::Value root;   // will contains the root value after parsing.
        Json::Reader reader;
        
        bool parsesuccess = reader.parse( result.second, root );
        if ( !parsesuccess )
        {
            // report to the user the failure and their locations in the document.
            std::cout  << "Failed to parse configuration\n" << reader.getFormattedErrorMessages();
            return responses;
        }
        
        const Json::Value addresses = root["addresses"];
        for ( int index = 0; index < addresses.size(); ++index ){  // Iterates over the sequence elements.
            responses.push_back(addresses[index].get("address", "").asString());

            // Debug Output
            std::cout << std::endl;
            std::cout <<  "Address Index: " << index << std::endl;
            std::cout <<  "chan: " << addresses[index].get("chan", false).asBool() << std::endl;
            std::cout <<  "address: " << addresses[index].get("address", "").asString() << std::endl;
            std::cout <<  "enabled: " << addresses[index].get("enabled", false).asBool() << std::endl;
            std::cout <<  "stream: " << addresses[index].get("stream", 0).asInt() << std::endl;
            std::cout <<  "label: " << addresses[index].get("label", 0).asString() << std::endl;
            
        }

        std::cout << "BitMessage API Response: " << result.second << std::endl;
    }
    return responses;
    
}



void BitMessage::createRandomAddress(){};
void BitMessage::createDeterministicAddresses(){};
void BitMessage::getDeterministicAddress(){};
void BitMessage::getAllInboxMessages(){};
void BitMessage::getInboxMessageByID(){};
void BitMessage::getSentMessageByAckData(){};
void BitMessage::getAllSentMessages(){};
void BitMessage::getSentMessageByID(){};
void BitMessage::getSentMessagesBySender(){};
void BitMessage::trashMessage(){};
void BitMessage::sendMessage(){};
void BitMessage::sendBroadcast(){};
void BitMessage::getStatus(){};
void BitMessage::listSubscriptions(){};
void BitMessage::addSubscription(){};
void BitMessage::deleteSubscription(){};
void BitMessage::listAddressBookEntries(){};
void BitMessage::addAddressBookEntry(){};
void BitMessage::deleteAddressBookEntry(){};
void BitMessage::trashSentMessageByAckData(){};
void BitMessage::createChan(){};
void BitMessage::joinChan(){};
void BitMessage::leaveChan(){};
void BitMessage::deleteAddress(){};
void BitMessage::decodeAddress(){};

