/*
** server.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Thu Jun 22 12:41:16 2017 girard
** Last update Sat Jul  1 15:59:52 2017 girard
*/

#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

static const t_server_data	*data_signal;

static void			free_data(t_server_data * const data)
{
  free(data->map);
  free(data->args_data.teams);
  erase_clients(data->c_data);
}

static void			signal_handler(int sig)
{
  (void)sig;
  printf("%s", "see you soon\n");
  free_data((t_server_data *)data_signal);
  exit(close_fd(data_signal->dc.fd, EXIT_SUCCESS));
}

int				main(const int ac, const char * const av[])
{
  t_server_data			data;

  (void)ac;
  srand(time(NULL));
  if (handle_args(av, &data.args_data) == CRITERR)
    return (CRITERR);
  if (init_server_connexion(&data) == CRITERR)
    return (CRITERR);
  data_signal = &data;
  if (signal(SIGINT, signal_handler) == SIG_ERR)
    return (CRITERR);
  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
    return (CRITERR);
  printf("Port : %d\n", data.args_data.port);
  if (server_execution(&data) == CRITERR)
    return (close_fd(data.dc.fd, CRITERR));
  free_data(&data);
  return (close_fd(data.dc.fd, EXIT_SUCCESS));
}
