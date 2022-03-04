/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:18:03 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/04 19:11:08 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define CMD_ERROR "Command error.\nUse of ';', '\\' or an unclosed quote.\n"
# define SPECIAL_CHARS "\"\'$"

typedef struct s_args
{
	struct s_args	*prev;
	struct s_args	*next;
	int				id;
}	t_args;

typedef struct s_coms
{
	int		id;
	t_args	args;
	char	*flag;
	char	**envs;
	int		cmd_input;
	int		cmd_output;
}	t_coms;

typedef struct s_env_vars
{
	char				*key;
	char				*value;
	struct s_env_vars	*next;
	struct s_env_vars	*prev;
}	t_env_vars;

// Parser.

int			ft_parse_input(char *str, t_env_vars *envs);

// Environment variables.

void		add_node_to_list(char *line, t_env_vars **head);
t_env_vars	*parse_env(char **ev);
void		print_list(t_env_vars *head);
int			count_env_vars(char **ev);

#endif