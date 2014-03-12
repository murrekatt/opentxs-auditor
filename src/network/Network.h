#pragma once
//
//  Network.h
//  Auditor
//

#include <string>
#include <vector>

class NetworkModule {
    
public:
    
    NetworkModule(){};
    virtual bool testApi(){ return true;};
    virtual std::vector<std::string> listAddresses(){return std::vector<std::string>();};
        
private:
    
    
};