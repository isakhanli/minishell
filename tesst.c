#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		i;
	char	*a, *b, *c;
	char	aa[] = "ech";
	char	bb[] = "echo";
	char	cc[] = "echoo";

	a = aa;
	b = bb;
	c = cc;
	printf("a = %s, compare word = 'echo', strncmp(a, echo, len(aa)) = %i, len a = %lu\n", a, strncmp(a, "echo", strlen(aa)), strlen(a));
	printf("b = %s, compare word = 'echo', strncmp(b, echo, len(bb) = %i, len b = %lu\n", b, strncmp(b, "echo", strlen(bb)), strlen(b));
	printf("c = %s, compare word = 'echo', strncmp(c, echo, len(cc)) = %i, len c = %lu\n", c, strncmp(c, "echo", strlen(cc)), strlen(c));
	printf("a = %s, compare word = 'echo', strncmp(a, echo, len(aa)) = %i\n", a, strncmp("echo", a, strlen(a)));
	printf("b = %s, compare word = 'echo', strncmp(b, echo, len(bb) = %i\n", b, strncmp("echo", b, strlen(b)));
	printf("c = %s, compare word = 'echo', strncmp(c, echo, len(cc)) = %i\n", c, strncmp("echo", c, strlen(c)));
	return (1);
}