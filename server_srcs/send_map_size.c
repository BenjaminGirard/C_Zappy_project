/*
** send_map_size.c for zappy in /home/sebastien.vidal/rendu/NETWORK/PSU_2016_zappy/server_srcs
**
** Made by sebastien vidal
** Login   <sebastien.vidal@epitech.net>
**
** Started on  Sun Jul  2 17:02:03 2017 sebastien vidal
** Last update Sun Jul  2 20:58:24 2017 bibzor
*/

#include <string.h>
#include "server.h"

int			send_map_size(t_server_data * const data,
				     t_client_data * const graphic)
{
  t_info_graphic	info;

  if ((info.x = int_to_str(data->args_data.width)) == NULL)
    return (CRITERR);
  if ((info.y = int_to_str(data->args_data.height)) == NULL)
    return (CRITERR);
  if (feed_tmp_str(&graphic->buff_writer, "map_size ") == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, info.x) == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, " ") == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, info.y) == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, "\n") == CRITERR)
    return (CRITERR);
  return (EXIT_SUCCESS);
}

int			send_death_to_graphic(t_client_data * const
					      graphic,
					      const int fd)
{
  t_info_graphic	info;

  if ((info.name = int_to_str(fd)) == NULL)
    return (CRITERR);
  if (feed_tmp_str(&graphic->buff_writer, "delete ") == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, "0") == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, " ") == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, info.name) == CRITERR ||
      feed_tmp_str(&graphic->buff_writer, "\n") == CRITERR)
    return (CRITERR);
  return (EXIT_SUCCESS);
}
