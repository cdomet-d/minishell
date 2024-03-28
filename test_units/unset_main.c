/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:53:39 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/28 14:12:28 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env	*env;

// 	// add in if of unset : 
// 	// printf("Match for %s found in node %ld > %s\n\n", key, i, (*env)->env);
// 	env = NULL;
// 	if (argc == 2)
// 	{
// 		init_env(envp, &env);
// 		print_env_for(env);
// 		unset(&env, argv[1]);
// 		print_env_for(env);
// 		env_freelst(env);
// 		exit(EXIT_SUCCESS);
// 	}
// 	else
// 		print_error(0, "Expected one argument");
// 	exit(EXIT_FAILURE);
// }