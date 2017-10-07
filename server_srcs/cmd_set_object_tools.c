/*
** cmd_set_object_tools.c for zappy in /home/sebastien.vidal/rendu/NETWORK/PSU_2016_zappy
**
** Made by sebastien vidal
** Login   <sebastien.vidal@epitech.net>
**
** Started on  Tue Jun 27 21:41:00 2017 sebastien vidal
** Last update Sun Jul  2 15:47:23 2017 sebastien vidal
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

int			drop_food(t_server_data * const data,
				  t_client_data * const tmp)
{
  t_client_data		*graphic;
  t_info_graphic	info;

  if (memset(&info, 0, sizeof(t_info_graphic)) == NULL)
    return (CRITERR);
  if (tmp->inventory.food > 0)
    {
      if ((graphic = get_graphic_client(data)) != NULL)
	{
	  if ((info.x = int_to_str(tmp->pos_x)) == NULL ||
	      (info.y = int_to_str(tmp->pos_y)) == NULL ||
	      (info.name = strdup("stone")) == NULL ||
	      (info.type = strdup("1")) == NULL ||
	      add_something(graphic, &info) == CRITERR)
	    return (CRITERR);
	  free_data_graphic(&info);
	}
      ++data->map[data->args_data.width * tmp->pos_y + tmp->pos_x].food;
      tmp->inventory.life = tmp->inventory.life - LIFE_UNIT;
      tmp->inventory.food = tmp->inventory.life / LIFE_UNIT;
    }
  else
    return (feed_tmp_str(&tmp->buff_writer, KO));
  return (feed_tmp_str(&tmp->buff_writer, OK));
}

int			drop_linemate(t_server_data * const data,
				      t_client_data * const tmp)
{
  t_client_data		*graphic;
  t_info_graphic	info;

  if (memset(&info, 0, sizeof(t_info_graphic)) == NULL)
    return (CRITERR);
  if (tmp->inventory.linemate > 0)
    {
      if ((graphic = get_graphic_client(data)) != NULL)
	{
	  if ((info.x = int_to_str(tmp->pos_x)) == NULL ||
	      (info.y = int_to_str(tmp->pos_y)) == NULL ||
	      (info.name = strdup("stone")) == NULL ||
	      (info.type = strdup("2")) == NULL ||
	      add_something(graphic, &info) == CRITERR)
	    return (CRITERR);
	  free_data_graphic(&info);
	}
      ++data->map[data->args_data.width *
		  tmp->pos_y + tmp->pos_x].linemate;
      --tmp->inventory.linemate;
    }
  else
    return (feed_tmp_str(&tmp->buff_writer, KO));
  return (feed_tmp_str(&tmp->buff_writer, OK));
}

int			drop_deraumere(t_server_data * const data,
				       t_client_data * const tmp)
{
  t_client_data		*graphic;
  t_info_graphic	info;

  if (memset(&info, 0, sizeof(t_info_graphic)) == NULL)
    return (CRITERR);
  if (tmp->inventory.deraumere > 0)
    {
      if ((graphic = get_graphic_client(data)) != NULL)
	{
	  if ((info.x = int_to_str(tmp->pos_x)) == NULL ||
	      (info.y = int_to_str(tmp->pos_y)) == NULL ||
	      (info.name = strdup("stone")) == NULL ||
	      (info.type = strdup("3")) == NULL ||
	      add_something(graphic, &info) == CRITERR)
	    return (CRITERR);
	  free_data_graphic(&info);
	}
      ++data->map[data->args_data.width *
		  tmp->pos_y + tmp->pos_x].deraumere;
      --tmp->inventory.deraumere;
    }
  else
    return (feed_tmp_str(&tmp->buff_writer, KO));
  return (feed_tmp_str(&tmp->buff_writer, OK));
}

int			drop_sibur(t_server_data * const data,
				   t_client_data * const tmp)
{
  t_client_data		*graphic;
  t_info_graphic	info;

  if (memset(&info, 0, sizeof(t_info_graphic)) == NULL)
    return (CRITERR);
  if (tmp->inventory.sibur > 0)
    {
      if ((graphic = get_graphic_client(data)) != NULL)
	{
	  if ((info.x = int_to_str(tmp->pos_x)) == NULL ||
	      (info.y = int_to_str(tmp->pos_y)) == NULL ||
	      (info.name = strdup("stone")) == NULL ||
	      (info.type = strdup("4")) == NULL ||
	      add_something(graphic, &info) == CRITERR)
	    return (CRITERR);
	  free_data_graphic(&info);
	}
      ++data->map[data->args_data.width *
		  tmp->pos_y + tmp->pos_x].sibur;
      --tmp->inventory.sibur;
    }
  else
    return (feed_tmp_str(&tmp->buff_writer, KO));
  return (feed_tmp_str(&tmp->buff_writer, OK));
}

int			drop_mendiane(t_server_data * const data,
				      t_client_data * const tmp)
{
  t_client_data		*graphic;
  t_info_graphic	info;

  if (memset(&info, 0, sizeof(t_info_graphic)) == NULL)
    return (CRITERR);
  if (tmp->inventory.mendiane > 0)
    {
      if ((graphic = get_graphic_client(data)) != NULL)
	{
	  if ((info.x = int_to_str(tmp->pos_x)) == NULL ||
	      (info.y = int_to_str(tmp->pos_y)) == NULL ||
	      (info.name = strdup("stone")) == NULL ||
	      (info.type = strdup("5")) == NULL ||
	      add_something(graphic, &info) == CRITERR)
	    return (CRITERR);
	  free_data_graphic(&info);
	}
      ++data->map[data->args_data.width *
		  tmp->pos_y + tmp->pos_x].mendiane;
      --tmp->inventory.mendiane;
    }
  else
    return (feed_tmp_str(&tmp->buff_writer, KO));
  return (feed_tmp_str(&tmp->buff_writer, OK));
}
