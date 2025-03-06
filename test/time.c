#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct s_philo
{
	struct timeval	start_time;
}					t_philo;

uint32_t	get_elapsed_time(struct timeval start)
{
	struct timeval	current;
	uint32_t		diff;

	if (gettimeofday(&current, NULL))
		perror("gettimeofday error");
	diff = (current.tv_sec - start.tv_sec) * 1000;
	diff += (current.tv_usec - start.tv_usec) / 1000;
	return (diff);
}

int	main(void)
{
	t_philo	philo;

	gettimeofday(&philo.start_time, NULL);
	while (1)
	{
		printf("%d\n", get_elapsed_time(philo.start_time));
		usleep(200000);
	}
	return (0);
}
