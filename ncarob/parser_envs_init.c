/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_envs_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:49:33 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/05 23:31:44 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envars	**ft_init_envars(char **envp)
{
	char		**key_value;
	t_envars	**envars;
	t_envars	*var;
	int			i;

	envars = &var;
	var = NULL;
	if (!envp)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		key_value = ft_split(envp[i], '=');
		var = ft_envar_new(key_value[0], key_value[1]);
		if (!var)
			exit(EXIT_FAILURE);
		ft_envar_add_back(envars, var);
	}
	return (envars);
}

void	ft_print_envars(t_envars *vars)
{
	while (vars)
	{
		printf("%s=%s\n", vars->key, vars->value);
		vars = vars->next;
	}
}
