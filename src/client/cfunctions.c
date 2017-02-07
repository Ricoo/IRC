/*
** cfunctions.c for myirc in /home/terran_j/rendu/PSU_2014_myirc
**
** Made by terran_j
** Login   <terran_j@epitech.net>
**
** Started on  Mon Apr  6 18:30:44 2015 terran_j
** Last update Sun Apr 12 21:50:03 2015 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "client.h"

int		cusers(t_ircclient *client, char *cmd)
{
  char		buf[BUF_SIZE];

  (void) cmd;
  if (client->sd == -1)
    return (printf("\033[31mYou are not connected to a server yet\033[0m\n"));
  sprintf(buf, "USERS\r\n");
  request(client->sd, buf);
  if (receive(client->sd, buf) < 0)
    return (printf("\033[31mTimeout.\033[0m\n"));
  if (!strncmp(buf, "393", 3))
    printf("\033[33mUsers on this server: %s\033[0m\n", buf + 4);
  return (0);
}

int		cmsg(t_ircclient *client, char *cmd)
{
  char		buf[BUF_SIZE];

  if (client->sd == -1)
    return (printf("\033[31mYou are not connected to a server yet\033[0m\n"));
  sprintf(buf, "PRIVMSG %s\r\n", cmd);
  request(client->sd, buf);
  return (0);
}

int		csend_file(t_ircclient *client, char *cmd)
{
  char		buf[BUF_SIZE];

  if (client->sd == -1)
    return (printf("\033[31mYou are not connected to a server yet\033[0m\n"));
  sprintf(buf, "SEND %s\r\n", cmd);
  request(client->sd, buf);
  receive(client->sd, buf);
  if (!strncmp(buf, "", 3)) //
    printf("%s: file sent\n", client->nick);
  else
    printf("%s: error, cannot sent file\n", client->nick);
  return (0);
}

int		caccept_file(t_ircclient *client, char *cmd)
{
  char		buf[BUF_SIZE];

  if (client->sd == -1)
    return (printf("\033[31mYou are not connected to a server yet\033[0m\n"));
  sprintf(buf, "ACCEPT %s\r\n", cmd);
  request(client->sd, buf);
  receive(client->sd, buf);
  if (!strncmp(buf, "", 3)) //
    printf("%s: files accepted\n", client->nick);
  else
    printf("%s: error, cannot accept files\n", client->nick);
  return (0);
}

int		cmessage(t_ircclient *client, char *cmd)
{
  char		buf[BUF_SIZE];

  if (client->sd == -1)
    return (printf("\033[31mYou are not connected to a server yet\033[0m\n"));
  sprintf(buf, "PRIVMSG $* %s\r\n", cmd);
  request(client->sd, buf);
  if (receive(client->sd, buf) < 0)
    return (0);
  printf("\033[31mError: cannot send message\033[0m\n");
  return (1);
}
