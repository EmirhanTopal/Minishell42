#include "minishell.h"

int is_numeric(char *str)
{
    int i = 0;

    if (!str || !str[0])
        return 0;

    // Opsiyonel: negatif sayılara izin ver
    if (str[0] == '-' || str[0] == '+')
        i++;

    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

int	ft_atoi(char *str)
{
	int		i;
    int		sign;
    int		result;
    
	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
        i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (sign * result);
}