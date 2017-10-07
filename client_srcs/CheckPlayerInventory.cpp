//
// CheckPlayerInventory.cpp for player in /home/ndejean/EPITECH/PSU/PSU_2016_zappy/client_ia_srcs
//
// Made by nicolas dejean
// Login   <benjamin.girard@epitech.eu>
//
// Started on  Mon Jun 26 13:12:12 2017 nicolas dejean
// Last update Sun Jul  2 19:33:13 2017 de Ganay Renaud
//

#include "Player.hpp"

bool                            Player::isElevation(s_level targetLevel)
{
  return (_vision[0].getNbPlayer() == targetLevel.nbPlayer &&
	  _inventory.getLinemate() >= targetLevel.linemate &&
	  _inventory.getDeraumere() >= targetLevel.deraumere &&
	  _inventory.getSibur() >= targetLevel.sibur &&
	  _inventory.getMendiane() >= targetLevel.mendiane &&
	  _inventory.getPhiras() >= targetLevel.phiras &&
	  _inventory.getThystame() >= targetLevel.thystame);
}

Item                            Player::searchRessources(s_level targetLevel)
{
  std::map< Item, std::pair< size_t, size_t > >       findItem =
  {
    { RES_THYSTAME, { _inventory.getThystame(), targetLevel.thystame } },
    { RES_PHIRAS, { _inventory.getPhiras(), targetLevel.phiras } },
    { RES_MENDIANE, { _inventory.getMendiane(), targetLevel.mendiane } },
    { RES_SIBUR, { _inventory.getSibur(), targetLevel.sibur } },
    { RES_DERAUMERE, { _inventory.getDeraumere(), targetLevel.deraumere } },
    { RES_LINEMATE, { _inventory.getLinemate(), targetLevel.linemate } },
  };

  for (auto it = findItem.begin(); it != findItem.end(); ++it)
    if (it->second.first < it->second.second)
      return (it->first);
  return (UNDEFINED);
}

Item                            Player::throwRessources(s_level targetLevel)
{
  std::map< Item, std::pair< size_t, size_t > >       findItem =
  {
    { RES_LINEMATE, { _inventory.getLinemate(), targetLevel.linemate } },
    { RES_DERAUMERE, { _inventory.getDeraumere(), targetLevel.deraumere } },
    { RES_SIBUR, { _inventory.getSibur(), targetLevel.sibur } },
    { RES_MENDIANE, { _inventory.getMendiane(), targetLevel.mendiane } },
    { RES_PHIRAS, { _inventory.getPhiras(), targetLevel.phiras } },
    { RES_THYSTAME, { _inventory.getThystame(), targetLevel.thystame } }
  };

  for (auto it = findItem.begin(); it != findItem.end(); ++it)
    if (it->second.first > it->second.second)
      return (it->first);
  return (UNDEFINED);
}

void                            Player::updateInventory(const std::vector< std::pair< std::string, size_t > >&parse)
{
  _inventory.setInventory(parse);
}
