//
//  BitMessageQueue.cpp
//  

#include "BitMessageQueue.h"

#include<boost/tokenizer.hpp>



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
        std::unique_lock<std::mutex> mlock(m_processing); // Don't stop the thread in the middle of processing
        m_stop = true;
        m_thread.join();
        mlock.unlock();
        return true;
    }
    else{
        std::cout << "BitMessageQueue is already stopped!" << std::endl;
        return false;
    }
}


bool BitMessageQueue::processing(){
    
    return m_working;
    
}


void BitMessageQueue::addToQueue(std::function<void()> command){
    
    MasterQueue.push(command);
    
}




int BitMessageQueue::queueSize(){
    
    return MasterQueue.size();
    
}


void BitMessageQueue::clearQueue(){
    
    MasterQueue.clear();
    
}




bool BitMessageQueue::parseNextMessage(){
    
    if(queueSize() == 0){
        return false;
    }
    
    std::unique_lock<std::mutex> mlock(m_processing);  // Don't let other functions interfere with our message parsing
    
    m_working = true; // Notify our atomic boolean that we are in the middle of a process
    
    std::function<void()> message = MasterQueue.pop();  // Pull out our function to run
    message();
    
    mlock.unlock();
    m_conditional.notify_one(); // Let other functions know that we're done and they can continue
    
    m_working = false; // Notify our atomic boolean that we are done with our processing

    
    return true;
}


BitMessageQueue::~BitMessageQueue(){
    
    try{
        stop();
    }
    
    catch(...){
        /* Will need to refactor this */
    }

}