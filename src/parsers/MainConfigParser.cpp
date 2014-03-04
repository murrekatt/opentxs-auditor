//
//  MainConfigParser.cpp
//  Auditor
//


#include "MainConfigParser.h"
#include "constants.h"

#include <boost/filesystem.hpp>
#include <boost/progress.hpp>
#include <boost/program_options.hpp>

#include <iostream>
#include <fstream>

namespace po = boost::program_options;



bool MainConfigParser::parse(){
    
    try {
        
        po::options_description desc("Default options");
        desc.add_options()
        ("config,c", po::value<std::string>(&configpath)->default_value("auditserver.conf"),"Configuration file, default auditserver.conf")
        ("help,h", "display this help text")
        ("version,v", "display version number")
        ;
        
        po::options_description network("Network options");
        network.add_options()
        ("network.netmodule", po::value<std::string>(&netmodule)->default_value("bitmessage"),"Net Communication Module")
        ("network.bitmessage.remotehost", po::value<std::string>(&remote_bitmessagehost)->default_value("localhost"), "Remote Bitmessage API Host")
        ("network.bitmessage.remoteport", po::value<int>(&remote_bitmessageport)->default_value(8442), "Remote Bitmessage API server port")
        ("network.bitmessage.remoteuser", po::value<std::string>(&remote_bitmessageuser)->default_value("defaultuser"), "Remote Bitmessage API Username")
        ("network.bitmessage.remotepass", po::value<std::string>(&remote_bitmessagepass)->default_value("defaultpass"), "Remote Bitmessage API Password")
        ;
        
        
        po::options_description config_file_options;
        config_file_options.add(network);
        
        po::variables_map vm;
    
        //  Parse our command line options
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
        
        if (vm.count("help")) {
            std::cout << g_versionString << std::endl;
            std::cout << desc << std::endl;
            std::cout << network << std::endl;
            exit(0);
        }
        if (vm.count("version")) {
            std::cout << g_versionString << std::endl;
            exit(0);
        }
        
        
        // Now Parse our config file
        
        std::ifstream ifs(configpath.c_str());
        if(!ifs)
        {
            std::cout << g_versionString << std::endl;
            std::cout << std::endl;
            //std::cout << "Usage:" << std::endl;
            std::cout << desc << std::endl;
            std::cout << std::endl;
            std::cout << "Error: could not open config file \"" << configpath << "\"" << std::endl;

            exit(0);
        }
        else
        {
            store(parse_config_file(ifs, config_file_options), vm);
            notify(vm);
        }
        
        
    }
    
    catch(std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        exit(1);
    }
    catch(...) {
        std::cerr << "Exception of unknown type!\n";
        return false;
    }
    return true;
}