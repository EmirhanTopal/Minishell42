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

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)(c))
		{
			return ((char *) &s[i]);
		}
		i++;
	}
	if ((unsigned char)(c) == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*p2;

	i = 0;
	while (s1[i] != '\0')
	{
		i++;
	}
	p2 = (char *) malloc((i + 1) * sizeof(char));
	if (p2 == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		((unsigned char *) p2)[i] = s1[i];
		i++;
	}
	p2[i] = '\0';
	return (p2);
}

char *ft_strndup(const char *s, size_t n)
{
    char *dup;
    size_t i;

    dup = malloc(n + 1);
    if (!dup)
        return (NULL);
    i = 0;
    while (i < n && s[i])
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}