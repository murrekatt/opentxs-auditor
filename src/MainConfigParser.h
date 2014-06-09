#pragma once

#include <Network.h>

#include <string>
#include <memory>

class MainConfigParser {
    
public:
    MainConfigParser(int _argc, char* _argv[]) : argc(_argc), argv(_argv){};
    
    bool parse();
    
    // Object Passing Functions
    NetworkModule* passNetworkModule();
    
private:
    int argc;
    char** argv;
    
    std::string configpath;
    
    //std::string m_netmodule;
    int remote_bitmessageport;
    std::string remote_bitmessagehost;
    std::string remote_bitmessageuser;
    std::string remote_bitmessagepass;
    std::shared_ptr<NetworkModule> m_netmodule;

 private:
    void setNetworkModule(std::string const module);
};
