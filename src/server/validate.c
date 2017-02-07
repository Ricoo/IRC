/*
** validate.c for myirc in /home/hegedu_e/Projects/PSU_2014_myirc
** 
** Made by 
** Login   <hegedu_e@epitech.net>
** 
** Started on  Sun Apr 12 19:53:48 2015 
** Last update Sun Apr 12 20:20:37 2015 
*/

#include <string.h>
#include "server.h"

int		is_in(char needle, char *haystack)
{
  while (*haystack)
    {
      if (needle == *haystack)
	return (1);
      haystack++;
    }
  return (0);
}

int		chan_valid(char *chan)
{
  if (*chan != '#')
    return (0);
  ++chan;
  while (*chan)
    {
      if (!is_in(*chan, "abcdefghijklmnopqrstuvwxyz") &&
	  !is_in(*chan, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") &&
	  !is_in(*chan, "0123456789"))
	return (0);
      ++chan;
    }
  return (1);
}

int		available(t_ircserver *server, char *nick)
{
  t_clientlist	*tmp;

  tmp = server->client_list;
  while (tmp)
    {
      if (tmp->client->nick && !strcmp(nick, tmp->client->nick))
	return (0);
      tmp = tmp->next;
    }
  while (*nick)
    {
      if (!is_in(*nick, "abcdefghijklmnopqrstuvwxyz") &&
	  !is_in(*nick, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") &&
	  !is_in(*nick, "0123456789"))
	return (0);
      ++nick;
    }
  return (1);
}
