#include <stdlib.h>
#include <stdio.h>

/* ###########################

$ gcc free.c && ./a.out
===== s1="a" =====
s1  :a, 0x16d5533b0
free:0�ׁ�q, 0x16d5533b0

===== s2="a" =====
s2  :a, 0x16d5533a8
s2  :(null), 0x16d5533a8
free:(null), 0x16d5533a8

 ########################### */

int main(void)
{
	char *s1 = (char *)malloc(sizeof(char *) * 2);
	s1[0] = 'a';
	s1[1] = '\0';

	printf("===== s1=\"a\" =====\n");
	printf("s1  :%s, %p\n", s1, &s1);
	free(s1);
	printf("free:%s, %p\n\n", s1, &s1);


	char *s2 = (char *)malloc(sizeof(char *) * 2);
	s2[0] = 'a';
	s2[1] = '\0';

	printf("===== s2=\"a\" =====\n");
	printf("s2  :%s, %p\n", s2, &s2);
	s2 = NULL;
	printf("s2  :%s, %p\n", s2, &s2);
	free(s2);
	printf("free:%s, %p\n\n", s2, &s2);

	return (0);
}
