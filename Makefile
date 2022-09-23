NAME	= 	pipex

SRCS_OBJS = mandatory/functions.o mandatory/pipex.o mandatory/queue.o mandatory/free.o mandatory/errors.o mandatory/ft_split.o mandatory/path_commands.o

BONUS_OBJS	= bonus/pipex_bonus.o bonus/utils/errors.o bonus/utils/ft_split.o bonus/utils/free.o bonus/utils/functions.o bonus/utils/path_commands.o bonus/utils/queue.o bonus/here_doc/free.o bonus/here_doc/functions.o bonus/here_doc/here_doc.o

LIB = libpipex.a

CFLAGS	= -Wall -Wextra -Werror

CC 	=	gcc

LOGO	=	"\n\n\033[0;32m ██████╗ ██╗██████╗ ███████╗██╗  ██╗     ██╗  ██╗██████╗\n\
██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝     ██║  ██║╚════██╗\n\
\033[0;32m██████╔╝██║██████╔╝█████╗   ╚███╔╝█████╗███████║ █████╔╝\n\
██╔═══╝ ██║██╔═══╝ ██╔══╝   ██╔██╗╚════╝╚════██║██╔═══╝ \n\
\033[0;32m██║     ██║██║     ███████╗██╔╝ ██╗          ██║███████╗\n\
╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝          ╚═╝╚══════╝\n\
                                  \t\t\t\t\t\\033[1;37mmade by hel-mefe \n                     "
.PHONY:	all clean fclean re bonus

all : $(NAME)
	@echo $(LOGO)

bonus : $(LIB)
	
$(LIB) : $(BONUS_OBJS)
	@echo "\n\n\033[32;1m -----> COMPILING BONUS IS DONE! ... ----> \033[0m "
	@$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(NAME)
	@ar -rc $(LIB) $(BONUS_OBJS)

$(NAME) : $(SRCS_OBJS)
	@echo "\n\n \033[32;1m -----> COMPILING IS DONE! ... -----> \033[0m "
	@$(CC) $(CFLAGS) $(SRCS_OBJS) -o $@

clean :
	@rm -f $(SRCS_OBJS)
	@rm -f $(BONUS_OBJS)

fclean : clean
	@rm -f $(LIB) $(NAME)

re: fclean all
