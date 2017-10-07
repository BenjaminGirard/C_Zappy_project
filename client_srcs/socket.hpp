#ifndef _SOCKET_
#define _SOCKET_

extern "C"
{
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include "common.h"
#include "ring_buffer.h"
}

#include <iostream>

class			Socket
{
protected:
  int			fd;
  struct sockaddr_in	s_in;
  t_ring_buff		buff_data;
public:
  Socket(std::string const& ip, int const port);
  ~Socket();

  void			readSocket();
  std::string		readCmd();
  void			writeSocket(std::string const& mess);
  void			reconnect();
  void			operator<<(std::string const& str)
  {
    writeSocket(str);
  };
  int			getFd()
  {
    return fd;
  }
};

class			SocketError : public std::exception
{
  std::string		_msg;
public:
  SocketError(const std::string &msg) throw()
    : _msg(msg) {};
  virtual		~SocketError(void) throw(){};
  const char		*what(void) const throw()
  {
    return _msg.c_str();
  };
};

#endif
