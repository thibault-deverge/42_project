/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype_minishell.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:33:12 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/15 17:41:04 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPE_MINISHELL_H
# define PROTOTYPE_MINISHELL_H

/* ********************************************	*/
/*					PROMPT & SIGNALS			*/
/* ********************************************	*/
/*			prompt								*/
char		*get_input(t_env *env);
int			is_empty_input(char *cmd);
/*			signals								*/
void		status_code(int status);
void		modify_signals(int behavior);
int			set_signal_heredoc(void);

/* ********************************************	*/
/*					PARSING						*/
/* ********************************************	*/
/*			main parsing function				*/
t_list		*main_parsing(t_list *lst, char *cmd, t_env *env);
/*			get environment						*/
void		get_environment(t_env *env, char **envp);
t_env		*add_variable(t_env *envp, char *str);
/*			pre_parsing (tokens)				*/
t_parse		*pre_parsing(t_parse *parse, char *cmd, t_env *env);
t_parse		*add_new_token(char *arg, int start, int len, t_parse *parse);
char		*get_value_of_key(char *key, int len, t_env *env);
void		define_rule_token(t_parse *parse, int rule);
int			manage_argument(char *cmd, t_parse *parse, int len, t_env *env);
int			get_exit_value(t_parse *parse, int len);
int			check_argument(char c);
/*			parse_command						*/
int			parse_commands(t_list *list_commands, t_parse *list_tokens);
int			handle_redirection(t_command *command, t_token *token);
int			is_single_point(t_command *command);
int			is_invalid_file(int rule);
int			is_redirection_invalid(char c);
int			is_command(t_token *token);

/* ********************************************	*/
/*					BUILT_IN					*/
/* ********************************************	*/
/*			main built-in functions				*/
int			exec_cd(t_command *command, t_env *env);
int			exec_echo(t_command *command, t_env *env);
int			exec_env(t_command *command, t_env *env);		
int			exec_export(t_command *command, t_env *env);
int			exec_exit(t_command *command, t_env *env);
int			exec_pwd(t_command *command, t_env *env);
int			exec_unset(t_command *command, t_env *env);
/*			utils								*/
int			export_error(char *src, char *sub, char *err_msg);
int			manage_variable(char *new_var, t_env *env);
int			check_key_name(char *key, int len, char *built);

/* ********************************************	*/
/*					EXECUTION					*/
/* ********************************************	*/
/*			main execution function				*/
int			main_execution(t_list *lst, t_env *env);
/*			builtins & redirections				*/
int			check_builtins(t_command *command, t_env *env);
int			is_builtin(t_command *command);
int			redi_manager(t_command *command);
int			heredoc_manager(t_list *lst);
void		close_heredoc(t_list *lst);
/*			single & multiples commands			*/
int			pipex(t_list *list_commands, t_env *env);
int			exec_command(char **command, char *paths, char **env);
int			first_cmd(t_list *list_cmd, int pipes[][2], t_env *env);
int			last_cmd(t_list *lst, t_command *cmd, int pipes[][2], t_env *env);
int			middle_cmd(t_list *lst, t_command *cmd, int pipes[][2], t_env *env);
int			single_cmd(t_list *lst, t_command *cmd, t_env *env);
/*			utils								*/
void		exit_child(t_list *lst, t_env *env, int perror, int exit_value);
void		exit_single_child(t_list *lst, t_env *env, int error, int exit_val);
int			check_signal(int stdin_dup);
int			make_dup_cmd(int pipes[][2], int idx_cmd);
int			heredoc_err(char *error, t_command *comman, int stdin_dup);
void		print_redi_error(char *err_src, char *err_msg);

/* ********************************************	*/
/*					UTILS						*/
/* ********************************************	*/
/*			environment							*/
t_variable	*add_new_variable(char *name, int len, t_env *env);
t_variable	*get_environment_node(t_env *env, char *var_name, int len);
t_variable	*get_last_var(t_env *env);
char		*get_environment_content(t_env *env, char *var_name);
char		**convert_env(t_env *env);
char		*set_new_content(t_variable *var, char *value);
void		set_ascii_index(t_env *env);
int			add_new_content(t_variable *var, char *value);
/*			command								*/
t_command	*initialize_command(void);
int			initialize_pid(t_list *lst);
int			is_empty_command(t_command *command);
int			is_last_command(t_command *command);
void		wait_allpid(t_list *list_commands);
/*			general								*/
long long	ft_atoll(const char *nptr, int *limits);
char		**ft_insert_matrix(char **matrice, char *str);
char		*ft_sepjoin(const char *s1, const char *s2, char c);
char		*ft_joinpath(char const *s1, char const *s2);
/*			Input/Output						*/
void		close_files(t_command *command);
void		close_pipe(int *pipe);
void		close_all_pipes(t_list *lst, t_command *command);
int			close_all(t_command *command, int fdin, int fdout);
/*			free memory							*/
void		free_main_lists(t_command *command, t_env *env);
void		free_env(t_variable *var);
void		free_commands(t_command *command);
void		free_tokens(t_token *token);
void		free_matrix(char **matrice);
void		free_matrices(char **matrix1, char **matrix2);
/*			errors handler						*/
void		throw_perror(int exit_value);
int			print_perso_error(char *err_sub, char *err_msg);
int			print_specific_error(char *err_msg, char err_arg);
int			print_error(char *err_msg);
int			print_perror(void);

#endif
