/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:41:59 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/14 13:17:22 by wurrigon         ###   ########.fr       */
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
	return (size_of_list);
}

char **get_sorted_keys(char **keys, int size_of_list)
{
	int 		i;
	int			j;
	char 		*tmp;

	i = 0;
	while (i < size_of_list)
	{
		j = 0;
		while (j < size_of_list - i - 1)
		{
			if (ft_strncmp(keys[j], keys[j + 1], ft_strlen(keys[j]) + 1) > 0)
			{
				tmp = keys[j];
				keys[j] = keys[j + 1];
				keys[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (keys);
}

char **handle_export_without_args(t_envars *list)
{
	int 	size;
	char	**tmp;
	int		i;
	
	size = get_list_size(list);
	tmp = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	if (!tmp)
		fatal_error(MLC_ERROR);
	while (list)
	{
		tmp[i] = ft_strjoin(list->key, "=", 0, 0);
		tmp[i] = ft_strjoin(tmp[i], list->value, 0, 0);
		if (tmp[i] == NULL)
			fatal_error(MLC_ERROR);
		list = list->next;
		i++;
	}
	tmp[i] = NULL;
	tmp = get_sorted_keys(tmp, size);
	return (tmp);
}

int is_valid_env_key(char *token)
{
	int i;

	i = 0;
	if (!ft_isalpha(token[i]) && token[i] != '_')
		return (0);
	i++;
	while (token[i] != '\0')
	{
		if (!ft_isascii(token[i]))
			return (0);
		i++;
	}
	return (1);
}

int is_equal_sign(char *token)
{
	int i;

	i = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void display_sorted_list(char **sorted_keys)
{
	int 	i;
	
	i = 0;
	while (sorted_keys[i] != NULL)
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, sorted_keys[i], ft_strlen(sorted_keys[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

void add_env_key_value_pair(t_envars **list, char *pair)
{
	t_envars 	*node;
	char		**key_value;

	key_value = ft_split(pair, '=');
	if (!key_value)
		fatal_error(MLC_ERROR);

	node = (t_envars *)malloc(sizeof(t_envars));
	if (!node)
		fatal_error(MLC_ERROR);
	node->key = key_value[0];
	node->value = key_value[1];
	free(key_value[0]);
	free(key_value[1]);
	free(key_value);
	node->next = NULL;
	// should be sorted
	ft_envar_add_back(list, node);
}

void execute_export(t_envars **list, t_cmnds *commands, t_shell *shell)
{
	int		i;
	char 	**sorted_keys;
	i = 0;

	sorted_keys = NULL;
	if (commands->args[1] == NULL)
	{
		dprintf(2, "HERE");
		shell->exit_status = 0;		
		sorted_keys = handle_export_without_args(*list);
		display_sorted_list(sorted_keys);
	}	
	else
	{
		while (commands->args[i])
		{
			if (!is_valid_env_key(commands->args[i]))
			{
				shell->exit_status = EXIT_ERR;
				write(STDERR_FILENO, "minishell: export: `", 20);
				write(STDERR_FILENO, commands->args[i], ft_strlen(commands->args[i]));
				write(STDERR_FILENO, ": not a valid identifier\n", 27);
			}
			else if (!is_equal_sign(commands->args[i]))
				shell->exit_status = 0;
			else
			{
				shell->exit_status = 0;
				// check_if_key_exists(commands->args[i]);
				add_env_key_value_pair(list, commands->args[i]);	
			}
			i++;
		}
	}
}