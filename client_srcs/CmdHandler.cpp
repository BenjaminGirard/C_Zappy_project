//
// CmdHandler.cpp for CmdHandler in /home/degana_r/PSU_2016_zappy/client_srcs
//
// Made by de Ganay Renaud
// Login   <degana_r@epitech.net>
//
// Started on  Tue Jun 27 14:20:09 2017 de Ganay Renaud
// Last update Sun Jul  2 19:42:47 2017 de Ganay Renaud
//

#include <regex>
#include <iostream>
#include "CmdHandler.hpp"
#include "Stoi.hpp"

void						CmdHandler::rmSpaces(std::string &str)
{
    str = std::regex_replace(str, std::regex("^ +| +$|( ) +"), "$1");
}

bool						CmdHandler::booleanHandler(std::string const &cmdHandler)
{
    if (cmdHandler == "ok")
	return (true);
    return (false);
}

std::vector<std::vector<std::string> >		CmdHandler::vectorHandler(std::string &cmdHandler)
{
    std::vector<std::vector<std::string> >	ret;
    std::vector<std::string>			temp;
    size_t					nb = 0;

    if ((nb = cmdHandler.find("[")) != std::string::npos)
      cmdHandler.erase(0, nb + 1);
    if ((nb = cmdHandler.find("]")) != std::string::npos)
      cmdHandler.erase(nb, cmdHandler.size() - 1);

    temp = str_to_vector(cmdHandler, ",");
    for (auto &it : temp)
    {
	rmSpaces(it);
	ret.push_back(str_to_vector(it, " "));
    }
    return (ret);
}

std::vector<std::string>			CmdHandler::str_to_vector(std::string &str,
								  std::string const &delimiter)
{
    std::vector<std::string>			ret;
    int						pos = 0;
    std::string					token;

    while ((pos = str.find(delimiter)) != static_cast<int>(std::string::npos))
    {
	token = str.substr(0, pos);
	if (str[0] == delimiter[0] && pos == 1)
	    ret.push_back(" ");
	else
	    ret.push_back(token);
	str.erase(0, pos + 1);
    }
    ret.push_back(str);
    return (ret);
}

std::vector<std::pair<std::string, size_t> >	CmdHandler::pairHandler(std::string &CmdHandler)
{
  std::vector<std::vector<std::string> >	temp;
  std::vector<std::pair<std::string, size_t> > ret;
  std::string::size_type			nbr = 0;

  temp = vectorHandler(CmdHandler);
  if (temp.size() > 1)
    for (auto &it : temp)
      try {
	int				stock;
	stock = std::stoi(it[1], &nbr);
	ret.push_back(std::make_pair(it[0], stock));
      }
      catch (...) {
	std::cerr << "Invalid answer from server" << std::endl;
      }
  return (ret);
}

int						CmdHandler::valueHandler(std::string &cmdHandler)
{
    int						ret;

    if (cmdHandler == "ko")
	return (-1);
    try {
	std::string::size_type			nbr = 0;
	ret = std::stoi(cmdHandler, &nbr);
    }
    catch (...) {
	std::cerr << "Invalid answer from server" << std::endl;
	return (-1);
    }
    return (ret);
}
