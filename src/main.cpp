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
    if(netModule->accessible()){
        std::cout << "Transport Layer is Accessible" << std::endl;
    }
    else{
        std::cout << "Transport Layer Failure" << std::endl;
        exit(0);
    }
    
    std::cout << std::endl;
    std::cout << "Running Network Module Tests:" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Number of Modules Loaded: " << netModule->modulesLoaded() << std::endl;
    std::cout << "Number of Modules Alive: " << netModule->modulesAlive() << std::endl;
    std::cout << "Network Accessibiility Test: " << netModule->accessible() << std::endl;
    std::cout << "Number of Modules Alive: " << netModule->modulesAlive() << std::endl;

    std::cout << "Address Accesibility Test: " << netModule->addressAccessible("BM-2cWNiCJahFd26v5ev5jH1GzKMNWiwbimDJ") << std::endl;
    std::cout << "Check Publish Support: " << netModule->publishSupport() << std::endl;
    
    
    
    
    
    std::cout << std::endl;
    std::cout << "BitMessage listAddressBookEntries Test" << std::endl;
    //std::cout << dynamic_cast<BitMessage*>(netModule)->listSubscriptions().at(0).getLabel().decoded() << std::endl;
    std::cout << dynamic_cast<BitMessage*>(netModule)->listAddressBookEntries().at(0).getLabel().decoded() << std::endl;
    //std::cout << dynamic_cast<BitMessage*>(netModule)->sendMessage("BM-", "BM-", base64("Testing"), base64("Knock if you receive this message?")) << std::endl;
    //std::cout << dynamic_cast<BitMessage*>(netModule)->getSentMessageByID().getMessage().decoded() << std::endl;
    //std::cout << "Message on last received message is: " << std::endl;
    //std::cout << dynamic_cast<BitMessage*>(netModule)->getInboxMessageByID((dynamic_cast<BitMessage*>(netModule)->getAllInboxMessages().at(0).getMsgID())).getMessage().decoded() << std::endl;



    
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
    std::cout << decoded << std::endl << std::endl;
    
    
}

