/*
** update_team_nb.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server_srcs
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Wed Jun 28 19:08:53 2017 girard
** Last update Sun Jul  2 11:46:07 2017 girard
*/

#include <string.h>
#include "server.h"

int			nb_players_in_team(t_server_data * const data,
					   const int fd)
{
  t_client_data		*tmp;
  t_client_data		*iter;
  int			res;
  int			t_idx;

  t_idx = -1;
  iter = data->c_data;
  res = 0;
  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (FAILURE);
  while (iter)
    {
      if (iter->team && tmp->team && strcmp(iter->team, tmp->team))
	res += 1;
      iter = iter->tail;
    }
  while (++t_idx < (int)data->args_data.nb_teams)
    if (tmp->team &&
	strcmp(data->args_data.teams[t_idx].name, tmp->team) == 0)
      break ;
  return (res - data->args_data.teams[t_idx].nb_members);
}

int			update_team_nb(t_server_data * const data,
			       const int fd)
{
  unsigned int		idx;
  t_client_data		*tmp;

  idx = 0;
  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  if (tmp->team == NULL)
    return (EXIT_SUCCESS);
  while (idx < data->args_data.nb_teams &&
	 data->args_data.teams[idx].name != tmp->team)
    idx++;
  if (idx < data->args_data.nb_teams)
    --data->args_data.teams[idx].nb_members;
  return (EXIT_SUCCESS);
}
