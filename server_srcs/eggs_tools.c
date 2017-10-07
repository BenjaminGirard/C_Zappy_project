/*
** eggs_tools.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Sat Jul  1 17:31:57 2017 girard
** Last update Sun Jul  2 13:35:45 2017 girard
*/

#include <string.h>
#include "server.h"

int				delete_idx_egg(t_egg * const egg,
					       const int nb_eggs,
					       const int idx)
{
  int				i;

  i = 0;
  while (i < nb_eggs && i < idx)
    ++i;
  ++i;
  while (i < nb_eggs)
    {
      egg[i - 1].x = egg[i].x;
      egg[i - 1].y = egg[i].y;
      egg[i - 1].cooldown = egg[i].cooldown;
      ++i;
    }
  return (EXIT_SUCCESS);
}

static int			assign_first_egg(t_client_data *
						 const egg_cli,
						 t_client_data * const client)
{
  int				i;

  i = 1;
  client->pos_x = egg_cli->eggs[0].x;
  client->pos_y = egg_cli->eggs[0].y;
  client->is_egg = true;
  while (i < egg_cli->nb_eggs)
    {
      egg_cli->eggs[i - 1].x = egg_cli->eggs[i].x;
      egg_cli->eggs[i - 1].y = egg_cli->eggs[i].y;
      egg_cli->eggs[i - 1].cooldown = egg_cli->eggs[i].cooldown;
      ++i;
    }
  --egg_cli->nb_eggs;
  if (egg_cli->nb_eggs == 0)
    {
      if (egg_cli->eggs)
	free(egg_cli->eggs);
      egg_cli->eggs = NULL;
    }
  return (feed_tmp_str(&egg_cli->buff_writer, OK));
}

static int			assign_team(t_server_data * const data,
					    t_client_data * const client,
					    const int t_idx)
{
  if ((int)data->args_data.teams[t_idx].nb_members >=
      data->args_data.nb_clients)
    {
      client->team = NULL;
      return (EXIT_SUCCESS);
    }
  ++data->args_data.teams[t_idx].nb_members;
  return (EXIT_SUCCESS);
}

int				hatch_egg(t_server_data * const data,
					  t_client_data * const client,
					   const int t_idx)
{
  t_client_data			*tmp;
  t_client_data			*close_egg;

  tmp = data->c_data;
  close_egg = NULL;
  while (tmp)
    {
      if (tmp->team &&
	  strcmp(data->args_data.teams[t_idx].name, tmp->team) == 0 &&
	  tmp->eggs && (!close_egg || !close_egg->eggs ||
			close_egg->eggs[0].cooldown
			< close_egg->eggs[0].cooldown))
	close_egg = tmp;
      tmp = tmp->tail;
    }
  if (close_egg)
    return (assign_first_egg(close_egg, client));
  return (assign_team(data, client, t_idx));

}
