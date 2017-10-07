/*
** cmd_eject_tools.c for zappy in /home/sebastien.vidal/rendu/NETWORK/PSU_2016_zappy/server_srcs
**
** Made by sebastien vidal
** Login   <sebastien.vidal@epitech.net>
**
** Started on  Wed Jun 28 14:26:03 2017 sebastien vidal
** Last update Fri Jun 30 15:24:34 2017 girard
*/

#include <stdio.h>
#include "server.h"

static int	print_eject_message(t_ring_buff * const buff,
				    const int val)
{
  char		*itos;

  if ((itos = int_to_str(val)) == NULL)
    return (CRITERR);
  if (feed_tmp_str(buff, "eject: ") == CRITERR ||
      feed_tmp_str(buff, itos) == CRITERR ||
      feed_tmp_str(buff, "\n") == CRITERR)
    return (CRITERR);
  return (EXIT_SUCCESS);
}

int		sent_eject_and_set_pos(t_client_data * const tmp,
				       const unsigned int x,
				       const unsigned int y,
				       const t_direction dir)
{
  tmp->pos_x = x;
  tmp->pos_y = y;
  if (dir == UP)
    return (print_eject_message(&tmp->buff_writer, 5));
  else if (dir == DOWN)
    return (print_eject_message(&tmp->buff_writer, 1));
  else if (dir == LEFT)
    return (print_eject_message(&tmp->buff_writer, 7));
  else
    return (print_eject_message(&tmp->buff_writer, 3));
}
