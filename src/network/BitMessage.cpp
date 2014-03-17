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
#include <algorithm>


BitMessage::BitMessage(std::string Host, int Port, std::string Username, std::string Pass) : m_host(Host), m_port(Port), m_username(Username), m_pass(Pass) {
    
    m_xmllib = new XmlRPC(m_host, m_port, true, 10000);
    m_xmllib->setAuth(m_username, m_pass);
    
}


BitMessage::~BitMessage(){
    delete m_xmllib;
}


// Inbox Management

std::vector<BitInboxMessage> BitMessage::getAllInboxMessages(){

    Parameters params;
    std::vector<BitInboxMessage> inbox;

    XmlResponse result = m_xmllib->run("getAllInboxMessages", params);
    
    if(result.first == false){
        std::cout << "Error: getAllInboxMessages failed" << std::endl;
        return inbox;
    }
    else if(result.second.type() == xmlrpc_c::value::TYPE_STRING){
        std::size_t found;
        found=std::string(ValueString(result.second)).find("API Error");
        if(found!=std::string::npos){
            std::cout << std::string(ValueString(result.second)) << std::endl;
            return inbox;
        }
    }
    
    Json::Value root;
    Json::Reader reader;
    
    bool parsesuccess = reader.parse( ValueString(result.second), root );
    if ( !parsesuccess )
    {
        std::cout  << "Failed to parse inbox\n" << reader.getFormattedErrorMessages();
        return inbox;
    }
    
    const Json::Value inboxMessages = root["inboxMessages"];
    for ( int index = 0; index < inboxMessages.size(); ++index ){  // Iterates over the sequence elements.
        
        // We need to sanitize our string, or else it will get cut off because of the newlines.
        std::string dirtyMessage = inboxMessages[index].get("message", "").asString();
        dirtyMessage.erase(std::remove(dirtyMessage.begin(), dirtyMessage.end(), '\n'), dirtyMessage.end());
        base64 cleanMessage(dirtyMessage, true);
        
        BitInboxMessage message(inboxMessages[index].get("msgid", "").asString(), inboxMessages[index].get("toAddress", "").asString(), inboxMessages[index].get("fromAddress", "").asString(), base64(inboxMessages[index].get("subject", "").asString(), true), cleanMessage, inboxMessages[index].get("encodingType", 0).asInt(), std::atoi(inboxMessages[index].get("receivedTime", 0).asString().c_str()), inboxMessages[index].get("read", false).asBool());
        
        inbox.push_back(message);
        
    }
    
    return inbox;

};




BitInboxMessage BitMessage::getInboxMessageByID(std::string msgID, bool setRead){

    Parameters params;
    
    params.push_back(ValueString(msgID));
    params.push_back(ValueBool(setRead));

    XmlResponse result = m_xmllib->run("getInboxMessageByID", params);
    
    if(result.first == false){
        std::cout << "Error: getInboxMessageByID failed" << std::endl;
        BitInboxMessage message("", "", "", base64(""), base64(""), 0, 0, false);
        return message;
    }
    else if(result.second.type() == xmlrpc_c::value::TYPE_STRING){
        std::size_t found;
        found=std::string(ValueString(result.second)).find("API Error");
        if(found!=std::string::npos){
            std::cout << std::string(ValueString(result.second)) << std::endl;
            BitInboxMessage message("", "", "", base64(""), base64(""), 0, 0, false);
            return message;
        }
    }
    
    
    Json::Value root;
    Json::Reader reader;
    
    bool parsesuccess = reader.parse( ValueString(result.second), root );
    if ( !parsesuccess )
    {
        std::cout  << "Failed to parse inbox\n" << reader.getFormattedErrorMessages();
        BitInboxMessage message("", "", "", base64(""), base64(""), 0, 0, false);
        return message;
    }
    
    const Json::Value inboxMessage = root["inboxMessage"];
    
    std::string dirtyMessage = inboxMessage[0].get("message", "").asString();
    dirtyMessage.erase(std::remove(dirtyMessage.begin(), dirtyMessage.end(), '\n'), dirtyMessage.end());
    base64 cleanMessage(dirtyMessage, true);
    
    
    BitInboxMessage message(inboxMessage[0].get("msgid", "").asString(), inboxMessage[0].get("toAddress", "").asString(), inboxMessage[0].get("fromAddress", "").asString(), base64(inboxMessage[0].get("subject", "").asString(), true), cleanMessage, inboxMessage[0].get("encodingType", 0).asInt(), std::atoi(inboxMessage[0].get("receivedTime", 0).asString().c_str()), inboxMessage[0].get("read", false).asBool());
     
    return message;

};



