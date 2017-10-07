//
// PlayerCore.cpp for player in /home/ndejean/EPITECH/PSU/PSU_2016_zappy/client_srcs
//
// Made by nicolas dejean
// Login   <benjamin.girard@epitech.eu>
//
// Started on  Tue Jun 27 13:21:04 2017 nicolas dejean
// Last update Sun Jul  2 19:37:15 2017 de Ganay Renaud
//

#include "Player.hpp"

void				Player::playTurn(const Action& action)
{
  auto				it = _infoLevel.find(_inventory.getLevel());
  Item				resNeeded;

  if (action == LOOK)
      return doAction(LOOK);
  if (action == INVENTORY)
      return doAction(INVENTORY);
  if (_inventory.getFood() < FOOD_BROADCAST)
      return doAction(lookForItem(RES_FOOD), RES_FOOD);
  if (action == FORK)
    return doAction(FORK);
  if (action == MESSAGE || _dir > -2)
    return moveToVoice(_dir);
  else if (it != _infoLevel.end())
    {
      if (action == TAKE_OBJECT)
	{
	  if (isElevation(it->second))
	      return takeAll();
	  else if ((resNeeded = searchRessources(it->second)) != UNDEFINED)
	      return doAction(lookForItem(resNeeded), resNeeded);
	  else
	    {
//	      std::string	str(_name + " " + _lvl + " UP");
	      return (moveToVoice(_dir));
	    }
	}
    }
}

void				Player::playerCore(const std::string& order)
{
    std::map< std::string, Action >		setInfo =
  {
    { "", LOOK },
    { "Look", INVENTORY },
    { "Inventory", TAKE_OBJECT },
    { "Take", LOOK },
    { "Incantation", FORK },
    { "Broadcast", LOOK },
    { "Message", LOOK },
    { "Forward", LOOK },
    { "Right", LOOK },
    { "Left", LOOK },
    { "Connect_nbr", LOOK },
    { "Fork", LOOK },
    { "Eject", LOOK },
    { "Set", LOOK },
  };

  for (auto it = setInfo.begin(); it != setInfo.end(); ++it)
    if (order == it->first)
      return playTurn(it->second);
}
