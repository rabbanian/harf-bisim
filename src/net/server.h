#ifndef HARF_BISIM_SRC_NET_SERVER_H_
#define HARF_BISIM_SRC_NET_SERVER_H_

#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>

#include "connection_manager.h"

namespace net {

class Server : public std::enable_shared_from_this<Server>
{
 public:
  Server(asio::io_context& ioc, asio::ip::tcp::endpoint& endpoint,
         net::ConnectionManager& manager);
  void Run();

 private:
  void OnAccept(std::error_code ec);
  void OnError(std::error_code ec);

  asio::ip::tcp::socket asio_socket_;
  asio::ip::tcp::acceptor asio_acceptor_;
  net::ConnectionManager& connection_manager_;
};

}  // namespace net

#endif  // HARF_BISIM_SRC_NET_SERVER_H_
