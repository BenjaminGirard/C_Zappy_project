/*
** check_int.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Thu Jun 22 16:25:14 2017 girard
** Last update Sat Jul  1 19:40:52 2017 bibzor
*/

#include <stdlib.h>

int			check_int(const char * const str)
{
  int			i;

  i = -1;
  while (str[++i])
    if (str[i] < '0' || str[i] > '9')
      return (-1);
  return (atoi(str));
}
