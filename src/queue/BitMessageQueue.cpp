//
//  BitMessageQueue.cpp
//  

#include "BitMessageQueue.h"


bool BitMessageQueue::start() {

    if(m_stop){
        m_stop = false;
        m_thread = std::thread(&BitMessageQueue::run, this);
        return true;
    }
    else{
        std::cout << "BitMessageQueue is already running!" << std::endl;
        return false;
    }
}


bool BitMessageQueue::stop() {
    
    if(!m_stop){
        m_stop = true;
        m_thread.join();
        return true;
    }
    else{
        std::cout << "BitMessageQueue is already stopped!" << std::endl;
        return false;
    }
}


void BitMessageQueue::addToQueue(std::string command){
    
    MasterQueue.push(command);
    
}




int BitMessageQueue::queueSize(){
    
    return MasterQueue.size();
    
}




bool BitMessageQueue::parseNextMessage(){
    
    return false;
    
}


BitMessageQueue::~BitMessageQueue(){
    
    try{
        stop();
    }
    
    catch(...){
        /* Will need to refactor this */
    }

}