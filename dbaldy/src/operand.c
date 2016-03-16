/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 17:48:33 by dbaldy            #+#    #+#             */
/*   Updated: 2016/02/27 15:17:40 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_pwd(char **tabl)
{
	char	*pwd;
	char	*ret;
	int		i;
	int		opt;

	i = 1;
	pwd = NULL;
	while (tabl[i] && (opt = check_opt(tabl[i])) > 0)
		i++;
	if (opt != 2 || (pwd = get_env_var("PWD")) == NULL)
	{
		pwd = getcwd(pwd, 1000);
		ret = ft_strjoin("PWD=", pwd);
		add_env(ret);
		free(ret);
	}
	else
	{
		ret = ft_strjoin("PWD=", pwd);
		add_env(ret);
		free(ret);
	}
	return (pwd);
}

char		*get_operand(char **tabl)
{
	int		i;
	int		opt;

	i = 1;
	while (tabl[i] && (opt = check_opt(tabl[i])) > 0)
		i++;
	if (tabl[i] && tabl[i + 1] && tabl[i + 2])
	{
		ft_dprintf(STDERR_FILENO, "cd: too many arguments\n");
		return (NULL);
	}
	if (tabl[i] == NULL)
		return (get_env_var("HOME"));
	else if (tabl[i] && tabl[i + 1])
		return (substitute(tabl[i], tabl[i + 1]));
	else
		return (my_aliases(tabl[i]));
	return (NULL);
}

int			check_opt(char *option)
{
	int		i;

	i = 1;
	if (option == NULL)
		return (1);
	if (option[0] != '-')
		return (0);
	while (option[i])
	{
		if (option[i] == 'P' || option[i] == 'L')
			i++;
		else
			return (0);
	}
	if (i < 2)
		return (0);
	return ((option[i - 1] == 'P') ? 2 : 1);
}

char		*get_path(char *operand)
{
	char	*local;
	char	*home;
	char	*ret;

	if (operand[0] == '/')
		return (ft_strdup(operand));
	else if (ft_strcmp(operand, ".") == 0 || ft_strcmp(operand, "..") == 0)
	{
		if ((home = get_env_var("PWD")) == NULL)
			home = getcwd(home, 1000);
		ret = ft_strjoin_multiple(3, home, "/", operand);
		free(home);
		return (ret);
	}
	else if ((local = ft_strjoin("./", operand)) != NULL)
		return (local);
	return (NULL);
}

void		change_pwd(char *operand, char *pwd, char **tabl)
{
	char	*buf;
	int		i;
	int		opt;

	buf = NULL;
	i = 1;
	change_env_var("OLDPWD", pwd);
	while (tabl[i] && (opt = check_opt(tabl[i])) > 0)
		i++;
	if (tabl[i] != NULL && (opt = check_opt(tabl[i - 1])) == 2)
	{
		buf = getcwd(buf, 1000);
		change_env_var("PWD", buf);
	}
	else if (ft_strcmp(operand, ".") == 0)
		return ;
	else if ((buf = ft_mypwd(operand)) != NULL)
		change_env_var("PWD", buf);
	if (buf != NULL)
		free(buf);
	if (g_print_ch != NULL)
		ft_dprintf(1, "%s\n", g_print_ch);
	if (g_print_ch != NULL)
		free(g_print_ch);
}
