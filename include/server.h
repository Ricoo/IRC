/*
** myirc.h for myirc in /home/hegedu_e/rendu/PSU_2014_myirc
**
** Made by
** Login   <hegedu_e@epitech.net>
**
** Started on  Mon Apr  6 14:30:12 2015
** Last update Sun Apr 12 20:16:49 2015 
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <sys/select.h>
# include "client.h"

# ifndef DEFAULT_PORT
#  define DEFAULT_PORT "6667"
# endif

# define NB_SFUNCS 8

typedef struct	s_ircserver t_ircserver;

typedef void (*t_sfptr)(t_ircserver *, t_ircclient *, char *);
typedef struct	s_pair_ssfptr {
  char		*cmd;
  t_sfptr	func;
}		t_pair_sfptr;

typedef struct	s_clientlist t_clientlist;
struct		s_clientlist {
  t_ircclient	*client;
  t_clientlist	*next;
};

struct		s_ircserver {
  int		sd;
  t_pair_sfptr	funcs[NB_SFUNCS];
  t_clientlist	*client_list;
  unsigned int	nb_cli;
  fd_set	fd_wr;
  fd_set	fd_rd;
  int		running;
};

void		snick(t_ircserver *server, t_ircclient *client, char *cmd);
void		slist(t_ircserver *server, t_ircclient *client, char *cmd);
void		sjoin(t_ircserver *server, t_ircclient *client, char *cmd);
void		spart(t_ircserver *server, t_ircclient *client, char *cmd);
void		susers(t_ircserver *server, t_ircclient *client, char *cmd);
void		smsg(t_ircserver *server, t_ircclient *client, char *cmd);
void		ssend_file(t_ircserver *server, t_ircclient *client, char *cmd);
void		saccept_file(t_ircserver *server, t_ircclient *client, char *cmd);
void		sbroadcast(t_ircserver *server, t_ircclient *client, char *cmd);

void		clean_command(char *buf);
void		do_actions(t_ircserver *server, t_ircclient *client);
void		init_sfuncs(t_ircserver *server);

void		createclient(t_ircserver *server);
void		deleteclient(t_ircclient *client);
void		clean(t_ircserver *server);

int		load_fdsets(t_ircserver *server);
int		select_server(t_ircserver *server);
int		init_server(t_ircserver *server, int port);

int		is_in(char needle, char *haystack);
int		available(t_ircserver *server, char *nick);
int		chan_valid(char *chan);

#endif /* ! SERVER_H_ */
