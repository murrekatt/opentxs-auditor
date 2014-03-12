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
    const std::string hello("Hello World");
    std::string encoded = base64_encode((const unsigned char *)hello.c_str(), hello.size());
    std::cout << encoded << std::endl;
    std::cout << base64_decode(encoded) << std::endl;
    
    
}

