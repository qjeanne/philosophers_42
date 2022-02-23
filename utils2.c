#include "philo.h"

static void	ft_itoa_malloc(char **str, long int ncopy, int size)
{
	if (ncopy < 0)
		*str = malloc(size + 2);
	else
		*str = malloc(size + 1);
}

int	ft_nbrlen(long int n)
{
	int		size;

	if (n == 0)
		return (1);
	size = 0;
	while (n)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int			size;
	char		*str;
	long int	ncopy;

	ncopy = n;
	size = ft_nbrlen(n);
	ft_itoa_malloc(&str, ncopy, size);
	if (str == 0)
		return (0);
	if (ncopy < 0)
	{
		str[0] = '-';
		ncopy = ncopy * (-1);
		size++;
	}
	str[size--] = '\0';
	if (ncopy == 0)
		str[size] = '0';
	while (ncopy)
	{
		str[size--] = ncopy % 10 + '0';
		ncopy = ncopy / 10;
	}
	return (str);
}
