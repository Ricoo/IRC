/*
** client.c for myirc in /home/hegedu_e/rendu/PSU_2014_myirc
** 
** Made by 
** Login   <hegedu_e@epitech.net>
** 
** Started on  Sun Apr 12 19:33:24 2015 
** Last update Sun Apr 12 21:58:18 2015 
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include "client.h"

int		select_client(t_ircclient *client, struct timeval *to)
{
  int		active;

  printf("[%s]:", (client->nick ? client->nick : "-"));
  fflush(stdout);
  while (client->running)
    {
      FD_ZERO(&client->fds);
      FD_SET(0, &client->fds);
      if (client->sd != -1)
	FD_SET(client->sd, &client->fds);
      active = select((client->sd == -1 ? 2 : client->sd + 1)
		      , &client->fds, NULL, NULL, to);
      if (active > 0)
	{
	  if (FD_ISSET(client->sd, &client->fds))
	    serv_request(client);
	  else if (FD_ISSET(0, &client->fds))
	    {
	      command(client);
	      fflush(stdout);
	    }
	}
    }
  disconnect_client(client);
  return (0);
}
void		init_client(t_ircclient *client)
{
  init_cfuncs(client);
  client->nick = NULL;
  client->channel = NULL;
  client->host = NULL;
  client->running = 1;
  client->sd = -1;
}

void		disconnect_client(t_ircclient *client)
{
  if (client->channel)
    {
      cpart(client, client->channel);
      free(client->channel);
    }
  if (client->sd != -1)
    {
      printf("Disconnected from %s\n", client->host);
      close(client->sd);
    }
  if (client->nick)
    free(client->nick);
  if (client->host)
    free(client->host);
  client->nick = NULL;
  client->channel = NULL;
  client->host = NULL;
  client->sd = -1;
}

int		connect_client(t_ircclient *client, char *address, int port)
{
  struct sockaddr_in	sin;
  struct protoent	*pe;
  struct hostent	*he;
  struct timeval	to;

  to.tv_sec = 2;
  to.tv_usec = 0;
  disconnect_client(client);
  pe = getprotobyname("TCP");
  if ((client->sd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1
      || (he = gethostbyname(address)) == NULL)
    return (-1);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  memcpy(&(sin.sin_addr), he->h_addr_list[0], he->h_length);
  if ((connect(client->sd, (const struct sockaddr *) &sin,
	       sizeof(sin)) == -1))
    {
      close(client->sd);
      return (-1);
    }
  setsockopt(client->sd, SOL_SOCKET, SO_RCVTIMEO,
	     (char *) &to, sizeof(to));
  client->host = strdup(address);
  return (0);
}
