#ifndef __OPENTXS_BTCDWALLETCLIENT_HPP__
#define __OPENTXS_BTCDWALLETCLIENT_HPP__

#include "WalletClient.hpp"
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <boost/asio/io_service.hpp>

namespace opentxs
{

class BtcdWalletClient : public WalletClient
{
public:
    explicit BtcdWalletClient(boost::asio::io_service& ioService);
    virtual ~BtcdWalletClient();

    virtual void connect();
    virtual void getDepositScript();

private:
    typedef websocketpp::client<websocketpp::config::asio_tls_client> Client;

private:
    boost::asio::io_service& ioService_;
    boost::asio::io_service::work work_;
    Client client_;
};

} // namespace opentxs

#endif // __OPENTXS_BTCDWALLETCLIENT_HPP__
