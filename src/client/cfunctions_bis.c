/*
** cfunctions_bis.c for myirc in /home/hegedu_e/rendu/PSU_2014_myirc
** 
** Made by 
** Login   <hegedu_e@epitech.net>
** 
** Started on  Sun Apr 12 19:41:22 2015 
** Last update Sun Apr 12 22:06:14 2015 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "client.h"

int		cconnect(t_ircclient *client, char *cmd)
{
  char		*address;
  char		*port;

  port = NULL;
  address = strtok(cmd, ":");
  if (!(port = strtok(NULL, ":")))
    port = DEFAULT_PORT;
  if (connect_client(client, address, atoi(port)) == -1)
    {
      client->sd = -1;
      return (printf("\033[31mCould not connect to %s at port %s\033[0m\n",
		     address, port));
    }
  else
    printf("\033[32mSuccessfully connected to %s\033[0m\n", address);
  return (0);
}

int		cnick(t_ircclient *client, char *cmd)
{
  char		buf[BUF_SIZE];

  if (client->sd == -1)
    return (printf("\033[31mYou are not connected to a server yet\033[0m\n"));
  sprintf(buf, "NICK %s\r\n", cmd);
  request(client->sd, buf);
  if (receive(client->sd, buf) < 0)
    {
      if (client->nick)
	{
	  free(client->nick);
	  printf("\033[32mickname successfully changed\033[0m\n");
	}
      else
	printf("\033[32mwelcome %s\033[0m\n", cmd);
      client->nick = strdup(cmd);      
    }
  else
    printf("Error, impossible to set this nickname\n");
  return (0);
}

int		clist(t_ircclient *client, char *cmd)
{
  char		buf[BUF_SIZE];

  if (client->sd == -1)
    return (printf("You are not connected to a server yet\n"));
  if (cmd[0] == '\0')
    sprintf(buf, "LIST\r\n");
  else
    sprintf(buf, "LIST %s\r\n", cmd);
  request(client->sd, buf);
  if (receive(client->sd, buf) < 0)
    return (printf("\033[31mTimeout.\033[0m\n"));
  if (!strncmp(buf, "322", 3))
    printf("\033[33mChannels available: %s\033[0m\n", buf + 4);
  return (0);
}

int		cjoin(t_ircclient *client, char *cmd)
{
  char		buf[BUF_SIZE];

  if (client->sd == -1)
    return (printf("\033[31mYou are not connected to a server yet\033[0m\n"));
  sprintf(buf, "JOIN %s\r\n", cmd);
  request(client->sd, buf);
  if (receive(client->sd, buf) < 0)
    {
      client->channel = strdup(cmd);
      return (printf("\033[32mchannel %s joined.\033[0m\n", cmd));
    }
  else
    printf("\033[31mError, impossible to join %s\033[0m\n", cmd);
  return (0);
}

int		cpart(t_ircclient *client, char *cmd)
{
  char		buf[BUF_SIZE];

  if (client->sd == -1)
    return (printf("\033[31mYou are not connected to a server yet\033[0m\n"));
  sprintf(buf, "PART %s\r\n", cmd);
  request(client->sd, buf);
  if (receive(client->sd, buf) < 0)
    return (printf("\033[32mchannel %s left\033[0m\n", cmd));
  else
    printf("\033[31mError : %s: you are not on this channel\033[0m\n", cmd);
  return (0);
}
