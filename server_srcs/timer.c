/*
** timer.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server_srcs
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Mon Jun 26 17:23:36 2017 girard
** Last update Tue Jun 27 17:10:40 2017 girard
*/

#include <sys/time.h>
#include "server.h"

long			get_unow(const struct timeval time)
{
  return (time.tv_sec * 1000000 + time.tv_usec);
}

long			get_diff_time(const struct timeval start)
{
  struct timeval	end;

  gettimeofday(&end, NULL);
  return ((end.tv_sec * 1000000 + end.tv_usec) -
	  (start.tv_sec * 1000000 + start.tv_usec));
}
