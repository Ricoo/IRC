/*
** sfunctions_bis.c for myirc in /home/hegedu_e/Projects/PSU_2014_myirc
** 
** Made by 
** Login   <hegedu_e@epitech.net>
** 
** Started on  Sun Apr 12 19:54:33 2015 
** Last update Sun Apr 12 21:18:44 2015 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

void		snick(t_ircserver *server, t_ircclient *client, char *cmd)
{
  char		buf[BUF_SIZE];

  if (available(server, cmd))
    {
      if (client->nick && client->channel)
	{
	  sprintf(buf, "%s changed his nickname to %s", client->nick, cmd);
	  sbroadcast(server, client, buf);
	}
      client->nick = strdup(cmd);
      printf("[INFO] %s: Nick '%s' available, client can proceed\n",
	     (client->nick ? client->nick : "Anonymous"), cmd);
    }
  else
    {
      request(client->sd, "433 Nickname invalid or in use");
      printf("[ERROR] %s: Nick '%s' unavailable, name invalid or in use\n",
	     (client->nick ? client->nick : "Anonymous"), cmd);
    }
}

void		slist(t_ircserver *server, t_ircclient *client, char *cmd)
{
  t_clientlist	*tmp;
  char		buf[BUF_SIZE];

  buf[0] = '\0';
  strcat(buf, "322 ");
  tmp = server->client_list;
  while (tmp)
    {
      if (tmp->client->channel && !strstr(buf, tmp->client->channel) &&
	  (!cmd[0] || strstr(tmp->client->channel, cmd)))
	{
	  if (strlen(buf) > 4)
	    strcat(buf, ", ");
	  strcat(buf, tmp->client->channel);
	}
      tmp = tmp->next;
    }
  if ((!cmd[0] || strstr("#base", cmd)) && !strstr(buf, "#base"))
    {
      if (strlen(buf) > 4)
	strcat(buf, ", ");
      strcat(buf, "#base");
    }
  request(client->sd, buf);
}

void		sjoin(t_ircserver *server, t_ircclient *client, char *cmd)
{
  char		buf[BUF_SIZE];

  (void) server;
  printf("[INFO] %s: tries to join channel '%s'\n",
	 (client->nick ? client->nick : "Anonymous"), cmd);
  if (!client->nick)
    {
      printf("[ERROR] Client id %d does not have a nickname\n", client->sd);
      request(client->sd, "431 No nickname given");
      return ;
    }
  if ((chan_valid(cmd)) && (!client->channel || strcmp(cmd, client->channel)))
    {
      if (client->channel)
	{
	  free(client->channel);
	  client->channel = NULL;
	}
      client->channel = strdup(cmd);
      sprintf(buf, "%s entered %s", client->nick, client->channel);
      sbroadcast(server, client, buf);      
      printf("[INFO] %s: channel changed to %s\n", client->nick, cmd);
      return ;
    }
  request(client->sd, "475 bad channel name");
}

void		spart(t_ircserver *server, t_ircclient *client, char *cmd)
{
  char		buf[BUF_SIZE];

  (void) server;
  printf("[INFO] %s: tries to leave channel '%s'\n",
	 (client->nick ? client->nick : "Anonymous"), cmd);
  if (!client->nick)
    {
      printf("[ERROR] Client id %d does not have a nickname\n", client->sd);
      request(client->sd, "431 No nickname given");
      return ;
    }
  if ((chan_valid(cmd)) && client->channel && !strcmp(cmd, client->channel))
    {
      sprintf(buf, "%s left %s", client->nick, client->channel);
      sbroadcast(server, client, buf);      
      free(client->channel);
      client->channel = NULL;
      printf("[INFO] %s: client left channel %s\n", client->nick, cmd);
    }
  else
    request(client->sd, "403 Not in a channel");
}

void		susers(t_ircserver *server, t_ircclient *client, char *cmd)
{
  t_clientlist	*tmp;
  char		buf[BUF_SIZE];

  (void) cmd;
  buf[0] = '\0';
  strcat(buf, "393 ");
  tmp = server->client_list;
  while (tmp)
    {
      if (tmp->client->nick)
	{
	  if (strlen(buf) > 4)
	    strcat(buf, ", ");
	  strcat(buf, tmp->client->nick);
	}
      tmp = tmp->next;
    }
  request(client->sd, buf);
}
