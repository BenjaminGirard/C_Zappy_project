//
// Player.hpp for player in /home/dejean/EPITECH/UNIX/PSU_2016_zappy/client_ia_srcs/includes
//
// Made by dejean
// Login   <benjamin.girard@epitech.eu>
//
// Started on  Fri Jun 23 17:47:49 2017 dejean
// Last update Sun Jul  2 15:22:57 2017 nicolas dejean
//

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <vector>
#include <queue>
#include "Select.hpp"
#include "Case.hpp"
#include "Inventory.hpp"
#include "socket.hpp"
#include "CmdHandler.hpp"

enum                            Action
{
  FORWARD,
  RIGHT,
  LEFT,
  LOOK,
  INVENTORY,
  BROADCAST_TEXT,
  CONNECT_NBR,
  FORK,
  EJECT,
  TAKE_OBJECT,
  SET_OBJECT,
  INCANTATION,
  MESSAGE
};

typedef struct			t_level
{
  size_t			nbPlayer;
  size_t			linemate;
  size_t			deraumere;
  size_t			sibur;
  size_t			mendiane;
  size_t			phiras;
  size_t			thystame;
}				s_level;

class				Player
{
  typedef void (Player::*fnct)(std::string const&);
private:
  std::vector< Case >				_vision;
  Inventory					_inventory;
  std::map< size_t, s_level >		_infoLevel;
  Socket					_socket;
  std::queue< std::string >			_order;
  std::string					_name;
  std::string					_lvl;
  std::pair<size_t, size_t>			_map;
  int						_dir;

public:
  Player(std::string const& ip, int port, std::string const& name);
  ~Player();
  Player(const Player& cp);
  Player			&operator=(const Player& cp);

  void				run();

  /* COMMANDES */
  void				forward(std::string const&);
  void				right(std::string const&);
  void				left(std::string const&);
  void				look(std::string const&);
  void				inventory(std::string const&);
  void				broadcast(std::string const&);
  void				connectNbr(std::string const&);
  void				fork(std::string const&);
  void				eject(std::string const&);
  void				take(std::string const&);
  void				set(std::string const&);
  void				incantation(std::string const&);
  /* COMMANDES */

  // AI ACTION
  int				needToRead(std::string &msg);
  bool				moveToVoice(int dir);
  void				takeAll();

  /* ELEVATION */
  void				startIncantation();
    void			setRessources();
    void			setXRessources(const std::string &ress, size_t nb);
    void			tellUp();

  /* CHECK PLAYER INVENTORY */
  Item				checkInventory(void);
  bool				isElevation(s_level targetLevel);
  Item				searchRessources(s_level targetLevel);
  Item				throwRessources(s_level targetLevel);

  /* CHECK PLAYER VISION */
  Action			lookForItem(const Item& ressources); // check case vision
  bool				checkCases(const Case& cases, const Item& ressources);
  void				updateInventory(const std::vector< std::pair< std::string, size_t > >&parse);
  void				updateCases(const std::vector< std::vector< std::string > >& ressources);


  /* SEND COMMANDS */
  void				doAction(const Action& action, const Item& ressources = UNDEFINED, const std::string& text = "");

  /* CORE */
  void				playTurn(const Action& action);
  void				aiLoop(Select &select, CmdHandler &cmd);
  bool				connectionLoop(Select &select, CmdHandler &cmd);
  void				playerCore(const std::string& order);

  int				getBroadcast(std::string& mess);

  /* GETTER */
  const Inventory		&getInventory(void) { return _inventory; }
};

#endif /* !PLAYER_HPP_ */
