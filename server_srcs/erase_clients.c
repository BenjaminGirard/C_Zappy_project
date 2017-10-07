/*
** erase_clients.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Wed Jun 28 14:14:41 2017 girard
** Last update Sun Jul  2 14:04:27 2017 sebastien vidal
*/

#include "server.h"

void			erase_clients(t_client_data * c_data)
{
  if (c_data == NULL)
    return ;
  erase_clients(c_data->tail);
  if (close_fd(c_data->fd, EXIT_SUCCESS) == CRITERR)
    exit(CRITERR);
  c_data = remove_client(c_data, c_data->fd);
}
