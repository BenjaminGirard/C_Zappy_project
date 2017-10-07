//
// Case.cpp for case in /home/dejean/EPITECH/UNIX/PSU_2016_zappy/client_ia_srcs
//
// Made by dejean
// Login   <benjamin.girard@epitech.eu>
//
// Started on  Sat Jun 24 16:25:27 2017 dejean
// Last update Sun Jul  2 15:24:41 2017 nicolas dejean
//

#include <iostream>
#include <algorithm>
#include "Case.hpp"

Case::Case():
  _itemInCase(),
  _setCaseRessources({
      { RES_FOOD, (&Case::setFood) },
      { FIND_PLAYER, (&Case::setNbPlayer) },
      { RES_LINEMATE, (&Case::setLinemate) },
      { RES_DERAUMERE, (&Case::setDeraumere) },
      { RES_SIBUR, (&Case::setSibur) },
      { RES_MENDIANE, (&Case::setMendiane) },
      { RES_PHIRAS, (&Case::setPhiras) },
      { RES_THYSTAME, (&Case::setThystame) }
    }),
  _food(0),
  _linemate(0),
  _deraumere(0),
  _sibur(0),
  _mendiane(0),
  _phiras(0),
  _thystame(0),
  _nbPlayer(0),
  _id(0)
{}

Case::Case(const Case& cp):
  _itemInCase(cp._itemInCase),
  _food(cp.getFood()),
  _linemate(cp.getLinemate()),
  _deraumere(cp.getDeraumere()),
  _sibur(cp.getSibur()),
  _mendiane(cp.getMendiane()),
  _phiras(cp.getPhiras()),
  _thystame(cp.getThystame()),
  _nbPlayer(cp.getNbPlayer()),
  _id(cp.getId())
{}

void				Case::clearItemInCase()
{
  _itemInCase.clear();
  _food = 0;
  _linemate = 0;
  _deraumere = 0;
  _sibur = 0;
  _mendiane = 0;
  _phiras = 0;
  _thystame = 0;
  _nbPlayer = 0;
}

void				Case::setCaseRessources(const std::vector< std::string >& ressources, size_t i)
{
  clearItemInCase();
  _id = i;
  for (auto res = ressources.begin(); res != ressources.end(); ++res)
    putItemInCase(*res);
  for (auto it = _itemInCase.begin(); it != _itemInCase.end(); ++it)
    std::cout << it->first << " : " << it->second << std::endl;

}

void				Case::putItemInCase(const std::string& item)
{
  std::map< std::string, std::pair< Item, get > >		setRes =
    {
      { FOOD, { RES_FOOD, (&Case::getFood) } },
      { LINEMATE, { RES_LINEMATE, (&Case::getLinemate) } },
      { DERAUMERE, { RES_DERAUMERE, (&Case::getDeraumere) } },
      { SIBUR, { RES_SIBUR, (&Case::getSibur) } },
      { MENDIANE, { RES_MENDIANE, (&Case::getMendiane) } },
      { PHIRAS, { RES_PHIRAS, (&Case::getPhiras) } },
      { THYSTAME, { RES_THYSTAME, (&Case::getThystame) } },
      { PLAYER, { FIND_PLAYER, (&Case::getNbPlayer) } }
    };

  set					s;
  get					g;
  auto map = setRes.find(item);

  if (map != setRes.end())
  {
    g = map->second.second;
    auto res = _setCaseRessources.find(map->second.first);
    if (res != _setCaseRessources.end())
    {
      s = res->second;
      std::cout << "STOCK IN ITEMINCASE " << map->first << std::endl;
      (this->*s)((this->*g)() + 1);
      for (auto it = _itemInCase.begin(); it != _itemInCase.end(); ++it)
      {
	if (it->first == map->second.first)
	{
	  it->second += 1;
	  return ;
	}
      }
      _itemInCase.push_back(std::make_pair(map->second.first, (this->*g)()));
    }
  }
}
