/*
** requests.c for myirc in /home/hegedu_e/rendu/PSU_2014_myirc
** 
** Made by 
** Login   <hegedu_e@epitech.net>
** 
** Started on  Sun Apr 12 19:30:52 2015 
** Last update Sun Apr 12 20:12:00 2015 
*/

#include <sys/socket.h>
#include <string.h>
#include "client.h"

int		receive(int sd, char *buf)
{
  int		ret;

  ret = recv(sd, buf, BUF_SIZE - 1, 0);
  buf[ret] = '\0';
  return (ret);
}

int		request(int sd, char *buf)
{
  int		ret;

  ret = send(sd, buf, strlen(buf), 0);
  return (ret);
}
