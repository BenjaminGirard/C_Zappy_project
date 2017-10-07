/*
** try_team_assignation.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Wed Jun 28 17:49:25 2017 girard
** Last update Sun Jul  2 19:55:05 2017 girard
*/

#include <string.h>
#include "server.h"

static int		print_team_assignation(t_server_data * const data,
					       t_client_data * const client,
					       const int t_idx)
{
  char			*tmp;

  if ((tmp = int_to_str(data->args_data.nb_clients -
			data->args_data.teams[t_idx].nb_members)) == NULL ||
      feed_tmp_str(&client->buff_writer, tmp) == CRITERR ||
      feed_tmp_str(&client->buff_writer, "\n") == CRITERR)
    return (CRITERR);
  if (tmp)
    free(tmp);
  if ((tmp = int_to_str(data->args_data.width)) == NULL ||
      feed_tmp_str(&client->buff_writer, tmp) == CRITERR ||
      feed_tmp_str(&client->buff_writer, " ") == CRITERR)
    return (CRITERR);
  if (tmp)
    free(tmp);
  if ((tmp = int_to_str(data->args_data.height)) == NULL ||
      feed_tmp_str(&client->buff_writer, tmp) == CRITERR ||
      feed_tmp_str(&client->buff_writer, "\n") == CRITERR)
    return (CRITERR);
  return (EXIT_SUCCESS);
}

static int		send_to_graphic_new_player(t_server_data * const
						   data,
						   const t_client_data *
						   const tmp)
{
  t_client_data		*graphic;
  t_info_graphic	info;

  if (memset(&info, 0, sizeof(t_info_graphic)) == NULL)
    return (CRITERR);
  if ((graphic = get_graphic_client(data)) == NULL)
    return (EXIT_FAILURE);
  if ((info.x = int_to_str(tmp->pos_x)) == NULL ||
      (info.y = int_to_str(tmp->pos_y)) == NULL ||
      (info.name = int_to_str(tmp->fd)) == NULL ||
      (info.type = strdup("0")) == NULL ||
      add_something(graphic, &info) == CRITERR)
    return (CRITERR);
  free_data_graphic(&info);
  return (EXIT_SUCCESS);
}

static int		team_assignation(t_server_data * const data,
					 t_client_data * const client,
					 const int t_idx)
{
  client->team = data->args_data.teams[t_idx].name;
  if (hatch_egg(data, client, t_idx) == CRITERR)
    return (CRITERR);
  if (client->team &&
      (print_team_assignation(data, client, t_idx) == CRITERR
       || send_to_graphic_new_player(data, client) == CRITERR))
    return (CRITERR);
  return (EXIT_SUCCESS);
}

static int		assign_graphic_pos(t_client_data * const client)
{
  client->pos_x = -1;
  client->pos_y = -1;
  return (EXIT_SUCCESS);
}

int			try_team_assignation(t_server_data * const data,
					     const int fd,
					     const char * const cmd)
{
  t_client_data		*tmp;
  char			*pure_cmd;
  unsigned int		idx;

  idx = -1;
  if (cmd[0] == 0)
    return (EXIT_SUCCESS);
  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  while (++idx < data->args_data.nb_teams)
    {
      if ((pure_cmd = epur_str(cmd)) == NULL ||
	  (strcmp(pure_cmd, data->args_data.teams[idx].name) == 0 &&
	   team_assignation(data, tmp, idx) == CRITERR))
	return (CRITERR);
      free(pure_cmd);
    }
  if (strcmp(GRAPHIC, cmd) == 0 && (first_co_graphic(data, tmp) == CRITERR ||
				    assign_graphic_pos(tmp) == CRITERR))
    return (CRITERR);
  if (tmp->team == NULL)
    return (feed_tmp_str(&tmp->buff_writer, KO));
  return (EXIT_SUCCESS);
}
