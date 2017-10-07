#include "Select.hpp"

Select::Select(int fd_socket)
  : fd(fd_socket)
{
  FD_ZERO(&readset);
  FD_SET(fd, &readset);
}

Select::~Select()
{
}

bool Select::isReadable()
{
  int result = select(fd + 1, &readset, NULL, NULL, NULL);
  if (result > 0 && FD_ISSET(fd, &readset))
    {
      return true;
    }
  return false;
}
