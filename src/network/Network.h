#pragma once
//
//  Network.h
//  Auditor
//

#include <string>


class NetworkModule {
    
public:
    
    NetworkModule(){};
    virtual bool testApi(){ return true;};
    virtual std::string listAddresses(){return "";};
        
private:
    
    
};