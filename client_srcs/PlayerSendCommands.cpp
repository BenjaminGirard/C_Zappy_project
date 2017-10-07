//
// PlayerSendCommands.cpp for player in /home/ndejean/EPITECH/PSU/PSU_2016_zappy/client_srcs
//
// Made by nicolas dejean
// Login   <benjamin.girard@epitech.eu>
//
// Started on  Mon Jun 26 16:34:07 2017 nicolas dejean
// Last update Sun Jul  2 19:40:40 2017 de Ganay Renaud
//

#include "Player.hpp"

void				Player::doAction(const Action& action, const Item& ressources, const std::string& text)
{
  static const std::map< Action, fnct >	callAction =
    {
      { FORWARD, (&Player::forward) },
      { RIGHT, (&Player::right) },
      { LEFT, (&Player::left) },
      { LOOK, (&Player::look) },
      { INVENTORY, (&Player::inventory) },
      { BROADCAST_TEXT, (&Player::broadcast) },
      { CONNECT_NBR, (&Player::connectNbr) },
      { FORK, (&Player::fork) },
      { EJECT, (&Player::eject) },
      { TAKE_OBJECT, (&Player::take) },
      { SET_OBJECT, (&Player::set) },
      { INCANTATION, (&Player::incantation) }
    };
  std::string			str = text;

  for (auto res = _inventory._ressourcesInventory.begin();
       res != _inventory._ressourcesInventory.end(); ++res)
      if (res->second.second == ressources)
	  str = res->first;

  fnct				f;
  for (auto it = callAction.begin(); it != callAction.end(); ++it)
    if (it->first == action)
    {
      f = it->second;
      return ((this->*f)(str));
    }
}
