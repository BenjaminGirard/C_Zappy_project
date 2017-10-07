//
// CheckPlayerVision.cpp for vision in /home/ndejean/EPITECH/PSU/PSU_2016_zappy/client_ia_srcs
//
// Made by nicolas dejean
// Login   <benjamin.girard@epitech.eu>
//
// Started on  Mon Jun 26 15:03:51 2017 nicolas dejean
// Last update Sat Jul  1 22:04:35 2017 nicolas dejean
//

#include "Player.hpp"

Action				Player::lookForItem(const Item& ressources)
{
  static Action			direction = LEFT;
  static bool			turn = false;

  for (auto cases = _vision.begin(); cases != _vision.end(); ++cases)
  {
    std::cout << "CASE ID: " << (*cases).getId() << std::endl;
    if ((*cases).getId() == 0 && checkCases(*cases, ressources))
    {
      std::cout << "entered TAKE OBJECT" << std::endl;
      return (TAKE_OBJECT);
    }
    if (turn == false && (direction == LEFT || direction == RIGHT))
    {
      turn = true;
      return (FORWARD);
    }
    if ((*cases).getId() > 3 && checkCases(*cases, ressources))
    {
      direction = FORWARD;
      return (FORWARD);
    }
    if (((*cases).getId() == 1 && checkCases(*cases, ressources)) || direction == LEFT)
    {
      turn = false;
      direction = RIGHT;
      return (LEFT);
    }
    if (((*cases).getId() == 3 && checkCases(*cases, ressources)) || direction == RIGHT)
    {
      turn = false;
      direction = LEFT;
      return (RIGHT);
    }
  }
  direction = FORWARD;
  return (FORWARD);
}

bool				Player::checkCases(const Case& cases,
						   const Item& ressources)
{
  int			i = 0;
  for (auto res = cases._itemInCase.begin(); res != cases._itemInCase.end(); ++res)
  {
    std::cout << "CASE " << i << ": " << res->first << std::endl;
    if (res->first == ressources)
      return (true);
    i++;
  }
  return (false);
}


void				Player::updateCases(const std::vector< std::vector< std::string > >& ressources)
{
  /* DOESN'T WORK ? */
  size_t				i = 0;

  _vision.clear();
  for (auto it = ressources.begin(); it != ressources.end(); ++it)
  {
    Case				tmp;
    std::cout << "CASES : "  << i << std::endl;
    tmp.setCaseRessources(*it, i);
    _vision.push_back(tmp);

    // std::cout << "----------CASES INVENTORY---------------" << std::endl;
    // std::cout << i << std::endl;
    // std::cout << "FOOD:" << _vision[i].getFood() << std::endl;
    // std::cout << "LINEMATE:" << _vision[i].getLinemate() << std::endl;
    // std::cout << "DERAUMERE:" << _vision[i].getDeraumere() << std::endl;
    // std::cout << "SIBUR:" << sibur << std::endl;
    // std::cout << "MENDIANE:" << mendiane << std::endl;
    // std::cout << "PHIRAS:" << phiras << std::endl;
    // std::cout << "THYSTAME:" << thystame << std::endl;

    i++;
  }
}
