//
//  MainConfigParser.cpp
//  Auditor
//


#include "MainConfigParser.h"
#include "Constants.h"

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
        
        po::options_description config("Config File Options");
        config.add_options()
     /*   ("dbhost", po::value<std::string>(&db_hostname)->default_value("localhost"),"Database Hostname")
        ("dbport", po::value<int>(&db_port)->default_value(5432), "Database Port")
        ("dbuser", po::value<std::string>(&db_username), "Database Username")
        ("dbpass", po::value<std::string>(&db_pass), "Database Password")
        ("dbname", po::value<std::string>(&db_name)->default_value(db_username), "Database Name") */
        ;
        
        
        po::options_description hidden("Hidden options");
        hidden.add_options()
      /*  ("server_port", po::value<int>(&serverPort)->default_value(5250), "Server Listening Port") */
        ;
        
        
        po::options_description config_file_options;
        config_file_options.add(config).add(hidden);
        
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
        
        if (vm.count("help")) {
            std::cout << desc << std::endl;
            std::cout << config << std::endl;
            exit(0);
        }
        if (vm.count("version")) {
            std::cout << "VP Auditor 0.0.0" << std::endl;
            exit(0);
        }
        
        
        std::ifstream ifs(configpath.c_str());
        if(!ifs)
        {
            std::cout << versiontext << std::endl;
            std::cout << std::endl;
            //std::cout << "Usage:" << std::endl;
            std::cout << desc << std::endl;
            std::cout << config << std::endl;
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