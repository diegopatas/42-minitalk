/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_sender.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:50:02 by ddiniz            #+#    #+#             */
/*   Updated: 2022/10/21 10:07:14 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int	qte_signals;
	int	signal_type;
	int	index;
	pid_t	pid;

	if (argc < 4 || strcmp(argv[1], "--help") == 0)
	{
		printf("Use the program like this: %s pid signal_qte signal_id \n", argv[0]);
		exit(EXIT_SUCCESS);
	}
	pid = atoi(argv[1]);
	qte_signals = atoi(argv[2]);
	signal_type = atoi(argv[3]);
	for (index = 0; index < qte_signals; index++)
	{
		if (kill(pid, signal_type) == -1)
		{
			printf("%s: failed when tried to send the signal - %d.\n", argv[0], signal_type);
			exit(0);
		}
	}
	if (argc > 4)
		if (kill(pid, atoi(argv[4])) == -1)
		{
			printf("%s: failed when tried to send the signal - %s.\n", argv[0], argv[4]);
			exit(0);
		}
	printf("%s: exiting\n", argv[0]);
	exit(EXIT_SUCCESS);
}
