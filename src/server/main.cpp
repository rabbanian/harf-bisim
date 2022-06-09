#include <asio/io_context.hpp>
#include <asio/signal_set.hpp>

#include "net/connection_manager.h"
#include "net/server.h"

int main()
{
  asio::io_context ioc;

  asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), 1234);

  net::ConnectionManager manager;
  std::make_shared<net::Server>(ioc, endpoint, manager)->Run();

  asio::signal_set signals(ioc, SIGINT, SIGTERM);
  signals.async_wait([&ioc](std::error_code const&, int) {
    ioc.stop();
  });

  ioc.run();
  return 0;
}
