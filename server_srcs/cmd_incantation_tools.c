/*
** cmd_incantation_tools.c for zappy in /home/sebastien.vidal/rendu/NETWORK/PSU_2016_zappy/server_srcs
**
** Made by sebastien vidal
** Login   <sebastien.vidal@epitech.net>
**
** Started on  Thu Jun 29 12:36:54 2017 sebastien vidal
** Last update Fri Jun 30 15:49:59 2017 girard
*/

#include <string.h>
#include "server.h"

int			print_current_level(t_ring_buff * const buff,
					    const int level)
{
  char			*itos;

  if ((itos = int_to_str(level)) == NULL)
    return (CRITERR);
  if (feed_tmp_str(buff, "Current level: ") == CRITERR ||
      feed_tmp_str(buff, itos) == CRITERR ||
      feed_tmp_str(buff, "\n") == CRITERR)
    return (CRITERR);
  if (itos)
    free(itos);
  return (EXIT_SUCCESS);
}

int			print_win(t_ring_buff * const buff,
				  const char * const str)
{
  if (feed_tmp_str(buff, "Team ") == CRITERR ||
      feed_tmp_str(buff, str) == CRITERR ||
      feed_tmp_str(buff, " WIN ! Congratulations !\n")
      == CRITERR)
    return (CRITERR);
  return (EXIT_SUCCESS);
}

int			check_end_game(const t_server_data *
				       const data,
				       const char * const team)
{
  t_client_data		*tmp;
  unsigned int		ret;

  ret = 0;
  tmp = data->c_data;
  while (tmp)
    {
      if (tmp->team != NULL && strcmp(team, tmp->team) == 0 &&
	  tmp->lvl == 8)
	++ret;
      tmp = tmp->tail;
    }
  if (ret >= 8)
    return (EXIT_SUCCESS);
  return (EXIT_FAILURE);
}
