//
//  BitMessage.h
//  

#include <memory>
#include <string>
#include "Network.h"
#include "XmlRPC.h"


class BitMessage : public NetworkModule {
    
    
public:
    
    BitMessage(std::string Host, int Port, std::string Username, std::string Pass);
    ~BitMessage();
    
    // Core API Functions
    bool testApi();
    int add(int x, int y);
    std::string listAddresses(); // This is technically "listAddresses2" in the API reference
    
    // Not yet implemented Functions
    // https://bitmessage.org/wiki/API_Reference
    void createRandomAddress();
    void createDeterministicAddresses();
    void getDeterministicAddress();
    void getAllInboxMessages();
    void getInboxMessageByID();
    void getSentMessageByAckData();
    void getAllSentMessages();
    void getSentMessageByID();
    void getSentMessagesBySender();
    void trashMessage();
    void sendMessage();
    void sendBroadcast();
    void getStatus();
    void listSubscriptions();
    void addSubscription();
    void deleteSubscription();
    void listAddressBookEntries();
    void addAddressBookEntry();
    void deleteAddressBookEntry();
    void trashSentMessageByAckData();
    void createChan();
    void joinChan();
    void leaveChan();
    void deleteAddress();
    void decodeAddress();
    
    
    // Extra BitMessage Options (some of these are pass-through functions)
    void setTimeout(int timeout);
    
private:
    
    // Private member variables
    std::string m_host;
    int m_port;
    std::string m_pass;
    std::string m_username;
    
    
    // Communication Library, XmlRPC in this case
    XmlRPC *m_xmllib;
    
    
    
};