#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int				balance = 0;
pthread_mutex_t	mutex;

void	write_balance(int new_balance)
{
	usleep(250000);
	balance = new_balance;
}

int	read_balance(void)
{
	usleep(250000);
	return (balance);
}

void	*deposit_balance(void *amount)
{
	int	account_balance;

    pthread_mutex_lock(&mutex);

	account_balance = read_balance();
	account_balance += *((int *)amount);

	write_balance(account_balance);

    pthread_mutex_unlock(&mutex);
	return (NULL);
}

int	main(void)
{
	int			before;
	int			deposit1;
	int			deposit2;
	pthread_t	thread1;
	pthread_t	thread2;
	int			after;

	before = read_balance();
	printf("Initial balance: %d\n", before);
	pthread_mutex_init(&mutex, NULL);
	deposit1 = 300;
	deposit2 = 200;
	pthread_create(&thread1, NULL, deposit_balance, (void *)&deposit1);
	pthread_create(&thread2, NULL, deposit_balance, (void *)&deposit2);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_mutex_destroy(&mutex);
	after = read_balance();
	printf(" balance: %d\n", after);
	return (0);
}
