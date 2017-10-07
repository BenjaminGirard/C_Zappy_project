//
// Player.cpp for player in /home/dejean/EPITECH/UNIX/PSU_2016_zappy/client_ia_srcs
//
// Made by dejean
// Login   <benjamin.girard@epitech.eu>
//
// Started on  Sat Jun 24 17:53:18 2017 dejean
// Last update Sun Jul  2 21:08:11 2017 nicolas dejean
//

#include "Player.hpp"
#include "Stoi.hpp"
#include "Fork.hpp"

void mainCall(std::string&, std::string&, int);

Player::Player(std::string const& ip, int port, std::string const& name):
  /* LEVEL, { NBPLAYER, LINEMATE, DERAUMERE, SIBUR, MENDIANE, PHIRAS, THYSTAME} */
  _inventory(),
  _infoLevel({
      {1, { 1, 1, 0, 0, 0, 0, 0} },
      {2, { 2, 1, 1, 1, 0, 0, 0} },
      {3, { 2, 2, 0, 1, 0, 2, 0} },
      {4, { 4, 1, 1, 2, 0, 1, 0} },
      {5, { 4, 1, 2, 1, 3, 0, 0} },
      {6, { 6, 1, 2, 3, 0, 1, 0} },
      {7, { 6, 2, 2, 2, 2, 2, 1} }
    }),
  _socket(ip, port),
  _name(name),
  _lvl("1"),
  _ip(ip),
  _port(port)
{}

Player::~Player()
{}

int Player::needToRead(std::string &str)
{
  int l = 0;

  if ((l = getBroadcast(str)) != -1)
    {
      size_t i = 0;
      if (str.find(_name) != std::string::npos)
      {
	if ((i = str.find(_lvl)) != std::string::npos)
	{
	  str.erase(0, i);
	  str.erase(0, str.find(" ") + 1);
	  return (l);
	}
	  return -1;
      }
      return -2;
    }
  return (-3);
}

void		Player::moveToVoice(int dir)
{
  static Action action;
  size_t	nbPlayer = _vision.front().getNbPlayer();

  if (nbPlayer == _infoLevel[_inventory.getLevel()].nbPlayer)
  {
    _dir = -3;
    return doAction(INCANTATION);
  }
  if (dir == 0 || dir <= -2)
    return tellUp();
  if (dir == 5)
    {
      if (action == LEFT || action == RIGHT)
      {
	action = FORWARD;
	return doAction(FORWARD);
      }
      action = RIGHT;
      doAction(RIGHT);
      return doAction(RIGHT);
    }
  else if (dir > 1 && dir < 5)
  {
    if (action == RIGHT)
      {
	action = FORWARD;
	return doAction(FORWARD);
      }
      action = LEFT;
    return doAction(LEFT);
  }
  else if (dir > 5 && dir < 9)
  {
    if (action == LEFT)
    {
      action = FORWARD;
      return doAction(FORWARD);
    }
    action = RIGHT;
    return doAction(RIGHT);
  }
  return doAction(FORWARD);
}

void		Player::aiLoop(Select &select, CmdHandler &cmd)
{
  std::string str("");
  std::string elevation("");
  std::string order("");
  _dir = -3;

  while (str.find("dead") == std::string::npos)
    {
      if (_order.size() < 1)
	playerCore(order);
      if (select.isReadable())
	{
	  _socket.readSocket();
	  while ((str = _socket.readCmd()) != "" && str.find("ko") == std::string::npos)
	    {
	      if (str.find("dead") != std::string::npos)
		return ;
	      if (str.find("Elevation underway") != std::string::npos)
	      {
		elevation = str;
		break ;
	      }
	      if (elevation.find("Elevation underway") != std::string::npos &&
		  str.find("Current level:") == std::string::npos)
		break ;
	      else
		elevation = "";
	      int dir = 0;
	      if ((dir = needToRead(str)) > -2  || str.find("UP") != std::string::npos)
	      {
	      	_dir = dir;
	      	order = "Message";
	      	break ;
	      }
	      if (_order.size() > 0)
		{
		  order = _order.front();
		  _order.pop();
		  if (order == "Fork")
		    Fork::forking(mainCall, _ip, _name, _port);
		  else if (order == "Look")
		    updateCases(cmd.vectorHandler(str));
		  else if (order == "Inventory")
		    updateInventory(cmd.pairHandler(str));
		  else if (str.find("Current level: ") != std::string::npos)
		  {
		    _lvl = str.back();
		    _inventory.setLevel(stoi(_lvl));
		  }
		  else if (str == std::string(_name + " " + _lvl + " UP"))
		    order = "Message";
		}
	    }
	}
    }
}

