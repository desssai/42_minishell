/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_envs_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:33:11 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/05 23:32:50 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envars	*ft_envar_new(char *key, char *value)
{
	t_envars	*var;

	var = (t_envars *)malloc(sizeof(t_envars));
	if (!var)
		return (NULL);
	var->key = key;
	var->value = value;
	var->prev = NULL;
	var->next = NULL;
	return (var);
}

void	ft_envar_add_front(t_envars **vars, t_envars *new_var)
{
	printf("YAY\n");
	new_var->next = NULL;
	*vars = new_var;
}

void	ft_envar_add_back(t_envars **vars, t_envars *new_var)
{
	t_envars	*copy;

	copy = *vars;
	if (!(*vars)->next)
		ft_envar_add_front(vars, new_var);
	else
	{
		while (copy->next)
			copy = copy->next;
		new_var->prev = copy;
		copy->next = new_var;
		new_var->next = NULL;
	}
}

void	ft_envar_del_one(t_envars **vars, t_envars *var)
{
	if (!vars || !(*vars) || !var)
		return ;
	free(var->key);
	free(var->value);
	if (var->prev)
		var->prev->next = var->next;
	else
		*vars = var->next;
	free(var);
}

void	ft_envars_clear(t_envars **vars)
{
	t_envars	*prev;

	if (!vars || !(*vars))
		return ;
	prev = NULL;
	while (*vars)
	{
		prev = (*vars);
		(*vars) = (*vars)->next;
		if (prev)
		{
			free(prev->key);
			free(prev->value);
			free(prev);
		}
	}
	if (prev)
	{
		free(prev->key);
		free(prev->value);
		free(prev);
	}
	*vars = NULL;
}
