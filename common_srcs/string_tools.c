/*
** string_tools.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Thu Jun 22 12:42:01 2017 girard
** Last update Fri Jun 30 15:00:23 2017 girard
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "common.h"

char			*int_to_str(const int nb)
{
  char			*res;

  if ((res = malloc(sizeof(char) * (11))) == NULL)
    return (NULL);
  if (memset(res, 0 , 11) == NULL)
    return (NULL);
  if (sprintf(res, "%d", nb) < 0)
    return (NULL);
  return (res);
}

char			*epur_str(const char * const str)
{
  char			*res;
  int			idx;
  int			res_idx;

  idx = 0;
  res_idx = 0;
  if ((res = malloc(sizeof(char) * (strlen(str) + 1))) == NULL)
    return (NULL);
  while (str[idx] == ' ' || str[idx] == '\t')
    ++idx;
  while (str[idx])
    {
      while (str[idx] && str[idx] != ' ' && str[idx] != '\t')
        res[res_idx++] = str[idx++];
      while (str[idx] == ' ' || str[idx] == '\t')
        idx++;
      if (str[idx])
        res[res_idx++] = ' ';
    }
  res[res_idx] = '\0';
  return (res);
}

char				*get_cmd_arg(const char * const line,
					     const unsigned int size_min)
{
  if (strlen(line) < size_min)
    return (NULL);
  return (strdup(&line[size_min - 1]));
}

bool				is_token_in_string(const char * const str,
						   const char token)
{
  int				i;

  i = -1;
  while (str[++i])
    if (str[i] == token)
      return (true);
  return (false);
}
