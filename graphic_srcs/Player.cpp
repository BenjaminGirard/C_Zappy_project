//
// Player.cpp for player in /home/dejean/EPITECH/UNIX/PSU_2016_zappy/client_ia_srcs
//
// Made by dejean
// Login   <benjamin.girard@epitech.eu>
//
// Started on  Sat Jun 24 17:53:18 2017 dejean
// Last update Mon Jul  3 23:58:32 2017 fourni_2
//

#include "Player.hpp"
#include "Stoi.hpp"
#include <iostream>
#include <fstream>
#include <string.h>

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
  _lvl("1")
{}

Player::~Player()
{}

int Player::needToRead(std::string &str)
{
  int l = 0;

  if ((l = getBroadcast(str)) != -1)
    {
      size_t i = 0;
      if (str.find(_name) != std::string::npos && (i = str.find(_lvl)) != std::string::npos)
	{
	  str.erase(0, i);
	  str.erase(0, str.find(" ") + 1);
	  return (l);
	}
    }
  return (-1);
}

bool		Player::moveToVoice(int dir)
{
  if (dir == 0 || dir == -1)
    return true;
  if (dir == 5)
    {
      right("");
      right("");
    }
  else if (dir > 1 && dir < 5)
    left("");
  else if (dir > 5 && dir < 9)
    right("");
  forward("");
  return false;
}

void		Player::aiLoop(Select &select, CmdHandler &cmd)
{
  std::string str("");
  std::string elevation("");
  std::string order("");
  std::ofstream fileo;
  std::ifstream filei;
  std::vector<std::string> cmds;
  char tmp[256];

  (void)cmd;
  memset(tmp, 0, 256);
  while (str.find("dead") == std::string::npos)
    {
      cmds.clear();
      if (select.isReadable())
	{
	  _socket.readSocket();
	  while ((str = _socket.readCmd()) != "##" && str != "")
	    {
	      if (str.find("dead") != std::string::npos)
		return ;
	      cmds.push_back(str);
	    }
	  str = "";
	  while (str != "@@")
	    {
	      filei.open("Zappy_Unity/Assets/mapInfo.txt", std::ofstream::in);
	      filei.getline(tmp, 256);
	      str = tmp;
	      filei.close();
	    }
	  fileo.open("Zappy_Unity/Assets/mapInfo.txt", std::ofstream::out | std::ofstream::trunc);
	  fileo << "#\n";
	  auto it = cmds.begin();
	  while (it != cmds.end())
	    {
	      if (*it != "" && *it != "#")
		fileo << *it + "\n";
	      it++;
	    }
	  fileo << "##\n";
	  fileo.close();
	}
    }
}

bool	Player::connectionLoop(Select &select, CmdHandler &cmd)
{
  std::string str("");
  std::string order("");

  (void)cmd;
  while (true)
    {
      if (select.isReadable())
	{
	  _socket.readSocket();
	  while ((str = _socket.readCmd()) != "")
	    {
	      if (str == "WELCOME")
		{
		  _socket << "GRAPHIC\n";
		  return true;
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
    {
      aiLoop(select, cmd);
    }
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
