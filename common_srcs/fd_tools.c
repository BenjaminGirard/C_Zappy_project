/*
** fd_tools.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Thu Jun 22 12:38:38 2017 girard
** Last update Sat Jul  1 19:45:22 2017 bibzor
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

int				close_fd(const int fd, const int ret)
{
  if (close(fd) == FAILURE)
    return (CRITERR);
  return (ret);
}
