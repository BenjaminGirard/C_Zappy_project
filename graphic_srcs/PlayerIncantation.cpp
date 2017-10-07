//
// PlayerIncatation.cpp for PlayerIncantation in /home/degana_r/PSU_2016_zappy/client_srcs
//
// Made by de Ganay Renaud
// Login   <degana_r@epitech.net>
//
// Started on  Sat Jul  1 14:57:09 2017 de Ganay Renaud
// Last update Sat Jul  1 18:20:32 2017 nicolas dejean
//

#include "Player.hpp"
#include "Stoi.hpp"

void				Player::setXRessources(const std::string &ress, size_t nb)
{
    for (size_t off = 0; off < nb; off++)
	set(ress);
}

void				Player::setRessources()
{
    t_level			tmp;

    tmp = _infoLevel[Stoi::getNbr(_lvl)];
    setXRessources(LINEMATE, tmp.linemate);
    setXRessources(DERAUMERE, tmp.deraumere);
    setXRessources(SIBUR, tmp.sibur);
    setXRessources(MENDIANE, tmp.mendiane);
    setXRessources(PHIRAS, tmp.phiras);
    setXRessources(THYSTAME, tmp.thystame);
}

void            Player::takeAll()
{
  size_t        id = _vision.size() - 1;
  size_t        food = _vision[0].getFood();
  size_t        linemate = _vision[0].getLinemate();
  size_t        deraumere = _vision[0].getDeraumere();
  size_t        sibur = _vision[0].getSibur();
  size_t        mendiane = _vision[0].getMendiane();
  size_t        phiras = _vision[0].getPhiras();
  size_t        thystame = _vision[0].getThystame();

  std::cout << "----------Take all---------------" << std::endl;
  std::cout << id << std::endl;
  std::cout << "FOOD:" << food << std::endl;
  std::cout << "LINEMATE:" << linemate << std::endl;
  std::cout << "DERAUMERE:" << deraumere << std::endl;
  std::cout << "SIBUR:" << sibur << std::endl;
  std::cout << "MENDIANE:" << mendiane << std::endl;
  std::cout << "PHIRAS:" << phiras << std::endl;
  std::cout << "THYSTAME:" << thystame << std::endl;

  if (food > 0)
    return take("food");
  if (linemate > 0)
    return take("linemate");
  if (deraumere > 0)
    return take("deraumere");
  if (sibur > 0)
    return take("sibur");
  if (mendiane > 0)
    return take("mendiane");
  if (phiras > 0)
    return take("phiras");
  if (thystame > 0)
    return take("thystame");
  setRessources();
  return doAction(INCANTATION);
}

void		Player::tellUp()
{
    broadcast(_name + " " + _lvl + " UP");
    if (_vision.front().getNbPlayer() == _infoLevel[Stoi::getNbr(_lvl)].nbPlayer
	&& isElevation(_infoLevel[_inventory.getLevel()]))
	takeAll();
}
