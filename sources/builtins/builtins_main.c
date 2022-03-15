/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:44:28 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/15 18:15:04 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void execute_command();

void	built_ins(t_envars **list, t_cmnds *store, t_shell *shell, char **envp)
{
	(void)envp;
	if (!store)
		return ;
	else if (ft_strncmp(store->args[0], "pwd", 4) == 0)
		execute_pwd(shell, store);
	else if (ft_strncmp(store->args[0], "env", 4) == 0)
		execute_env(*list, shell, store->args);
	else if (ft_strncmp(store->args[0], "unset", 6) == 0)
		execute_unset(list, &store->args[1], shell);
	else if (ft_strncmp(store->args[0], "exit", 5) == 0)
		execute_exit(shell, store);
	else if (ft_strncmp(store->args[0], "cd", 3) == 0)
		execute_cd(list, store, shell);
	else if (ft_strncmp(store->args[0], "echo", 5) == 0)
		execute_echo(store->args, shell);
	else if (ft_strncmp(store->args[0], "export", 7) == 0)
		execute_export(list, store, shell);
	else
	{
		char *path;
		pid_t pid;
		path = store->args[0];
		pid = fork();
		if (pid == 0)
		{
			if (access(path, F_OK) < 0)
			{
				write(STDERR_FILENO, "minishell: ", 12);
				write(STDERR_FILENO, store->args[0], ft_strlen(store->args[0]));
				write(STDERR_FILENO, ": No such file or directory\n", 29);
				return ;
			}
			execve(path, store->args, envp);
			write(STDERR_FILENO, "minishell: ", 12);
			write(STDERR_FILENO, store->args[0], ft_strlen(store->args[0]));
			write(STDERR_FILENO, " : command not found\n", 21);		
		}
		else
			wait(NULL);
		// execute_command(list, store, shell, envp);
	}
}
