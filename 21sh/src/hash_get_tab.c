/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_get_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 10:54:42 by cbaldy            #+#    #+#             */
/*   Updated: 2016/04/25 16:27:47 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	hash_add_elem(t_hash_tree *new, t_hash_tree *root)
{
	t_hash_tree	*tmp;
	int			i;

	tmp = root;
	i = 1;
	while (i != 0)
	{
		if (ft_strcmp(new->name, tmp->name) > 0 && tmp->right != NULL)
			tmp = tmp->right;
		else if (ft_strcmp(new->name, tmp->name) <= 0 && tmp->left != NULL)
			tmp = tmp->left;
		else
			i = 0;
	}
	if (ft_strcmp(new->name, tmp->name) > 0)
		tmp->right = new;
	else if (ft_strcmp(new->name, tmp->name) <= 0)
		tmp->left = new;
	return (0);
}

static int	hash_build_tree(char *name, char *path, t_hash_tree **root)
{
	t_hash_tree	*new;

	if ((new = (t_hash_tree *)malloc(sizeof(t_hash_tree))) == NULL)
		return (0);
	new->name = ft_strdup(name);
	new->path = mod_strjoin(ft_strjoin(path, "/"), name, 1);
	new->left = NULL;
	new->right = NULL;
	new->root = NULL;
	if (*root == NULL)
		*root = new;
	else
		hash_add_elem(new, *root);
	return (1);
}

static int	hash_build_tab(t_hash_tree *root, char **arr, int i)
{
	if (root->left != NULL)
		i = hash_build_tab(root->left, arr, i);
	arr[i] = mod_strjoin(ft_strjoin(root->name, "="), root->path, 1);
	i++;
	if (root->right != NULL)
		i = hash_build_tab(root->right, arr, i);
	free(root->name);
	free(root->path);
	free(root);
	return (i);
}

static int	hash_explore_dir(char *path, t_hash_tree **root)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				nb;

	nb = 0;
	if ((dirp = opendir(path)) != NULL)
	{
		while ((dp = readdir(dirp)) != NULL)
			if (dp->d_name[0] != '.')
				nb += hash_build_tree(dp->d_name, path, root);
		closedir(dirp);
	}
	return (nb);
}

int			hash_get_tab(void)
{
	char		**path;
	char		**arr;
	t_hash_tree	*root;
	int			i;
	int			nb;

	if ((i = sh_is_new_var("PATH")) < 0)
		return (0);
	root = NULL;
	nb = 0;
	path = ft_strsplit(&(ft_strchr(g_env[i], '=')[1]), ':');
	i = 0;
	while (path[i] != NULL)
	{
		nb += hash_explore_dir(path[i], &root);
		i++;
	}
	if ((arr = (char **)malloc(sizeof(char *) * (nb + 1))) == NULL)
		return (0);
	hash_build_tab(root, arr, 0);
	arr[nb] = NULL;
	g_hash = arr;
	ft_free_tab(path);
	return (0);
}
