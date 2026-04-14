/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 20:11:52 by username          #+#    #+#             */
/*   Updated: 2026/04/14 16:33:55 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}					t_type;

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	char			*append;
	char			*heredoc;
	int				expand_heredoc;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_token
{
	char			*content;
	int				type;
	int				quote;
	struct s_token	*next;

}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_exec
{
	int				prev_fd;
	pid_t			pid;
	int				pipefd[2];
	t_cmd			*first;

}					t_exec;

typedef struct s_shell
{
	t_env			*env;
	int				quote;

}					t_shell;

extern int			g_signal;

/////////////////////////////////////////////////////////////////////
//  _______  _______  _______  _______ _________ _        _______  //
// (  ____ )(  ___  )(  ____ )(  ____ \\__   __/( (    /|(  ____ \ //
// | (    )|| (   ) || (    )|| (    \/   ) (   |  \  ( || (    \/ //
// | (____)|| (___) || (____)|| (_____    | |   |   \ | || |       //
// |  _____)|  ___  ||     __)(_____  )   | |   | (\ \) || | ____  //
// | (      | (   ) || (\ (         ) |   | |   | | \   || | \_  ) //
// | )      | )   ( || ) \ \__/\____) |___) (___| )  \  || (___) | //
// |/       |/     \||/   \__/\_______)\_______/|/    )_)(_______) //
//																	//
/////////////////////////////////////////////////////////////////////

char				*ft_get_env(t_env *env, char *var_name);
t_env				*init_env(char **envp);
void				free_array(char **array);
void				free_env(t_env *env);
t_token				*ft_lexer(char *input, t_shell *shell);
int					first_occurence(char *str, char c, char other_check);
t_token				*create_token(char *str, t_token *token, int quote);
t_token				*check_token(t_token *token, t_token *link);
char				**input_to_token(char *input, int *size, t_shell *shell);
char				*handle_quotes(char *input, int *i, int *j, t_shell *shell);
char				*without_quotes(char *input, int *i, int *j,
						t_shell *shell);
int					is_operator(char to_check);
char				end_handling_quotes(char *input, int *i, int *j);
void				free_tmp(t_token *tmp);
int					how_c_in_row(char *start, char c);
int					to_link_redir(int *i, char *str, t_token **token,
						t_token **link);
t_token				*token_loop_pipe(t_token *token, int *i, int *start,
						t_token **link);
t_token				*token_loop_in(t_token *token, int *i, int *start,
						t_token **link);
t_token				*token_loop_out(t_token *token, int *i, int *start,
						t_token **link);
t_cmd				*ft_parsing(t_token *token);
t_cmd				*create_cmd(t_token **token, t_cmd *cmd);
char				*ft_get_env(t_env *env, char *var_name);
int					quote_switch(int quote, char to_check);
t_token				*check_expand_token(t_token *token, t_shell *shell);
void				free_expand(char *str, char *tmp, char *join);
int					size_expand(char *input, int i);
int					*quote_array_create(char *input, int size);
int					expand_in_quote(char *input, char **str, int *i,
						t_shell *shell);
int					can_expand(char to_check);
char				*init_str_quotes(char *input, int i);
char				**create_cmd_expand(t_token **token, int *i, char **args);
char				*create_cmd_arg(t_token **token, int *i);
char				**cmd_args_init(t_token *token);
int					check_space_tab(char *to_check);
void				free_token(t_token *token);
void				free_cmd(t_cmd *cmd);
char				**list_to_array(t_env *env);
int					ft_readline(t_shell *shell);
char				*expand_token(char *input, t_shell *shell);
int					check_dollar(char *str);
t_env				*create_node(char *key, char *value);
void				add_back_copy(t_env *env, t_env *node);
int					get_env_size(t_env *env);
void				cmd_other_type(t_token **token, t_cmd **cmd);
int					ft_count_token(char *input);
void				run_minishell(t_cmd *cmd_list, t_token *token,
						t_shell *shell);
void				increment_shlvl(t_env **env);
int					is_builtin_name(char *cmd);
int					prepare_all_heredocs(t_cmd *cmd_list, t_token *token,
						t_shell *shell);
void				run_minishell(t_cmd *cmd_list, t_token *token,
						t_shell *shell);
char				**ft_split_mod(char const *s, char c, char other_c);

/////////////////////////////////////////////////////////////////////
//  _______           _______  _______          _________ _______  //
// (  ____ \|\     /|(  ____ \(  ____ \|\     /|\__   __/(  ____ \ //
// | (    \/( \   / )| (    \/| (    \/| )   ( |   ) (   | (    \/ //
// | (__     \ (_) / | (__    | |      | |   | |   | |   | (__     //
// |  __)     ) _ (  |  __)   | |      | |   | |   | |   |  __)    //
// | (       / ( ) \ | (      | |      | |   | |   | |   | (       //
// | (____/\( /   \ )| (____/\| (____/\| (___) |   | |   | (____/\ //
// (_______/|/     \|(_______/(_______/(_______)   )_(   (_______/ //
//																	//
/////////////////////////////////////////////////////////////////////

char				*path_finder(char *cmd, char *path);
int					is_builtins(t_cmd *cmd, t_shell *shell, t_token *token);
int					ft_strcmp(char *s1, char *s2);
void				execute_pipeline(t_cmd *cmd_list, t_shell *shell,
						t_token *token);
int					parent_process(char **input, t_shell *shell);
void				setup_child_pipes(t_cmd *cmd, int prev_fd, int pipefd[2]);
void				child_process(char **args, t_shell *shell);
void				exec_child(t_cmd *cmd, t_exec *exec, t_shell *shell,
						t_token *token);
int					handle_input(t_cmd *cmd);
int					handle_output(t_cmd *cmd);
int					ft_heredoc(char *end_of_file, int need_to_expand,
						t_shell *shell);
int					ft_redir_in(char *file);
int					ft_redir_out(char *file);
int					ft_append(char *file);
void				free_child_resources(t_exec *exec, t_shell *shell,
						t_token *token);
void				init_signals(void);
void				ignore_signals_execution(void);
void				restore_default_signals(void);
void				init_signals_heredoc(void);

///////////////////////////////////////////////////////////////////////////
//  ______           _________ _    __________________ _        _______  //
// (  ___ \ |\     /|\__   __/( \   \__   __/\__   __/( (    /|(  ____ \ //
// | (   ) )| )   ( |   ) (   | (      ) (      ) (   |  \  ( || (    \/ //
// | (__/ / | |   | |   | |   | |      | |      | |   |   \ | || (_____  //
// |  __ (  | |   | |   | |   | |      | |      | |   | (\ \) |(_____  ) //
// | (  \ \ | |   | |   | |   | |      | |      | |   | | \   |      ) | //
// | )___) )| (___) |___) (___| (____/\| |   ___) (___| )  \  |/\____) | //
// |/ \___/ (_______)\_______/(_______/)_(   \_______/|/    )_)\_______) //
//																			//
///////////////////////////////////////////////////////////////////////////

int					ft_echo(char **args);
int					ft_pwd(void);
int					ft_env(t_env *env_list);
int					check_arg_cd(int n_arg);
int					n_arg_init(char **path);
int					ft_cd(char **path, t_env *env);
int					ft_export(t_env **env, char **args);
int					ft_exit(t_cmd *cmd, t_token *token, t_shell *shell);
int					ft_unset(t_env **env_list, char **args);
int					is_valid_identifier(char *arg);
char				*extract_key(char *arg);
char				*extract_value(char *arg);
void				sort_env_array(t_env **array, int count);
t_env				*find_env_node(t_env *env, char *key);
t_env				*create_env_node(char *key, char *value);
void				add_back_env(t_env **env, t_env *new_node);
int					count_env_nodes(t_env *env);
t_env				**create_env_array(t_env *env, int count);

#endif
