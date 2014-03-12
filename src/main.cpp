//
//  main.cpp
//  Auditor
//


#include <iostream>
#include "MainConfigParser.h"
#include "Network.h"

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
    netModule->verify();
    
}

