/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_build_cmd.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaldy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 10:20:49 by cbaldy            #+#    #+#             */
/*   Updated: 2016/03/25 16:16:30 by cbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_BUILD_CMD_H
# define TREE_BUILD_CMD_H

# include "lexer.h"

t_tree	*tree_build_cmd(t_parse *tok);
int		tree_place_cmd(t_tree *new, t_tree **root);
t_tree	*tree_new_elem(char **cmd, int type);
int		tree_place_type_pipe(t_tree *new, t_tree **root);
int		tree_place_type_red(t_tree *new, t_tree **root);
int		tree_place_type_end(t_tree *new, t_tree **root);

#endif
