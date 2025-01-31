/**
 * Copyright (c) 2009, Sun Microsystems Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of Sun Microsystems Inc. nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <sys/types.h>
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#ifdef HAVE_SYS_RESOURCE_H
#include <sys/resource.h>
#endif

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "sigar.h"
#include "sigar_private.h"
#include "sigar_format.h"
#include "sigar_tests.h"

TEST(test_sigar_loadavg_get) {
	sigar_loadavg_t loadavg;
	int ret;

	if (SIGAR_OK == (ret = sigar_loadavg_get(t, &loadavg))) {
		assert(loadavg.loadavg[0] >= 0);
		assert(loadavg.loadavg[1] >= 0);
		assert(loadavg.loadavg[2] >= 0);
	} else {
		switch (ret) {
			/* track the expected error code */
		default:
#if !(defined(_WIN32))
			/* win32 has no loadavg */
			fprintf(stderr, "ret = %d (%s)\n", ret, sigar_strerror(t, ret));
			assert(ret == SIGAR_OK); 
#endif
			break;
		}
	}

	return 0;
}

int main() {
	sigar_t *t;
	int err = 0;
	
	int ret = sigar_open(&t);
	assert(SIGAR_OK == ret);

	test_sigar_loadavg_get(t);

	sigar_close(t);

	return 0;
}
