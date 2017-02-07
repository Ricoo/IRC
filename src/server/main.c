/*
** main.c<server> for myirc in /home/hegedu_e/rendu/PSU_2014_myirc
**
** Made by
** Login   <hegedu_e@epitech.net>
**
** Started on  Mon Apr  6 14:24:40 2015
** Last update Sun Apr 12 20:13:52 2015 
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

int		main(int ac, char **av)
{
  t_ircserver	server;
  int		port;

  if (ac > 1)
    port = atoi(av[1]);
  else
    port = atoi(DEFAULT_PORT);
  if (init_server(&server, port))
    {
      printf("Could not bind to port %d\n", port);
      return (EXIT_FAILURE);
    }
  select_server(&server);
  return (EXIT_SUCCESS);
}
