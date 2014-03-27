/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:24:28 by tcaron            #+#    #+#             */
/*   Updated: 2014/03/26 23:17:30 by sguirrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# define BUFF_SIZE 100
# define HASH_SIZE 4096

# include <unistd.h>

/*
** AINSI escape code
*/

# define UL_ON "\033[4m"
# define UL_OFF "\033[24m"
# define CURSOR_BACK "\033[D"
# define CURSOR_NEXT "\033[C"
# define CURSOR_DOWN "\033[B"
# define CURSOR_UP "\033[A"
# define BLUE "\033[1;34m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define RED "\033[1;31m"
# define END "\033[0m"
# define SH_NAME "\033[1;35m[42SH]\033[0m "
# define HO_2 ((*input[2] == 0x48 || *input[2] == 0x46) && *input[3] == '\0')
# define HOMEND (*input[0] == 0x1B && *input[1] == 0x5B && HO_2)
# define CHAR_S(c) (c == '"' || c == '\'' || c == '`')
# define CHAR_END(c) (!(c) || c == ' ' || c == '\\')
# define OP_1(c) (c != '>' && c != '<' && c != '$')
# define OP(c) (c != ';' && c != '|' && c != '\t' && c != ' ' && OP_1(c))

typedef struct		s_list
{
	char			*key;
	char			*data;
	struct s_list	*next;
}					t_list;

typedef struct		s_parse
{
	char			*word;
	struct s_parse	*next;
}					t_parse;

typedef struct		s_data
{
	char			*cmd;
	char			*path;
	struct s_data	*right;
}					t_data;

typedef void		(*t_handler)();

typedef struct		s_builtin_cmd
{
	char			*name;
	t_handler		handler;
}					t_builtin_cmd;

typedef struct		s_seq
{
	char			*cmd;
	char			*path;
	t_handler		func;
	char			*args;
	char			*extra;
	char			**exec_tab;
	char			*file;
	int				fd[2];
	int				two[2];
	struct s_seq	*next;
	struct s_seq	*prev;
}					t_seq;

typedef struct		s_cmd
{
	char			*origin;
	char			*clean;
	t_seq			*seq;
	int				id;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct		s_input
{
	char			*result;
	char			*save;
	int				cursor_pos;
	int				cursor_max;
}					t_input;

typedef struct		s_comp
{
	char			*choice;
	int				id;
	struct s_comp	*next;
	struct s_comp	*prev;
}					t_comp;

/*
** Builtin dir
*/

t_handler			ft_isfunc(char *cmd);
void				do_exit(t_seq *seq);
void				ft_cd(t_seq *seq);
void				ft_echo(t_seq *seq);
void				ft_read(t_seq *seq);
t_list				**ft_add_data(char *s, int *op);
void				ft_set(t_seq *seq);
void				ft_unset(t_seq *seq);
void				ft_env(t_seq *seq);
void				set_env(t_seq *seq);
void				unset_env(t_seq *seq);
void				ft_init_builtin(t_builtin_cmd *tab);
void				ft_free_builtin(t_builtin_cmd *tab);
void				ft_init_op_tab(int op[3]);
int					ft_env_i(int check);

/*
** Cleaner dir
*/

void				ft_cleaner(t_data **path, t_cmd *cmd, int value);
void				ft_clean_seq(t_seq *seq);

/*
** Completion dir
*/

void				ft_completion(char **input, t_input *final);
void				ft_print_choice(t_comp *list, int i);
void				ft_free_list_comp(t_comp *list);

/*
** Cpy_cut_paste dir
*/

char				*ft_ccp_seq(t_input *final);

/*
** Cursor_motion dir
*/

char				*ft_check_key_lr(t_input *final, int value);
char				*print_word(t_input *final, char *input);
void				ft_place_cursor(t_input *final);
void				ft_prev_word(t_input *final);
void				ft_next_word(t_input *final);
void				ft_next_line(t_input *final);
void				ft_prev_line(t_input *final);

/*
** Error dir
*/

void				ft_error_malloc(void *value, char *msg);

/*
** Exec fir
*/

void				ft_launch(int do_fork, t_seq *seq, char **environ);
void				ft_pipe(t_seq *seq);
int					ft_gotredirection(t_seq *cmd, char *str);
void				ft_redirection(t_seq *cmd);
void				ft_exec(t_seq *seq);

/*
** Globbing dir
*/

void				check_glob(char **buffer);

/*
** History dir
*/

int					ft_current_id(int more);
char				*ft_get_current_line(t_cmd *line);
char				*ft_get_env(char *s);

/*
** Lexer dir
*/

t_seq				*ft_recursive_lexer(char **tab, t_seq *seq);
t_seq				*ft_lexer(char *s);
t_seq				*ft_init_seq(void);
int					ft_check_cmd(t_seq *seq, char **tab);

/*
** Memlib dir
*/

void				*ft_malloc(int s);
void				ft_free(void *var);
void				ft_free_data_hash(t_data **var);
void				ft_free_split(char **var);
void				test_free(char **var);

/*
** Parser dir
*/

char				*ft_parse_clean(char *buffer);
t_parse				*ft_add_word(char *s, t_parse *final);
char				*ft_get_var(char *s);
void				ft_init_op(char *token, int *i, char *op[9][3]);
void				ft_free_op(char *op[9][3]);
void				ft_build_env(t_seq *seq);

/*
** Path_control dir
*/

void				ft_init_path(void);
int					ft_hash(char *key);
t_data				**ft_save_path_data(t_data **tab);
void				ft_set_node(char *cmd, char *path, t_data **tab);
char				*ft_cmdpath(char *cmd);
void				ft_init_tab(t_data **tab);

/*
** Program_main dir
*/

char				*ft_get_input(t_cmd *line);
int					ft_get_id(int more);
void				ft_add_elem(t_cmd *line);
char				*ft_read_input(char *buffer, int fd);
char				**ft_cpy_env(int send);

/*
** Prompt dir
*/

int					ft_prompt_len(int size);
void				ft_prompt(void);

/*
** Syntax dir
*/

int					ft_first_control_syntax(char *input);
char				*ft_second_control(char *s);
char				*ft_get_exclamation(t_cmd *line);

/*
** Termods dir
*/

int					ft_restore(void);
int					ft_non_canonical(void);
int					ft_putchar_term(int c);
void				ft_signal(void);

/*
** Touch_control dir
*/

int					ft_key_up_or_down(char *buf);
int					ft_key_left_or_rigth(char *buf);
char				*ft_check_key(char **input, t_input *final, t_cmd *line);
char				*ft_check_key_ud(t_input *final, t_cmd *line);
int					ft_key1(char *input, t_input *final, t_cmd *line);

#endif
