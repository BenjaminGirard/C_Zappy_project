/*
** cmd_forward.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server_srcs
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Sat Jun 24 14:09:49 2017 girard
** Last update Sun Jul  2 20:57:11 2017 bibzor
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

static void			set_pos(t_client_data * const tmp,
					const unsigned int x,
					const unsigned int y)
{
  tmp->pos_y = y;
  tmp->pos_x = x;
}

static void			move(const t_server_data * const data,
				     t_client_data * const tmp)
{
  if (tmp->dir == UP)
    {
      if (tmp->pos_y == 0)
	return (set_pos(tmp, tmp->pos_x,
			data->args_data.height - 1));
      return (set_pos(tmp, tmp->pos_x, tmp->pos_y - 1));
    }
  else if (tmp->dir == DOWN)
    {
      if (tmp->pos_y == (unsigned int)data->args_data.height - 1)
	return (set_pos(tmp, tmp->pos_x, 0));
      return (set_pos(tmp, tmp->pos_x, tmp->pos_y + 1));
    }
  else if (tmp->dir == LEFT)
    {
      if (tmp->pos_x == 0)
	return (set_pos(tmp, data->args_data.width - 1,
			tmp->pos_y));
      return (set_pos(tmp, tmp->pos_x - 1, tmp->pos_y));
    }
  else
    if (tmp->pos_x == (unsigned int)data->args_data.width - 1)
      return (set_pos(tmp, 0, tmp->pos_y));
  return (set_pos(tmp, tmp->pos_x + 1, tmp->pos_y));
}

static int			send_move_graphic(t_client_data * const
						  graphic,
						  const t_info_graphic *
						  const data)
{
  if (feed_tmp_str(&graphic->buff_writer, "move ") == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, data->x) == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, " ") == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, data->y) == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, " ") == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, data->name) == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, "\n") == CRITERR)
    return (CRITERR);
  return (EXIT_SUCCESS);
}

int				cmd_forward(t_server_data * const data,
					    const int fd,
					    const char * const cmd)
{
  t_client_data			*tmp;
  t_client_data			*graphic;
  t_info_graphic		info;

  (void)cmd;
  if (memset(&info, 0, sizeof(t_info_graphic)) == NULL)
    return (CRITERR);
  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  move(data, tmp);
  if ((graphic = get_graphic_client(data)) != NULL)
    {
      if ((info.x = int_to_str(tmp->pos_x)) == NULL ||
	  (info.y = int_to_str(tmp->pos_y)) == NULL ||
	  (info.name = int_to_str(tmp->fd)) == NULL)
	return (CRITERR);
      if (send_move_graphic(graphic, &info) == CRITERR)
	return (CRITERR);
      free_data_graphic(&info);
    }
  return (feed_tmp_str(&tmp->buff_writer, OK));
}

int				cmd_check_forward(t_server_data *
						  const data,
						  const int fd,
						  const char * const cmd)
{
  t_client_data			*tmp;

  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  if (strlen(cmd) > strlen("Forward"))
    return (CRITERR);
  return (EXIT_SUCCESS);
}
