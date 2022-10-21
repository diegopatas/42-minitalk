#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
// #define _BSD_SOURCE
#define _GNU_SOURCE
#include <string.h>

void	print_sigset(FILE *file_target, const char *prefix, const sigset_t *signal_set)
{
	int	signal;
	int	count;

	count = 0;
	for (signal = 1; signal < NSIG; signal++)
	{
		if (sigismember(signal_set, signal))
		{
			count++;
			fprintf(file_target, "%s%d (%s)\n", prefix, signal, strsignal(signal));
		}
	}
	if (count == 0)
		fprintf(file_target, "%s<empty signal set>\n", prefix);
}

int	print_sigmask(FILE *file_target, const char *message)
{
	sigset_t actual_mask;

	if (message != NULL)
		fprintf(file_target, "%s", message);

	if (sigprocmask(SIG_BLOCK, NULL, &actual_mask) == -1)
		return (-1);
	print_sigset(file_target, "\t\t", &actual_mask);
	return (0);
}

int	print_pendingsigs(FILE *file_target, const char *message)
{
	sigset_t pending_sigs;

	if (message != NULL)
		fprintf(file_target, "%s", message);
	if (sigpending(&pending_sigs) == -1)
		return (-1);
	print_sigset(file_target, "\t\t", &pending_sigs);
	return (0);
}
