/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:55:57 by ddiniz            #+#    #+#             */
/*   Updated: 2022/11/09 23:02:43 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

static	int	message_char_send(int target_pid, unsigned char target_char)
{
	unsigned char	mask;

	mask = 1 << 7;
	while (mask)
	{
		if (target_char & mask)
			kill(target_pid, SIGUSR1);
		else
			kill(target_pid, SIGUSR2);
		mask >>= 1;
		usleep(500);
	}
	return (EXIT_SUCCESS);
}

static	int	message_send(int target_pid, const char *message)
{
	while (*message)
	{
		message_char_send(target_pid, *message);
		message++;
	}
	ft_printf("\nEnding transmission...%c\n", 0);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	if (argc == 3)
		return (message_send(ft_atoi(argv[1]), argv[2]));
	ft_printf("Invalid number of arguments!");
	return (EXIT_SUCCESS);
}
