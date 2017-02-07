/*
** cfuncs.c for myirc in /home/hegedu_e/rendu/PSU_2014_myirc
** 
** Made by 
** Login   <hegedu_e@epitech.net>
** 
** Started on  Sun Apr 12 19:32:31 2015 
** Last update Sun Apr 12 20:06:38 2015 
*/

#include <stdlib.h>
#include <string.h>
#include "client.h"

void		init_cfuncs(t_ircclient *client)
{
  client->funcs[0].cmd = strdup("/server ");
  client->funcs[0].func = &cconnect;
  client->funcs[1].cmd = strdup("/nick ");
  client->funcs[1].func = &cnick;
  client->funcs[2].cmd = strdup("/list");
  client->funcs[2].func = &clist;
  client->funcs[3].cmd = strdup("/users");
  client->funcs[3].func = &cusers;
  client->funcs[4].cmd = strdup("/join ");
  client->funcs[4].func = &cjoin;
  client->funcs[5].cmd = strdup("/part");
  client->funcs[5].func = &cpart;
  client->funcs[6].cmd = strdup("/msg ");
  client->funcs[6].func = &cmsg;
  client->funcs[7].cmd = strdup("/send_file ");
  client->funcs[7].func = &csend_file;
  client->funcs[8].cmd = strdup("/accept_file ");
  client->funcs[8].func = &caccept_file;
}

void		delete_cfuncs(t_ircclient *client)
{
  int		i;

  i = 0;
  while (i < 9)
    {
      free(client->funcs[i].cmd);
      ++i;
    }
}
