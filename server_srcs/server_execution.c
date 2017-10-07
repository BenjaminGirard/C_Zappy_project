/*
** server_execution.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Thu Jun 22 12:41:34 2017 girard
** Last update Sun Jul  2 19:30:05 2017 de Ganay Renaud
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "server.h"

static int		handle_isset(t_server_data * const data,
				     const bool read)
{
  t_client_data		*tmp;

  if (read && FD_ISSET(data->dc.fd, &data->select_data.fd_read))
    if ((data->c_data = add_client(data, data->dc.fd)) == NULL)
      return (CRITERR);
  tmp = data->c_data;
  while (tmp)
    {
      if (read && FD_ISSET(tmp->fd, &data->select_data.fd_read))
	if (read_data_from_client(data, tmp->fd) == CRITERR)
	  return (CRITERR);
      if (!read && FD_ISSET(tmp->fd, &data->select_data.fd_write))
	if (write_data_to_client(tmp, tmp->fd) == CRITERR)
	  return (CRITERR);
      tmp = tmp->tail;
    }
  return (EXIT_SUCCESS);
}

static int		init_loop_exec(t_server_data * const data)
{
  int			fd_max;
  t_client_data		*tmp;

  data->select_data.tv.tv_sec = 0;
  data->select_data.tv.tv_usec = USEC_RATIO / data->args_data.freq;
  FD_ZERO(&data->select_data.fd_read);
  FD_ZERO(&data->select_data.fd_write);
  FD_SET(data->dc.fd, &data->select_data.fd_read);
  fd_max = data->dc.fd;
  tmp = data->c_data;
  while (tmp != NULL)
    {
      FD_SET(tmp->fd, &data->select_data.fd_read);
      if (tmp->buff_writer.tmp != NULL && tmp->buff_writer.tmp[0] != 0)
	FD_SET(tmp->fd, &data->select_data.fd_write);
      fd_max = ((fd_max > tmp->fd) ? (fd_max) : (tmp->fd));
      tmp = tmp->tail;
    }
  return (fd_max);
}

int			server_execution(t_server_data * const data)
{
  int			fd_max;

  while (true)
    {
      fd_max = init_loop_exec(data);
      if (select(fd_max + 1, &data->select_data.fd_read,
		 &data->select_data.fd_write, NULL,
		 &data->select_data.tv) == FAILURE)
	return (CRITERR);
      if (update_data(data) == CRITERR ||
	  handle_isset(data, true) == CRITERR ||
	  handle_clients_cmd(data) == CRITERR ||
	  handle_isset(data, false) == CRITERR)
	return (CRITERR);
    }
  return (EXIT_SUCCESS);
}
