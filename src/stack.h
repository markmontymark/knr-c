#ifndef MRK_KNR_C_STACK_H_
#define MRK_KNR_C_STACK_H_

#include "arraylist_int.h"
#include <stdio.h>

typedef struct stk stk_t;
struct stk
{
	int idx;
	arraylist_int_t * data;
};
#define stk_s sizeof(stk_t)

stk_t * 	stk_new();
int		stk_is_empty(stk_t *);
void 		stk_push(stk_t *,int );
int 		stk_pop (stk_t *);
void 		stk_dump(stk_t *,FILE * out);
void 		stk_print(stk_t *,FILE * out);
void 		stk_free(stk_t *);
int 		stk_get_top(stk_t *);
void		stk_swap(stk_t *, int, int);

#endif
