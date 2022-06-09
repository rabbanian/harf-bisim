#ifndef HARF_BISIM_SRC_NET_CONNECTION_MANAGER_H_
#define HARF_BISIM_SRC_NET_CONNECTION_MANAGER_H_

#include <memory>
#include <unordered_set>

#include "net/connection.h"
#include "net/packet.h"

namespace net {

class ConnectionManager
{
 public:
  ConnectionManager() = default;
  void Add(net::Connection &con);
  void Remove(net::Connection &con);
  void SendToALL(net::Connection &con, net::Packet &&p);

 private:
  std::unordered_set<net::Connection *> connections_;
};

}  // namespace net

#endif  // HARF_BISIM_SRC_NET_CONNECTION_MANAGER_H_
