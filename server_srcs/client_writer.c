/*
** client_writer.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Fri Jun 30 12:56:26 2017 girard
** Last update Sat Jul  1 20:10:21 2017 bibzor
*/

#include <unistd.h>
#include <string.h>
#include "server.h"

int			write_data_to_client(t_client_data * const c_data,
					     const int fd)
{
  int			dp_ret;
  int			len;

  if ((dp_ret = write(fd, c_data->buff_writer.tmp,
		      strlen(c_data->buff_writer.tmp))) < 0)
    return (CRITERR);
  len = c_data->buff_writer.size_tmp - dp_ret;
  if (memmove(c_data->buff_writer.tmp,
	      &c_data->buff_writer.tmp[dp_ret],
	      len) == NULL)
    return (CRITERR);
  if (memset(&c_data->buff_writer.tmp[len],
	     0, dp_ret) == NULL)
    return (CRITERR);
  return (EXIT_SUCCESS);
}
