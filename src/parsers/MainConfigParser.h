//
//  MainConfigParser.h
//  Auditor
//


#include <string>

class MainConfigParser {
    
public:
    MainConfigParser(int _argc, char* _argv[]) : argc(_argc), argv(_argv){};
    
    bool parse();
    
private:
    
    int argc;
    char** argv;
    
    std::string configpath;
    
    // Network
    std::string netmodule;
    int remote_bitmessageport;
    std::string remote_bitmessagehost;
    std::string remote_bitmessageuser;
    std::string remote_bitmessagepass;


    
    
};


