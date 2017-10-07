/*
** args_functions.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server_srcs
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Thu Jun 22 14:21:29 2017 girard
** Last update Sat Jul  1 19:49:04 2017 bibzor
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

int				get_arg_port(const char * const av[],
					     t_args * const data_args)
{
  if ((!av[1] || is_an_option(av[1]) || (av[2] && !is_an_option(av[2]))) ||
      (data_args->port = check_int(av[1])) < 0)
    {
      printf("\nn-p option only accepts valid ports\n\n");
      return (CRITERR);
    }
  return (EXIT_SUCCESS);
}

int				get_arg_width(const char * const av[],
					     t_args * const data_args)
{
  if ((!av[1] || is_an_option(av[1]) || (av[2] && !is_an_option(av[2]))) ||
      ((data_args->width = check_int(av[1])) < 10 || data_args->width > 30))
    {
      printf("\n-x option only accepts integer values between 10 and 30\n\n");
      return (CRITERR);
    }
  return (EXIT_SUCCESS);
}

int				get_arg_height(const char * const av[],
					     t_args * const data_args)
{
  if ((!av[1] || is_an_option(av[1]) || (av[2] && !is_an_option(av[2]))) ||
      (data_args->height = check_int(av[1])) < 10 || data_args->height > 30)
    {
      printf("\n-y option only accepts integer values between 10 and 30\n\n");
      return (CRITERR);
    }
  return (EXIT_SUCCESS);
}

int				get_arg_clientnb(const char * const av[],
					     t_args * const data_args)
{
  if ((!av[1] || is_an_option(av[1]) || (av[2] && !is_an_option(av[2]))) ||
      (data_args->nb_clients = check_int(av[1])) < 1)
    {
      printf("\n-c option only accepts integer values \
greater or equal to 1\n\n");
      return (CRITERR);
    }
  return (EXIT_SUCCESS);
}
