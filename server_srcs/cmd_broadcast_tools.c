/*
** calc_affine_coef.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Thu Jun 29 09:05:25 2017 girard
** Last update Sun Jul  2 17:20:30 2017 sebastien vidal
*/

#include <string.h>
#include "server.h"

int				find_abs_x(t_server_data * const data,
					   t_client_data * const broadcaster,
					   t_client_data * const current)
{
  int				resx_right;
  int				resx_left;

  resx_right = broadcaster->pos_x;
  resx_left = broadcaster->pos_x;
  while (resx_right % data->args_data.width != (int)current->pos_x)
    ++resx_right;
  while (((resx_left < 0) ? ((data->args_data.width - 1) -
			    ((resx_left * -1) % data->args_data.width)) :
	  (resx_left)) != (int)current->pos_x)
    --resx_left;
  return (resx_right - broadcaster->pos_x < broadcaster->pos_x - resx_left ?
	  resx_right : resx_left);
}

int				find_abs_y(t_server_data * const data,
					   t_client_data * const broadcaster,
					   t_client_data * const current)
{
  int				resy_down;
  int				resy_up;

  resy_down = broadcaster->pos_y;
  resy_up = broadcaster->pos_y;
  while (resy_down % data->args_data.width != (int)current->pos_y)
    ++resy_down;
  while (((resy_up < 0) ? ((data->args_data.width - 1) -
			    ((resy_up * -1) % data->args_data.width)) :
	  (resy_up)) != (int)current->pos_y)
    --resy_up;
  return (resy_down - broadcaster->pos_y < broadcaster->pos_y - resy_up ?
	  resy_down : resy_up);
}

double				calc_affine_coef(const int x1, const int y1,
						 const int x2, const int y2)
{
  return (((double)(y2 - y1)) / ((double)(x2 - x1)));
}

int				write_broadcast_buffer(t_ring_buff *
						       const buff,
						       const int way,
						       const char * const str)
{
  char				*itos;

  itos = NULL;
  if ((itos = int_to_str(way)) == NULL)
    return (CRITERR);
  if (feed_tmp_str(buff, "message ") == CRITERR ||
      feed_tmp_str(buff, itos) == CRITERR ||
      feed_tmp_str(buff, ",") == CRITERR ||
      feed_tmp_str(buff, &str[strlen("Broadcast")]) == CRITERR ||
      feed_tmp_str(buff, "\n") == CRITERR)
    return (CRITERR);
  if (itos)
    free(itos);
  return (EXIT_SUCCESS);
}