bool	Player::connectionLoop(Select &select, CmdHandler &cmd)
{
  std::string str("");
  std::string order("");
  int	nbr = 0;

  std::string name = _name + "\n";
  while (true)
    {
      if (select.isReadable())
	{
	  _socket.readSocket();
	  while ((str = _socket.readCmd()) != "")
	    {
	      if (str == "WELCOME")
		_socket << name;
	      else if (str.find(" ") == std::string::npos && (nbr = Stoi::getNbr(str)) == -1)
		return (false);
	      else if (str.find(" ") != std::string::npos)
		{
		  std::vector<std::string>	tmp;
		  int				nb_x = 0;
		  int				nb_y = 0;

		  tmp = cmd.str_to_vector(str, " ");
		  if ((nb_x = Stoi::getNbr(tmp[0])) == -1 || (nb_y = Stoi::getNbr(tmp[1])) == -1)
		    return (false);
		  _map = std::make_pair(nb_x, nb_y);
		  return (true);
		}
	    }
	}
    }
  return (true);
}

void	Player::run()
{
  CmdHandler	cmd;
  Select select(_socket.getFd());

  if (connectionLoop(select, cmd))
      aiLoop(select, cmd);
}

int			Player::getBroadcast(std::string& mess)
{
  int                   ret = 0;

  if (mess.find("message") == std::string::npos)
    return (-1);
  mess.erase(0, mess.find(" ") + 1);
  ret = Stoi::getNbr(mess);
  mess.erase(0, mess.find(" ") + 1);
  return ret;
}

void	Player::forward(std::string const& /*command*/)
{
  _socket << "Forward\n";
  _order.push("Forward");
}

void	Player::right(std::string const& /*command*/)
{
  _socket << "Right\n";
  _order.push("Right");
}

void	Player::left(std::string const& /*command*/)
{
  _socket << "Left\n";
  _order.push("Left");
}

void	Player::look(std::string const& /*command*/)
{
  _socket << "Look\n";
  _order.push("Look");
}

void	Player::inventory(std::string const& /*command*/)
{
  _socket << "Inventory\n";
  _order.push("Inventory");
}

void	Player::broadcast(std::string const&str)
{
  std::string s("Broadcast ");
  s += str;
  s += "\n";
  _socket << s;
  _order.push("Broadcast");
}

void	Player::connectNbr(std::string const& /*command*/)
{
  _socket << "Connect_nbr\n";
  _order.push("Connect_nbr");
}

void	Player::fork(std::string const& /*command*/)
{
  _socket << "Fork\n";
  _order.push("Fork");
}

void	Player::eject(std::string const& /*command*/)
{
  _socket << "Eject\n";
  _order.push("Eject");
}

void	Player::take(std::string const&str)
{
  std::string s("Take ");
  s += str;
  s += "\n";

  _socket << s;
  _order.push("Take");
}

void	Player::set(std::string const&str)
{
  std::string s("Set ");
  s += str;
  s += "\n";
  _socket << s;
  _order.push("Set");
}

void	Player::incantation(std::string const& /*command*/)
{
  _socket << "Incantation\n";
  _order.push("Incantation");
}
