//
// Inventory.hpp for inve in /home/dejean/EPITECH/UNIX/PSU_2016_zappy/client_ia_srcs/includes
//
// Made by dejean
// Login   <benjamin.girard@epitech.eu>
//
// Started on  Fri Jun 23 18:03:21 2017 dejean
// Last update Sun Jul  2 15:24:25 2017 nicolas dejean
//

#ifndef INVENTORY_HPP_
#define INVENTORY_HPP_

#include <string>
#include <map>
#include <vector>

static const size_t		MIN_FOOD = 5;
static const size_t		FORK_FOOD = 8;
static const std::string	FOOD = "food";
static const std::string	LINEMATE = "linemate";
static const std::string	DERAUMERE = "deraumere";
static const std::string	SIBUR = "sibur";
static const std::string	MENDIANE = "mendiane";
static const std::string	PHIRAS = "phiras";
static const std::string	THYSTAME = "thystame";
static const std::string	PLAYER = "player";

enum				Item
{
  RES_FOOD,
  ELEVATION,
  FIND_PLAYER,
  RES_LINEMATE,
  RES_DERAUMERE,
  RES_SIBUR,
  RES_MENDIANE,
  RES_PHIRAS,
  RES_THYSTAME,
  UNDEFINED
};

class				Inventory
{
  typedef void (Inventory::*set)(size_t);
public:
  Inventory();
  ~Inventory() = default;
  Inventory(const Inventory& cp) = delete;
  Inventory					&operator=(const Inventory& cp) = delete;

  std::map< std::string, std::pair< set, Item> >	_ressourcesInventory;
  /* GETTER && SETTER */
  size_t				getFood(void) { return _food;}
  size_t				getLinemate(void) { return _linemate;}
  size_t				getDeraumere(void) { return _deraumere;}
  size_t				getSibur(void) { return _sibur;}
  size_t				getMendiane(void) { return _mendiane;}
  size_t				getPhiras(void) { return _phiras;}
  size_t				getThystame(void) { return _thystame;}
  size_t				getLevel(void) { return _level;}
  size_t				getGroupSlotLeft(void) { return _groupSlotLeft;}

  void				setFood(size_t food) { _food = food;}
  void				setLinemate(size_t linemate) { _linemate = linemate;}
  void				setDeraumere(size_t deraumere) {  _deraumere = deraumere;}
  void				setSibur(size_t sibur) {  _sibur = sibur;}
  void				setMendiane(size_t mendiane) {  _mendiane = mendiane;}
  void				setPhiras(size_t phiras) {  _phiras = phiras;}
  void				setThystame(size_t thystame) {  _thystame = thystame;}
  void				setLevel(size_t level) {  _level = level;}
  void				setGroupSlotLeft(size_t groupSlotLeft) {  _groupSlotLeft = groupSlotLeft;}

  void					setInventory(const std::vector< std::pair< std::string, size_t > >&parse);
  void					addLevel(void) { _level += 1; }

// case vector<vector<string>>
private:
  size_t				_food;
  size_t				_linemate;
  size_t				_deraumere;
  size_t				_sibur;
  size_t				_mendiane;
  size_t				_phiras;
  size_t				_thystame;
  size_t				_level;
  size_t				_groupSlotLeft;
};

#endif /* !INVENTORY_HPP_ */
