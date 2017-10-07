/*
** ring_buffer.h for zappy in /home/bibzor/rendu/NETWORK/ring_buffer
**
** Made by bibzor
** Login   <sebastien.vidal@epitech.eu>
**
** Started on  Thu Jun 22 20:45:53 2017 bibzor
** Last update Sun Jul  2 18:04:42 2017 sebastien vidal
*/

#ifndef RING_BUFFER_H
# define RING_BUFFER_H

# include "common.h"

# define BUFF_SIZE	4096

static const int	SYS_ERR = -1;

typedef struct		s_ring_buff
{
  char			buff[BUFF_SIZE];
  char			*tmp;
  unsigned int		size_tmp;
}			t_ring_buff;

int			feed_tmp_str(t_ring_buff * const buff,
				     const char * const str);

int			init_ring_buff(t_ring_buff * const buff_data);

int			feed_cmd(t_ring_buff * const buff_data);
int			read_data(t_ring_buff * const buff_data,
				  const int fd);
char			*read_cmd(t_ring_buff * const buff_data);
void			free_buff(t_ring_buff * const buff_data);

char			*default_return(void);

#endif /* RING_BUFFER_H */
