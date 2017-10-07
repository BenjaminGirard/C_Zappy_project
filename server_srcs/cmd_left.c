/*
** cmd_forward.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server_srcs
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Sat Jun 24 14:09:49 2017 girard
** Last update Sun Jul  2 17:35:49 2017 sebastien vidal
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

int				cmd_left(t_server_data * const data,
					 const int fd,
					 const char * const cmd)
{
  t_client_data			*tmp;

  (void)cmd;
  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  if (tmp->dir == RIGHT)
    tmp->dir = UP;
  else
    tmp->dir += 1;
  return (feed_tmp_str(&tmp->buff_writer, OK));
}

int				cmd_check_left(t_server_data *
					       const data,
					       const int fd,
					       const char * const cmd)
{
  t_client_data			*tmp;

  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  if (strlen(cmd) > strlen("Left"))
    return (CRITERR);
  return (EXIT_SUCCESS);
}
