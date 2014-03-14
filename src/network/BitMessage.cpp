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


// Inbox Management

void BitMessage::getAllInboxMessages(){

    Parameters params;

    XmlResponse result = m_xmllib->run("getAllInboxMessages", params);
    
    if(result.first == false){
        std::cout << "Error: getAllInboxMessages failed" << std::endl;
        //return responses;
    }
    else if(result.second.type() == xmlrpc_c::value::TYPE_STRING){
        std::size_t found;
        found=std::string(ValueString(result.second)).find("API Error");
        if(found!=std::string::npos){
            std::cout << std::string(ValueString(result.second)) << std::endl;
            //return responses;
        }
    }
    
    std::cout << "Inbox Messages: " << std::string(ValueString(result.second)) << std::endl;


};

void BitMessage::getInboxMessageByID(std::string msgID, bool setRead){};

void BitMessage::getSentMessageByAckData(std::string ackData){};

void BitMessage::getAllSentMessages(){};

void BitMessage::getSentMessageByID(std::string msgID){};

void BitMessage::getSentMessagesBySender(BitMessageAddress address){};

void BitMessage::trashMessage(std::string msgID){};

void BitMessage::trashSentMessageByAckData(std::string ackData){};

// Message Management

void BitMessage::sendMessage(BitMessageAddress fromAddress, BitMessageAddress toAddress, base64 subject, base64 message, int encodingType){};

void BitMessage::sendBroadcast(BitMessageAddress fromAddress, base64 subject, base64 message, int encodingType){};

// Subscription Management

void BitMessage::listSubscriptions(){};

void BitMessage::addSubscription(BitMessageAddress address, base64 label){};

void BitMessage::deleteSubscription(BitMessageAddress address){};


// Channel Management

BitMessageAddress BitMessage::createChan(base64 password){

    Parameters params;
    params.push_back(ValueString(password.encoded()));
    
    XmlResponse result = m_xmllib->run("createChan", params);
    
    if(result.first == false){
        std::cout << "Error: createChan failed" << std::endl;
        return BitMessageAddress(base64(""), "", 0, false, false);
    }
    else if(result.second.type() == xmlrpc_c::value::TYPE_STRING){
        std::size_t found;
        found=std::string(ValueString(result.second)).find("API Error");
        if(found!=std::string::npos){
            std::cout << std::string(ValueString(result.second)) << std::endl;
            return BitMessageAddress(base64(""), "", 0, false, false);
        }
    }
    
    std::cout << "BitMessage API Response: " << std::string(ValueString(result.second)) << std::endl;
    
    return BitMessageAddress(base64(""), std::string(ValueString(result.second)));

};




void BitMessage::joinChan(base64 password, BitMessageAddress address){};



bool BitMessage::leaveChan(BitMessageAddress address){

    Parameters params;
    params.push_back(ValueString(address.getAddress()));
    
    XmlResponse result = m_xmllib->run("leaveChan", params);
    
    if(result.first == false){
        std::cout << "Error: leaveChan failed" << std::endl;
        return false;
    }
    else if(result.second.type() == xmlrpc_c::value::TYPE_STRING){
        std::size_t found;
        found=std::string(ValueString(result.second)).find("API Error");
        if(found!=std::string::npos){
            std::cout << std::string(ValueString(result.second)) << std::endl;
            return false;
        }
    }
    
    std::cout << "BitMessage API Response: " << std::string(ValueString(result.second)) << std::endl;

    return true;
};




// Address Management

std::vector<BitMessageAddress> BitMessage::listAddresses(){
    
    std::vector<xmlrpc_c::value> params;
    std::vector<BitMessageAddress> responses;
    
    XmlResponse result = m_xmllib->run("listAddresses2", params);
    
    if(result.first == false){
        std::cout << "Error: listAddresses2 failed" << std::endl;
        return responses;
    }
    else if(result.second.type() == xmlrpc_c::value::TYPE_STRING){
        std::size_t found;
        found=std::string(ValueString(result.second)).find("API Error");
        if(found!=std::string::npos){
            std::cout << std::string(ValueString(result.second)) << std::endl;
            return responses;
        }
    }
    
    Json::Value root;
    Json::Reader reader;
    
    bool parsesuccess = reader.parse( ValueString(result.second), root );
    if ( !parsesuccess )
    {
        std::cout  << "Failed to parse configuration\n" << reader.getFormattedErrorMessages();
        return responses;
    }
    
    const Json::Value addresses = root["addresses"];
    for ( int index = 0; index < addresses.size(); ++index ){  // Iterates over the sequence elements.
        BitMessageAddress entry(base64(addresses[index].get("label", "").asString()), addresses[index].get("address", "").asString(), addresses[index].get("stream", 0).asInt(), addresses[index].get("enabled", false).asBool(), addresses[index].get("chan", false).asBool());
        
        responses.push_back(entry);
        
        // Debug Output
        std::cout << std::endl;
        std::cout <<  "Address Index: " << index << std::endl;
        
        std::string label;
        label = responses.at(index).getLabel().decoded();
        label.erase(label.find_last_not_of(" \n\r\t")+1);
        std::cout <<  "label: " << label << std::endl;
        
        std::cout <<  "address: " << responses.at(index).getAddress() << std::endl;
        std::cout <<  "stream: " << responses.at(index).getStream() << std::endl;
        std::cout <<  "enabled: " << responses.at(index).getEnabled() << std::endl;
        std::cout <<  "chan: " << responses.at(index).getChan() << std::endl;
        std::cout << std::endl;
        
        
    }
    
    //std::cout << "BitMessage API Response: " << std::string(ValueString(result.second)) << std::endl;
    
    return responses;
    
}



