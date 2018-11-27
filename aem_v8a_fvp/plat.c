/*
 * Copyright 2018 Google LLC
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

paddr_t plat_get_fdt_addr(void)
{
	/* FDT is loaded at a known address. */
	return pa_init(0x82000000);
}

void plat_get_initrd_range(paddr_t *begin, paddr_t *end)
{
	/* initrd is loaded at a known address but...
	 * TODO: the size is hardcoded */
	*begin = pa_init(0x84000000);
	*end = pa_add(*begin, 0x12EF200);
}
