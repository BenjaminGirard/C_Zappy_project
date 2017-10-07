/*
** send_to_graphic_tools.c for zappy in /home/sebastien.vidal/rendu/NETWORK/PSU_2016_zappy/server_srcs
**
** Made by sebastien vidal
** Login   <sebastien.vidal@epitech.net>
**
** Started on  Sun Jul  2 11:48:55 2017 sebastien vidal
** Last update Sun Jul  2 17:02:48 2017 sebastien vidal
*/

#include <string.h>
#include "server.h"

int			delete_stone(t_client_data * const graphic,
				     const t_info_graphic * const data)
{
  if (feed_tmp_str(&graphic->buff_writer, "delete ") == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, data->name) == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, " ") == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, data->type) == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, " ") == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, data->x) == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, " ") == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, data->y) == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, "\n") == CRITERR)
    return (CRITERR);
  return (EXIT_SUCCESS);
}

int			add_fl(const t_ressources *tile,
			       t_client_data * const graphic,
			       char * const x,
			       char * const y)
{
  t_info_graphic	info;

  if (memset(&info, 0, sizeof(t_info_graphic)) == NULL)
    return (CRITERR);
  info.x = x;
  info.y = y;
  if ((info.name = strdup("stone")) == NULL)
    return (CRITERR);
  if (tile->food > 0)
    {
      if ((info.type = strdup("1")) == NULL ||
	  add_few_stones(graphic, tile->food, &info) == CRITERR)
	return (CRITERR);
    }
  if (tile->linemate > 0)
    {
      if (info.type)
	free(info.type);
      if ((info.type = strdup("2")) == NULL ||
	  add_few_stones(graphic, tile->linemate, &info) == CRITERR)
	return (CRITERR);
    }
  if (info.name)
    free(info.name);
  return (EXIT_SUCCESS);
}

int			add_ds(const t_ressources *tile,
			       t_client_data * const graphic,
			       char * const x,
			       char * const y)
{
  t_info_graphic	info;

  if (memset(&info, 0, sizeof(t_info_graphic)) == NULL)
    return (CRITERR);
  info.x = x;
  info.y = y;
  if ((info.name = strdup("stone")) == NULL)
    return (CRITERR);
  if (tile->deraumere > 0)
    {
      if ((info.type = strdup("3")) == NULL ||
	  add_few_stones(graphic, tile->deraumere, &info) == CRITERR)
	return (CRITERR);
    }
  if (tile->sibur > 0)
    {
      if (info.type)
	free(info.type);
      if ((info.type = strdup("4")) == NULL ||
	  add_few_stones(graphic, tile->sibur, &info) == CRITERR)
	return (CRITERR);
    }
  if (info.name)
    free(info.name);
  return (EXIT_SUCCESS);
}

int			add_mp(const t_ressources *tile,
			       t_client_data * const graphic,
			       char * const x,
			       char * const y)
{
  t_info_graphic	info;

  if (memset(&info, 0, sizeof(t_info_graphic)) == NULL)
    return (CRITERR);
  info.x = x;
  info.y = y;
  if ((info.name = strdup("stone")) == NULL)
    return (CRITERR);
  if (tile->mendiane > 0)
    {
      if ((info.type = strdup("5")) == NULL ||
	  add_few_stones(graphic, tile->mendiane, &info) == CRITERR)
	return (CRITERR);
    }
  if (tile->phiras > 0)
    {
      if (info.type)
	free(info.type);
      if ((info.type = strdup("6")) == NULL ||
	  add_few_stones(graphic, tile->phiras, &info) == CRITERR)
	return (CRITERR);
    }
  if (info.name)
    free(info.name);
  return (EXIT_SUCCESS);
}

int			add_t(const t_ressources *tile,
			      t_client_data * const graphic,
			      char * const x,
			      char * const y)
{
  t_info_graphic	info;

  if (memset(&info, 0, sizeof(t_info_graphic)) == NULL)
    return (CRITERR);
  info.x = x;
  info.y = y;
  if ((info.name = strdup("stone")) == NULL)
    return (CRITERR);
  if (tile->thystame > 0)
    {
      if ((info.type = strdup("7")) == NULL ||
	  add_few_stones(graphic, tile->thystame, &info) == CRITERR)
	return (CRITERR);
    }
  if (info.name)
    free(info.name);
  return (EXIT_SUCCESS);
}
