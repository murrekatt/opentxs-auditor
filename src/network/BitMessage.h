//
//  BitMessage.h
//  

#include <memory>
#include <string>
#include "Network.h"
#include "XmlRPC.h"
#include "base64.h"

class BitMessageAddress {
    
public:
    
    BitMessageAddress(base64 label, std::string address, int stream=1, bool enabled=true, bool chan=false) : m_label(label), m_address(address), m_stream(stream), m_enabled(enabled), m_chan(chan) {};
    
    // Note "getLabel" returns a base64 formatted label, you will need to decode this object via base64::decoded
    base64 getLabel(){return m_label;};
    std::string getAddress(){return m_address;};
    int getStream(){return m_stream;};
    bool getEnabled(){return m_enabled;};
    bool getChan(){return m_chan;};
    
private:
    
    base64 m_label;
    std::string m_address;
    int m_stream;
    bool m_enabled;
    bool m_chan;
};


class BitMessage : public NetworkModule {

public:
    
    BitMessage(std::string Host, int Port, std::string Username, std::string Pass);
    ~BitMessage();
    
    
    //
    // Core API Functions
    // https://bitmessage.org/wiki/API_Reference
    //

    // Inbox Management
    
    void getAllInboxMessages();
    
    void getInboxMessageByID(std::string msgID, bool setRead=true);
    
    void getSentMessageByAckData(std::string ackData);
    
    void getAllSentMessages();
    
    void getSentMessageByID(std::string msgID);
    
    void getSentMessagesBySender(BitMessageAddress address);
    
    void trashMessage(std::string msgID);
    
    void trashSentMessageByAckData(std::string ackData);

    
    // Message Management
    void sendMessage(BitMessageAddress fromAddress, BitMessageAddress toAddress, base64 subject, base64 message, int encodingType=2);
    void sendMessage(BitMessageAddress fromAddress, BitMessageAddress toAddress, std::string subject, std::string message, int encodingType=2){sendMessage(fromAddress, toAddress, base64(subject), base64(message), encodingType);};

    void sendBroadcast(BitMessageAddress fromAddress, base64 subject, base64 message, int encodingType=2);
    void sendBroadcast(BitMessageAddress fromAddress, std::string subject, std::string message, int encodingType=2){sendBroadcast(fromAddress, base64(subject), base64(message), encodingType);};

    
    // Subscription Management
    
    void listSubscriptions();
    
    void addSubscription(BitMessageAddress address, base64 label);
    void addSubscription(BitMessageAddress address, std::string label){addSubscription(address, base64(label));};

    void deleteSubscription(BitMessageAddress address);
    
    
    // Channel Management
    
    BitMessageAddress createChan(base64 password);
    void createChan(std::string password){createChan(base64(password));};
    
    void joinChan(base64 password, BitMessageAddress address);
    void joinChan(std::string password, BitMessageAddress address){joinChan(base64(password), address);};
    
    bool leaveChan(BitMessageAddress address);
    
    
    // Address Management
    
    std::vector<BitMessageAddress> listAddresses(); // This is technically "listAddresses2" in the API reference
    
    void createRandomAddress(base64 label, bool eighteenByteRipe=false, int totalDifficulty=1, int smallMessageDifficulty=1);
    void createRandomAddress(std::string label, bool eighteenByteRipe=false, int totalDifficulty=1, int smallMessageDifficulty=1){createRandomAddress(label, eighteenByteRipe, totalDifficulty, smallMessageDifficulty);};

    void createDeterministicAddresses(base64 password, int numberOfAddresses=1, int addressVersionNumber=0, int streamNumber=0, bool eighteenByteRipe=false, int totalDifficulty=1, int smallMessageDifficulty=1);
    void createDeterministicAddresses(std::string password, int numberOfAddresses=1, int addressVersionNumber=0, int streamNumber=0, bool eighteenByteRipe=false, int totalDifficulty=1, int smallMessageDifficulty=1){createDeterministicAddresses(base64(password), numberOfAddresses, addressVersionNumber, streamNumber, eighteenByteRipe, totalDifficulty, smallMessageDifficulty);};
    
    void getDeterministicAddress(base64 password, int addressVersionNumber=4, int streamNumber=1);
    void getDeterministicAddress(std::string password, int addressVersionNumber=4, int streamNumber=1){getDeterministicAddress(base64(password), addressVersionNumber, streamNumber);};
    
    void listAddressBookEntries();
    
    void addAddressBookEntry(BitMessageAddress address, base64 label);
    void addAddressBookEntry(BitMessageAddress address, std::string label){addAddressBookEntry(address, base64(label));};

    void deleteAddressBookEntry(BitMessageAddress address);
    
    void deleteAddress(BitMessageAddress address);
    
    void decodeAddress(BitMessageAddress address);
    
    
    // Other API Commands
    
    bool testApi();
    int add(int x, int y);
    void getStatus();
    
    
    // Extra BitMessage Options (some of these are pass-through functions not related to the API)

    void setTimeout(int timeout);
    
    
private:
    
    typedef std::vector<xmlrpc_c::value> Parameters;
    typedef xmlrpc_c::value_int ValueInt;
    typedef xmlrpc_c::value_i8 ValueI8;
    typedef xmlrpc_c::value_boolean ValueBool;
    typedef xmlrpc_c::value_double ValueDouble;
    typedef xmlrpc_c::value_string ValueString;
    typedef xmlrpc_c::value_datetime ValueDateTime;
    typedef xmlrpc_c::value_bytestring ValueByteString;
    typedef xmlrpc_c::value_nil ValueNil;
    typedef xmlrpc_c::value_array ValueArray;
    typedef xmlrpc_c::value_struct ValueStruct;
    
    // Private member variables
    std::string m_host;
    int m_port;
    std::string m_pass;
    std::string m_username;
    
    
    // Communication Library, XmlRPC in this case
    XmlRPC *m_xmllib;
    
    
    
};