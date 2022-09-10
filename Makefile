NAME		:= pipex
CC			:= cc 
RM			:= rm -f
CFLAGS		:= -Wall -Wextra -Werror -O
DFLAGS		:= -MMD -MP
SRCS		:= 	pipex_main.c \
				pipex_begin.c \
				pipex_open.c \
				pipex_pipe.c \
				pipex_child.c \
				pipex_multi_pipe.c \
				pipex_close.c \
				pipex_run_get_path.c \
				pipex_run_make_v_argv.c \
				pipex_run_util.c \
				pipex_wait.c \
				pipex_finish.c \
				pipex_x_util.c \
				pipex_x_sys_call.c \
				pipex_x_sys_call2.c \
				pipex_free_struct.c \

B_SRCS	:= 

LIBFT		= $(LIBDIR)libft.a
INCLUDE		= -I$(INCDIR)


DEPENDS		= $(OBJECTS:.o=.d)

OBJS		= $(SRCS:%.c=%.o)
OBJECTS		= $(addprefix $(OBJDIR)/, $(OBJS))

B_OBJS		= $(B_SRCS:%.c=%.o)
B_OBJECTS   = $(addprefix $(OBJDIR)/, $(B_OBJS))
ifdef WITH_BONUS
	OBJS += $(B_OBJECTS)
endif

INCDIR		= include/
LIBDIR		= libft/
OBJDIR		= obj
ifeq "$(strip $(OBJDIR))" ""
  OBJDIR	= .
endif
# SRCDIR    = src/
# ifeq "$(strip $(SRCDIR))" ""
#   SRCDIR  = .
# endif


$(NAME): $(OBJECTS) $(LIBFT)
	@echo $(BLUE)"----- $(NAME) $(CC) start-----"$(RESET)
	$(CC) -o $@ $^ $(CFLAGS) $(DFLAGS) $(INCLUDE) $(MFLAGS)
	@echo $(GREEN)"----- $(NAME) $(CC) done-----"$(RESET)

$(OBJDIR)/%.o: %.c
	@echo $(SKYBLUE) "make .o" $(RESET)
	 -mkdir -p $(OBJDIR) 
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT): FORCE
	$(MAKE) -C $(LIBDIR)
	@echo $(GREEN)"----- $(LIBFT) $(CC) done-----"$(RESET)
FORCE:

all: $(NAME) 

clean:
	$(MAKE) clean -C $(LIBDIR)
	@echo $(YELLOW)"----- $(LIBFT) clean done-----"$(RESET)
	$(RM) $(OBJECTS) $(DEPENDS)
	@echo $(YELLOW)"----- $(NAME) clean done-----"$(RESET)

fclean:	clean
	$(MAKE) fclean -C $(LIBDIR)
	@echo $(RED)"----- $(LIBFT) fclean done-----"$(RESET)
	$(RM) $(NAME)
	@echo $(RED)"----- $(NAME) fclean done-----"$(RESET)

re: fclean all

-include $(DEPENDS)

bonus: 
	make WITH_BONUS=1

debug: CFLAGS +=  -g  -fsanitize=address -fsanitize=undefined 
debug: re

.PHONY: all clean fclean re bonus

RED			=	"\033[31m"
GREEN		=	"\033[32m"
YELLOW		=	"\033[33m"
BLUE		=	"\033[34m"
PURPLE		=	"\033[35m"
SKYBLUE		=	"\033[36m"
RESET		=	"\033[0m"