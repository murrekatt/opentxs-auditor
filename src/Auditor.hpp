#ifndef __OPENTXS_AUDITOR_HPP__
#define __OPENTXS_AUDITOR_HPP__

#include "BtcdWalletClient.hpp"
#include <boost/asio/io_service.hpp>

namespace opentxs
{

class Auditor
{
public:
  explicit Auditor(boost::asio::io_service& ioService);

private:
  boost::asio::io_service& ioService_;
  BtcdWalletClient walletClient_;
};

} // namespace opentxs

#endif // __OPENTXS_AUDITOR_HPP__
