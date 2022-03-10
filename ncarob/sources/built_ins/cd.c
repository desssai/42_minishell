/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:42:12 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/10 22:07:40 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handle_unset_home(t_shell *shell)
{
	write(STDERR_FILENO, "minishell: cd: ", 15);
	write(STDERR_FILENO, "HOME not set\n", 14);
	shell->exit_status = EXIT_ERR;
}

void handle_empty_input(t_envars *list, t_shell *shell)
{
	char		*root_path;
	int			status;

	root_path = find_env_node(list, "HOME");
	status = chdir(root_path);
	if (status == -1)
		handle_unset_home(shell);
}

void handle_non_existing_path(t_cmnds *commands, t_shell *shell)
{
	write(STDERR_FILENO, "minishell: cd: ", 15);
	write(STDERR_FILENO, *commands->args, ft_strlen(*commands->args));
	write(STDERR_FILENO, ": No such file or directory\n", 29);
	shell->exit_status = EXIT_ERR;
}

void change_old_pwd_environ(t_envars **list, char *old_path)
{
	// t_envars	*old_pwd_node;

	// old_pwd_node = ft_envar_new("OLD_PWD", old_path);
	// if (!old_pwd_node)
	// 	fatal_error(MLC_ERROR);
	// ft_envar_del_one(list, "OLDPWD");
	// ft_envar_add_back(list, old_pwd_node);
	t_envars *tmp;
	tmp = *list;
	while (tmp)
	{
		if ((ft_strncmp(tmp->key, "OLD_PWD", 7) == 0) 
			&& (ft_strlen(tmp->key) == ft_strlen("OLD_PWD")))
			break ;
		tmp = tmp->next;
	}
	free(tmp->value);
	tmp->value = ft_strdup(old_path);
	
}

void change_new_pwd_environ(t_envars **list, char *new_path)
{
	// t_envars *new_pwd_node;

	// new_pwd_node = ft_envar_new("PWD", new_path);
	// if (!new_pwd_node)
	// 	fatal_error(MLC_ERROR);
	// ft_envar_del_one(list, "PWD");
	// ft_envar_add_back(list, new_pwd_node);
	t_envars *tmp;
	tmp = *list;
	while (tmp)
	{
		if ((ft_strncmp(tmp->key, "PWD", 3) == 0) 
			&& (ft_strlen(tmp->key) == ft_strlen("PWD")))
			break ;
		tmp = tmp->next;
	}
	free(tmp->value);
	tmp->value = ft_strdup(new_path);
}

void execute_cd(t_envars **list, t_cmnds **commands, t_shell *shell)
{
	int		status;
	char	old_path[MAX_PATH];
	char	new_path[MAX_PATH];

	t_cmnds *tmp;
	tmp = *commands;
	shell->exit_status = 0;
	if (getcwd(old_path, MAX_PATH) == NULL)
		fatal_error(MLC_ERROR);
	if (tmp->args == NULL)
		handle_empty_input(*list, shell);
	else 
	{
		status = chdir(tmp->infile);
		if (status == -1)
		{
			handle_non_existing_path(*commands, shell);
		}
	}
	if (getcwd(new_path, MAX_PATH) == NULL)
		fatal_error(MLC_ERROR);
	change_old_pwd_environ(list, old_path);
	change_new_pwd_environ(list, new_path);
}

/*
	1. save current path (old_path)
	2. change path (chdir)
	3. handle if path doesn't exist
	4. handle if path is empty
		- find home environ var
		- if no home, throw an error
		- else, cd to home
	5. change OLD_PWD in environ
	6. change PWD in environ
	done, you are perfect
*/