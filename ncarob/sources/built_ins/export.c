/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:41:59 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/12 20:10:33 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int get_list_size(t_envars *list)
{
	t_envars	*tmp;
	int			size_of_list;

	tmp = list;
	size_of_list = 0;
	while (tmp != NULL)
	{
		size_of_list++;
		tmp = tmp->next;
	}
	if (size_of_list == 0)
		return 0;
	return (size_of_list);
}

void handle_export_without_args(t_envars *list)
{
	int size;

	size = get_list_size(list);
}

int is_valid_env_key(char *token)
{
	if (!ft_isalpha(*token) && *token != "_")
		return (0);
	token++;
	while (*token != '\0')
	{
		if (!ft_isascii(*token))
			return (0);
		token++;
	}
	return (1);
}

int is_equal_sign(char *token)
{
	while (*token != '\0')
	{
		if (*token == "=")
			return (1);
		token++;
	}
	return (0);
}

void execute_export(t_envars **list, t_cmnds *commands, t_shell *shell)
{
	int i;

	i = 0;
	// No options
	// It will simply print all names marked for an export to a child process
	if (!commands->args)
	{
		// sort list "declare -x" and display it
		shell->exit_status = 0;		
		handle_export_without_args(*list);
	}
	else
	{
		while (commands>args[i])
		{
			if (!is_valid_env_key(commands->args[i]))
			{
				shell->exit_status = EXIT_ERR;
				write(STDERR_FILENO, "minishell: export: `", 20);
				write(STDERR_FILENO, commands->args[i], ft_strlen(commands->args[i]));
				write(STDERR_FILENO, "': not a valid identifier\n", 27);
			}
			else if (!is_equal_sign(commands->args[i]))
				shell->exit_status = 0;
			else
			{
				// It will export key-values pairs	
			}
			i++;
		}
	}
}