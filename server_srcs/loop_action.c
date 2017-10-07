/*
** loop_action.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server_srcs
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Tue Jun 27 11:07:25 2017 girard
** Last update Sun Jul  2 20:58:30 2017 bibzor
*/

#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"

static int		update_eggs_client(t_server_data * const data,
					   t_client_data * const client)
{
  int			i;

  i = -1;
  if (!client->eggs || client->nb_eggs == 0)
    return (EXIT_SUCCESS);
  while (++i < client->nb_eggs)
    {
      client->eggs[i].cooldown = client->eggs[i].cooldown -
	get_diff_time(data->unow);
      if (client->eggs[i].cooldown < 0)
	{
	  if (feed_tmp_str(&client->buff_writer, KO) == CRITERR)
	    return (CRITERR);
	  delete_idx_egg(client->eggs, client->nb_eggs, i);
	  --i;
	  --client->nb_eggs;
	  if (client->nb_eggs == 0)
	    {
	      if (client->eggs)
		free(client->eggs);
	      client->eggs = NULL;
	    }
	}
    }
  return (EXIT_SUCCESS);
}

static int		update_time_action(t_server_data * const data,
					   t_client_data * const c_data,
					   const int idx)
{
  c_data->action[idx].cooldown = c_data->action[idx].cooldown -
    get_diff_time(data->unow);
  if (c_data->action[idx].cooldown <= 0.0)
    {
      c_data->action[idx].cooldown = 0.0;
      if (c_data->action[idx].action_cmd(data, c_data->fd,
					 c_data->action[idx].cmd) == CRITERR)
	return (CRITERR);
      if (c_data->action[idx].cmd)
	free(c_data->action[idx].cmd);
      c_data->action[idx].cmd = NULL;
    }
  return (EXIT_SUCCESS);
}

static int		kill_player(t_server_data * const data,
				     t_client_data * dp)
{
  t_client_data		*graphic;
  t_client_data		*save_dp;

  if (write(dp->fd, DEAD, strlen(DEAD)) == CRITERR)
    return (CRITERR);
  save_dp = dp;
  dp = dp->tail;
  if ((graphic = get_graphic_client(data)) != NULL)
    if (send_death_to_graphic(graphic, save_dp->fd) == CRITERR)
      return (CRITERR);
  if (close_connexion(data, save_dp->fd) == CRITERR)
    return (CRITERR);
  return (EXIT_SUCCESS);
}

static int		update_action_clients(t_server_data * const data)
{
  t_client_data		*tmp;
  int			idx;

  tmp = data->c_data;
  while (tmp)
    {
      if (tmp->team && strcmp(tmp->team, GRAPHIC) != 0)
	{
	  if (update_eggs_client(data, tmp) == CRITERR)
	    return (CRITERR);
	  tmp->inventory.life = tmp->inventory.life -
	    (get_diff_time(data->unow) * (data->args_data.freq));
	  if (tmp->inventory.life <= 0 && (kill_player(data, tmp)) == CRITERR)
	    return (CRITERR);
	  tmp->inventory.food = tmp->inventory.life / LIFE_UNIT;
	  idx = -1;
	  while (++idx < DEFAULT_ACTION)
	    if (tmp->action[idx].cooldown > 0.0 &&
		update_time_action(data, tmp, idx) == CRITERR)
	      return (CRITERR);
	}
      tmp = tmp->tail;
    }
  return (EXIT_SUCCESS);
}

int			update_data(t_server_data * const data)
{
  t_client_data		*graph;

  if ((graph = get_graphic_client(data)) != NULL)
    {
      data->graphic_cooldown = data->graphic_cooldown -
	get_diff_time(data->unow);
      if (data->graphic_cooldown <= 0)
	{
	  send_graphical_msg(data, "##\n");
	  send_graphical_msg(data, "#\n");
	  data->graphic_cooldown = USEC_RATIO / data->args_data.freq;
	}
    }
  if (update_action_clients(data) == CRITERR)
    return (CRITERR);
  gettimeofday(&data->unow, NULL);
  return (EXIT_SUCCESS);
}
