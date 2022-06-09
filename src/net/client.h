#ifndef HARF_BISIM_SRC_NET_CLIENT_H_
#define HARF_BISIM_SRC_NET_CLIENT_H_

#include <thread>
#include <mutex>
#include <queue>

#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>

#include "packet.h"

namespace net
{

class Client
{
 public:
  Client();
  ~Client();
  void Connect(std::string host, int port);
  void Send(net::Packet packet);
  void SetOnRead(std::function<void(net::Packet)> readFn);
  void SetOnConnect(std::function<void()> connectFn);

 private:
  void OnError(std::error_code ec);
  void OnConnect(std::error_code ec);
  void OnWrite(std::error_code ec, std::size_t bytes);
  void OnHeaderRead(std::error_code ec, std::size_t bytes);
  void OnBodyRead(std::error_code ec, std::size_t bytes);

  std::thread context_thread_;
  asio::io_context asio_context_;
  asio::executor_work_guard<asio::io_context::executor_type> asio_guard_;
  asio::ip::tcp::socket asio_socket_;

  std::mutex mx_;
  std::queue<net::Packet> write_packets_;
  net::Packet read_packet_;

  std::function<void(net::Packet)> read_callback_;
  std::function<void()> connect_callbak_;
};

}

#endif  // HARF_BISIM_SRC_NET_CLIENT_H_
