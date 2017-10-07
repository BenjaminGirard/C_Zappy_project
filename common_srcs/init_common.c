/*
** init_common.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Thu Jun 22 12:38:52 2017 girard
** Last update Thu Jun 22 12:39:53 2017 girard
*/

#include "netdb.h"
#include "common.h"

int				init_socket(void)
{
  struct protoent		*pe;

  pe = getprotobyname("TCP");
  if (!pe)
    return (FAILURE);
  return (socket(PF_INET, SOCK_STREAM, pe->p_proto));
}
