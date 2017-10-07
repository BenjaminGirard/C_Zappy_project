/*
** get_tiles.c for zappy in /home/bibzor/rendu/NETWORK/PSU_2016_zappy/server_srcs
**
** Made by bibzor
** Login   <sebastien.vidal@epitech.eu>
**
** Started on  Mon Jun 26 21:57:29 2017 bibzor
** Last update Fri Jun 30 16:12:22 2017 girard
*/

#include <stdio.h>
#include "server.h"

int			get_tiles_up(const t_server_data * const data,
				     const t_client_data * const tmp,
				     const t_ctrl * const data_ctrl)
{
  int			i;
  int			x;
  int			y;

  i = 0;
  x = tmp->pos_x - data_ctrl->deep;
  y = tmp->pos_y - data_ctrl->deep;
  x = (x < 0) ? ((data->args_data.width - 1) -
		 ((x * (-1)) % data->args_data.width)) :
    (x % data->args_data.width);
  y = (y < 0) ? ((data->args_data.height - 1) -
		 ((y * (-1)) % data->args_data.height)) :
    (y % data->args_data.height);
  while (i < data_ctrl->deep * 2 + 1)
    {
      if (feed_tmp_str((t_ring_buff * const)&tmp->buff_writer,
		       ",") == CRITERR ||
	  print_result_look(data, tmp, x, y) == CRITERR)
	return (CRITERR);
      ++i;
      x = (x + 1) % data->args_data.width;
    }
  return (EXIT_SUCCESS);
}

int			get_tiles_down(const t_server_data * const data,
				       const t_client_data * const tmp,
				       const t_ctrl * const data_ctrl)
{
  int			i;
  int			x;
  int			y;

  i = 0;
  x = (tmp->pos_x + data_ctrl->deep) % data->args_data.width;
  y = (tmp->pos_y + data_ctrl->deep) % data->args_data.height;
  while (i < data_ctrl->deep * 2 + 1)
    {
      if (feed_tmp_str((t_ring_buff * const)&tmp->buff_writer,
		       ",") == CRITERR ||
	  print_result_look(data, tmp, x, y) == CRITERR)
	return (CRITERR);
      ++i;
      x = (x - 1 < 0) ? ((data->args_data.width - 1) -
			 ((x * (-1)) % data->args_data.width)) :
	((x - 1) % data->args_data.width);
    }
  return (EXIT_SUCCESS);
}

int			get_tiles_left(const t_server_data * const data,
				       const t_client_data * const tmp,
				       const t_ctrl * const data_ctrl)
{
  int			i;
  int			x;
  int			y;

  i = 0;
  x = (tmp->pos_x - data_ctrl->deep);
  x = (x < 0) ? ((data->args_data.width - 1) -
		 ((x * (-1)) % data->args_data.width)) :
    (x % data->args_data.width);
  y = (tmp->pos_y + data_ctrl->deep) % data->args_data.height;
  while (i < data_ctrl->deep * 2 + 1)
    {
      if (feed_tmp_str((t_ring_buff * const)&tmp->buff_writer,
		       ",") == CRITERR ||
	  print_result_look(data, tmp, x, y) == CRITERR)
	return (CRITERR);
      ++i;
      y = (y - 1 < 0) ? ((data->args_data.height - 1) -
			 ((y * (-1)) % data->args_data.height)) :
	((y - 1) % data->args_data.height);
    }
  return (EXIT_SUCCESS);
}

int			get_tiles_right(const t_server_data * const data,
					const t_client_data * const tmp,
					const t_ctrl * const data_ctrl)
{
  int			i;
  int			x;
  int			y;

  i = 0;
  x = (tmp->pos_x + data_ctrl->deep) % data->args_data.width;
  y = (tmp->pos_y - data_ctrl->deep);
  y = (y < 0) ? ((data->args_data.height - 1) -
		 ((y * (-1)) % data->args_data.height)) :
    (y % data->args_data.height);
  while (i < data_ctrl->deep * 2 + 1)
    {
      if (feed_tmp_str((t_ring_buff * const)&tmp->buff_writer,
		       ",") == CRITERR ||
	  print_result_look(data, tmp, x, y) == CRITERR)
	return (CRITERR);
      ++i;
      y = (y + 1) % data->args_data.height;
    }
  return (EXIT_SUCCESS);
}
