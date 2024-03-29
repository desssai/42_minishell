/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:41:52 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/24 22:01:08 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_args_quantity(t_list *args)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = args;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

bool	is_numeric(const char *str)
{
	if (*str == '-')
		str++;
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

static int	result(const char *str, unsigned long long res, int negative)
{
	int					i;
	unsigned long long	long_num;

	long_num = LLU;
	long_num++;
	i = 0;
	while (!(*str >= '0' && *str <= '9'))
		str++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if ((res > LLU && negative == 1) \
		|| (res > long_num && negative == -1) || i > 19)
		return (EXIT_BIG_NUM);
	return (res * negative);
}

static int	get_lvl(char *str, int negative)
{
	unsigned long long	ret;
	char				*tmp;

	ret = 0;
	tmp = str;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
	{
		negative = -negative;
		str++;
	}
	else if (*str == '+')
		str++;
	if (*str < '0' || *str > '9')
		return (EXIT_NON_NUMERIC);
	while (*str >= '0' && *str <= '9')
	{
		ret = ret * 10 + *str - '0';
		str++;
	}
	if (*str == '\0')
		return (result(tmp, ret, negative));
	else
		return (EXIT_NON_NUMERIC);
}

void	execute_exit(t_shell **shell, t_list *args)
{
	write(STDERR_FILENO, "exit\n", 5);
	if (args->next)
	{
		if (get_args_quantity(args) != 2)
		{
			write(STDERR_FILENO, "minishell: exit: ", 17);
			write(STDERR_FILENO, args->content, ft_strlen(args->content));
			write(STDERR_FILENO, " too many arguments\n", 20);
			(*shell)->exit_status = EXIT_ERR;
		}
		else if (is_numeric(args->next->content) == false)
		{
			write(STDERR_FILENO, "minishell: exit: ", 17);
			write(STDERR_FILENO, args->next->content,
				ft_strlen(args->next->content));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			(*shell)->exit_status = EXIT_NON_NUMERIC;
			exit((*shell)->exit_status);
		}
		else if (is_numeric(args->next->content) == true)
			exit(get_lvl(args->next->content, 1));
	}
	exit((*shell)->exit_status);
}
