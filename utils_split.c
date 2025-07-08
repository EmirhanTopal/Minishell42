#include "minishell.h"

static	int	countwords(char const *s, char c)
{
	int	i;
	int	count;
	int	flag;

	i = 0;
	count = 0;
	flag = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && flag == 0)
		{
			flag = 1;
			count++;
		}
		else if (s[i] == c)
		{
			flag = 0;
		}
		i++;
	}
	return (count);
}

static	char	**ft_free(char **s1, size_t word)
{
	while (word > 0)
	{
		word--;
		free(s1[word]);
	}
	free(s1);
	return (NULL);
}

static	char	*writewords(char const *s, int start, int finish)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (finish - start + 1));
	if (!str)
		return (NULL);
	while (start < finish)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	int		ba;
	int		index;
	char	**bigarr;

	i = -1;
	index = -1;
	ba = 0;
	bigarr = (char **) malloc (sizeof(char *) * (countwords(s, c) + 1));
	if (bigarr == NULL)
		return (ft_free(bigarr, i + 1));
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && (index >= 0))
		{
			bigarr[ba++] = writewords(s, index, i);
			if (bigarr[ba - 1] == NULL)
				return (ft_free(bigarr, ba - 1));
			index = -1;
		}
	}
	bigarr[ba] = NULL;
	return (bigarr);
}