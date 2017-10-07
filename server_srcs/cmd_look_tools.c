/*
** cmd_look_tools.c for zappy in /home/bibzor/rendu/NETWORK/PSU_2016_zappy/server_srcs
**
** Made by bibzor
** Login   <sebastien.vidal@epitech.eu>
**
** Started on  Mon Jun 26 19:32:38 2017 bibzor
** Last update Fri Jun 30 16:07:14 2017 girard
*/

#include <stdio.h>
#include "server.h"

static int		get_tiles_player(t_client_data * current,
					 const t_client_data * const tmp,
					 const int x, const int y)
{
  if ((current = find_player_pos(current, (unsigned int)x,
				 (unsigned int)y)) == NULL)
    return (EXIT_SUCCESS);
  else
    {
      if (feed_tmp_str((t_ring_buff * const)&tmp->buff_writer,
		       " player") == CRITERR)
	return (CRITERR);
      get_tiles_player(current->tail, tmp, x, y);
    }
  return (EXIT_SUCCESS);
}

static int		obj_print(const char * const str,
				  const t_client_data *const tmp,
				  const unsigned int nb)
{
  unsigned int		i;

  i = -1;
  while (++i < nb)
    {
      if (feed_tmp_str((t_ring_buff * const)&tmp->buff_writer,
		       " ") == CRITERR ||
	  feed_tmp_str((t_ring_buff * const)&tmp->buff_writer,
		       str) == CRITERR)
	return (CRITERR);
    }
  return (EXIT_SUCCESS);
}

static int		get_tiles_stones_and_food(const t_ressources *
						  const tile,
						  const t_client_data *
						  const tmp)
{
  if (obj_print("food", tmp, tile->food) == CRITERR ||
      obj_print("linemate", tmp, tile->linemate) == CRITERR ||
      obj_print("deraumere", tmp, tile->deraumere) == CRITERR ||
      obj_print("sibur", tmp, tile->sibur) == CRITERR ||
      obj_print("mendiane", tmp, tile->mendiane) == CRITERR ||
      obj_print("phiras", tmp, tile->phiras) == CRITERR ||
      obj_print("thystame", tmp, tile->thystame) == CRITERR)
    return (CRITERR);
  return (EXIT_FAILURE);
}

int			print_result_look(const t_server_data * const data,
					  const t_client_data * const tmp,
					  const int x, const int y)
{
  if (get_tiles_player(data->c_data, tmp, x, y) == CRITERR ||
      get_tiles_stones_and_food(&data->map[data->args_data.width * y + x],
		       tmp) == CRITERR)
    return (CRITERR);
  return (EXIT_SUCCESS);
}
