//
// Inventory.cpp for inv in /home/dejean/EPITECH/UNIX/PSU_2016_zappy/client_ia_srcs
//
// Made by dejean
// Login   <benjamin.girard@epitech.eu>
//
// Started on  Sat Jun 24 16:01:09 2017 dejean
// Last update Sat Jul  1 16:59:20 2017 nicolas dejean
//

#include <iostream>
#include "Inventory.hpp"

Inventory::Inventory():
  _ressourcesInventory({
      { FOOD, { (&Inventory::setFood), RES_FOOD } },
      { LINEMATE, { (&Inventory::setLinemate), RES_LINEMATE } },
      { DERAUMERE, { (&Inventory::setDeraumere), RES_DERAUMERE } },
      { SIBUR, { (&Inventory::setSibur), RES_SIBUR } },
      { MENDIANE, { (&Inventory::setMendiane), RES_MENDIANE } },
      { PHIRAS, { (&Inventory::setPhiras), RES_PHIRAS } },
      { THYSTAME, { (&Inventory::setThystame), RES_THYSTAME } }
    }),
  _food(10),
  _linemate(0),
  _deraumere(0),
  _sibur(0),
  _mendiane(0),
  _phiras(0),
  _thystame(0),
  _level(1)
{}

void				Inventory::setInventory(const std::vector< std::pair< std::string, size_t > >& parse)
{
  std::cout << "--------- INVENTORY UPDATE--------------" << std::endl;

  for (auto it = parse.begin(); it != parse.end(); ++it)
  {
    std::cout << it->first << " :" << it->second << std::endl;
    auto res = _ressourcesInventory.find(it->first);
    if (res != _ressourcesInventory.end())
    {
      set			s = res->second.first;
      (this->*s)(it->second);
    }
  }
  std::cout << "Linemate " << _linemate << std::endl;
  std::cout << "Food " << _food << std::endl;
  std::cout << "Deraumere " << _deraumere << std::endl;
  std::cout << "sibur " << _sibur << std::endl;
  std::cout << "phiras " << _phiras << std::endl;
  std::cout << "mendiane " << _mendiane << std::endl;
  std::cout << "thystaem " << _thystame << std::endl;
  std::cout << "------------- END -------------------" << std::endl;
}
