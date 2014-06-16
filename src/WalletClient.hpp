#ifndef __OPENTXS_WALLETCLIENT_HPP__
#define __OPENTXS_WALLETCLIENT_HPP__

namespace opentxs
{

struct WalletClient
{
  virtual ~WalletClient() {}

  virtual void connect() = 0;
  virtual void getDepositScript() = 0;
};

} // namespace opentxs

#endif // __OPENTXS_WALLETCLIENT_HPP__
