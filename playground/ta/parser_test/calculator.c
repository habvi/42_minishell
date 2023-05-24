#include "test.h"

int calculator(t_tree *node)
{
    int left;
    int right;

    if (!node)
        return (0);
    if (node->kind == nd_num)
        return (node->val);
    left = calculator(node->lhs);
    right = calculator(node->rhs);
//    printf("left:%d, right:%d\n", left, right);
    if (node->kind == nd_add)
        return (left + right);
    if (node->kind == nd_sub)
        return (left - right);
    if (node->kind == nd_mul)
        return (left * right);
    return (left / right);
}
