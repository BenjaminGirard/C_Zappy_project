/*
** get_grapic_client.c for zappy in /home/sebastien.vidal/rendu/NETWORK/PSU_2016_zappy/server_srcs
**
** Made by sebastien vidal
** Login   <sebastien.vidal@epitech.net>
**
** Started on  Sun Jul  2 12:59:03 2017 sebastien vidal
** Last update Sun Jul  2 17:22:28 2017 sebastien vidal
*/

#include <string.h>
#include "server.h"

t_client_data			*get_graphic_client(const t_server_data *
						   const data)
{
  t_client_data			*tmp;

  tmp = data->c_data;
  while (tmp)
    {
      if (tmp->team && strcmp(tmp->team, GRAPHIC) == 0)
	return (tmp);
      tmp = tmp->tail;
    }
  return (NULL);
}
