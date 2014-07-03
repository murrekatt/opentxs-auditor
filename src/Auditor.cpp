#include "Auditor.hpp"

namespace opentxs
{

Auditor::Auditor(boost::asio::io_service& ioService)
    : ioService_(ioService)
    , walletClient_(ioService_)
{
}

} // namespace opentxs
