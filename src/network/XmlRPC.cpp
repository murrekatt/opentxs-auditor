//
//  XmlRPC.cpp
//  


#include "XmlRPC.h"


bool XmlRPC::run(){
    
    try {
        
        xmlrpc_c::clientXmlTransport_curl myTransport(
                                                      xmlrpc_c::clientXmlTransport_curl::constrOpt()
                                                      .timeout(10000)  // milliseconds
                                                      .user_agent("sample_add/1.0"));
        
        xmlrpc_c::client_xml myClient(&myTransport);
        
        std::string const methodName("helloWorld");
        
        xmlrpc_c::paramList sampleAddParms;
        sampleAddParms.add(xmlrpc_c::value_string("Hello"));
        sampleAddParms.add(xmlrpc_c::value_string("Auditor"));
        
        xmlrpc_c::rpcPtr myRpcP(methodName, sampleAddParms);
        
        std::string const serverUrl("http://localhost:8442");
        
        xmlrpc_c::carriageParm_http0 myCarriageParm(serverUrl);
        myCarriageParm.setUser("", "");
        myCarriageParm.allowAuthBasic();
        
        myRpcP->call(&myClient, &myCarriageParm);
        
        assert(myRpcP->isFinished());
        
        std::string const sum(xmlrpc_c::value_string(myRpcP->getResult()));
        // Assume the method returned an integer; throws error if not
        
        std::cout << "\nResponse is: " << sum << std::endl;
        
    } catch (std::exception const& e) {
        std::cerr << "Client threw error: " << e.what() << std::endl;
        return false;
    } catch (...) {
        std::cerr << "Client threw unexpected error." << std::endl;
        return false;
    }
    
    return true;
    

    
}