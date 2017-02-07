/*
** main.c<client> for myirc in /home/hegedu_e/rendu/PSU_2014_myirc
**
** Made by
** Login   <hegedu_e@epitech.net>
**
** Started on  Mon Apr  6 14:24:35 2015
** Last update Sun Apr 12 20:03:24 2015 
*/

#include <stdlib.h>
#include <time.h>
#include "client.h"

int		main()
{
  t_ircclient	client;
  struct timeval to;

  to.tv_sec = 2;
  to.tv_usec = 0;
  client.running = 1;
  init_client(&client);
  select_client(&client, &to);
  delete_cfuncs(&client);
  return (EXIT_SUCCESS);
}
