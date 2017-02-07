/*
** command.c for myirc in /home/hegedu_e/Projects/PSU_2014_myirc
** 
** Made by 
** Login   <hegedu_e@epitech.net>
** 
** Started on  Sun Apr 12 19:38:14 2015 
** Last update Sun Apr 12 20:32:56 2015 
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

void		clean_command(char *buf)
{
  while (*buf)
    {
      if (*buf == '\r' || *buf == '\n')
	*buf = '\0';
      ++buf;
    }
}

void		do_actions(t_ircserver *server, t_ircclient *client)
{
  char		cmd[BUF_SIZE];
  int		ret;
  int		i;

  if ((ret = receive(client->sd, cmd)) <= 1)
    client->running = ret;
  else if (ret > 1)
    {
      i = 0;
      clean_command(cmd);
      while (i < NB_SFUNCS && strncmp(cmd, server->funcs[i].cmd,
			      strlen(server->funcs[i].cmd)))
	i += 1;
      if (i < NB_SFUNCS)
	{
	  server->funcs[i].func(server, client, cmd + strlen(server->funcs[i].cmd) +
				(cmd[strlen(server->funcs[i].cmd)] == ' ' ? 1 : 0));
	}
    }
  else
    printf("Read error (socket id: %d)\n", client->sd);
}
