#ifndef __OPENTXS_BTCDWALLETCLIENT_HPP__
#define __OPENTXS_BTCDWALLETCLIENT_HPP__

#include "WalletClient.hpp"
#include <boost/asio/io_service.hpp>

namespace opentxs
{

class BtcdWalletClient : public WalletClient
{
public:
  explicit BtcdWalletClient(boost::asio::io_service& ioService);
  virtual ~BtcdWalletClient();

private:
  boost::asio::io_service& ioService_;
  boost::asio::io_service::work work_;
};

} // namespace opentxs

#endif // __OPENTXS_BTCDWALLETCLIENT_HPP__
