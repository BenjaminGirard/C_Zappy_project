/*
** cmd_forward.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server_srcs
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Sat Jun 24 14:09:49 2017 girard
** Last update Sun Jul  2 17:36:01 2017 sebastien vidal
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

static int			look_up_and_down(const t_server_data *
						 const data,
						 const t_client_data *
						 const tmp,
						 const int key)
{
  unsigned int			i;
  t_ctrl			data_ctrl;

  i = 0;
  data_ctrl.key = key;
  while (++i <= tmp->lvl)
    {
      data_ctrl.deep = i;
      if (((key == 0) ? (get_tiles_up(data, tmp, &data_ctrl)) :
	   (get_tiles_down(data, tmp, &data_ctrl))) == CRITERR)
	return (CRITERR);
    }
  return (EXIT_SUCCESS);
}

static int			look_right_and_left(const t_server_data *
						    const data,
						    const t_client_data *
						    const tmp,
						    const int key)
{
  unsigned int			i;
  t_ctrl			data_ctrl;

  i = 0;
  data_ctrl.key = key;
  while (++i <= tmp->lvl)
    {
      data_ctrl.deep = i;
      if (((key == 0) ? (get_tiles_left(data, tmp, &data_ctrl)) :
	   (get_tiles_right(data, tmp, &data_ctrl))) == CRITERR)
	return (CRITERR);
    }
  return (EXIT_SUCCESS);
}

static int			look_around(t_server_data * const data,
					    t_client_data * const tmp)
{
  if (print_result_look(data, tmp, tmp->pos_x, tmp->pos_y) == CRITERR)
    return (CRITERR);
  if (tmp->dir == UP || tmp->dir == DOWN)
    {
      if (((tmp->dir == UP) ? (look_up_and_down(data, tmp, 0)) :
	   (look_up_and_down(data, tmp, 1))) == CRITERR)
	return (CRITERR);
    }
  else
    {
      if (((tmp->dir == LEFT) ? (look_right_and_left(data, tmp, 0)) :
	   (look_right_and_left(data, tmp, 1))) == CRITERR)
	return (CRITERR);
    }
  return (EXIT_SUCCESS);
}

int				cmd_look(t_server_data * const data,
					 const int fd,
					 const char * const cmd)
{
  t_client_data			*tmp;

  (void)cmd;
  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  if (feed_tmp_str(&tmp->buff_writer, "[") == CRITERR||
      look_around(data, tmp) == CRITERR ||
      feed_tmp_str(&tmp->buff_writer, " ]\n") == CRITERR)
    return (CRITERR);
  return (EXIT_SUCCESS);
}

int				cmd_check_look(t_server_data *
					       const data,
					       const int fd,
					       const char * const cmd)
{
  t_client_data			*tmp;

  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  if (strlen(cmd) > strlen("Look"))
    return (CRITERR);
  return (EXIT_SUCCESS);
}
