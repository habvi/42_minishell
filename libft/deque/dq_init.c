#include "deque.h"

void	deque_init(t_deque *deque, int init_num, t_deque *init_node)
{
	deque->num = init_num;
	deque->next = init_node;
	deque->prev = init_node;
}
