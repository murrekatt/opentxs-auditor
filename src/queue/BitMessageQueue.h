#pragma once

#ifndef _VP_QUEUE_BITMESSAGEQUEUE_H_
#define _VP_QUEUE_BITMESSAGEQUEUE_H_

#include "BitMessage.h"
#include <atomic>
#include <mutex>
#include <condition_variable>

class BitMessage;

class BitMessageQueue {
    
public:
    
    BitMessageQueue(BitMessage *parent) : parentInterface(parent), m_stop(true), m_thread() { }
    ~BitMessageQueue();
    
    // Public Thread Managers
    bool start();
    bool stop();
    
    bool processing();
    // Queue Managers
    void addToQueue(std::function<void()> command);
    
    int queueSize();
    void clearQueue();
    
    // Add function to determine amount of time last command has run.
    // Use boost::chrono?
    
protected:
    std::atomic<bool> m_stop;  
    void run(){ while(!m_stop){parseNextMessage();} }; // Obviously this will be our message parsing loop
    
private:
    std::thread m_thread;
    std::mutex m_processing;
    std::condition_variable m_conditional;
    
    std::atomic<bool> m_working;
    
    BitMessage *parentInterface;
    
    MsgQueue<std::function<void()>> MasterQueue;
     
    bool parseNextMessage();
};

#endif // _VP_QUEUE_BITMESSAGEQUEUE_H_
