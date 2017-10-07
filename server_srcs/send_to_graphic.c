/*
** send_to_graphic.c for zappy in /home/sebastien.vidal/rendu/NETWORK/PSU_2016_zappy/server_srcs
**
** Made by sebastien vidal
** Login   <sebastien.vidal@epitech.net>
**
** Started on  Sat Jul  1 22:25:30 2017 sebastien vidal
** Last update Sun Jul  2 20:01:37 2017 girard
*/

#include <string.h>
#include "server.h"

int			add_something(t_client_data * const graphic,
				      const t_info_graphic * const data)
{
  if (feed_tmp_str(&graphic->buff_writer, "add ") == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, data->type) == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, " ") == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, data->x) == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, " ") == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, data->y) == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, " ") == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, data->name) == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, "\n") == CRITERR)
    return (CRITERR);
  return (EXIT_SUCCESS);
}

void			free_data_graphic(t_info_graphic * const data)
{
  if (data->name)
    free(data->name);
  if (data->x)
    free(data->x);
  if (data->y)
    free(data->y);
  if (data->type)
    free(data->type);
}

static int		add_all_player(const t_server_data *
				       const data,
				       t_client_data * const graphic)
{
  t_client_data		*tmp;
  t_info_graphic	info;

  tmp = data->c_data;
  if (memset(&info, 0, sizeof(t_info_graphic)) == NULL)
    return (CRITERR);
  while (tmp)
    {
      if (tmp != graphic)
	{
	  if ((info.x = int_to_str((int)tmp->pos_x)) == NULL ||
	      (info.y = int_to_str((int)tmp->pos_y)) == NULL ||
	      (info.name = int_to_str(tmp->fd)) == NULL ||
	      (info.type = int_to_str(0)) == NULL ||
	      add_something(graphic, &info) == CRITERR)
	    return (CRITERR);
	  free_data_graphic(&info);
	}
      tmp = tmp->tail;
    }
  return (EXIT_SUCCESS);
}

int			add_few_stones(t_client_data * const graphic,
				       const unsigned int nb,
				       t_info_graphic *
				       const info)
{
  unsigned int		i;

  i = -1;
  while (++i < nb)
    {
      if (add_something(graphic, info) == CRITERR)
	return (CRITERR);
    }
  return (EXIT_SUCCESS);
}

int			first_co_graphic(t_server_data * const data,
					 t_client_data * const graphic)
{
  char			*x;
  char			*y;
  int			height;
  int			i;

  i = -1;
  height = 0;
  graphic->team = GRAPHIC;
  if (send_graphical_msg(data, "#\n") == CRITERR ||
      send_map_size(data, graphic) == CRITERR ||
      add_all_player(data, graphic) == CRITERR)
    return (CRITERR);
  while (++i < data->args_data.width * data->args_data.height)
    {
      if (i != 0 && i % data->args_data.width == 0)
	++height;
      if ((x = int_to_str(i % data->args_data.width)) == NULL ||
	  (y = int_to_str(height)) == NULL ||
	  add_fl(&data->map[i], graphic, x, y) == CRITERR ||
	  add_ds(&data->map[i], graphic, x, y) == CRITERR ||
	  add_mp(&data->map[i], graphic, x, y) == CRITERR ||
	  add_t(&data->map[i], graphic, x, y) == CRITERR)
	return (CRITERR);
    }
  return (send_end_begin_msg(data));
}
