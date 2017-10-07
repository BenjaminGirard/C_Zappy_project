/*
** cmd_take_object_tools.c for zappy in /home/sebastien.vidal/rendu/NETWORK/PSU_2016_zappy/server_srcs
**
** Made by sebastien vidal
** Login   <sebastien.vidal@epitech.net>
**
** Started on  Tue Jun 27 20:42:27 2017 sebastien vidal
** Last update Sun Jul  2 16:22:01 2017 sebastien vidal
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

int			take_food(t_server_data * const data,
				  t_client_data * const tmp)
{
  t_client_data		*graphic;
  t_info_graphic	info;

  if (memset(&info, 0, sizeof(t_info_graphic)) == NULL)
    return (CRITERR);
  if (data->map[data->args_data.width * tmp->pos_y + tmp->pos_x].food > 0)
    {
      if ((graphic = get_graphic_client(data)) != NULL)
	{
	  if ((info.x = int_to_str(tmp->pos_x)) == NULL ||
	      (info.y = int_to_str(tmp->pos_y)) == NULL ||
	      (info.name = strdup("1")) == NULL ||
	      (info.type = strdup("1")) == NULL ||
	      delete_stone(graphic, &info) == CRITERR)
	    return (CRITERR);
	  free_data_graphic(&info);
	}
      tmp->inventory.life += LIFE_UNIT;
      tmp->inventory.food = tmp->inventory.life / LIFE_UNIT;
      --data->map[data->args_data.width * tmp->pos_y + tmp->pos_x].food;
    }
  else
    return (feed_tmp_str(&tmp->buff_writer, KO));
  return (feed_tmp_str(&tmp->buff_writer, OK));
}

int			take_linemate(t_server_data * const data,
			      t_client_data * const tmp)
{
  t_client_data		*graphic;
  t_info_graphic	info;

  if (memset(&info, 0, sizeof(t_info_graphic)) == NULL)
    return (CRITERR);
  if (data->map[data->args_data.width *
		tmp->pos_y + tmp->pos_x].linemate > 0)
    {
      if ((graphic = get_graphic_client(data)) != NULL)
	{
	  if ((info.x = int_to_str(tmp->pos_x)) == NULL ||
	      (info.y = int_to_str(tmp->pos_y)) == NULL ||
	      (info.name = strdup("1")) == NULL ||
	      (info.type = strdup("2")) == NULL ||
	      delete_stone(graphic, &info) == CRITERR)
	    return (CRITERR);
	  free_data_graphic(&info);
	}
      ++tmp->inventory.linemate;
      --data->map[data->args_data.width *
		  tmp->pos_y + tmp->pos_x].linemate;
    }
  else
    return (feed_tmp_str(&tmp->buff_writer, KO));
  return (feed_tmp_str(&tmp->buff_writer, OK));
}

int		take_deraumere(t_server_data * const data,
			       t_client_data * const tmp)
{
  t_client_data		*graphic;
  t_info_graphic	info;

  if (memset(&info, 0, sizeof(t_info_graphic)) == NULL)
    return (CRITERR);
  if (data->map[data->args_data.width *
		tmp->pos_y + tmp->pos_x].deraumere > 0)
    {
      if ((graphic = get_graphic_client(data)) != NULL)
	{
	  if ((info.x = int_to_str(tmp->pos_x)) == NULL ||
	      (info.y = int_to_str(tmp->pos_y)) == NULL ||
	      (info.name = strdup("1")) == NULL ||
	      (info.type = strdup("3")) == NULL ||
	      delete_stone(graphic, &info) == CRITERR)
	    return (CRITERR);
	  free_data_graphic(&info);
	}
      ++tmp->inventory.deraumere;
      --data->map[data->args_data.width *
		  tmp->pos_y + tmp->pos_x].deraumere;
    }
  else
    return (feed_tmp_str(&tmp->buff_writer, KO));
  return (feed_tmp_str(&tmp->buff_writer, OK));
}

int		take_sibur(t_server_data * const data,
			   t_client_data * const tmp)
{
  t_client_data		*graphic;
  t_info_graphic	info;

  if (memset(&info, 0, sizeof(t_info_graphic)) == NULL)
    return (CRITERR);
  if (data->map[data->args_data.width * tmp->pos_y + tmp->pos_x].sibur > 0)
    {
      if ((graphic = get_graphic_client(data)) != NULL)
	{
	  if ((info.x = int_to_str(tmp->pos_x)) == NULL ||
	      (info.y = int_to_str(tmp->pos_y)) == NULL ||
	      (info.name = strdup("1")) == NULL ||
	      (info.type = strdup("4")) == NULL ||
	      delete_stone(graphic, &info) == CRITERR)
	    return (CRITERR);
	  free_data_graphic(&info);
	}
      ++tmp->inventory.sibur;
      --data->map[data->args_data.width * tmp->pos_y + tmp->pos_x].sibur;
    }
  else
    return (feed_tmp_str(&tmp->buff_writer, KO));
  return (feed_tmp_str(&tmp->buff_writer, OK));
}

int		take_mendiane(t_server_data * const data,
			  t_client_data * const tmp)
{
  t_client_data		*graphic;
  t_info_graphic	info;

  if (memset(&info, 0, sizeof(t_info_graphic)) == NULL)
    return (CRITERR);
  if (data->map[data->args_data.width *
		tmp->pos_y + tmp->pos_x].mendiane > 0)
    {
      if ((graphic = get_graphic_client(data)) != NULL)
	{
	  if ((info.x = int_to_str(tmp->pos_x)) == NULL ||
	      (info.y = int_to_str(tmp->pos_y)) == NULL ||
	      (info.name = strdup("1")) == NULL ||
	      (info.type = strdup("5")) == NULL ||
	      delete_stone(graphic, &info) == CRITERR)
	    return (CRITERR);
	  free_data_graphic(&info);
	}
      ++tmp->inventory.mendiane;
      --data->map[data->args_data.width *
		  tmp->pos_y + tmp->pos_x].mendiane;
    }
  else
    return (feed_tmp_str(&tmp->buff_writer, KO));
  return (feed_tmp_str(&tmp->buff_writer, OK));
}
