/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:09:53 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/15 21:32:20 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handle_signals(t_cmnds *command)
{
	
}

void execute_system_bin(t_cmnds *command, t_shell *shell, char **envp)
{
	char 	*path;
	pid_t 	pid;
	
	(void)shell;
	handle_signals(command);
	path = command->args[0];
	pid = fork();
	if (pid == -1)
		fatal_error("fork");
	if (pid == 0)
	{
		// if (access(path, F_OK) < 0)
		// {
		// 	write(STDERR_FILENO, "minishell: ", 12);
		// 	write(STDERR_FILENO, command->args[0], ft_strlen(command->args[0]));
		// 	write(STDERR_FILENO, ": No such file or directory\n", 29);
		// 	return ;
		// }
		if (ft_strncmp(command->args[0], "", 1) != 0) 
		{
			shell->exit_status = 0;
			execve(path, command->args, envp);
			shell->exit_status = 1;
			write(STDERR_FILENO, "minishell: ", 12);
			write(STDERR_FILENO, command->args[0], ft_strlen(command->args[0]));
			write(STDERR_FILENO, " : command not found\n", 21);		
		}
	}
	else
		wait(NULL);
}

void execute_command(t_cmnds *command, t_shell *shell, char **envp)
{
	if (is_built_in(command->args[0]))
		built_ins(&(command->envs), command, shell, envp);
	else
		execute_system_bin(command, shell, envp);
}