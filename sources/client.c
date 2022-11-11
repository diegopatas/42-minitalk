/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:55:57 by ddiniz            #+#    #+#             */
/*   Updated: 2022/11/11 12:42:00 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk_bonus.h>

static volatile int	g_answer;

static	void	signal_handler(int signal)
{
	if (signal == SIGUSR1)
		g_answer = TRUE;
	return ;
}

static	int	message_char_send(int target_pid, unsigned char target_char)
{
	unsigned char		mask;

	mask = 1 << 7;
	while (mask)
	{
		g_answer = FALSE;
		usleep(MICROSECS);
		if (target_char & mask)
			kill(target_pid, SIGUSR1);
		else
			kill(target_pid, SIGUSR2);
		mask >>= 1;
		while (!g_answer)
			;
	}
	return (EXIT_SUCCESS);
}

static	int	message_send(int target_pid, const char *message)
{
	int	ch_count;

	ch_count = 0;
	if (signal(SIGUSR1, signal_handler) == SIG_ERR)
	{
		ft_printf("Fatal: SIGUSR1 setting failed!%c\n", 0);
		exit(EXIT_FAILURE);
	}
	if (signal(SIGUSR2, signal_handler) == SIG_ERR)
	{
		ft_printf("Fatal: SIGUSR2 setting failed!%c\n", 0);
		exit(EXIT_FAILURE);
	}
	while (*message)
	{
		message_char_send(target_pid, *message);
		message++;
		ch_count++;
	}
	ft_printf("Ending transmission... \nDone!%c\n", 0);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	if (argc == 3)
		return (message_send(ft_atoi(argv[1]), argv[2]));
	ft_printf("Invalid number of arguments!");
	ft_printf("Usage: ./client server_PID <Message>%c", 0);
	return (EXIT_SUCCESS);
}
