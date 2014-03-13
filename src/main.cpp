//
//  main.cpp
//  Auditor
//


#include <iostream>
#include <string>
#include "MainConfigParser.h"
#include "Network.h"

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
    netModule->listAddresses();
    
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

