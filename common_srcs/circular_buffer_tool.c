/*
** circular_buffer_tool.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server_srcs
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Sat Jun 24 14:19:14 2017 girard
** Last update Sun Jul  2 18:18:29 2017 sebastien vidal
*/

#include <stdlib.h>
#include <string.h>
#include "ring_buffer.h"

int			feed_tmp_str(t_ring_buff * const buff,
				     const char * const str)
{
  int			size_rea;

  if (strlen(buff->tmp) + strlen(str) < buff->size_tmp)
    {
      if ((buff->tmp = strcat(buff->tmp, str)) == NULL)
	return (CRITERR);
      return (EXIT_SUCCESS);
    }
  size_rea = buff->size_tmp + (BUFF_SIZE *
			       ((strlen(str) / BUFF_SIZE) + 1));
  if ((buff->tmp = realloc(buff->tmp, sizeof(char) *
			   size_rea)) == NULL)
    return (CRITERR);
  if (memset(&buff->tmp[strlen(buff->tmp)], 0, size_rea - strlen(buff->tmp))
      == NULL)
    return (CRITERR);
  if ((buff->tmp = strcat(buff->tmp, str)) == NULL)
    return (CRITERR);
  buff->size_tmp = size_rea;
  return (EXIT_SUCCESS);
}

char			*default_return(void)
{
  char			*res;

  if ((res = malloc(sizeof(char) * (1))) == NULL)
    return (NULL);
  res[0] = 0;
  return (res);
}
