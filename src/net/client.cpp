#include "client.h"

#include <asio/read.hpp>
#include <asio/write.hpp>
#include <iostream>

using namespace net;

Client::Client()
    : asio_guard_(asio_context_.get_executor()), asio_socket_(asio_context_)
{
  context_thread_ = std::thread([this]() { this->asio_context_.run(); });
}

Client::~Client()
{
  asio_context_.stop();
  context_thread_.join();
}

void Client::Connect(std::string host, int port)
{
  std::error_code ec;
  asio::ip::tcp::endpoint endpoint(asio::ip::make_address(host, ec), port);
  asio_socket_.async_connect(
      endpoint, [this](std::error_code ec) { this->OnConnect(ec); });
}

void Client::Send(net::Packet packet)
{
  std::lock_guard lock(mx_);
  write_packets_.emplace(std::move(packet));
  if (write_packets_.size() > 1) return;

  asio::async_write(asio_socket_, write_packets_.front().GetBuffer(),
                    [this](std::error_code ec, std::size_t bytes) {
                      this->OnWrite(ec, bytes);
                    });
}

void Client::OnWrite(std::error_code ec, std::size_t bytes)
{
  if (ec) {
    OnError(ec);
    return;
  }

  std::lock_guard lock(mx_);
  write_packets_.pop();
  if (write_packets_.empty()) return;

  asio::async_write(asio_socket_, write_packets_.front().GetBuffer(),
                    [this](std::error_code ec, std::size_t bytes) {
                      this->OnWrite(ec, bytes);
                    });
}

void Client::OnError(std::error_code ec)
{
  std::cerr << "Client Error: " << ec.message() << std::endl;
}

void Client::OnConnect(std::error_code ec)
{
  if (ec) {
    OnError(ec);
    return;
  }

  connect_callbak_();

  asio::async_read(asio_socket_, read_packet_.GetHeader(),
                   [this](std::error_code ec, std::size_t bytes) {
                     this->OnHeaderRead(ec, bytes);
                   });
}

void Client::OnHeaderRead(std::error_code ec, std::size_t bytes)
{
  if (ec) {
    OnError(ec);
    return;
  }

  asio::async_read(asio_socket_, read_packet_.GetBody(),
                   [this](std::error_code ec, std::size_t bytes) {
                     this->OnBodyRead(ec, bytes);
                   });
}

void Client::OnBodyRead(std::error_code ec, std::size_t bytes)
{
  if (ec) {
    OnError(ec);
    return;
  }

  read_callback_(std::move(read_packet_));

  asio::async_read(asio_socket_, read_packet_.GetHeader(),
                   [this](std::error_code ec, std::size_t bytes) {
                     this->OnHeaderRead(ec, bytes);
                   });
}

void Client::SetOnRead(std::function<void(net::Packet)> callback)
{
  read_callback_ = std::move(callback);
}

void Client::SetOnConnect(std::function<void()> connectFn)
{
  connect_callbak_ = std::move(connectFn);
}
