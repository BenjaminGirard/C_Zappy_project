/*
** player_data_tools.c for  in /home/tetard/eptechY2/PSU/PSU_2016_zappy/server_srcs
**
** Made by girard
** Login   <benjamin.girard@epitech.eu>
**
** Started on  Mon Jun 26 12:35:32 2017 girard
** Last update Tue Jun 27 22:12:47 2017 sebastien vidal
*/

#include "server.h"

static void			init_action_spec(t_client_data * const c_data,
						 const int freq)
{
  c_data->action[FORWARD_ACTION].cmd_proto = "Forward" ;
  c_data->action[RIGHT_ACTION].cmd_proto = "Right";
  c_data->action[LEFT_ACTION].cmd_proto = "Left";
  c_data->action[LOOK_ACTION].cmd_proto = "Look";
  c_data->action[INVENTORY_ACTION].cmd_proto = "Inventory";
  c_data->action[BROADCAST_ACTION].cmd_proto = "Broadcast";
  c_data->action[CONNECT_NBR_ACTION].cmd_proto = "Connect_nbr";
  c_data->action[FORK_ACTION].cmd_proto = "Fork";
  c_data->action[EJECT_ACTION].cmd_proto = "Eject";
  c_data->action[TAKE_ACTION].cmd_proto = "Take";
  c_data->action[SET_ACTION].cmd_proto = "Set";
  c_data->action[INCANTATION_ACTION].cmd_proto = "Incantation";
  c_data->action[FORWARD_ACTION].cooldown_val = 7000000.0 / freq;
  c_data->action[RIGHT_ACTION].cooldown_val = 7000000.0 / freq;
  c_data->action[LEFT_ACTION].cooldown_val =  7000000.0 / freq;
  c_data->action[LOOK_ACTION].cooldown_val =  7000000.0 / freq;
  c_data->action[INVENTORY_ACTION].cooldown_val =  1000000.0 / freq;
  c_data->action[BROADCAST_ACTION].cooldown_val =  7000000.0 / freq;
  c_data->action[CONNECT_NBR_ACTION].cooldown_val = 0.0;
  c_data->action[FORK_ACTION].cooldown_val = 42000000.0 / freq;
  c_data->action[EJECT_ACTION].cooldown_val =  7000000.0 / freq;
  c_data->action[TAKE_ACTION].cooldown_val =  7000000.0 / freq;
  c_data->action[SET_ACTION].cooldown_val =  7000000.0 / freq;
  c_data->action[INCANTATION_ACTION].cooldown_val =  300000000.0 / freq;
}

static void			init_action_checkers(t_client_data *
						     const c_data)
{
  c_data->action[FORWARD_ACTION].check_cmd = cmd_check_forward;
  c_data->action[RIGHT_ACTION].check_cmd = cmd_check_right;
  c_data->action[LEFT_ACTION].check_cmd = cmd_check_left;
  c_data->action[LOOK_ACTION].check_cmd = cmd_check_look;
  c_data->action[INVENTORY_ACTION].check_cmd = cmd_check_inventory;
  c_data->action[BROADCAST_ACTION].check_cmd = cmd_check_broadcast;
  c_data->action[CONNECT_NBR_ACTION].check_cmd = cmd_check_connect_nbr;
  c_data->action[FORK_ACTION].check_cmd = cmd_check_fork;
  c_data->action[EJECT_ACTION].check_cmd = cmd_check_eject;
  c_data->action[TAKE_ACTION].check_cmd = cmd_check_take_object;
  c_data->action[SET_ACTION].check_cmd = cmd_check_set_object;
  c_data->action[INCANTATION_ACTION].check_cmd = cmd_check_incantation;
}

void				init_action(t_client_data * const c_data,
					    const int freq)
{
  int				i;

  i = -1;
  while (++i < DEFAULT_ACTION)
    {
      c_data->action[i].cooldown = 0.0;
      c_data->action[i].cmd = NULL;
    }
  c_data->action[FORWARD_ACTION].action_cmd = cmd_forward;
  c_data->action[RIGHT_ACTION].action_cmd = cmd_right;
  c_data->action[LEFT_ACTION].action_cmd = cmd_left;
  c_data->action[LOOK_ACTION].action_cmd = cmd_look;
  c_data->action[INVENTORY_ACTION].action_cmd = cmd_inventory;
  c_data->action[BROADCAST_ACTION].action_cmd = cmd_broadcast;
  c_data->action[CONNECT_NBR_ACTION].action_cmd = cmd_connect_nbr;
  c_data->action[FORK_ACTION].action_cmd = cmd_fork;
  c_data->action[EJECT_ACTION].action_cmd = cmd_eject;
  c_data->action[TAKE_ACTION].action_cmd = cmd_take_object;
  c_data->action[SET_ACTION].action_cmd = cmd_set_object;
  c_data->action[INCANTATION_ACTION].action_cmd = cmd_incantation;
  init_action_checkers(c_data);
  init_action_spec(c_data, freq);
}

t_client_data			*find_player_pos(t_client_data * const c_data,
						 const unsigned int x,
						 const unsigned int y)
{
  t_client_data			*tmp;

  tmp = c_data;
  while (tmp)
    {
      if (tmp->pos_x == x && tmp->pos_y == y)
        return (tmp);
      tmp = tmp->tail;
    }
  return (NULL);
}
