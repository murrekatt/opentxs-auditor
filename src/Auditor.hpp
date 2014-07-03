#ifndef __OPENTXS_AUDITOR_HPP__
#define __OPENTXS_AUDITOR_HPP__

#include "wallet/WalletClient.hpp"

namespace opentxs
{

class Auditor
{
public:
    Auditor();

private:
    WalletClient walletClient_;
};

} // namespace opentxs

#endif // __OPENTXS_AUDITOR_HPP__
