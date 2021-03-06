/* getitimer -- Get the state of an interval timer.  Linux/Alpha/tv32 version.
   Copyright (C) 2019-2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <shlib-compat.h>

#if SHLIB_COMPAT (libc, GLIBC_2_0, GLIBC_2_1)

#include <sys/time.h>
#include <alpha-tv32-compat.h>

int
attribute_compat_text_section
__setitimer_tv32 (int which, const struct itimerval32 *restrict new_value,
		  struct itimerval32 *restrict old_value)
{
  struct itimerval new_value_64;
  new_value_64.it_interval
    = alpha_valid_timeval32_to_timeval (new_value->it_interval);
  new_value_64.it_value
    = alpha_valid_timeval32_to_timeval (new_value->it_value);

  if (old_value == NULL)
    return __setitimer (which, &new_value_64, NULL);

  struct itimerval old_value_64;
  if (__setitimer (which, &new_value_64, &old_value_64) == -1)
    return -1;

  /* Write all fields of 'old_value' regardless of overflow.  */
  old_value->it_interval
     = alpha_valid_timeval_to_timeval32 (old_value_64.it_interval);
  old_value->it_value
     = alpha_valid_timeval_to_timeval32 (old_value_64.it_value);
  return 0;
}

compat_symbol (libc, __setitimer_tv32, setitimer, GLIBC_2_0);
#endif
