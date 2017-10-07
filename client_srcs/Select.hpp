#ifndef _SELECT_
#define _SELECT_

#include <stdlib.h>
#include <sys/select.h>

class Select
{
  int fd;
  fd_set readset;
public:
  Select(int);
  ~Select();
  bool isReadable();
};

#endif
