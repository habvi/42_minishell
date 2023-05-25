#include "test.h"

// want to
// ( 1 + 2 ) * ( 3 + 4 ) + 5
// -> [( 1 + 2 )] * [( 3 + 4 ) + 5]
//  sep by term ... ?

// priority of pipeline commands
// a | b | c && d | e || f | g | h
// [a | b | c] && [d | e] || [f | g | h]

// priority of four arithmetic operations
// a + b + c * d + e / f + g + h
// a + b + (c * d) + (e / f) + g + h になるので、四則演算とは優先順位が異なる


// a * b * c  +  d * e -  f * g * h
//  is same priority as
// a | b | c  && d | e || f | g | h


//  a * b * c  +  d * e  -  f * g * h
// (a * b * c) + (d * e) - (f * g * h)
// left + right
//        left           - right


// treeをたどりながら実行すれば良いので、切り取る必要はない？

void    cut_sub_tree(t_tree *node)
{

}