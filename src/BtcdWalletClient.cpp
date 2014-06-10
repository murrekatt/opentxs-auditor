#include "BtcdWalletClient.hpp"

namespace opentxs
{

BtcdWalletClient::BtcdWalletClient(boost::asio::io_service& ioService)
  : ioService_(ioService)
  , work_(ioService_)
{
}

BtcdWalletClient::~BtcdWalletClient()
{
}

} // namespace opentxs
