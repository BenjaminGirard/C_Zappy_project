/*
** timer.h for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server_srcs
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Tue Jun 27 17:04:00 2017 girard
** Last update Sat Jul  1 20:05:12 2017 bibzor
*/

#ifndef TIMER_H_
# define TIMER_H_

# include <sys/time.h>
# include <stdbool.h>

static const unsigned int	USEC_RATIO = 1000000;

long				get_unow(const struct timeval time);
long				get_diff_time(const struct timeval start);

#endif /* !TIMER_H_ */
