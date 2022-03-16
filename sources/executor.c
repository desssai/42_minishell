/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:09:53 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/16 17:47:51 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **get_command_arguments(t_list *args)
{
	t_list	*curr;
	char 	**cmd_args;
	int		quan;
	int		i;
	
	i = 0;
	curr = args;
	quan = get_args_quantity(args);
	cmd_args = (char **)malloc(sizeof(char *) * quan);
	if (!cmd_args)
		fatal_error(MLC_ERROR);
	while (i < quan && curr)
	{
		cmd_args[i] = ft_strdup(curr->content);
		if (!cmd_args[i])
			fatal_error(MLC_ERROR);
		curr = curr->next; 
		i++;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}

void execute_system_bin(t_cmnds *command, t_shell *shell, char **envp)
{
	char 	*path;
	pid_t 	pid;
	char	**cmd_args;
	int 	status;
	
	(void)shell;
	cmd_args = get_command_arguments(command->args);
	path = command->args->content;
	pid = fork();
	if (pid == 0)
	{
		// if (access(path, F_OK) < 0)
		// {
		// 	write(STDERR_FILENO, "minishell: ", 12);
		// 	write(STDERR_FILENO, command->args[0], ft_strlen(command->args[0]));
		// 	write(STDERR_FILENO, ": No such file or directory\n", 29);
		// 	return ;
		// }
		if (ft_strncmp(command->args->content, "", 1) != 0) 
		{
			execve(path, cmd_args, envp);
			free(cmd_args);
			write(STDERR_FILENO, "minishell: ", 12);
			write(STDERR_FILENO, command->args->content, ft_strlen(command->args->content));
			write(STDERR_FILENO, " : command not found\n", 21);
		}
	}
	else
	{
		// catch_signals();		
		waitpid(-1, &status, 0);
	}
}

void execute_command(t_cmnds *command, t_shell *shell, char **envp)
{
	if (is_built_in(command->args->content))
		built_ins(&(command->envs), command, shell, envp);
	else
	{
		execute_system_bin(command, shell, envp);
	}
}