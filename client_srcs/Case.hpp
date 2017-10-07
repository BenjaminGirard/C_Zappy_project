//
// Case.hpp for case in /home/dejean/EPITECH/UNIX/PSU_2016_zappy/client_ia_srcs/includes
//
// Made by dejean
// Login   <benjamin.girard@epitech.eu>
//
// Started on  Fri Jun 23 17:33:51 2017 dejean
// Last update Sun Jul  2 15:24:53 2017 nicolas dejean
//

#ifndef CASE_HPP_
#define CASE_HPP_

#include <vector>
#include "Inventory.hpp"

class				Case
{
  typedef void (Case::*set)(size_t);
  typedef size_t (Case::*get)(void) const;

public:
  Case();
  ~Case() = default;
  Case(const Case& cp);
  Case					&operator=(const Case& cp) = delete;

  std::vector< std::pair< Item, size_t > >			_itemInCase; // update instead of size_t
  std::map< Item, set >			_setCaseRessources; // update instead of size_t

  /* UPDATE CASES */
  void					clearItemInCase();
  void					setCaseRessources(const std::vector< std::string >& ressources,
							  size_t i);
  void					putItemInCase(const std::string& item);

  /* GETTER && SETTER */
  size_t				getFood(void) const  { return _food;}
  size_t				getLinemate(void) const { return _linemate;}
  size_t				getDeraumere(void) const { return _deraumere;}
  size_t				getSibur(void) const { return _sibur;}
  size_t				getMendiane(void) const { return _mendiane;}
  size_t				getPhiras(void) const { return _phiras;}
  size_t				getThystame(void) const { return _thystame;}
  size_t				getNbPlayer(void) const { return _nbPlayer;}
  size_t				getId(void) const { return _id;}

  void					setFood(size_t food) { _food = food; }
  void					setLinemate(size_t linemate) { _linemate = linemate; }
  void					setDeraumere(size_t deraumere) { _deraumere = deraumere; }
  void					setSibur(size_t sibur) { _sibur = sibur; }
  void					setMendiane(size_t mendiane) { _mendiane = mendiane; }
  void					setPhiras(size_t phiras) { _phiras = phiras; }
  void					setThystame(size_t thystame) { _thystame = thystame; }
  void					setNbPlayer(size_t nbPlayer) { _nbPlayer = nbPlayer; }
  void					setId(size_t id) { _id = id; }

private:
  /* SUPPRESS size_t ? */
  size_t				_food;
  size_t				_linemate;
  size_t				_deraumere;
  size_t				_sibur;
  size_t				_mendiane;
  size_t				_phiras;
  size_t				_thystame;
  size_t				_nbPlayer;
  size_t				_id;
  /* No values just enum */
};

#endif /* !CASE_HPP_ */
