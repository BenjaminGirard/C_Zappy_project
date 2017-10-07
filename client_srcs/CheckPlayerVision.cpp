//
// CheckPlayerVision.cpp for vision in /home/ndejean/EPITECH/PSU/PSU_2016_zappy/client_ia_srcs
//
// Made by nicolas dejean
// Login   <benjamin.girard@epitech.eu>
//
// Started on  Mon Jun 26 15:03:51 2017 nicolas dejean
// Last update Sun Jul  2 19:34:02 2017 de Ganay Renaud
//

#include "Player.hpp"

Action				Player::lookForItem(const Item& ressources)
{
  static Action			direction = LEFT;
  static bool			turn = false;

  for (auto cases = _vision.begin(); cases != _vision.end(); ++cases)
  {
    if ((*cases).getId() == 0 && checkCases(*cases, ressources))
      return (TAKE_OBJECT);
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
    if (res->first == ressources)
      return (true);
    i++;
  }
  return (false);
}


void				Player::updateCases(const std::vector< std::vector< std::string > >& ressources)
{
  size_t				i = 0;

  _vision.clear();
  for (auto it = ressources.begin(); it != ressources.end(); ++it)
  {
    Case				tmp;
    tmp.setCaseRessources(*it, i);
    _vision.push_back(tmp);
    i++;
  }
}
