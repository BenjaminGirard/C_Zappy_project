/*
** init_server_tools.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Thu Jun 22 12:38:59 2017 girard
** Last update Sun Jul  2 21:06:59 2017 nicolas dejean
*/

#include <sys/time.h>
#include <netdb.h>
#include <string.h>
#include "server.h"

static int			init_bind(const int port,
                                          t_data_con *dc)
{
  dc->s_in.sin_family = AF_INET;
  dc->s_in.sin_port = htons(port);
  dc->s_in.sin_addr.s_addr = INADDR_ANY;
  return (bind(dc->fd,
               (const struct sockaddr *)&(dc->s_in),
                sizeof(dc->s_in)));
}

int				init_accept(t_data_con *dc)
{
  return (accept(dc->fd, (struct sockaddr *)(&dc->s_in), &(dc->s_in_size)));
}

static int			init_server_map(t_server_data * const data)
{
  int				i;

  i = 0;
  if ((data->map =
       malloc(sizeof(t_ressources) *
	      (data->args_data.width * data->args_data.height))) == NULL)
    return (CRITERR);
  while (i < data->args_data.width * data->args_data.height)
    {
      data->map[i].food = rand() % 50;
      data->map[i].linemate = rand() % 3;
      data->map[i].deraumere = rand() % 3;
      data->map[i].sibur = rand() % 3;
      data->map[i].mendiane = rand() % 3;
      data->map[i].phiras = rand() % 3;
      data->map[i].thystame = rand() % 3;
      ++i;
    }
  return (EXIT_SUCCESS);
}

static int			init_server_data(t_server_data * const data)
{
  data->c_data = NULL;
  data->graphic_cooldown = USEC_RATIO / data->args_data.freq;
  gettimeofday(&data->unow, NULL);
  data->dc.s_in_size = sizeof(struct sockaddr);
  FD_ZERO(&data->select_data.fd_read);
  FD_ZERO(&data->select_data.fd_write);
  data->select_data.tv.tv_sec = 0;
  data->select_data.tv.tv_usec = USEC_RATIO / data->args_data.freq;
  if (memset(&data->dc.s_in, 0, data->dc.s_in_size) == NULL)
    return (CRITERR);
  if ((data->dc.fd = init_socket()) == FAILURE)
    return (CRITERR);
  if (init_server_map(data) == CRITERR)
    return (CRITERR);
  return (EXIT_SUCCESS);
}

int				init_server_connexion(t_server_data *
						      const data)
{
  if (init_server_data(data) == CRITERR)
    return (CRITERR);
  if (init_bind(data->args_data.port, &data->dc) == FAILURE)
    return (close_fd(data->dc.fd, CRITERR));
  if (listen(data->dc.fd, 42) == FAILURE)
    return (close_fd(data->dc.fd, CRITERR));
  return (EXIT_SUCCESS);
}
