/*
 * Copyright 2018 The Hafnium Authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "hf/addr.h"
#include "hf/dlog.h"
#include "hf/fdt_handler.h"
#include "hf/mpool.h"

/* This is set by plat_entry.S. */
uintpaddr_t plat_fdt_addr;

paddr_t plat_get_fdt_addr(void)
{
	return pa_init(plat_fdt_addr);
}

void plat_get_initrd_range(paddr_t *begin, paddr_t *end, struct mpool *ppool)
{
	struct fdt_header *fdt;
	struct fdt_node n;

	/* Get the memory map from the FDT. */
	fdt = fdt_map(plat_get_fdt_addr(), &n, ppool);
	if (!fdt) {
		return;
	}

	if (!fdt_find_child(&n, "")) {
		dlog("Unable to find FDT root node.\n");
		goto out_unmap_fdt;
	}

	fdt_find_initrd(&n, begin, end);

out_unmap_fdt:
	if (!fdt_unmap(fdt, ppool)) {
		dlog("Unable to unmap fdt.");
	}
}
