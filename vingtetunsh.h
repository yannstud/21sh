/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vingtetunsh.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:48:22 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/27 11:34:54 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VINGTETUNSH_H
# define VINGTETUNSH_H
# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <sys/stat.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <fcntl.h>
# include <dirent.h>
# include <libc.h>
# include <string.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/xattr.h>
# define RED "\033[1;31m"
# define NORMAL "\033[0m"
# define CM ft_strcmp
# define LENMAX 5000

typedef struct			s_qots
{
	int					cursh;
	int					subsh;
	int					crosh;
	int					qu;
	int					dqu;
	int					bqu;
}						t_qots;

typedef struct			s_history
{
	char				*command;
	int					cursor;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;

typedef struct			s_line
{
	char				*line;
	char				c;
	char				*selected;
	char				ret;
	size_t				count;
	size_t				icol;
	size_t				iline;
}						t_line;

typedef struct			s_elem
{
	int					cursor;
	int					select;
	char				*name;
	struct s_elem		*next;
	struct s_elem		*prev;
}						t_elem;

typedef int	t_token_type;
typedef int	t_char_type;

typedef struct			s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct			s_token
{
	char				*str;
	int					len;
	t_token_type		type;
	struct s_token		*next;
	struct s_token		*prev;
	int					fd_from;
	int					fd_to;
	char				*filename;
}						t_token;

typedef struct			s_btree
{
	struct s_btree		*parent;
	struct s_btree		*right;
	struct s_btree		*left;
	struct s_token		*data;
}						t_btree;

typedef struct			s_fds
{
	int					fd_stdin;
	int					fd_stdout;
	int					fd_stderr;
}						t_fds;

typedef struct			s_heredoc
{
	char				*content;
	char				*end_word;
	int					position;
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct			s_cmd
{
	char				*command;
	int					give_me_more;
	int					debug;
	t_env				*enva;
	t_token				*head;
	t_btree				*ast;
	int					heredoc_mode;
	int					heredoc_total;
	int					heredoc_done;
	t_heredoc			*heredoc;
	t_heredoc			*heredoc1;
}						t_cmd;

enum	e_char_type
{
	CHAR_NONE,
	CHAR_LETTER,
	CHAR_BLANK,
	CHAR_NEWLINE,
	CHAR_DQUOTE,
	CHAR_SQUOTE,
	CHAR_AND,
	CHAR_DIGIT,
	CHAR_SEMICOLON,
	CHAR_COMPARE,
	CHAR_PIPE
};

enum	e_token_type
{
	TOKEN_NONE,
	TOKEN_BLANK,
	TOKEN_NEWLINE,
	TOKEN_WORD,
	TOKEN_SQUOTE,
	TOKEN_BQUOTE,
	TOKEN_DQUOTE,
	TOKEN_IO_NUMBER,
	TOKEN_LESSGREAT,
	TOKEN_GREAT,
	TOKEN_LESS,
	TOKEN_DLESS,
	TOKEN_DGREAT,
	TOKEN_LESSAND,
	TOKEN_ANDGREAT,
	TOKEN_GREATAND,
	TOKEN_PIPE,
	TOKEN_OR_IF,
	TOKEN_AND_IF,
	TOKEN_AND,
	TOKEN_SEMI
};

/*
**	---------------------------  SRCS --------------------------------
**	cd_file.c
*/
int						back_to_olddir(char *old_pwd, char **env, char *pwd);
int						goto_dir(char *old_pwd, char **av, char *pwd,
							char **env);
int						cd_built(char **av, char *pwd, char **env);
void					help_is_cd(char **line, char **av, char **env);
int						is_cd(char **av, char **env);
/*
**	cmd.c
*/
t_cmd					*set_cmd(char *line, t_cmd **cmd);
t_cmd					*init_cmd(void);
t_cmd					*reset_cmd(t_cmd **cmd);
t_cmd					*insert_mode(char *line, t_cmd **cmd);
t_cmd					*heredoc_mode(char *line, t_cmd **cmd);
/*
**	env_file.c
*/
int						print_env(char **env);
char					**clearenvz(char **env);
char					**get_new_env(char **env);
char					**get_new_av(char **av, int decallage);
char					**get_new_replace(char **av, int decallage, char *new);
/*
**	echo_file.c
*/
void					witch_cmd(char **av, char **env, char **path);
int						is_echo(char **av);
/*
**	env_file2.c
*/
int						env_built(char **av, char **env, char **path);
int						setenv_help(char **av, char **env);
int						setenv_built(char **av, char **env, char **path);
int						unsetenv_help(char **av, char **env);
int						unsetenv_built(char **av, char **env);
/*
**	error_file.c
*/
void					free_args(char **str, char **str2, char **str3,
							char *str4);
void					print_error_file(char *command);
void					print_error(char *new_path);
/*
**	parsing.c
*/
char					**check_param(char **env);
char					*getpath(char **path, char *line);
char					**init_env(char **envp);
void					change_pwd(char *old_pwd, char *new_pwd, char **env);
char					*get_old_pwd(char **env);
/*
**	main.c
*/
char					*get_home(char *pwd);
void					launch_exec(t_history *list, t_cmd **cmd);
void					parsing_ok(t_history *list, t_cmd **cmd);
void					enter(t_line *line, t_history *list, t_cmd **cmd);
void					end_enter(t_cmd **cmd);
/*
**	utils.c
*/
char					*get_home(char *pwd);
void					init(t_line *line);
void					all_ifs(t_line *line, char *ret, t_cmd **cmd,
							t_history *list);
int						gestion_ctrl_d(char *buffer, t_cmd **cmd, t_line *line,
							t_history *list);
/*
**	---------------------------  LINE EDITING --------------------------------
**	cursoractions.c
*/
void					opt_left(t_line *line);
void					opt_right(t_line *line);
void					go_end(t_line *line);
void					go_home(t_line *line);
void					curs_right(t_line *line);
/*
**	copy.c
*/
int						control_p(t_line *line);
char					*make_str(char *str, char *line, char *selected,
							size_t count);
int						control_k(t_line *line);
void					print_line(char *str);
/*
**	cursormoove.c
*/
void					going_right(t_line *line);
void					curs_left(t_line *line);
void					opt_left_right(t_line *line);
void					opt_down(t_line *line);
void					opt_high(t_line *line);
/*
**	deletting.c
*/
void					insert_inline(t_line *line, char c);
int						del_left(t_line *line);
void					del_carac(t_line *line);
/*
**	stractions.c
*/
char					*ft_strindexcat(char *dest, char *src, size_t index);
struct termios			sigleton(struct termios term);
void					left2(t_line *line);
void					left(size_t i);
/*
**	process_arrows.c
*/
void					witch_arrow(t_history *list, t_line *line, char **env,
							t_cmd **cmd);
void					process_dcab(char *ret, t_line *line, t_history *list);
void					next_command(t_history *list, t_line *line, char *ret);
void					last_command(t_history *list, t_line *line, char *ret);
int						instant_arrow(char *buffer, t_line *line, char **env);
/*
**	strdeletting.c
*/
void					simple_clear_line(t_line *line);
void					clear_line(t_line *line);
void					right_del(t_line *line);
void					write_del_line(char *str, t_line *line);
void					clear_right_del(t_line *line);
/*
**	signal.c
*/
void					ft_signal(void);
void					sig_handler(int sig);
void					sig_int(void);
pid_t					ft_pid(pid_t pid, int i);
void					sig_c(t_line *line, t_cmd *cmd);
/*
**	processing_line.c
*/
void					ft_strlinecat(t_line *line);
void					strcat_inline(char ret, t_line *line);
int						sigline(int i, int mode);
int						has_line(char *line);
/*
**	termcapsactions.c
*/
void					exit_term(int i);
void					pause_term(void);
void					init_term(void);
void					restore_term_ori(void);
void					re_init_term(void);
/*
**	---------------------------  FT_SELECT ------------------------------------
**	print_select.c
*/
void					print_list(t_elem **alst);
void					print_my_names(t_elem *tmp, t_elem **alst);
void					print_too_small(void);
t_line					*singleline(t_line *line);
/*
**	dellistselect.c
*/
void					freenode(t_elem *node);
void					del_with_all(t_elem *list);
void					del_without_prev(t_elem *list);
void					del_without_next(t_elem *list);
void					return_back(int count_lines, int ws_col);
/*
**	lists.c
*/
t_elem					*init_select_list(void);
void					add_front_select_list(t_elem **alst, t_elem *new,
							char *name);
void					whitch_select_arrow(char *buff, t_elem **list);
/*
**	moove.c
*/
void					moove_curs_right(t_elem **list);
void					moove_curs_left(t_elem **list);
void					choose(t_elem **list);
/*
**	size_term.c
*/
int						max_size_words(t_elem **list);
void					resize_names(t_elem **list, char *name, size_t t,
							int cursor);
int						calc_term_larg(t_elem **list);
/*
**	autocompletion.c
*/
void					calc_size_needed(t_elem **alst);
void					autocompletion(t_line *line, char **env);
void					termcaps_begin_select(t_elem **alst);
t_elem					*parsing_error_select(t_line *line, char **env);
void					calc_size_needed(t_elem **alst);
/*
**	parsing_select.c
*/
char					**parsing_help(int i, char **env);
t_elem					*parsing_path(char **env, char *str, t_line *line);
void					parsing_select_noargs(t_elem *alst);
void					parsing_select(char *str, char *name_rep, t_elem *alst);
/*
**	end_select.c
*/
void					return_elem(t_elem **list, t_line *line);
void					ft_freet_elem(t_elem **list);
char					*set_name(t_line *line, t_elem *tmp);
void					termcaps_end_select(int i);
void					quit_select(t_line *line, t_elem **alst, int i);
/*
**	---------------------------  HISTORY ------------------------------------
**	createhistory.c
*/
t_history				*init_history();
void					add_front_history(t_history **alst, char *name);
int						check_name(char *str);
t_history				*init_list(char *name);
void					create_history(char *command, t_history *list);
/*
**	history.c
*/
char					*get_next_command(t_history **alst);
char					*get_last_command(t_history **alst);
int						control_l(t_line *line);
void					clear_histo(t_line *line);
/*
**	-------------------------------- PRINT -------------------------------------
**	print.c
*/
int						print_env_list(t_env *env);
/*
**	print_err.c
*/
void					err_no_cmd(char *cmd);
int						err_no_fd(int fd_nbr);
int						err_no_file(char *msg);
int						err_no_file_perm(char *msg);
void					print_err_cd(int stat_res, char *path,
							struct stat path_stat);
void					print_err(char *name, int type);
/*
**	print_err2.c
*/
void					parsing_error(char *str);
void					print_prompt(int i);
/*
**	-------------------------------- LEXER -------------------------------------
**	lexer.c
*/
void					handle_switch(t_token **head, char **cmd,
							int start, char *tmp);
void					get_token(t_token **head, char *cmd);
/*
**	lexer_handler1.c
*/
void					handle_blank(char **cmd, t_token **head);
void					handle_semicolon(char **cmd, t_token **head);
void					handle_dquote(char **cmd, t_token **head, char *tmp,
							int start);
void					handle_squote(char **cmd, t_token **head, char *tmp,
							int start);
void					handle_newline(char **cmd, t_token **head);
/*
**	lexer_handler2.c
*/
void					handle_pipe(char **cmd, t_token **head);
void					handle_and(char **cmd, t_token **head);
void					handle_word(char **cmd, t_token **head, char *tmp,
							int start);
void					handle_digit(char **cmd, t_token **head, char *tmp,
							int start);
/*
**	lexer_handler3.c
*/
void					handle_compare_great(char **cmd, t_token **head);
void					handle_compare_less(char **cmd, t_token **head);
/*
**	lexer_print.c
*/
void					print_tokens(t_token *head);
/*
**	lexer_utils.c
*/
int						get_ascii_type(int c);
t_token					*new_elem(char *str, t_char_type type);
void					add_token(t_token **head, t_char_type type, char *str);
char					*crop_str(char *tmp, char *cmd, int start, int diff);
void					lexer_error(void);
/*
**	-------------------------------- PARSER ------------------------------------
**	parser.c
*/
t_token_type			get_type(t_token_type type);
int						check_first(t_token *head);
int						check_last(t_token *head);
int						check_middle(t_token *head);
int						check_unsopprted_tokens(t_token *head);
int						parsing(t_token *head);
/*
**	parser_quote.c
*/
int						gestion_quotes2(char *cmd);
int						check_unsopprted_tokens(t_token *head);
/*
**	-------------------------------- UTILS -------------------------------------
**	env_parse.c
*/
void					add_to_env(t_env **head, int *index);
t_env					*parse_env(void);
t_env					*minimum_env(void);
int						get_list_size(t_env *li);
char					**get_env_char(t_env *env);
/*
**	fds.c
*/
t_fds					*get_terminal(void);
void					restore_fds(void);
/*
**	free.c
*/
void					free_heredoc(t_heredoc *elem);
void					free_token(t_token *elem);
void					free_env(char *value, char *name, t_env *env);
void					free_tabz(char **tabz);
/*
**	gnl.c
*/
int						check_read(char **rest, char **line);
int						get_line_len(char **rest);
int						last_line(char **rest, char **line);
int						ft_read(char **rest, char *str, char **line);
int						get_next_line(const int fd, char **line);
/*
**	shlvl.c
*/
void					increase_shlvl(t_env **env);
int						is_digit_only(char *str);
int						singlexex(int i);
/*
**	utils.c
*/
char					**get_path(t_env *env);
char					*add_slash(char *full_path);
void					add_element(t_env *prev, t_env **env, char *name,
							char *value);
char					**split_setenv(char *str);
char					*realloc_str(char *str1, char *str2);
/*
**	utils2.c
*/
int						open_file(char *filename, int append, int read);
/*
**	-------------------------------- EXEC -------------------------------------
**	exec.c
*/
char					**tabz_pocess(t_token *tkn, int i);
char					**tabz_from_token(t_token *tkn);
int						exec(char **tabz, t_env *env, int to_fork, t_cmd *cmd);
int						start_exec(t_btree *ast, t_env *env, int to_fork,
								t_cmd *cmd);
int						exec_recursive(t_btree *ast, t_env *env,
							int to_fork, t_cmd *cmd);
/*
**	exec_core.c
*/
int						run_cmd(char *path, char **tabz, t_env *env,
							int to_fork);
char					*get_executable(char *name, char **path);
int						bin_exist(char *path);
int						not_bultin(char **tabz, t_env **env, int to_fork);
char					*browse_dir(char *name,
							char *path, char *folder_name);
/*
**	exec_operat.c
*/
int						exec_semicolon(t_btree *ast, t_env *env, t_cmd *cmd);
int						exec_and(t_btree *ast, t_env *env, t_cmd *cmd);
int						exec_or(t_btree *ast, t_env *env, t_cmd *cmd);
int						exec_pipe(t_btree *ast, t_env *env, t_cmd *cmd);
void					dup_both(int fd);
int						exec_write_and_closed(t_btree *ast, t_env *env,
											int to_fork, t_cmd *cmd);
/*
**	exec_redir.c
*/
int						exec_write(t_btree *ast, t_env *env, int to_fork,
							t_cmd *cmd);
int						exec_andwrite(t_btree *ast, t_env *env, int to_fork,
							t_cmd *cmd);
int						exec_write_and_closed(t_btree *ast, t_env *env,
							int to_fork, t_cmd *cmd);
int						exec_write_and(t_btree *ast, t_env *env,
							int to_fork, t_cmd *cmd);
int						exec_read_and(t_btree *ast, t_env *env,
							int to_fork, t_cmd *cmd);
int						exec_read(t_btree *ast, t_env *env, int to_fork,
							t_cmd *cmd);
int						exec_heredoc(t_btree *ast, t_env *env, int to_fork,
							t_cmd *cmd);
/*
**	heredoc.c
*/
void					add_heredoc(t_cmd **cmd, int pos, char *end_word);
int						parse_heredoc(t_cmd **cmd);
int						last_is_oper(t_token *head, char *cmd);
/*
**	-------------------------------- BUILTINS --------------------------------
**	builtin_cd.c
*/
char					*get_value(t_env *env, char *name);
int						edit_value(char *name, char *value, t_env **env);
int						change_dir(char *path, t_env **env);
int						cd_home(t_env **env, char **tabz, char *new_path,
							char *folder);
int						ft_cd(t_env **env, char **tabz);
/*
**	builtins_echo.c
*/
int						ft_echo(t_env **env, char **tabz);
/*
**	builtins_env.c
*/
t_env					*copy_env(t_env *env);
char					**realloc_tab(char **tabz, int i);
void					free_tmp_env(t_env *tmp);
int						process_tabs(char **tabz, t_env **tmp, int i);
int						ft_env(t_env **env, char **tabz, t_cmd *cmd);
/*
**	builtins_exit.c
*/
int						ft_exit(char **tabz);
/*
**	builtin_setenv.c
*/
int						add_edit_env(t_env **env, t_env *tmp, t_env *element);
int						ft_setenv(t_env **env, char **tabz, int i);
int						ft_setenvloop(t_env **env, char **tabz, int i,
								t_cmd *cmd);
/*
**	builtin_unsetenv.c
*/
void					delete_env(t_env **env, t_env *prev, t_env *tmp,
								t_cmd *cmd);
int						ft_unsetenv(t_env **env, char **tabz, int i,
								t_cmd *cmd);
int						ft_clearenv(t_env **env);
int						ft_unsetenvloop(t_env **env, char **tabz, t_cmd *cmd);
/*
**	-------------------------------- AST -------------------------------------
**	ast.c
*/
t_btree					*split_cmd(t_token *head);
void					gen_tree_prefix(t_btree *ast);
t_btree					*create_ast(t_token *head);
/*
**	ast_operat.c
*/
t_token					*has_operator(t_token *head);
t_btree					*ast_operator(t_token *node);
/*
**	ast_print.c
*/
void					print_tree_prefix(t_btree *ast);
/*
**	ast_redir.c
*/
t_token					*has_redirection(t_token *head);
t_token					*handle_redir_left(t_token *node);
t_token					*handle_redir_right(t_token *node);
t_btree					*ast_redirection(t_token *node, t_token *head);
/*
**	ast_tree.c
*/
t_btree					*new_tree(t_token *token);
t_btree					*join_tree(t_btree *left, t_btree *right,
							t_token *token);
void					clean_tree(t_btree *ast);

#endif
