#include <stdlib.h>
#include <stdio.h>
#include "ft_deque.h"

static t_deque	*init_test()
{
	t_deque	*deque;

	deque = deque_new();
	if (deque == NULL)
	{
		printf("Error: malloc\n");
		exit(EXIT_FAILURE);
	}
	printf("deque_new success\n");
	debug_deque_print(deque, __func__);
	return (deque);
}

static void	add_front_test(t_deque *deque, char *s)
{
	t_deque_node	*new_node;

	new_node = deque_node_new(s);
	if (new_node == NULL)
	{
		printf("Error: malloc\n");
		exit(EXIT_FAILURE);
	}
	deque_add_front(deque, new_node);
	printf("add_front success\n");
	debug_deque_print(deque, __func__);
}

static void	add_back_test(t_deque *deque)
{
	t_deque_node	*new_node;

	new_node = deque_node_new(NULL);
	if (new_node == NULL)
	{
		printf("Error: malloc\n");
		exit(EXIT_FAILURE);
	}
	deque_add_back(deque, new_node);
	printf("add_back success\n");
	debug_deque_print(deque, __func__);
}

static void	pop_back_test(t_deque *deque)
{
	t_deque_node	*pop_node;

	pop_node = deque_pop_back(deque);
	if (pop_node == NULL)
	{
		printf("pop_back failed\n");
		deque_print(deque);
		return ;
	}
	printf("pop_back success: %s\n", (char *)pop_node->content);
	deque_clear_node(&pop_node, free);
	debug_deque_print(deque, __func__);
}

static void	pop_front_test(t_deque *deque)
{
	t_deque_node	*pop_node;

	pop_node = deque_pop_front(deque);
	if (pop_node == NULL)
	{
		printf("pop_front failed\n");
		deque_print(deque);
		return ;
	}
	printf("pop_front success: %s\n", (char *)pop_node->content);
	deque_clear_node(&pop_node, free);
	debug_deque_print(deque, __func__);
}

static void	pop_selected_node_test(t_deque *deque, size_t idx)
{
	t_deque_node	*pop_node = deque->node;
	size_t			i;

	if (!deque_is_empty(deque))
	{
		i = 0;
		while (pop_node && i < idx)
		{
			pop_node = pop_node->next;
			i++;
		}
	}
	deque_pop_selected_node(deque, pop_node);
	if (pop_node)
	{
		printf("pop_selected success: %s\n", (char *)pop_node->content);
		deque_clear_node(&pop_node, free);
	}
	debug_deque_print(deque, __func__);
}

char *get_s(char c)
{
	char	*s;

	s =  malloc(2);
	s[0] = c;
	s[1] = '\0';
	return (s);
}

int	main(void)
{
	t_deque	*deque = init_test();

	add_front_test(deque, get_s('a'));
	add_back_test(deque);
	add_back_test(deque);
	add_back_test(deque);
	add_back_test(deque);
	add_back_test(deque);
	add_front_test(deque, get_s('b'));
	add_front_test(deque, get_s('c'));
	add_front_test(deque, get_s('d'));
	add_back_test(deque);

	pop_back_test(deque);
	pop_back_test(deque);
	pop_back_test(deque);
	pop_back_test(deque);
	pop_back_test(deque);
	pop_back_test(deque);
	pop_back_test(deque);
	pop_back_test(deque);
	pop_back_test(deque);
	pop_back_test(deque);
	pop_back_test(deque);

	add_front_test(deque, get_s('c'));
	add_front_test(deque, get_s('b'));
	add_front_test(deque, get_s('a'));

	pop_front_test(deque);
	pop_front_test(deque);
	pop_front_test(deque);
	pop_front_test(deque);
	pop_front_test(deque);
	pop_front_test(deque);

	add_front_test(deque, get_s('c'));
	add_front_test(deque, get_s('b'));
	add_front_test(deque, get_s('a'));

	pop_selected_node_test(deque, 1);

	add_front_test(deque, get_s('d'));
	add_front_test(deque, get_s('e'));
	add_front_test(deque, get_s('f'));

	pop_selected_node_test(deque, 1);
	pop_selected_node_test(deque, 3);
	pop_selected_node_test(deque, 0);
	pop_selected_node_test(deque, 1);
	pop_selected_node_test(deque, 0);
	pop_selected_node_test(deque, 0);

	deque_clear_all(&deque, free);
	return (EXIT_SUCCESS);
}
