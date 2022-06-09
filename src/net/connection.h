#ifndef HARF_BISIM_SRC_NET_CONNECTION_H_
#define HARF_BISIM_SRC_NET_CONNECTION_H_

#include <asio/ip/tcp.hpp>
#include <memory>
#include <mutex>
#include <queue>

#include "net/packet.h"

namespace net {
class ConnectionManager;

class Connection : public std::enable_shared_from_this<Connection>
{
 public:
  Connection(asio::ip::tcp::socket socket, net::ConnectionManager &manager);
  ~Connection();
  void Run();
  void Send(net::Packet packet);

 private:
  void OnHeaderRead(std::error_code ec, std::size_t bytes);
  void OnBodyRead(std::error_code ec, std::size_t bytes);
  void OnError(std::error_code ec);
  void OnWrite(std::error_code ec, std::size_t bytes);

  asio::ip::tcp::socket asio_socket_;
  net::Packet read_packet_;
  std::queue<net::Packet> write_packets_;
  net::ConnectionManager &manager_;
  std::mutex mx_;
};

}  // namespace net

#endif  // HARF_BISIM_SRC_NET_CONNECTION_H_
