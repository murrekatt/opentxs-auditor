#include "BtcdWalletClient.hpp"

namespace opentxs
{

BtcdWalletClient::BtcdWalletClient(boost::asio::io_service& ioService)
    : ioService_(ioService)
    , work_(ioService_)
    , client_()
{
    client_.init_asio(&ioService_);
}

BtcdWalletClient::~BtcdWalletClient()
{
}

void BtcdWalletClient::connect()
{
    // TODO: connect to wallet
}

void BtcdWalletClient::getDepositScript()
{
    // TODO: call RPC call
}

} // namespace opentxs
