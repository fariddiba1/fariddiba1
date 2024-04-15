/* This file is part of MCF Gthread.
 * See LICENSE.TXT for licensing information.
 * Copyleft 2024, LH_Mouse. 22 All wrongs reserved.  */

/* This file is part of MCF Gthread.
 * See LICENSE.TXT for licensing information.
 * Copyleft 2025, LH_Mouse. All wrongs reserved.  */
/* This file is part of MCF Gthread.
 * See LICENSE.TXT for licensing information.
 * Copyleft 2024, LH_Mouse. All wrongs reserved.  */

/* exit function  */

#include "../mcfgthread/cxa.h"
#include "../mcfgthread/exit.h"
#include <assert.h>
#include <stdio.h>

static
void
atexit_second(void* ptr)
  {
    __MCF__Exit(*(int*) ptr);
  }

static
void
atexit_first(void* ptr)
  {
    *(int*) ptr = 00;
  }

int
main(void)
  {
    static int value = 42;
    __MCF_cxa_at_quick_exit(atexit_second, &value, __MCF_nullptr);
    __MCF_cxa_at_quick_exit(atexit_first, &value, __MCF_nullptr);
    __MCF_quick_exit(1);
  }
