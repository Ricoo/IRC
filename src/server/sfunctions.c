/*
** sfunctions.c for myirc in /home/terran_j/rendu/PSU_2014_myirc/src/server
**
** Made by terran_j
** Login   <terran_j@epitech.net>
**
** Started on  Tue Apr  7 17:40:07 2015 terran_j
** Last update Sun Apr 12 20:49:01 2015 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

void		smsg(t_ircserver *server, t_ircclient *client, char *cmd)
{
  t_clientlist	*tmp;
  char		buf[BUF_SIZE];

  if (!client->channel)
      request(client->sd, "441 you are not in a channel");
  tmp = server->client_list;
  if (!strncmp(cmd, "$*", 2))
    {
      sprintf(buf, "[%s]: %s", client->nick, cmd + 3);
      sbroadcast(server, client, buf);
    }
  else
    while (tmp)
      {
	if (tmp->client != client &&
	    !strncmp(tmp->client->nick, cmd, strlen(tmp->client->nick)))
	  {
	    printf("[INFO] %s whispered %s\n", client->nick, tmp->client->nick);
	    sprintf(buf, "[%s](whisper): %s", client->nick,
		    cmd + strlen(tmp->client->nick));
  	    request(tmp->client->sd, buf);
	  }
	tmp = tmp->next;
      }
}

void		ssend_file(t_ircserver *server, t_ircclient *client, char *cmd)
{
  (void)server;
  (void)client;
  (void)cmd;
}

void		saccept_file(t_ircserver *server, t_ircclient *client, char *cmd)
{
  (void)server;
  (void)client;
  (void)cmd;
}

void		sbroadcast(t_ircserver *server, t_ircclient *client, char *cmd)
{
  t_clientlist	*tmp;

  printf("[INFO] %s: sending message to channel %s\n",
	 client->nick, client->channel);
  tmp = server->client_list;
  while (tmp)
    {
      if (tmp->client != client &&
	  client->channel && tmp->client->channel &&
	  !strcmp(tmp->client->channel, client->channel))
	request(tmp->client->sd, cmd);
      tmp = tmp->next;
    }
}
