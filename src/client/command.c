/*
** command.c for myirc in /home/hegedu_e/rendu/PSU_2014_myirc
** 
** Made by 
** Login   <hegedu_e@epitech.net>
** 
** Started on  Sun Apr 12 19:39:13 2015 
** Last update Sun Apr 12 20:38:11 2015 
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "client.h"

void		serv_request(t_ircclient *client)
{
  char		buf[BUF_SIZE];
  int		ret;

  if ((ret = receive(client->sd, buf)) < 1)
    disconnect_client(client);
  buf[ret] = '\0';
  if (buf[0] != '[')
    printf("\033[33m");
  printf("\r%s\033[0m\n", buf);
  printf("[%s]: ", (client->nick ? client->nick : "-"));
  fflush(stdout);
}

int		read_prompt(t_ircclient *client, char *buf)
{
  int		ret;

  (void)client;
  if ((ret = read(0, buf, BUF_SIZE)))
    buf[ret - 1] = '\0';
  return (ret);
}

void		command(t_ircclient *client)
{
  static char	cmd[BUF_SIZE];
  char		*epured;
  int		i;

  if ((i = read_prompt(client, cmd)) <= 1)
    client->running = i;
  else if (cmd[0] == '/')
    {
      i = 0;
      epured = my_epur(cmd);
      while (i < NB_CFUNCS && strncmp(epured, client->funcs[i].cmd,
			      strlen(client->funcs[i].cmd)))
	i += 1;
      if (i < NB_CFUNCS)
	client->funcs[i].func(client, epured + strlen(client->funcs[i].cmd) +
			      (epured[strlen(client->funcs[i].cmd)] == ' ' ? 1 : 0));
      else
	printf("Command not found %s\n", epured);
      free(epured);
    }
  else
    cmessage(client, cmd);
  printf("[%s]: ", (client->nick ? client->nick : "-"));
  fflush(stdout);
}