void BitMessage::getAllSentMessages(){

    Parameters params;
    
    XmlResponse result = m_xmllib->run("getAllSentMessages", params);
    
    if(result.first == false){
        std::cout << "Error: getAllSentMessages failed" << std::endl;
        BitInboxMessage message("", "", "", base64(""), base64(""), 0, 0, false);
        return ;
    }
    else if(result.second.type() == xmlrpc_c::value::TYPE_STRING){
        std::size_t found;
        found=std::string(ValueString(result.second)).find("API Error");
        if(found!=std::string::npos){
            std::cout << std::string(ValueString(result.second)) << std::endl;
            BitInboxMessage message("", "", "", base64(""), base64(""), 0, 0, false);
            return;
        }
    }

    std::cout << std::string(ValueString(result.second)) << std::endl;
    
};

void BitMessage::getSentMessageByID(std::string msgID){};

void BitMessage::getSentMessageByAckData(std::string ackData){};

void BitMessage::getSentMessagesBySender(std::string address){};

bool BitMessage::trashMessage(std::string msgID){

    Parameters params;
    params.push_back(ValueString(msgID));
    
    XmlResponse result = m_xmllib->run("trashMessage", params);
    
    if(result.first == false){
        std::cout << "Error: trashMessage failed" << std::endl;
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

void BitMessage::trashSentMessageByAckData(std::string ackData){};

// Message Management

void BitMessage::sendMessage(std::string fromAddress, std::string toAddress, base64 subject, base64 message, int encodingType){};

void BitMessage::sendBroadcast(std::string fromAddress, base64 subject, base64 message, int encodingType){};

// Subscription Management

void BitMessage::listSubscriptions(){};

void BitMessage::addSubscription(std::string address, base64 label){};

void BitMessage::deleteSubscription(std::string address){};


// Channel Management

std::string BitMessage::createChan(base64 password){

    Parameters params;
    params.push_back(ValueString(password.encoded()));
    
    XmlResponse result = m_xmllib->run("createChan", params);
    
    if(result.first == false){
        std::cout << "Error: createChan failed" << std::endl;
        return "";
    }
    else if(result.second.type() == xmlrpc_c::value::TYPE_STRING){
        std::size_t found;
        found=std::string(ValueString(result.second)).find("API Error");
        if(found!=std::string::npos){
            std::cout << std::string(ValueString(result.second)) << std::endl;
            return "";
        }
    }
    
    std::cout << "BitMessage API Response: " << std::string(ValueString(result.second)) << std::endl;
    
    return std::string(ValueString(result.second));

};




bool BitMessage::joinChan(base64 password, std::string address){

    Parameters params;
    params.push_back(ValueString(password.encoded()));
    params.push_back(ValueString(address));
    
    XmlResponse result = m_xmllib->run("joinChan", params);
    
    if(result.first == false){
        std::cout << "Error: joinChan failed" << std::endl;
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



bool BitMessage::leaveChan(std::string address){

    Parameters params;
    params.push_back(ValueString(address));
    
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

BitMessageIdentities BitMessage::listAddresses(){
    
    std::vector<xmlrpc_c::value> params;
    BitMessageIdentities responses;
    
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
        BitMessageIdentity entry(base64(addresses[index].get("label", "").asString()), addresses[index].get("address", "").asString(), addresses[index].get("stream", 0).asInt(), addresses[index].get("enabled", false).asBool(), addresses[index].get("chan", false).asBool());
        
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

bool BitMessage::addAddressBookEntry(std::string address, base64 label){

    Parameters params;
    params.push_back(ValueString(address));
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


bool BitMessage::deleteAddressBookEntry(std::string address){

    Parameters params;
    params.push_back(ValueString(address));
    
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



bool BitMessage::deleteAddress(std::string address){

    Parameters params;
    params.push_back(ValueString(address));
    
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

void BitMessage::decodeAddress(std::string address){};





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


