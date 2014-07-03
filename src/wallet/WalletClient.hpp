#ifndef __OPENTXS_WALLETCLIENT_HPP__
#define __OPENTXS_WALLETCLIENT_HPP__

namespace opentxs
{

struct WalletClient
{
    WalletClient();

    void connect();
    void getDepositScript();
};

} // namespace opentxs

#endif // __OPENTXS_WALLETCLIENT_HPP__
