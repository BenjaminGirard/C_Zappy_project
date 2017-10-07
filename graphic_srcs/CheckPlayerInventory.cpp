//
// CheckPlayerInventory.cpp for player in /home/ndejean/EPITECH/PSU/PSU_2016_zappy/client_ia_srcs
//
// Made by nicolas dejean
// Login   <benjamin.girard@epitech.eu>
//
// Started on  Mon Jun 26 13:12:12 2017 nicolas dejean
// Last update Sun Jul  2 15:25:23 2017 nicolas dejean
//

#include "Player.hpp"

bool                            Player::isElevation(s_level targetLevel)
{
  std::cout << "--------------IS INCANTATION---------------" << std::endl;
  std::cout << "PLAYER " << _vision[0].getNbPlayer() << " TARGET " << targetLevel.nbPlayer << std::endl;
  std::cout << "LINEMATE " << _inventory.getLinemate() << " TARGET " << targetLevel.linemate << std::endl;
  std::cout << "DERAUMERE " << _inventory.getDeraumere() << " TARGET " << targetLevel.deraumere << std::endl;
  std::cout << "SIBUR " << _inventory.getSibur() << " TARGET " << targetLevel.sibur << std::endl;
  std::cout << "MENDIANE " << _inventory.getMendiane()<< " TARGET " << targetLevel.mendiane << std::endl;
  std::cout << "PHIRAS " << _inventory.getPhiras()<< " TARGET " << targetLevel.phiras << std::endl;
  std::cout << "THYSTAME " << _inventory.getThystame()<< " TARGET " << targetLevel.thystame << std::endl;
  std::cout << "--------------END INCANTATION---------------" << std::endl;


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

  std::cout << "entered search ressources" << std::endl;
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
