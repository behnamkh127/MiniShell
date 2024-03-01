/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:51:49 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/09 15:13:39 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>

typedef struct s_echo
{
	char	*str;
	int		count_quat;
	int		count_double;
	int		sign_n;
	int		sign_quat;
	int		sign_double;
}	t_echo;

typedef struct s_node
{
	char					*str;
	int						shlvl;
	struct s_node			*next;
}	t_node;

typedef struct s_pars
{
	t_node				*args;
	struct s_pars		*next;
}	t_pars;

typedef struct s_variable
{
	char				*name;
	char				*value;
	int					shlvl;
	struct s_variable	*next;
}	t_variable;

typedef struct s_mini
{
	char					**envp;
	char					**args;
	char					**lines;
	char					*line;
	int						error;
	char					*pwd;
	char					*oldpwd;
	struct s_variable		*var;
	struct s_node			*env;
	struct s_node			*export;
	int						shlvl;
	int						fd_input;
	int						out_sign;
	int						fd_out;
	int						fd_here_doc;
	int						pipe_count;
	int						std_out;
	int						std_in;
	char					*infile;
	char					*outfile;
}	t_mini;

//main:
void	read_prompt(t_mini **mini);

//bultins
void	bultins(t_mini **mini, int i);
void	mini_bultins(t_mini **mini, char *temp);
void	back_to_top(t_mini **mini, char *temp);

//cd
void	cd(t_mini **mini);
char	*quat_handle(char *str, int i);
char	*make_str(t_mini **mini, char *str);
void	exit_cd(t_mini **mini, char *str, char *err, int error);

//env
void	env(t_mini **mini);
void	print_env(t_mini **mini, int i);
void	env_add(t_mini **mini, t_node **env, char *str);
void	update_env(t_mini **mini);
int		check_need_change(t_node *temp, t_mini **mini);

//var
void	var(t_mini	**mini);
int		update_var(t_mini **mini, char **arr);
void	creat_line(t_mini **mini, char **args);
void	add_node(t_mini **mini, char **arr);

//mini_unset
void	unset(t_mini **mini, int i);

//echo
void	echo(t_mini **mini, int i);
void	creat_str(t_echo **echo, t_mini **mini, int i);
void	init_struct(t_echo **echo);
int		check_quats(char *str, int i);
void	free_echo(t_echo **echo, t_mini **mini, char *err, int error);

//echo_print
int		control_str(char *str, int i);
int		case_sign(t_echo **echo, t_mini **mini, int i);
int		case_sign2(t_echo **echo, t_mini **mini, int i);
int		echo_print(t_echo **echo, t_mini **mini, int i);
void	reg_print(t_echo **echo, t_mini **mini);

//echo_print2
void	handle_n(t_echo **echo, char *line);
void	search_variable(char *str, t_mini **mini);
void	echo_quat(t_echo **echo, t_mini **mini);
void	find_variable(char *str, t_mini **mini);

//mini_unset
void	find_del_var(t_mini **mini, char *str);
void	unset(t_mini **mini, int i);
void	find_del_env(t_node **root, char *str);
void	find_del_exp(t_node **root, char *str);

//export
void	export(t_mini **mini);
void	print_exp(t_node **exp);
void	add_sorted(t_mini **mini, t_node **exp, char *str);
void	init_export(t_mini **mini, char *env, t_node **exp, int i);
void	continue_add_sorted(t_node *new, t_node **exp);

//export_var
void	export_var(t_mini **mini);
void	find_in_var(t_mini **mini, char **arr);
int		find_in_env(t_mini **mini, char *str, int i);
void	add_to_env(t_mini **mini, int i);
int		check_env(t_mini **mini, char *str);

//exit
void	my_exit(t_mini **mini);
int		check_is_num(char *str);
void	find_error(t_mini **mini, char **args, int len);
void	correct_exit(t_mini **mini, char **args, char *line);

//exit_utils
void	delete_nodes(t_mini **mini);
void	delete_var(t_mini **mini);
void	final_exit(t_mini **mini);
void	remove_node(t_mini **mini, t_node **root);

//input
void	change_input(t_mini **mini, int i);
void	open_file(t_mini **mini, char *file_name, int sign);
int		skip_quat(char *mini, int i);
char	*skip_quat2(char *line);

//here_doc
void	find_here_doc(t_mini **mini);
char	*make_delimiter(char *location);
void	init_input(t_mini **mini, t_node **key);
int		update_line(t_mini **mini, t_node **key, int i);
void	free_link(t_mini **mini, t_node **key);

//output
void	change_output(t_mini **mini);
char	*valid_line(t_mini **mini, char *line, char *temp);
char	*append_output(t_mini **mini, char *line, char *temp);
void	open_outfile(t_mini **mini, char *filename, char *temp);
void	edit_line(t_mini **mini);

//scan_line
void	scan_line(t_mini **mini);
int		less_condition(t_mini **mini, char *line, int i);
int		pipe_condition(t_mini **mini, char *line, int i);
int		great_condition(t_mini **mini, char *line, int i);
void	scan_exit(t_mini **mini, char *err, int error);

//exec
void	exec(t_mini **mini);
char	*find_path(t_mini **mini, char *path);
void	exec_exit(t_mini **mini, int sign);
void	test_break(char **with_slash, char **path_final);
char	*ft_getenv(t_mini **mini);

//process
void	do_processes(t_mini **mini, int **fd_pipe, int i);
void	single_process(t_mini **mini, int i);
void	first_process(t_mini **mini, int **fd_pipe, int i);
void	last_process(t_mini **mini, int **fd_pipe, int i);
void	repeated_process(t_mini **mini, int **fd_pipe, int i);

//fork_pipe
void	fork_pipe_excute(t_mini **mini);
void	close_in_loop(t_mini **mini, int **fd_pipe, int i);
void	free_pipe_pid(int **fd_pipe, int *pid);
int		**init_pipe(t_mini **mini, int **pid);
void	do_fork(t_mini **mini, int *pid, int **fd_pipe, int i);

//mini_exit
void	mini_exit(t_mini **mini);
void	free_array(char **diff);
void	close_wait(t_mini **mini, int **fd_pipe, int *pid);

//signal
void	handle_sigint(int sig);
void	handle_sigint2(int sig);
void	handle_sigint3(int sig);

//utils
char	*make_small(char *arg);
int		ft_strcmp(char *s1, char *s2);
int		is_space(char temp);

//scan_line_utils
void	slash_condition(t_mini **mini, char *line);
void	first_char(t_mini **mini, char *line);
void	question_mark(t_mini **mini);
void	question_mark2(t_mini **mini, int i, int j, int len);
void	question_mark3(t_mini **mini, int i, char *str1, char *str2);

//parsing

void	parsing(t_mini **mini);
int		add_args(t_node **args, char *line, int i, int len);
void	pars_add_node(t_node **args, char *str);
void	make_lines(t_mini **mini, t_node **args, int k);
int		make_args(t_node **args, char *line, int i, int len);

//parsing_utils
void	free_args(t_node **args);
int		count_len(t_node **args);
#endif
