#include "packet.h"

net::Packet::Packet(net::Packet &&from) noexcept : Packet()
{
  *this = std::move(from);
}

net::Packet &net::Packet::operator=(net::Packet &&from) noexcept
{
  if (this == &from) return *this;
  payload_ = std::move(from.payload_);
  header_ = from.header_;
  from.header_ = {0};

  return *this;
}

asio::mutable_buffer net::Packet::GetHeader()
{
  return asio::buffer(&header_, sizeof(header_));
}

asio::mutable_buffer net::Packet::GetBody()
{
  payload_.resize(header_.size);
  return asio::buffer(payload_.data(), payload_.size());
}

std::array<asio::const_buffer, 2> net::Packet::GetBuffer() const
{
  return {asio::buffer(&header_, sizeof(header_)),
          asio::buffer(payload_.data(), payload_.size())};
}

net::Packet::Packet(std::vector<std::uint8_t> data) : payload_(std::move(data))
{
  header_.size = data.size();
}

std::vector<std::uint8_t> net::Packet::GetPayload()
{
  return payload_;
}
