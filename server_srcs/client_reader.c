/*
** client_reader.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Thu Jun 22 12:38:23 2017 girard
** Last update Sun Jul  2 16:21:50 2017 girard
*/

#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

int				cmd_compare(const char * const line,
					    const char * const cmd)
{
  int				idx;

  idx = -1;
  if (!line)
    return (false);
  while (line[++idx] && line[idx] != ' ')
    if (cmd[idx] != line[idx])
      break ;
  if (!cmd[idx] && (!line[idx] || line[idx] == ' '))
    return (true);
  return (false);
}

int				close_connexion(t_server_data * const data,
						const int fd)
{
  t_client_data			*tmp;

  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  if (!tmp->is_egg && update_team_nb(data, fd) == CRITERR)
    return (CRITERR);
  printf("Connexion closed\n");
  if (close_fd(fd, EXIT_SUCCESS) == CRITERR)
    return (CRITERR);
  data->c_data = remove_client(data->c_data, fd);
  return (EXIT_SUCCESS);
}

int				read_data_from_client(t_server_data *
						      const data,
						      const int fd)
{
  t_client_data			*tmp;

  if ((tmp = find_client_fd(data->c_data, fd)) == NULL ||
      read_data(&tmp->buff_reader, fd) == CRITERR)
    return (close_connexion(data, fd));
  return (EXIT_SUCCESS);
}
