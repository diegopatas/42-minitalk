/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:29:04 by ddiniz            #+#    #+#             */
/*   Updated: 2022/10/20 22:57:51 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <string.h>


static void	signal_handler(int sig)
{
	static int count_c = 0;

	if (sig == SIGINT)
	{
		count_c++;
		printf("Number of pressing 'CTRL+C' (%d)\n", count_c);
		printf("Signal name: %s\n", strsignal(sig));
		return ;
	}
	else if (sig == SIGTSTP)
	{
		printf("Here\n");
		printf("Signal name: %s\n", strsignal(sig));
		return ;
	}
	printf("You pressed 'CTRL+\\'!\n");
	printf("Good job!");
	printf("Signal name: %s\n", strsignal(sig));
	exit(0);
}

int	main(void)
{
	sigset_t group_to_block;
	sigset_t group_aux;
	int	count;

	/* Setting mask on group_to_block_1: blocking CTRL+C signal */
	sigemptyset(&group_to_block);
	sigaddset(&group_to_block, SIGINT);
	if (sigprocmask(SIG_BLOCK, &group_to_block, &group_aux) == -1)
	{
		printf("The program failed to set the 'group_to_block' as mask!%c\nExiting...", 0);
		exit(0);
	}
	/* This loop cannot be stopped by CTRL+C signal */
	count = 0;
	while (count < 7)
	{
		printf("Wait %d rounds to interrupt this program with 'CTRL+C' signal\n", 7 - count);
		sleep(1);
		count++;
	}
	if (sigprocmask(SIG_SETMASK, &group_aux, NULL) == -1)
	{
		printf("The program failed to set the 'group_aux' as mask!%c\nExiting...", 0);
		exit(0);
	}
	if (sigprocmask(SIG_UNBLOCK, &group_to_block, &group_aux) == -1)
	{
		printf("The program failed to unset the 'group_aux' as mask!%c\nExiting...", 0);
		exit(0);
	}
	if (signal(SIGINT, signal_handler) == SIG_ERR) //handle CTRL+C
	{
		printf("The program failed to define signal handling %c\nExiting...", 0);
		exit(0);
	}
	if (signal(SIGTSTP, signal_handler) == SIG_ERR) //handle CTRL+Z
	{
		printf("The program failed to define signal handling %c\nExiting...", 0);
		exit(0);
	}
	if (signal(SIGQUIT, signal_handler) == SIG_ERR)//handle "CTRL+\"
	{
		printf("The program failed to define signal handling %c\nExiting...", 0);
		exit(0);
	}
	while(1)
		pause();
}
