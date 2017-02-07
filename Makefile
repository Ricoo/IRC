## Makefile for generic Makefile in /home/hegedu_e/Projets/Generic
## 
## Made by Eric Hegedus
## Login   <hegedu_e@epitech.net>
## 
## Started on  Fri Oct 25 11:54:03 2013 Eric Hegedus
## Last update Sun Apr 12 20:08:56 2015 
##

NAME_CLIENT	=	client

NAME_SERVER	=	server

SRC_CLIENT	=	src/client/main.c \
			src/client/client.c \
			src/client/cfuncs.c\
			src/client/command.c \
			src/client/cfunctions.c \
			src/client/cfunctions_bis.c \
			src/common/util.c \
			src/common/requests.c

SRC_SERVER	=	src/server/main.c \
			src/server/server.c \
			src/server/sfuncs.c \
			src/server/command.c \
			src/server/sfunctions.c \
			src/server/sfunctions_bis.c \
			src/server/validate.c \
			src/server/clientgesture.c \
			src/common/util.c \
			src/common/requests.c

OBJ_CLIENT	=	$(SRC_CLIENT:src/%.c=build/%.o)

OBJ_SERVER	=	$(SRC_SERVER:src/%.c=build/%.o)

CFLAGS		=	-Iinclude $(if $(DEBUG), -ggdb3,-O2 -W -Wall -Wextra)

ECHO		=	echo -e
RM_FORMAT	=	$(ECHO) "\033[31m[RM]\t\t\033[0m"
CC_FORMAT	=	$(ECHO) "\033[32m[CC]"$(MODE)"\t\033[0m"
LD_FORMAT	=	$(ECHO) "\033[33m[LD]\t\t\033[0m"
DONE_FORMAT	=	$(ECHO) "\033[36m[DONE]  \t\033[0m"

ifeq ($(DEBUG), 1)
	MODE	=	"\033[35m[DEBUG]"
else
	MODE	=	"\033[35m[NORMAL]"
endif

all		:	$(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT)	:	$(OBJ_CLIENT)
			@cc -o $@ $^ $(LDFLAGS)
			@$(LD_FORMAT) $^
			@$(DONE_FORMAT) $@

$(NAME_SERVER)	:	$(OBJ_SERVER)
			@cc -o $@ $^ $(LDFLAGS)
			@$(LD_FORMAT) $^
			@$(DONE_FORMAT) $@

build/%.o	:	src/%.c
			@mkdir -pv build/client build/server build/common
			@cc -c $(CFLAGS) $^ -o $@
			@$(CC_FORMAT) $^ "->" $@

clean		:
			@rm -f $(OBJ_CLIENT)
			@$(RM_FORMAT) $(OBJ_CLIENT) | sed 's/o /o\n\t\t /g'
			@rm -f $(OBJ_SERVER)
			@$(RM_FORMAT) $(OBJ_SERVER) | sed 's/o /o\n\t\t /g'

fclean		:	clean
			@rm -f $(NAME_CLIENT)
			@$(RM_FORMAT) $(NAME_CLIENT)
			@rm -f $(NAME_SERVER)
			@$(RM_FORMAT) $(NAME_SERVER)

re		:	fclean all

.PHONY		:	all clean fclean re
