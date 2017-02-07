/*
** server.c for myirc in /home/hegedu_e/Projects/PSU_2014_myirc
** 
** Made by 
** Login   <hegedu_e@epitech.net>
** 
** Started on  Sun Apr 12 19:36:04 2015 
** Last update Wed Jun 24 10:37:48 2015 
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include "server.h"

int		load_fdsets(t_ircserver *server)
{
  t_clientlist	*list;
  int		max;

  list = server->client_list;
  max = server->sd;
  FD_ZERO(&server->fd_rd);
  FD_SET(server->sd, &server->fd_rd);
  while (list != NULL)
    {
      if (max < list->client->sd)
	max = list->client->sd;
      FD_SET(list->client->sd, &server->fd_rd);
      list = list->next;
    }
  return (max);
}

int		select_server(t_ircserver *server)
{
  t_clientlist	*list;
  int		active;

  while (server->running)
    {
      active = select(load_fdsets(server) + 1, &server->fd_rd, NULL, NULL, NULL);
      if (active > 0)
	{
	  list = server->client_list;
	  if (FD_ISSET(server->sd, &server->fd_rd))
	    createclient(server);
	  else
	    while (list != NULL)
	      {
		if (FD_ISSET(list->client->sd, &server->fd_rd))
		  do_actions(server, list->client);
		list = list->next;
	      }
	  clean(server);
	}
    }
  close(server->sd);
  return (0);
}

int	init_server(t_ircserver *server, int port)
{
  struct protoent *pe;
  struct sockaddr_in sin;

  pe = getprotobyname("TCP");
  if ((server->sd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (-1);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if ((bind(server->sd, (const struct sockaddr *) &sin, sizeof(sin)) == -1)
      || listen(server->sd, 42))
    {
      close(server->sd);
      return (-1);
    }
  init_sfuncs(server);
  server->running = 1;
  server->client_list = NULL;
  printf("[INFO] Listening on port %d\n", port);
  return (0);
}
