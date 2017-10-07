/*
** send_grphical_msg.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Sun Jul  2 17:22:33 2017 girard
** Last update Sun Jul  2 20:00:52 2017 girard
*/

#include "server.h"

int			send_end_begin_msg(t_server_data * const data)
{
  t_client_data		*graph;

  if ((graph = get_graphic_client(data)) == NULL)
    return (EXIT_SUCCESS);
  if (feed_tmp_str(&graph->buff_writer, "##\n") == CRITERR ||
      feed_tmp_str(&graph->buff_writer, "#\n") == CRITERR)
    return (CRITERR);
  return (EXIT_SUCCESS);
}

int			send_graphical_msg(t_server_data * const data,
					   const char * const str)
{
  t_client_data		*graph;

  if ((graph = get_graphic_client(data)) == NULL)
    return (EXIT_SUCCESS);
  return (feed_tmp_str(&graph->buff_writer, str));
}
