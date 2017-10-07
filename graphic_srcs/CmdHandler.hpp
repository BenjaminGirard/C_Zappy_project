//
// CmdHandler.hpp for CmdHandler in /home/degana_r/PSU_2016_zappy/client_srcs
//
// Made by de Ganay Renaud
// Login   <degana_r@epitech.net>
//
// Started on  Tue Jun 27 14:20:20 2017 de Ganay Renaud
// Last update Sun Jul  2 15:25:49 2017 nicolas dejean
//

#ifndef CMDHANDLER_HPP_
# define CMDHANDLER_HPP_

#include <vector>
#include <string>
#include <map>

class						CmdHandler
{
    typedef bool (CmdHandler::*fnct)(std::string const &);
    std::map<std::string, fnct>		_callback =
    {
	{"Forward", (&CmdHandler::booleanHandler)},
	{"Right", (&CmdHandler::booleanHandler)},
	{"Left", (&CmdHandler::booleanHandler)},
	{"Broadcast", (&CmdHandler::booleanHandler)},
	{"Fork", (&CmdHandler::booleanHandler)},
	{"Eject", (&CmdHandler::booleanHandler)},
	{"Take", (&CmdHandler::booleanHandler)},
	{"Set", (&CmdHandler::booleanHandler)}
    };

public:
    CmdHandler() = default;
    ~CmdHandler() = default;
    CmdHandler(const CmdHandler &cp) = delete;
    CmdHandler			&operator=(const CmdHandler &cp) = delete;

    bool					booleanHandler(std::string const &cmdReturn);
    std::vector<std::string>			str_to_vector(std::string &str,
							      std::string const &delimiter);
    std::vector<std::vector<std::string> >	vectorHandler(std::string &cmdHandler);
    std::vector<std::pair<std::string, size_t> > pairHandler(std::string &cmdHandler);
    int						 valueHandler(std::string &cmdHandler);

    void					rmSpaces(std::string &str);
};

#endif /* !CMDHANDLER_HPP_ */
