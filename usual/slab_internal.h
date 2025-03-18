#ifndef _USUAL_SLAB_INTERNAL_H_
#define _USUAL_SLAB_INTERNAL_H_

#include <usual/statlist.h>
#include <usual/slab.h>
#include <usual/spinlock.h>

/*
* Store for pre-initialized objects of one type.
*/
struct Slab {
	struct List head;
	struct StatList freelist;
	struct StatList fraglist;
	char name[32];
	unsigned final_size;
	unsigned total_count;
	slab_init_fn  init_func;
	CxMem *cx;
};

/*
 * Header for each slab.
 */
struct SlabFrag {
	struct List head;
};


void init_slab(struct Slab *slab, const char *name, unsigned obj_size,
		      unsigned align, slab_init_fn init_func,
		      CxMem *cx);

void slab_destroy_internal(struct Slab *slab);

void run_slab_stats(struct Slab *slab, slab_stat_fn cb_func, void *cb_arg);

#endif /* _USUAL_SLAB_INTERNAL_H_ */
