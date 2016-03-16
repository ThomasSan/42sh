/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir_aux2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 15:32:08 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/14 18:05:31 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_path(char *tab, char *buf)
{
	char	*pwd;

	if (ft_strcmp(tab, "..") != 0 && ft_strcmp(tab, ".") != 0)
		pwd = ft_strjoin_multiple(3, buf, "/", tab);
	else if (ft_strcmp(tab, ".") == 0)
		pwd = ft_strdup(buf);
	else
		pwd = ft_strtrunc(buf, '/');
	return (pwd);
}

char		*clean_pwd(char *ret)
{
	char		**tabl;
	char		*buf;
	int			i;
	char		*pwd;

	i = 0;
	pwd = ft_strdup("");
	tabl = my_pwd(ret);
	free(ret);
	buf = ft_strdup("");
	while (tabl[i])
	{
		free(pwd);
		pwd = build_path(tabl[i], buf);
		free(buf);
		buf = (i > 0) ? ft_strdup(pwd) : ft_strdup("");
		i++;
	}
	ft_freetab(tabl);
	free(buf);
	return (pwd);
}

char		*ft_mypwd(char *operand)
{
	char		*ret;
	char		*buf;

	if (operand[0] == '/')
		return (ft_strdup(operand));
	else
	{
		if ((buf = get_env_var("PWD")) == NULL)
			buf = getcwd(buf, 1000);
		ret = (ft_strcmp(buf, "/") != 0) ?
			ft_strjoin_multiple(3, buf, "/", operand) : ft_strdup(buf);
		free(buf);
	}
	ret = clean_pwd(ret);
	return (ret);
}

char		*my_aliases(char *operand)
{
	char	*buf;
	char	*new;
	char	*old;

	new = ft_strdup(operand);
	buf = get_env_var("HOME");
	if (operand[0] == '-' && (operand[1] == '/' || operand[1] == '\0'))
	{
		if ((old = get_env_var("OLDPWD")) == NULL)
			old = ft_strdup("");
		free(new);
		new = ft_strjoin(old, &operand[1]);
		g_print_ch = (buf != NULL) ? ft_replace_str(new, buf, "~") :
			ft_strdup(new);
		free(old);
	}
	else if (operand[0] == '~' && (operand[1] == '/' || operand[1] == '\0'))
	{
		free(new);
		new = (buf != NULL) ? ft_strjoin(buf, &operand[1]) : new;
	}
	if (buf != NULL)
		free(buf);
	return (new);
}
