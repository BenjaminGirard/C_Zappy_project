/*
** client_data_tools.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Thu Jun 22 12:38:13 2017 girard
** Last update Sun Jul  2 17:03:17 2017 girard
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

t_client_data			*find_client_fd(t_client_data *c_data,
						const int fd)
{
  t_client_data			*tmp;

  tmp = c_data;
  while (tmp)
    {
      if (tmp->fd == fd)
	return (tmp);
      tmp = tmp->tail;
    }
  return (NULL);
}

static void			init_client_inventory(t_client_data *
						      const tmp)
{
  tmp->inventory.life = LIFE_UNIT * 10;
  tmp->inventory.food = tmp->inventory.life / LIFE_UNIT;
  tmp->inventory.linemate = 0;
  tmp->inventory.deraumere = 0;
  tmp->inventory.sibur = 0;
  tmp->inventory.mendiane = 0;
  tmp->inventory.phiras = 0;
  tmp->inventory.thystame = 0;
  tmp->lvl = 1;
}

static t_client_data		*init_node(t_server_data * const data,
					   t_client_data * node,
					   const int serv_fd)
{
  struct sockaddr_in		client_sin;
  socklen_t			client_sin_len;

  client_sin_len = sizeof(client_sin);
  if (memset(&client_sin, 0, client_sin_len) == NULL ||
      (node = malloc(sizeof(t_client_data))) == NULL ||
      (node->fd = accept(serv_fd, (struct sockaddr *)&client_sin,
			 &client_sin_len)) == FAILURE ||
      init_ring_buff(&node->buff_reader) == CRITERR ||
      init_ring_buff(&node->buff_writer) == CRITERR)
    return (NULL);
  node->team = NULL;
  node->eggs = NULL;
  node->nb_eggs = 0;
  node->tail = NULL;
  node->is_egg = false;
  node->dir = UP;
  node->pos_x = rand() % data->args_data.width;
  node->pos_y = rand() % data->args_data.height;
  init_client_inventory(node);
  init_action(node, data->args_data.freq);
  return (node);
}

t_client_data			*add_client(t_server_data * const data,
					    const int serv_fd)
{
  t_client_data			*node;

  node = NULL;
  if ((node = init_node(data, node, serv_fd)) == NULL)
    return (NULL);
  if (feed_tmp_str(&node->buff_writer, WELCOME) == CRITERR)
    return (NULL);
  if (data->c_data == NULL)
    return (node);
  node->tail = data->c_data->tail;
  data->c_data->tail = node;
  return (data->c_data);
}

t_client_data			*remove_client(t_client_data *c_data,
					       const int fd)
{
  t_client_data			*tmp;
  t_client_data			*prev;

  tmp = c_data;
  if (tmp && tmp->fd == fd)
    {
      free_buff(&tmp->buff_reader);
      return (c_data->tail);
    }
  if (!tmp)
    return (NULL);
  prev = tmp;
  while (tmp)
    {
      if (tmp->fd == fd)
	{
	  prev->tail = tmp->tail;
	  free_buff(&tmp->buff_reader);
	  return (c_data);
	}
      prev = tmp;
      tmp = tmp->tail;
    }
  return (c_data);
}
