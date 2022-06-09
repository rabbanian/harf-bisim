#ifndef HARF_BISIM_SRC_NET_PACKET_H_
#define HARF_BISIM_SRC_NET_PACKET_H_

#include <vector>
#include <array>
#include <asio/buffer.hpp>
#include <cstddef>
#include <cstdint>

namespace net {

class Packet
{
 public:
  Packet() = default;
  Packet(const Packet& from) = default;
  Packet(Packet&& from) noexcept;
  explicit Packet(std::vector<std::uint8_t> data);
  Packet& operator=(const Packet& from) = default;
  Packet& operator=(Packet&& from) noexcept;

  asio::mutable_buffer GetHeader();
  asio::mutable_buffer GetBody();
  std::array<asio::const_buffer, 2> GetBuffer() const;
  std::vector<std::uint8_t> GetPayload();

 private:
  struct Header
  {
    std::uint32_t size;
  } header_ = {};
  std::vector<std::uint8_t> payload_;
};

}  // namespace net

#endif  // HARF_BISIM_SRC_NET_PACKET_H_
