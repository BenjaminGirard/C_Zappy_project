/*
** ring_buffer.c for zappy in /home/bibzor/rendu/NETWORK/ring_buffer
**
** Made by bibzor
** Login   <sebastien.vidal@epitech.eu>
**
** Started on  Thu Jun 22 20:49:14 2017 bibzor
** Last update Sun Jun 25 15:37:31 2017 girard
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "ring_buffer.h"

void			free_buff(t_ring_buff * const buff_data)
{
  if (buff_data->tmp)
    free(buff_data->tmp);
}

int			init_ring_buff(t_ring_buff * const buff_data)
{
  if (memset(buff_data, 0, sizeof(t_ring_buff)) == NULL)
    return (CRITERR);
  if ((buff_data->tmp = malloc(sizeof(char) * BUFF_SIZE)) == NULL)
    return (CRITERR);
  if (memset(buff_data->tmp, 0, BUFF_SIZE) == NULL)
    return (CRITERR);
  buff_data->size_tmp = BUFF_SIZE;
  return (EXIT_SUCCESS);
}

static int		feed_tmp(t_ring_buff * const buff_data)
{
  if (strlen(buff_data->tmp) + strlen(buff_data->buff) >= buff_data->size_tmp)
    {
      if ((buff_data->tmp = realloc(buff_data->tmp,
				    buff_data->size_tmp + BUFF_SIZE)) == NULL)
	return (CRITERR);
      if (memset(&buff_data->tmp[buff_data->size_tmp], 0, BUFF_SIZE)
      	  == NULL)
      	return (CRITERR);
      buff_data->size_tmp += BUFF_SIZE;
    }
  if (memcpy(&buff_data->tmp[strlen(buff_data->tmp)], buff_data->buff,
	     strlen(buff_data->buff)) == NULL)
    return (CRITERR);
  return (EXIT_SUCCESS);
}

int			read_data(t_ring_buff * const buff_data,
				  const int fd)
{
  int			read_ret;

  while ((read_ret = read(fd, buff_data->buff, BUFF_SIZE - 1)))
    {
      if (read_ret == SYS_ERR ||
	  feed_tmp(buff_data) == CRITERR ||
	  memset(buff_data->buff, 0, BUFF_SIZE) == NULL)
	return (CRITERR);
      if (read_ret != BUFF_SIZE - 1)
	break ;
    }
  if (read_ret == 0)
    return (CRITERR);
  return (EXIT_SUCCESS);
}

char			*read_cmd(t_ring_buff * const buff_data)
{
  int			idx;
  int			len;
  char			*cmd;

  cmd = NULL;
  idx = 0;
  while (buff_data->tmp[idx] && buff_data->tmp[idx] != '\n')
    ++idx;
  if (buff_data->tmp[idx] != '\n')
    return (default_return());
  if ((cmd = malloc(sizeof(char) * (idx + 1))) == NULL ||
      memcpy(cmd, buff_data->tmp, idx + 1) == NULL)
    return (NULL);
  cmd[idx] = 0;
  len = strlen(buff_data->tmp) - idx;
  if (memmove(buff_data->tmp, &buff_data->tmp[idx + 1],
	      len) == NULL)
    return (NULL);
  if (memset(&buff_data->tmp[len], 0, idx)
      == NULL)
    return (NULL);
  return (cmd);
}
