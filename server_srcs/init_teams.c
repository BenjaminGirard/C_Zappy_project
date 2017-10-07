/*
** init_teams.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Wed Jun 28 16:40:40 2017 girard
** Last update Wed Jun 28 19:32:48 2017 girard
*/

#include <string.h>
#include "server.h"

int				init_default_teams(t_args * const data_args)
{
  unsigned int			idx;

  data_args->nb_teams = DEFAULT_NB_PLAYERS;
  if ((data_args->teams = malloc(sizeof(t_team) * (data_args->nb_teams)))
      == NULL)
    return (CRITERR);
  idx = 0;
  while (idx < data_args->nb_teams)
    {
      data_args->teams[idx].name = DEF_TEAM_NAME[idx];
      data_args->teams[idx].nb_members = 0;
      ++idx;
    }
  return (EXIT_SUCCESS);
}

static bool			team_exists(const t_team * const teams,
					    const char * const str)
{
  int				i;

  i = -1;
  while (teams[++i].name)
    if (strcmp(teams[i].name, str) == 0)
      return (true);
  return (false);
}

int				get_arg_names(const char * const av[],
					     t_args * const data_args)
{
  int				size_struct;
  int				idx;

  size_struct = 1;
  while (av[size_struct] && !is_an_option(av[1]))
    ++size_struct;
  if (size_struct == 1)
    return (init_default_teams(data_args));
  data_args->nb_teams = size_struct - 1;
  if ((data_args->teams = malloc(sizeof(t_team) * (data_args->nb_teams)))
      == NULL)
    return (CRITERR);
  if (!memset(data_args->teams, 0, sizeof(t_team) * (data_args->nb_teams)))
    return (CRITERR);
  idx = -1;
  while (++idx < (int)data_args->nb_teams)
    {
      if (team_exists(data_args->teams, av[idx + 1]))
	return (CRITERR);
      data_args->teams[idx].name = av[idx + 1];
      data_args->teams[idx].nb_members = 0;
    }
  return (EXIT_SUCCESS);
}
