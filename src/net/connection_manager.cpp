#include "connection_manager.h"

#include <iostream>

void net::ConnectionManager::Add(net::Connection& con)
{
  connections_.insert(&con);
}

void net::ConnectionManager::Remove(net::Connection& con)
{
  connections_.erase(&con);
}

void net::ConnectionManager::SendToALL(net::Connection& con, net::Packet&& p)
{
  std::cout << "Sending To ALL" << std::endl;
  for (auto &connection : connections_) {
    if (&con == connection) continue;
    connection->Send(p);
  }
}
