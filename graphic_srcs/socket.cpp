#include "socket.hpp"

// try catch socket

Socket::Socket(std::string const& ip, int const port)
{
  if (init_ring_buff(&buff_data) == CRITERR)
    throw (SocketError("Can't open TCP socket"));
  struct protoent *pe = getprotobyname("TCP");
  
  fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (fd == -1)
    throw (SocketError("Can't open TCP socket"));
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);
  s_in.sin_addr.s_addr = inet_addr(ip.c_str());
  reconnect();
}

void Socket::writeSocket(std::string const &mess)
{
  if (fd < 0 || dprintf(fd, "%s", mess.c_str()) < 0)
    {
      throw (SocketError("Can't write, no socket"));
    }
}

extern "C" void Socket::readSocket()
{
  read_data(&buff_data, fd);
}

extern "C" std::string Socket::readCmd()
{
  return std::string(read_cmd(&buff_data));
}

void Socket::reconnect()
{
  if (connect(fd, (struct sockaddr*)&s_in, sizeof(s_in)) < 0)
    {
      throw (SocketError("Connection Failed"));
    }
}

Socket::~Socket()
{
  close(fd);
}
