/*
** cmd_forward.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server_srcs
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Sat Jun 24 14:09:49 2017 girard
** Last update Sun Jul  2 17:32:37 2017 sebastien vidal
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

static const t_broad_res	broad_res[] =
  {
    {0, 0, 0.0, 0.0, 0},
    {0, 1, 0.0, 0.0, 1},
    {0, 2, 0.0, 0.0, 5},
    {1, 0, 0.0, 0.0, 3},
    {2, 0, 0.0, 0.0, 7},
    {2, 2, 3.0, -3, 1},
    {1, 2, 3.0, -3, 1},
    {1, 1, 3.0, -3.0, 5},
    {2, 1, 3.0, -3.0, 5},
    {1, 2, -0.333, -3.0, 4},
    {1, 2, 0.0, -0.333, 7},
    {1, 1, 0.333, 0.0, 7},
    {1, 1, 3.0, 0.333, 2},
    {2, 1, -0.33, -3.0, 8},
    {2, 1, 0, -0.333, 3},
    {2, 2, 0.333, 0, 3},
    {2, 2, 3, 0.333, 6}
  };

static int			find_result_broad_way(double coef,
						      t_broad_res * const res)
{
  int				i;

  i = 4;
  while (++i < 9)
    if (res->x_sup == broad_res[i].x_sup &&
	res->y_sup == broad_res[i].y_sup &&
	(coef > broad_res[i].coef_min ||
	 coef < broad_res[i].coef_max))
      {
	res->res = broad_res[i].res;
	return (EXIT_SUCCESS);
      }
  while (i < (int)(sizeof(broad_res) / sizeof(t_broad_res)))
    {
      if (res->x_sup == broad_res[i].x_sup &&
	  res->y_sup == broad_res[i].y_sup &&
	  coef < broad_res[i].coef_min &&
	  coef > broad_res[i].coef_max)
	{
	  res->res = broad_res[i].res;
	  return (EXIT_SUCCESS);
	}
      ++i;
    }
  return (EXIT_SUCCESS);
}

static int			find_coefficient(t_server_data * const data,
						 t_client_data *
						 const broadcaster,
						 t_client_data *
						 const current,
						 t_broad_res * const res)
{
  int				abs_x;
  int				abs_y;
  int				idx;
  double			coef;

  if (memset(res, 0, sizeof(t_broad_res)) == NULL)
    return (CRITERR);
  abs_x = find_abs_x(data, broadcaster, current);
  abs_y = find_abs_y(data, broadcaster, current);
  res->x_sup = XOSUPXT(abs_x, (int)broadcaster->pos_x);
  res->y_sup = YOSUPYT(abs_y, (int)broadcaster->pos_y);
  idx = -1;
  while (++idx < 5)
    if (res->x_sup == broad_res[idx].x_sup && res->y_sup ==
	broad_res[idx].y_sup)
      {
	res->res = broad_res[idx].res;
	return (EXIT_SUCCESS);
      }
  coef = calc_affine_coef(abs_x, abs_y, (int)broadcaster->pos_x,
			  (int)broadcaster->pos_y);
  find_result_broad_way(coef, res);
  return (EXIT_SUCCESS);
}

static int			send_broadcast_message(t_client_data * const
						       client, const int dir,
						       const char * const cmd)
{
  int				res_dir;

  res_dir = (dir + (client->dir * 2)) % 9 ;
  return (write_broadcast_buffer(&client->buff_writer, res_dir, cmd));
}

int				cmd_broadcast(t_server_data * const data,
					      const int fd,
					      const char * const cmd)
{
  t_client_data			*broadcaster;
  t_client_data			*tmp;
  t_broad_res			tmp_res;

  if ((broadcaster = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  tmp = data->c_data;
  while (tmp)
    {
      if (!(tmp->fd == broadcaster->fd))
	{
	  if (find_coefficient(data, broadcaster, tmp, &tmp_res) == CRITERR)
	    return (CRITERR);
	  if (send_broadcast_message(tmp, tmp_res.res, cmd) == CRITERR)
	    return (CRITERR);
	}
      tmp = tmp->tail;
    }
  return (feed_tmp_str(&broadcaster->buff_writer, OK));
}

int				cmd_check_broadcast(t_server_data * const data,
					      const int fd,
					      const char * const cmd)
{
  t_client_data			*tmp;

  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  if (strlen(cmd) <= strlen("Broadcast"))
    return (CRITERR);
  return (EXIT_SUCCESS);
}
