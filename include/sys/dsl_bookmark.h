/*
 * CDDL HEADER START
 *
 * This file and its contents are supplied under the terms of the
 * Common Development and Distribution License ("CDDL"), version 1.0.
 * You may only use this file in accordance with the terms of version
 * 1.0 of the CDDL.
 *
 * A full copy of the text of the CDDL should have accompanied this
 * source.  A copy of the CDDL is also available via the Internet at
 * http://www.illumos.org/license/CDDL.
 *
 * CDDL HEADER END
 */
/*
 * Copyright (c) 2013 by Delphix. All rights reserved.
 */

#ifndef	_SYS_DSL_BOOKMARK_H
#define	_SYS_DSL_BOOKMARK_H

#include <sys/zfs_context.h>
#include <sys/dsl_dataset.h>

#ifdef	__cplusplus
extern "C" {
#endif

struct dsl_pool;
struct dsl_dataset;

/*
 * On disk zap object.
 */
typedef struct zfs_bookmark_phys {
	uint64_t zbm_guid;		/* guid of bookmarked dataset */
	uint64_t zbm_creation_txg;	/* birth transaction group */
	uint64_t zbm_creation_time;	/* bookmark creation time */

	/* the following fields are reserved for redacted send / recv */
	uint64_t zbm_redaction_obj;	/* redaction list object */
	uint64_t zbm_flags;		/* ZBM_FLAG_* */
	uint64_t zbm_referenced_bytes_refd;
	uint64_t zbm_compressed_bytes_refd;
	uint64_t zbm_uncompressed_bytes_refd;
	uint64_t zbm_referenced_freed_before_next_snap;
	uint64_t zbm_compressed_freed_before_next_snap;
	uint64_t zbm_uncompressed_freed_before_next_snap;

	/* fields used for raw sends */
	uint64_t zbm_ivset_guid;
} zfs_bookmark_phys_t;


#define	BOOKMARK_PHYS_SIZE_V1	(3 * sizeof (uint64_t))
#define	BOOKMARK_PHYS_SIZE_V2	(12 * sizeof (uint64_t))

int dsl_bookmark_create(nvlist_t *, nvlist_t *);
int dsl_get_bookmarks(const char *, nvlist_t *, nvlist_t *);
int dsl_get_bookmarks_impl(dsl_dataset_t *, nvlist_t *, nvlist_t *);
int dsl_bookmark_destroy(nvlist_t *, nvlist_t *);
int dsl_bookmark_lookup(struct dsl_pool *, const char *,
    struct dsl_dataset *, zfs_bookmark_phys_t *);

#ifdef	__cplusplus
}
#endif

#endif /* _SYS_DSL_BOOKMARK_H */
