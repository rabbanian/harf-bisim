#include "connection.h"

#include <asio/read.hpp>
#include <asio/write.hpp>
#include <iostream>

#include "net/connection_manager.h"

using namespace net;

Connection::Connection(asio::ip::tcp::socket socket,
                                      ConnectionManager &manager)
    : asio_socket_(std::move(socket)), manager_(manager)
{
  manager_.Add(*this);
}

void Connection::Run()
{
  asio::async_read(
      asio_socket_, read_packet_.GetHeader(),
      [self = shared_from_this()](std::error_code ec, std::size_t bytes) {
        self->OnHeaderRead(ec, bytes);
      });
}

void Connection::OnHeaderRead(std::error_code ec,
                                             std::size_t bytes)
{
  if (ec) {
    OnError(ec);
    return;
  }

  asio::async_read(
      asio_socket_, read_packet_.GetBody(),
      [self = shared_from_this()](std::error_code ec, std::size_t bytes) {
        self->OnBodyRead(ec, bytes);
      });
}

void Connection::OnBodyRead(std::error_code ec,
                                           std::size_t bytes)
{
  if (ec) {
    OnError(ec);
    return;
  }

  manager_.SendToALL(*this, std::move(read_packet_));

  asio::async_read(
      asio_socket_, read_packet_.GetHeader(),
      [self = shared_from_this()](std::error_code ec, std::size_t bytes) {
        self->OnHeaderRead(ec, bytes);
      });
}

void Connection::OnWrite(std::error_code ec, std::size_t bytes)
{
  if (ec) {
    OnError(ec);
    return;
  }

  std::lock_guard lock(mx_);
  write_packets_.pop();
  if (write_packets_.empty()) return;

  asio::async_write(
      asio_socket_, write_packets_.front().GetBuffer(),
      [self = shared_from_this()](std::error_code ec, std::size_t bytes) {
        self->OnWrite(ec, bytes);
      });
}

void Connection::OnError(std::error_code ec)
{
  std::cerr << "Connection Error: " << ec.message() << std::endl;
}

void Connection::Send(Packet packet)
{
  std::lock_guard lock(mx_);
  write_packets_.emplace(std::move(packet));
  if (write_packets_.size() > 1) return;

  asio::async_write(
      asio_socket_, write_packets_.front().GetBuffer(),
      [self = shared_from_this()](std::error_code ec, std::size_t bytes) {
        self->OnWrite(ec, bytes);
      });
}

Connection::~Connection() { manager_.Remove(*this); }
