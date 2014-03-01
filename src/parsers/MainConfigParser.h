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
    
    std::string configpath;
    int argc;
    char** argv;

    
    
};


