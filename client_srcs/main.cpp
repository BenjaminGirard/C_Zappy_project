#include "Player.hpp"
#include "socket.hpp"

int printHelp()
{
  std::cout << "USAGE: ./zappy_ai -p port -n name -m machine" << std::endl;
  std::cout << "port	is the port number" << std::endl;
  std::cout << "name	is the name of the team" << std::endl;
  std::cout << "machine	is the name of the machine; localhost by default" << std::endl;
  return 0;
}

void		mainCall(std::string &ip, std::string &name, int port)
{
  try
    {
      Player p(ip, port, name);
      p.run();
    }
  catch(SocketError const& e)
    {
      std::cerr << "Error in Socket: " << e.what() << std::endl;
    }
}

int		main(int argc, char **argv)
{
  int		port;
  std::string	ip = "0.0.0.0";
  std::string	name;

  if (argc == 1 || std::string(argv[1]) == "-help")
    return printHelp();
  for (int i = 1; i < argc; i++)
    {
      std::string tmp(argv[i]);
      if (tmp == "-p" && i++ < argc)
	{
	  std::string::size_type sz;
	  try
	    {
	      port = std::stoi(argv[i], &sz);
	    }
	  catch (...)
	    {
	      return printHelp();
	    }
	}
      else if (tmp == "-n" && i++ < argc)
	name = std::string(argv[i]);
      else if (tmp == "-m" && i++ < argc)
	ip = std::string(argv[i]);
      else
	return printHelp();
    }
  mainCall(ip, name, port);
  return 0;
}
