/*
** handle_clients_cmd.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server_srcs
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Fri Jun 30 12:14:22 2017 girard
** Last update Sat Jul  1 20:22:05 2017 bibzor
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

static int			treat_cmd(t_server_data * const data,
					  const int fd,
					  const char * const cmd)
{
  int				i;
  t_client_data			*tmp;

  i = -1;
  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  printf("received cmd : %s\n", cmd);
  if (tmp->team == NULL)
    return (try_team_assignation(data, fd, cmd));
  while (++i < DEFAULT_ACTION)
    if (cmd_compare(cmd, tmp->action[i].cmd_proto) == true)
      {
        if (tmp->action[i].check_cmd(data, fd, cmd) == CRITERR)
          return (feed_tmp_str(&tmp->buff_writer, KO));
        tmp->action[i].cooldown = tmp->action[i].cooldown_val;
        if ((tmp->action[i].cmd = strdup(cmd)) == NULL)
          return (CRITERR);
        return (EXIT_SUCCESS);
      }
  return (feed_tmp_str(&tmp->buff_writer, KO));
}

static bool		is_timer_over(t_client_data * const c_data)
{
  int			i;

  i = -1;
  while (++i < DEFAULT_ACTION)
    if (c_data->action[i].cooldown != 0.0)
      return (false);
  return (true);
}

int			handle_clients_cmd(t_server_data * const data)
{
  t_client_data		*tmp;
  char			*line;

  tmp = data->c_data;
  while (tmp)
    {
      line = NULL;
      if (is_timer_over(tmp))
	{
	  if ((line = read_cmd(&tmp->buff_reader)) == NULL)
	    return (close_connexion(data, tmp->fd));
	  if (line[0] != 0 && treat_cmd(data, tmp->fd, line) == CRITERR)
	    return (CRITERR);
	}
      tmp = tmp->tail;
      if (line)
	free(line);
    }
  return (EXIT_SUCCESS);
}
