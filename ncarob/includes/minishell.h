/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:18:03 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/06 15:46:03 by ncarob           ###   ########.fr       */
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
# include "../libft/libft.h"

# define MLC_ERROR "minishell: not enough memory.\n"
# define CMD_ERROR "command error.\nUse of ';', '\\' or an unclosed quote.\n"
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

typedef struct s_envars
{
	char				*key;
	char				*value;
	struct s_envars		*next;
}	t_envars;

// Command Parser.

int			ft_parse_input(char *str, t_envars *envs);

// Environment Variables Parser.

void		ft_envar_add_back(t_envars **vars, t_envars *new_var);
void		ft_envar_del_one(t_envars **vars, char *key);
t_envars	*ft_envar_new(char *key, char *value);
void		ft_envars_clear(t_envars **vars);
void		ft_print_envars(t_envars *vars);
t_envars	*ft_init_envars(char **envp);

#endif