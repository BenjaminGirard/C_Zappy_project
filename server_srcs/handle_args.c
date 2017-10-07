/*
** handle_args.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Thu Jun 22 12:38:45 2017 girard
** Last update Sat Jul  1 20:00:47 2017 bibzor
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

static const t_arg_action	ARG_ACTION[] =
  {
    {"-p", get_arg_port},
    {"-x", get_arg_width},
    {"-y", get_arg_height},
    {"-n", get_arg_names},
    {"-c", get_arg_clientnb},
    {"-f", get_arg_freq},
  };

int				get_arg_freq(const char * const av[],
					     t_args * const data_args)
{
  if ((!av[1] || is_an_option(av[1]) || (av[2] && !is_an_option(av[2]))) ||
      ((data_args->freq = check_int(av[1])) < 2 || data_args->freq > 10000))
    {
      printf("\n-f option only accepts integer values\
 between 2 and 10000\n\n");
      return (CRITERR);
    }
  return (EXIT_SUCCESS);
}

bool				is_an_option(const char * const arg)
{
  int				idx;

  idx = 0;
  while (idx < (int)(sizeof(ARG_ACTION) / sizeof(t_arg_action)))
    {
      if (strcmp(arg, ARG_ACTION[idx].option) == 0)
	return (true);
      ++idx;
    }
  return (false);
}

static int			init_default_args_values(t_args *
							 const args_data)
{
  args_data->port = 4242;
  args_data->width = 10;
  args_data->height = 10;
  args_data->teams = NULL;
  args_data->nb_clients = 3;
  args_data->freq = 100;
  return (EXIT_SUCCESS);
}

static int			check_args_validity(const t_args
						    * const args_data)
{
  if (args_data->port == ARGS_ERR ||
      args_data->width == ARGS_ERR ||
      args_data->height == ARGS_ERR ||
      args_data->nb_clients == ARGS_ERR ||
      args_data->freq == ARGS_ERR)
    return (CRITERR);
  return (EXIT_SUCCESS);
}

int				handle_args(const char * const av[],
					    t_args * const args_data)
{
  int				idx;
  int				opidx;

  idx = 1;
  init_default_args_values(args_data);
  if (av[idx] && !is_an_option(av[idx]))
    return (write_usage(CRITERR));
  while (av[idx])
    {
      opidx = -1;
      while (++opidx < (int)(sizeof(ARG_ACTION) / sizeof(t_arg_action)))
	if (strcmp(av[idx], ARG_ACTION[opidx].option) == 0)
	  {
	    if (ARG_ACTION[opidx].arg_action(&av[idx], args_data) == CRITERR)
	      return (write_usage(CRITERR));
	    break ;
	  }
      ++idx;
      while (av[idx] && !is_an_option(av[idx]))
	++idx;
    }
  if (args_data->teams == NULL && init_default_teams(args_data) == CRITERR)
    return (CRITERR);
  return (check_args_validity(args_data));
}
