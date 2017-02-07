/*
** sfuncs.c for myirc in /home/hegedu_e/Projects/PSU_2014_myirc
** 
** Made by 
** Login   <hegedu_e@epitech.net>
** 
** Started on  Sun Apr 12 19:35:34 2015 
** Last update Sun Apr 12 21:15:28 2015 
*/

#include <string.h>
#include "server.h"

void		init_sfuncs(t_ircserver *server)
{
  server->funcs[0].cmd = strdup("NICK");
  server->funcs[0].func = &snick;
  server->funcs[1].cmd = strdup("LIST");
  server->funcs[1].func = &slist;
  server->funcs[2].cmd = strdup("USERS");
  server->funcs[2].func = &susers;
  server->funcs[3].cmd = strdup("JOIN");
  server->funcs[3].func = &sjoin;
  server->funcs[4].cmd = strdup("PART");
  server->funcs[4].func = &spart;
  server->funcs[5].cmd = strdup("PRIVMSG");
  server->funcs[5].func = &smsg;
  server->funcs[6].cmd = strdup("SENDFILE");
  server->funcs[6].func = &ssend_file;
  server->funcs[7].cmd = strdup("ACCEPTFILE");
  server->funcs[7].func = &saccept_file;
}
