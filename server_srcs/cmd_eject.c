/*
** cmd_forward.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server_srcs
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Sat Jun 24 14:09:49 2017 girard
** Last update Sun Jul  2 17:34:27 2017 sebastien vidal
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

static bool			check_tiles(t_client_data * const c_data,
					    const t_client_data * const cur)
{
  t_client_data			*tmp;

  tmp = c_data;
  while (tmp)
    {
      if (tmp->pos_x == cur->pos_x && tmp->pos_y == cur->pos_y && tmp != cur)
	return (true);
      tmp = tmp->tail;
    }
  return (false);
}

static int			move_drone(t_server_data *const data,
					   const t_direction dir,
					   t_client_data * const tmp)
{
  if (dir == UP)
    {
      if (tmp->pos_y == 0)
	return (sent_eject_and_set_pos(tmp, tmp->pos_x,
				       data->args_data.height - 1, dir));
      return (sent_eject_and_set_pos(tmp, tmp->pos_x, tmp->pos_y - 1, dir));
    }
  else if (dir == DOWN)
    {
      if (tmp->pos_y == (unsigned int)data->args_data.height - 1)
	return (sent_eject_and_set_pos(tmp, tmp->pos_x, 0, dir));
      return (sent_eject_and_set_pos(tmp, tmp->pos_x, tmp->pos_y + 1, dir));
    }
  else if (dir == LEFT)
    {
      if (tmp->pos_x == 0)
	return (sent_eject_and_set_pos(tmp, data->args_data.width - 1,
				       tmp->pos_y, dir));
      return (sent_eject_and_set_pos(tmp, tmp->pos_x - 1, tmp->pos_y, dir));
    }
  else
    if (tmp->pos_x == (unsigned int)data->args_data.width - 1)
      return (sent_eject_and_set_pos(tmp, 0, tmp->pos_y, dir));
  return (sent_eject_and_set_pos(tmp, tmp->pos_x + 1, tmp->pos_y, dir));
}

static int			eject_drones(t_server_data * const data,
					     t_client_data * const c_data,
					     const t_client_data *const cur)
{
  t_client_data			*tmp;

  tmp = c_data;
  while (tmp)
    {
      if (tmp->pos_x == cur->pos_x && tmp->pos_y == cur->pos_y && tmp != cur)
	if (move_drone(data, cur->dir, tmp) == CRITERR ||
	    eject_drones(data, tmp->tail, cur) == CRITERR)
	  return (CRITERR);
      tmp = tmp->tail;
    }
  return (EXIT_SUCCESS);
}

int				cmd_eject(t_server_data * const data,
					      const int fd,
					      const char * const cmd)
{
  t_client_data			*tmp;

  (void)cmd;
  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  if (check_tiles(data->c_data, tmp) == false)
    return (feed_tmp_str(&tmp->buff_writer, KO));
  else
    if (eject_drones(data, data->c_data, tmp) == CRITERR ||
	feed_tmp_str(&tmp->buff_writer, KO) == CRITERR)
      return (CRITERR);
  return (EXIT_SUCCESS);
}

int				cmd_check_eject(t_server_data * const data,
						const int fd,
						const char * const cmd)
{
  t_client_data			*tmp;

  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  if (strlen(cmd) > strlen("Eject"))
    return (CRITERR);
  return (EXIT_SUCCESS);
}
