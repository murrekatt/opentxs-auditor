//
//  main.cpp
//  Auditor
//


#include <iostream>
#include <string>
#include "MainConfigParser.h"
#include "Network.h"
#include "BitMessage.h"

#include "base64.h"

int main(int argc, char * argv[])
{

    // Read Config
    MainConfigParser mainConfigParser(argc, argv);
    if(!mainConfigParser.parse()){
        std::cout << "Configuration Parser Error" << std::endl;
    }
    
    // Startup Network
        // Contact Transaction Server (Optional)
        // Echo to BitMessage (or other communication layer) Network
    
    NetworkModule *netModule = mainConfigParser.passNetworkModule();
    if(netModule->testApi()){
        std::cout << "Transport Layer is Accessible" << std::endl;
    }
    else{
        std::cout << "Transport Layer Failure" << std::endl;
        exit(0);
    }
    
    std::cout << "BitMessage listAddresses Test" << std::endl;
    dynamic_cast<BitMessage*>(netModule)->listAddresses();
    
    std::cout << std::endl;
    std::cout << "BitMessage add Test" << std::endl;
    std::cout << dynamic_cast<BitMessage*>(netModule)->add(2, 3) << std::endl;
    
    std::cout << std::endl;
    std::cout << "BitMessage getAllSentMessages Test" << std::endl;
    //std::cout << dynamic_cast<BitMessage*>(netModule)->getSentMessageByID().getMessage().decoded() << std::endl;
    //std::cout << "Message on last received message is: " << std::endl;
    //std::cout << dynamic_cast<BitMessage*>(netModule)->getInboxMessageByID((dynamic_cast<BitMessage*>(netModule)->getAllInboxMessages().at(0).getMsgID())).getMessage().decoded() << std::endl;
    //dynamic_cast<BitMessage*>(netModule)->createChan(base64("passwordl"));
    //dynamic_cast<BitMessage*>(netModule)->leaveChan(BitMessageAddress(base64(""), "BM-2cTUFbCqKb5u1DkHNtWKYRNnLP4R6eNhQF"));


    
    std::cout << std::endl;
    std::cout << "Base64 Test" << std::endl;
    base64 message("Hello");
    std::cout << message.encoded() << std::endl;
    std::string decoded;
    decoded << message;
    std::cout << decoded << std::endl;
    std::string world("World");
    world >> message;
    std::cout << message.encoded() << std::endl;
    decoded << message;
    std::cout << decoded << std::endl;

    
    
}

