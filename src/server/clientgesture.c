/*
** clientgesture.c for myirc in /home/hegedu_e/Projects/PSU_2014_myirc
** 
** Made by 
** Login   <hegedu_e@epitech.net>
** 
** Started on  Sun Apr 12 19:37:04 2015 
** Last update Sun Apr 12 20:19:08 2015 
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include "server.h"

void		deleteclient(t_ircclient *client)
{
  printf("[INFO] Client disconnected (id:%d)\n", client->sd);
  close(client->sd);
  free(client->nick);
  free(client->channel);
  free(client);
}

void		createclient(t_ircserver *server)
{
  t_clientlist	*tmp;
  int		sd;
  struct sockaddr_in cli;
  int		client_len;

  client_len = sizeof(cli);
  if ((sd = accept(server->sd, (struct sockaddr *) &cli,
		   (socklen_t *) &client_len)) == -1)
    return ;
  tmp = server->client_list;
  if (server->client_list == NULL)
    tmp = (server->client_list = malloc(sizeof(t_clientlist)));
  else
    {
      while (tmp->next)
	tmp = tmp->next;
      tmp = (tmp->next = malloc(sizeof(t_clientlist)));
    }
  tmp->client = malloc(sizeof(t_ircclient));
  tmp->client->running = 1;
  tmp->client->sd = sd;
  tmp->client->nick = NULL;
  tmp->client->channel = NULL;
  tmp->next = NULL;
  printf("[INFO] Client connected (id:%d)\n", sd);
}

void		clean(t_ircserver *server)
{
  t_clientlist	*list;
  t_clientlist	*tmp;

  list = server->client_list;
  if (list && list->client->running == 0)
    {
      server->client_list = list->next;
      deleteclient(list->client);
      free(list);
    }
  list = server->client_list;
  while (list && list->next)
    {
      tmp = list->next;
      if (tmp && tmp->client->running == 0)
	{
	  list->next = tmp->next;
	  deleteclient(tmp->client);
	  free(tmp);
	}
      else
	list = list->next;
    }
}
