#------------[MANDATORY]
NAME			=	minishell
CC				=	cc
HEADER			=	-I ./include -I $(LIBFT_DIR)/include
RM				=	rm -f
RMDIR			=	rm -rf
MKDIR			=	mkdir -p

#------------[FLAGS]
CFLAGS			= 	$(W_FLAGS)
VFLAGS			=	--track-fds=yes --trace-children=yes --leak-check=full
DEBUG_FLAGS		= 	-g3
RL_FLAGS		= 	-lreadline
W_FLAGS			= 	-Wall -Wextra -Werror

#------------[PATH]
OUTPUT_PATH 	=	output
SRCS_PATH		=	srcs

#------------[LIBRARY]
LIBFT_DIR		=	include/KML
LIBFT_FILE		=	$(LIBFT_DIR)/kml.a

#------------[ROOT_FILES]
FILE			=	$(MAIN) $(PARSER) $(PROCESS) $(EXIT) $(UTILS) $(ENV) $(BUILTIN) $(SIGNAL)

#------------[SUBFILES]

MAIN			=	$(addprefix $(MAIN_PATH)/, $(addsuffix .c, $(MAIN_FILE)))
MAIN_PATH		=	minishell
MAIN_FILE		=	main

PROCESS			=	$(addprefix $(PROCESS_PATH)/, $(addsuffix .c, $(PROCESS_FILE)))
PROCESS_PATH	=	process
PROCESS_FILE	=	builtin_control clear debug get_t heredoc process redirect utils exec/access exec/clear exec/exec 

EXIT			=	$(addprefix $(EXIT_PATH)/, $(addsuffix .c, $(EXIT_FILE)))
EXIT_PATH		=	exit
EXIT_FILE		=	exit get_t

PARSER			=	$(addprefix $(PARSER_PATH)/, $(addsuffix .c, $(PARSER_FILE)))
PARSER_PATH		=	parser
PARSER_FILE		=	lexer parser syntax utils error expand redirect cmd redirect2 expand2 split unquote
EXIT			=	$(addprefix $(EXIT_PATH)/, $(addsuffix .c, $(EXIT_FILE)))
EXIT_PATH		=	exit
EXIT_FILE		=	exit get_t

ENV				=	$(addprefix $(ENV_PATH)/, $(addsuffix .c, $(ENV_FILE)))
ENV_PATH		=	env
ENV_FILE		=	add_env clear_env del_env env_new get_t get_value_env init_env print_env set_env tool

BUILTIN			=	$(addprefix $(BUILTIN_PATH)/, $(addsuffix .c, $(BUILTIN_FILE)))
BUILTIN_PATH	=	builtin
BUILTIN_FILE	=	builtin ft_chdir ft_echo ft_env ft_exit ft_export ft_pwd ft_unset

SIGNAL			=	$(addprefix $(SIGNAL_PATH)/, $(addsuffix .c, $(SIGNAL_FILE)))
SIGNAL_PATH		=	signal
SIGNAL_FILE		=	get_t sig_heredoc sig

#------------[OBJECT_AND_SOURCE]
SRC				=	$(addprefix $(SRCS_PATH)/, $(FILE))
OBJ				=	$(patsubst $(SRCS_PATH)/%.c, $(OUTPUT_PATH)/%.o, $(SRC))

#------------[SUPPRESS]
SUPPRESS := "\
{\n\
\treadline_leak\n\
\tMemcheck:Leak\n\
\t...\n\
\tfun:readline\n\
}\n\
{\n\
\tadd_history_leak\n\
\tMemcheck:Leak\n\
\t...\n\
\tfun:add_history\n\
}\
"
#------------[PROCESS]
all: 			$(NAME)
				@ printf "\033[38;5;46m\033[1m⟪ Complete ⟫\033[0m\n"

$(NAME): 		$(OBJ) Makefile
				@ make -s lib
				$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FILE) $(HEADER) $(RL_FLAGS) -o $(NAME)

$(OUTPUT_PATH)/%.o: $(SRCS_PATH)/%.c
				@ $(MKDIR) $(dir $@)
				$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

lib:
				@ make -sC $(LIBFT_DIR)

clean:
				@ $(RM) $(OBJ)
				@ make clean -sC $(LIBFT_DIR)
				@printf "\033[38;5;196;1m<< Destroy all Minishell object files >>\033[0m\n"

fclean: clean
				@ $(RM) $(NAME)
				@ $(RMDIR) $(OUTPUT_PATH)
				@printf "\033[38;5;196;1m<< Destroy all Minishell executable files>>\033[0m\n"
				@ make fclean -sC $(LIBFT_DIR)

valgrind:		$(NAME)
				@ echo $(SUPPRESS) > readline.supp
				@ valgrind --suppressions=readline.supp $(VFLAGS) ./$(NAME)

re: fclean all

.PHONY: all clean fclean re lib valgrind