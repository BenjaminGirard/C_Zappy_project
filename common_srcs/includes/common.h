/*
** common.h for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Thu Jun 22 12:38:30 2017 girard
** Last update Sat Jul  1 20:07:01 2017 bibzor
*/

#ifndef COMMON_H_
# define COMMON_H_

# include <stdbool.h>
# include <netinet/in.h>

static const int		CRITERR = 84;
static const int		FAILURE = -1;

static const char		* const CRLF = "\r\n";

static const char		* const KO = "ko\n";
static const char		* const OK = "ok\n";
static const char		* const DEAD = "dead\n";
static const char		* const WELCOME = "WELCOME\n";

typedef struct			s_data_con
{
  int				fd;
  struct sockaddr_in		s_in;
  socklen_t			s_in_size;
}				t_data_con;

int				init_socket(void);

int				close_fd(const int fd,
					 const int ret);

char				*get_cmd_arg(const char * const line,
					     const unsigned int size_min);

char				*int_to_str(const int nb);
char				*epur_str(const char * const str);
bool				is_token_in_string(const char * const str,
						   const char token);

int				check_int(const char * const str);

#endif /* !COMMON_H_ */
