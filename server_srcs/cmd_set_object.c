/*
** cmd_forward.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server_srcs
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Sat Jun 24 14:09:49 2017 girard
** Last update Sun Jul  2 17:36:28 2017 sebastien vidal
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

static int			drop_phiras(t_server_data * const data,
					  t_client_data * const tmp)
{
  t_client_data			*graphic;
  t_info_graphic		info;

  if (memset(&info, 0, sizeof(t_info_graphic)) == NULL)
    return (CRITERR);
  if (tmp->inventory.phiras > 0)
    {
      if ((graphic = get_graphic_client(data)) != NULL)
	{
	  if ((info.x = int_to_str(tmp->pos_x)) == NULL ||
	      (info.y = int_to_str(tmp->pos_y)) == NULL ||
	      (info.name = strdup("stone")) == NULL ||
	      (info.type = strdup("6")) == NULL ||
	      add_something(graphic, &info) == CRITERR)
	    return (CRITERR);
	  free_data_graphic(&info);
	}
      ++data->map[data->args_data.width *
		  tmp->pos_y + tmp->pos_x].phiras;
      --tmp->inventory.phiras;
    }
  else
    return (feed_tmp_str(&tmp->buff_writer, KO));
  return (feed_tmp_str(&tmp->buff_writer, OK));
}

static int			drop_thystame(t_server_data * const data,
					  t_client_data * const tmp)
{
  t_client_data			*graphic;
  t_info_graphic		info;

  if (memset(&info, 0, sizeof(t_info_graphic)) == NULL)
    return (CRITERR);
  if (tmp->inventory.thystame > 0)
    {
      if ((graphic = get_graphic_client(data)) != NULL)
	{
	  if ((info.x = int_to_str(tmp->pos_x)) == NULL ||
	      (info.y = int_to_str(tmp->pos_y)) == NULL ||
	      (info.name = strdup("stone")) == NULL ||
	      (info.type = strdup("7")) == NULL ||
	      add_something(graphic, &info) == CRITERR)
	    return (CRITERR);
	  free_data_graphic(&info);
	}
      ++data->map[data->args_data.width *
		  tmp->pos_y + tmp->pos_x].thystame;
      --tmp->inventory.thystame;
    }
  else
    return (feed_tmp_str(&tmp->buff_writer, KO));
  return (feed_tmp_str(&tmp->buff_writer, OK));
}

static const t_t_and_d_object	DATA_OBJECT[] =
  {
    { "food", drop_food },
    { "linemate", drop_linemate },
    { "deraumere", drop_deraumere },
    { "sibur", drop_sibur },
    { "mendiane", drop_mendiane },
    { "phiras", drop_phiras },
    { "thystame", drop_thystame }
  };

int				cmd_set_object(t_server_data * const data,
					       const int fd,
					       const char * const cmd)
{
  int				i;
  t_client_data			*tmp;

  i = 0;
  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  while (i < (int)(sizeof(DATA_OBJECT) / sizeof(t_t_and_d_object)))
    {
      if (strcmp(cmd + 4, DATA_OBJECT[i].object) == 0)
	return (DATA_OBJECT[i].check_object(data, tmp));
      ++i;
    }
  return (feed_tmp_str(&tmp->buff_writer, KO));
}

int				cmd_check_set_object(t_server_data *
						     const data,
						     const int fd,
						     const char * const cmd)
{
  t_client_data			*tmp;

  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  if (strlen(cmd) < strlen("Set  "))
    return (CRITERR);
  return (EXIT_SUCCESS);
}
