/*
** cmd_forward.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server_srcs
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Sat Jun 24 14:09:49 2017 girard
** Last update Sun Jul  2 17:34:06 2017 sebastien vidal
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

static t_team			*find_team(const t_server_data * const data,
					   const t_client_data * const tmp)
{
  unsigned int			i;
  t_team			*ret;

  i = 0;
  ret = data->args_data.teams;
  while (i < data->args_data.nb_teams)
    {
      if (ret[i].name != NULL && strcmp(ret[i].name, tmp->team) == 0)
	return (&ret[i]);
      ++i;
    }
  return (NULL);
}

int				cmd_connect_nbr(t_server_data * const data,
						const int fd,
						const char * const cmd)
{
  (void)data;
  (void)fd;
  (void)cmd;
  return (EXIT_SUCCESS);
}

int				cmd_check_connect_nbr(t_server_data *
						      const data,
						      const int fd,
						      const char *
						      const cmd)
{
  t_client_data			*tmp;
  const t_team			*actual;
  char				*itos;

  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  if (strlen(cmd) > strlen("Connect_nbr"))
    return (CRITERR);
  if ((actual = find_team(data, tmp)) == NULL)
    return (CRITERR);
  if ((itos = int_to_str(data->args_data.nb_clients - actual->nb_members))
      == NULL)
    return (CRITERR);
  if (feed_tmp_str(&tmp->buff_writer, itos) == CRITERR ||
      feed_tmp_str(&tmp->buff_writer, "\n") == CRITERR)
    return (CRITERR);
  if (itos)
    free(itos);
  return (EXIT_SUCCESS);
}
