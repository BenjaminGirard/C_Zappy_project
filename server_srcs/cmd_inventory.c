/*
** cmd_forward.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server_srcs
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Sat Jun 24 14:09:49 2017 girard
** Last update Sun Jul  2 17:35:39 2017 sebastien vidal
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

static int			print_f_l_d(t_client_data *
					    const client)
{
  char				*tmp;

  if (feed_tmp_str(&client->buff_writer, "[ food ") == CRITERR ||
      (tmp = int_to_str((int)client->inventory.food)) == NULL ||
      feed_tmp_str(&client->buff_writer, tmp) == CRITERR)
    return (CRITERR);
  if (tmp)
    free(tmp);
  if (feed_tmp_str(&client->buff_writer, ", linemate ") == CRITERR ||
      (tmp = int_to_str((int)client->inventory.linemate)) == NULL ||
      feed_tmp_str(&client->buff_writer, tmp) == CRITERR)
    return (CRITERR);
  if (tmp)
    free(tmp);
  if (feed_tmp_str(&client->buff_writer, ", deraumere ") == CRITERR ||
      (tmp = int_to_str((int)client->inventory.deraumere)) == NULL ||
      feed_tmp_str(&client->buff_writer, tmp) == CRITERR)
    return (CRITERR);
  if (tmp)
    free(tmp);
  return (EXIT_SUCCESS);
}

static int			print_s_m_p(t_client_data *
					    const client)
{
  char				*tmp;

  if (feed_tmp_str(&client->buff_writer, ", sibur ") == CRITERR ||
      (tmp = int_to_str((int)client->inventory.sibur)) == NULL ||
      feed_tmp_str(&client->buff_writer, tmp) == CRITERR)
    return (CRITERR);
  if (tmp)
    free(tmp);
  if (feed_tmp_str(&client->buff_writer, ", mendiane ") == CRITERR ||
      (tmp = int_to_str((int)client->inventory.mendiane)) == NULL ||
      feed_tmp_str(&client->buff_writer, tmp) == CRITERR)
    return (CRITERR);
  if (tmp)
    free(tmp);
  if (feed_tmp_str(&client->buff_writer, ", phiras ") == CRITERR ||
      (tmp = int_to_str((int)client->inventory.phiras)) == NULL ||
      feed_tmp_str(&client->buff_writer, tmp) == CRITERR)
    return (CRITERR);
  if (tmp)
    free(tmp);
  return (EXIT_SUCCESS);
}

int				cmd_inventory(t_server_data * const data,
					      const int fd,
					      const char * const cmd)
{
  t_client_data			*tmp;
  char				*nb_t;

  (void)cmd;
  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  if (print_f_l_d(tmp) == CRITERR ||
      print_s_m_p(tmp) == CRITERR)
    return (CRITERR);
  if (feed_tmp_str(&tmp->buff_writer, ", thystame ") == CRITERR ||
      (nb_t = int_to_str(tmp->inventory.thystame)) == NULL ||
      feed_tmp_str(&tmp->buff_writer, nb_t) == CRITERR ||
      feed_tmp_str(&tmp->buff_writer, " ]\n") == CRITERR)
    return (CRITERR);
  return (EXIT_SUCCESS);
}

int				cmd_check_inventory(t_server_data *
						    const data,
						    const int fd,
						    const char * const cmd)
{
  t_client_data			*tmp;

  if ((tmp = find_client_fd(data->c_data, fd)) == NULL)
    return (CRITERR);
  if (strlen(cmd) > strlen("Inventory"))
    return (CRITERR);
  return (EXIT_SUCCESS);
}
