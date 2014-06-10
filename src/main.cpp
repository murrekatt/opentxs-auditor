#include "Auditor.hpp"
#include <boost/asio.hpp>
#include <thread>
#include <iostream>

int main()
{
  std::cout << "opentxs auditor starting...\n";

  boost::asio::io_service ioService;

  opentxs::Auditor auditor(ioService);

  std::thread runner([&ioService]() { ioService.run(); });
  runner.join();

  std::cout << "opentxs auditor stopped.\n";

  return 0;
}
