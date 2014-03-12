//
//  XmlRPC.h
//  

#include <cassert>
#include <cstdlib>
#include <string>
#include <iostream>

#include <xmlrpc-c/girerr.hpp>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client.hpp>


class XmlRPC {
    
public:
    
    XmlRPC(){};
    ~XmlRPC(){};
    
    bool run(std::string user, std::string pass);
    
private:
    
    
    
};