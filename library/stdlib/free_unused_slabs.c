/*

 */

#ifndef _STDLIB_HEADERS_H
#include "stdlib_headers.h"
#endif /* _STDLIB_HEADERS_H */

/****************************************************************************/

#ifndef _STDLIB_MEMORY_H
#include "stdlib_memory.h"
#endif /* _STDLIB_MEMORY_H */

/****************************************************************************/

/* Free all currently unused slabs, regardless of whether they
 * are ready to be purged (SlabNode.sn_EmptyDecay == 0).
 */
void
__free_unused_slabs(void)
{
	if(__slab_data.sd_InUse)
	{
		struct MinNode * free_node;
		struct MinNode * free_node_next;
		struct SlabNode * sn;

		__memory_lock();

		for(free_node = (struct MinNode *)__slab_data.sd_EmptySlabs.mlh_Head ; 
		    free_node->mln_Succ != NULL ;
		    free_node = free_node_next)
		{
			free_node_next = (struct MinNode *)free_node->mln_Succ;

			/* free_node points to SlabNode.sn_EmptyLink, which
			 * directly follows the SlabNode.sn_MinNode.
			 */
			sn = (struct SlabNode *)&free_node[-1];

			/* Unlink from list of empty slabs. */
			Remove((struct Node *)free_node);

			/* Unlink from list of slabs of the same size. */
			Remove((struct Node *)sn);

			FreeVec(sn);
		}

		__memory_unlock();
	}
}
