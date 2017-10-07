#ifndef __STOI__
#define __STOI__

#include <string>

class Stoi
{
public:
  Stoi() = default;
  ~Stoi() = default;

  static int getNbr(std::string const& str)
  {
    std::string::size_type        nbr = 0;
    int				ret =0;
    try {
      ret = std::stoi(str, &nbr);
      return (ret);
    }
    catch (...) {
      return (-1);
    }

  }
};

#endif