void BitMessage::createRandomAddress(base64 label, bool eighteenByteRipe, int totalDifficulty, int smallMessageDifficulty){};

void BitMessage::createDeterministicAddresses(base64 password, int numberOfAddresses, int addressVersionNumber, int streamNumber, bool eighteenByteRipe, int totalDifficulty, int smallMessageDifficulty){};

void BitMessage::getDeterministicAddress(base64 password, int addressVersionNumber, int streamNumber){};

void BitMessage::listAddressBookEntries(){};

bool BitMessage::addAddressBookEntry(BitMessageAddress address, base64 label){

    Parameters params;
    params.push_back(ValueString(address.getAddress()));
    params.push_back(ValueString(label.encoded()));
    
    XmlResponse result = m_xmllib->run("addAddressBookEntry", params);
    
    if(result.first == false){
        std::cout << "Error: addAddressBookEntry failed" << std::endl;
        return false;
    }
    else if(result.second.type() == xmlrpc_c::value::TYPE_STRING){
        std::size_t found;
        found=std::string(ValueString(result.second)).find("API Error");
        if(found!=std::string::npos){
            std::cout << std::string(ValueString(result.second)) << std::endl;
            return false;
        }
    }
    
    std::cout << "BitMessage API Response: " << std::string(ValueString(result.second)) << std::endl;
    
    return true;

};



bool BitMessage::deleteAddressBookEntry(BitMessageAddress address){

    Parameters params;
    params.push_back(ValueString(address.getAddress()));
    
    XmlResponse result = m_xmllib->run("deleteAddressBookEntry", params);
    
    if(result.first == false){
        std::cout << "Error: deleteAddressBookEntry failed" << std::endl;
        return false;
    }
    else if(result.second.type() == xmlrpc_c::value::TYPE_STRING){
        std::size_t found;
        found=std::string(ValueString(result.second)).find("API Error");
        if(found!=std::string::npos){
            std::cout << std::string(ValueString(result.second)) << std::endl;
            return false;
        }
    }
    
    std::cout << "BitMessage API Response: " << std::string(ValueString(result.second)) << std::endl;
    
    return true;

};



bool BitMessage::deleteAddress(BitMessageAddress address){

    Parameters params;
    params.push_back(ValueString(address.getAddress()));
    
    XmlResponse result = m_xmllib->run("deleteAddress", params);
    
    if(result.first == false){
        std::cout << "Error: deleteAddress failed" << std::endl;
        return false;
    }
    else if(result.second.type() == xmlrpc_c::value::TYPE_STRING){
        std::size_t found;
        found=std::string(ValueString(result.second)).find("API Error");
        if(found!=std::string::npos){
            std::cout << std::string(ValueString(result.second)) << std::endl;
            return false;
        }
    }
    
    std::cout << "BitMessage API Response: " << std::string(ValueString(result.second)) << std::endl;
    
    return true;

};

void BitMessage::decodeAddress(BitMessageAddress address){};





// Other API Commands

bool BitMessage::testApi(){
    
    Parameters params;
    params.push_back(ValueString("Hello"));
    params.push_back(ValueString("Auditor"));
    
    XmlResponse result = m_xmllib->run("helloWorld", params);
    
    if(result.first == false){
        std::cout << "Error Accessing BitMessage API" << std::endl;
        return false;
    }
    else if(result.second.type() == xmlrpc_c::value::TYPE_STRING){
        std::size_t found;
        found=std::string(ValueString(result.second)).find("API Error");
        if(found!=std::string::npos){
            std::cout << std::string(ValueString(result.second)) << std::endl;
            return false;
        }
    }
    
    std::cout << "BitMessage API is Active: " << std::string(ValueString(result.second)) << std::endl;
    
    return true;
    
}



int BitMessage::add(int x, int y){
    
    Parameters params;
    params.push_back(ValueInt(x));
    params.push_back(ValueInt(y));
    
    XmlResponse result = m_xmllib->run("add", params);
    
    if(result.first == false){
        std::cout << "Error: add failed" << std::endl;
        return -1;
    }
    else if(result.second.type() == xmlrpc_c::value::TYPE_STRING){
        std::size_t found;
        found=std::string(ValueString(result.second)).find("API Error");
        if(found!=std::string::npos){
            std::cout << std::string(ValueString(result.second)) << std::endl;
            return -1;
        }
        std::cout << "Unexpected Response to API Command: add" << std::endl;
        return -1;
    }
    else{
        return ValueInt(result.second);
        
    }
    
};




void BitMessage::getStatus(){};


