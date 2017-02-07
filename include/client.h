/*
** client.h for myirc in /home/hegedu_e/rendu/PSU_2014_myirc
** 
** Made by 
** Login   <hegedu_e@epitech.net>
** 
** Started on  Sun Apr 12 19:43:04 2015 
** Last update Sun Apr 12 20:09:38 2015 
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include <sys/select.h>

# define DEFAULT_PORT "6667"

# define BUF_SIZE 4096
# define NB_CFUNCS 9

typedef struct	s_ircclient t_ircclient;

typedef int (*t_cfptr)(t_ircclient *, char *);
typedef struct	s_pair_cfptr {
  char		*cmd;
  t_cfptr	func;
}		t_pair_cfptr;

struct		s_ircclient {
  int		sd;
  t_pair_cfptr	funcs[NB_CFUNCS];
  char		*host;
  char		*nick;
  char		*channel;
  fd_set	fds;
  int		running;
};

int		cconnect(t_ircclient *client, char *cmd);
int             cnick(t_ircclient *client, char *cmd);
int		clist(t_ircclient *client, char *cmd);
int             cjoin(t_ircclient *client, char *cmd);
int             cpart(t_ircclient *client, char *cmd);
int             cusers(t_ircclient *client, char *cmd);
int             cmsg(t_ircclient *client, char *cmd);
int             csend_file(t_ircclient *client, char *cmd);
int             caccept_file(t_ircclient *client, char *cmd);
int             cmessage(t_ircclient *client, char *cmd);

void		init_client(t_ircclient *client);
int		receive(int sd, char *buf);
int		request(int sd, char *msg);
int		read_prompt(t_ircclient *client, char *buf);
void		command(t_ircclient *client);
void		serv_request(t_ircclient *client);
int		select_client(t_ircclient *client, struct timeval *timeout);
void		disconnect_client(t_ircclient *client);
int		connect_client(t_ircclient *client, char *address, int port);
void		init_cfuncs(t_ircclient *client);
void		delete_cfuncs(t_ircclient *client);

char		*my_epur(char *str);

#endif /* !CLIENT_H_ */
