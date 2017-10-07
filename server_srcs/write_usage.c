/*
** write_usage.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server_srcs
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Thu Jun 22 15:51:36 2017 girard
** Last update Thu Jun 22 15:56:28 2017 girard
*/

#include <stdio.h>

int			write_usage(const int ret)
{
  printf("USAGE:\t./zappy_server -p port -x width -y height -n name1 name2 \
... -c clientsNb -f freq\n");
  printf("\tport\tis the port number\n");
  printf("\twidth\tis the width of the world\n");
  printf("\theight\tis the height of the world\n");
  printf("\tnameX\tis the name of the team X\n");
  printf("\tclientsNb\tis the number of authorized clients per team\n");
  printf("\tfreq\tis the reciprocal of time unit for execution of actions\n");
  return (ret);
}
