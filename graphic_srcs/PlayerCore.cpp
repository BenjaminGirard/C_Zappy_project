//
// PlayerCore.cpp for player in /home/ndejean/EPITECH/PSU/PSU_2016_zappy/client_srcs
//
// Made by nicolas dejean
// Login   <benjamin.girard@epitech.eu>
//
// Started on  Tue Jun 27 13:21:04 2017 nicolas dejean
// Last update Sun Jul  2 15:23:39 2017 nicolas dejean
//

#include "Player.hpp"

void				Player::playTurn(const Action& action)
{
  auto				it = _infoLevel.find(_inventory.getLevel());
  Item				resNeeded;

  if (action == LOOK)
    {
      std::cout << "ACTUAL ORDER : LOOK" << std::endl;
      return doAction(LOOK);
    }
  if (action == INVENTORY)
    {
      std::cout << "ACTUAL ORDER : INVENTORY" << std::endl;
      return doAction(INVENTORY);
    }
  if (_inventory.getFood() < MIN_FOOD)
    {
      std::cout << "ACTUAL ORDER : FOOD" << std::endl;
      return doAction(lookForItem(RES_FOOD), RES_FOOD);
    }
  if (action == FORK)
  {
    std::cout << "ACTUAL ORDER : FORK" << std::endl;
    return doAction(FORK);
  }
  if (action == MESSAGE)
    {
      if (moveToVoice(_dir))
	return doAction(INCANTATION);
      // MOVE TO BROADCAST
      // return broadcastDirection();
    }
  else if (it != _infoLevel.end())
    {
      if (action == TAKE_OBJECT)
	{
	  if (isElevation(it->second))
	    {
	      std::cout << "ACTUAL ORDER : INCANTATION" << std::endl;
	      return takeAll();
	    }
	  else if ((resNeeded = searchRessources(it->second)) != UNDEFINED)
	    {
	      std::cout << "ACTUAL ORDER : TAKE OBJECT" << std::endl;
	      std::cout << resNeeded << std::endl;
	      return doAction(lookForItem(resNeeded), resNeeded);
	    }
	  else
	    {

	      std::cout << "ACTUAL ORDER : BRAODCAST" << std::endl;

	      std::string	str(_name + " " + _lvl + " UP");
	      if (moveToVoice(_dir))
		return (tellUp());

	    }
	}
    }
}

void				Player::playerCore(const std::string& order)
{
  std::cout << "LAST ORDER : " << order << std::endl;
  std::map< std::string, Action >		setInfo =
  {
    { "", LOOK },
    { "Look", INVENTORY },
    { "Inventory", TAKE_OBJECT },
    { "Take", LOOK },
    { "Incantation", FORK }, // take evrything on case and drop all that is needed for incantation
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
  {
    if (order == it->first)
      return playTurn(it->second);
  }
}
