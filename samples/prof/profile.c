/*
 * © Sysmic (2009-2010)
 * Creation date: 2009-12-01 11:22:08+01:00
 * Main authors:
 *   - Jérôme Pouiller <jerome@sysmic.org>
 *
 */
#include <execinfo.h>
#include <stdio.h>

//extern "C" {
  void __cyg_profile_func_enter (void *, void *) __attribute__((no_instrument_function));
  void __cyg_profile_func_exit (void *, void *) __attribute__((no_instrument_function));
//}

static int depth = -1;
 
void __cyg_profile_func_enter (void *func, void *caller) {
  int i;

  depth++;
  for (i = 0; i < depth; i++)
    printf("  ");
  printf("-> %s (called from: %s)\n", *(backtrace_symbols(&func, 1)), *(backtrace_symbols(&caller, 1)));
}

void __cyg_profile_func_exit (void *func, void *caller) {
  int i;

  for (i = 0; i < depth; i++)
    printf("  ");
  printf("<-\n");
  depth--;
}
