// NOTE: This file contains code derived from or inspired by:
//		AstriX ("The AstriX Operating System") at https://codeberg.org/AstriX/AstriX.
// Copyright (c) 2023-2025 NotYourFox, sigsegv
// SPDX-License-Identifier: GPL-3.0-or-later

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "kreflock.h"
#include "kstring.h"
#include "sys/panic.h"
#include <stdbool.h>
#include <stdint.h>

struct reflock_private {
	struct {
		char *magic;
		volatile int refcount;
	} data;
};

#define REFLOCK_MAGIC "r3f10ck"

static inline struct reflock_private *reflock_get_private_ptr(reflock_t *lock) {
	return (struct reflock_private *)(&lock->data);
}

void reflock_make(reflock_t *lock) {
	struct reflock_private *private = reflock_get_private_ptr(lock);
	private->data.magic = REFLOCK_MAGIC;
	private->data.refcount = 0;
}

bool reflock_validate_magic(reflock_t *lock) {
	struct reflock_private *private = reflock_get_private_ptr(lock);
	return !strcmp(private->data.magic, REFLOCK_MAGIC);
}

void reflock_acquire(reflock_t *lock) {
	struct reflock_private *private = reflock_get_private_ptr(lock);

	if (!reflock_validate_magic(lock)) {
		panic("broken reflock (invalid magic)");
	}

	if (!private->data.refcount && lock->on_lock) {
		lock->on_lock();
	}

	private->data.refcount++;
}

void reflock_release(reflock_t *lock) {
	struct reflock_private *private = reflock_get_private_ptr(lock);

	if (!reflock_validate_magic(lock)) {
		panic("broken reflock (invalid magic field)");
	}

	if (!private->data.refcount) {
		if (lock->strict) {
			panic("Attempted to release empty strict reflock");
		}

		return;
	}

	if (!--private->data.refcount && lock->on_unlock) {
		lock->on_unlock();
	}
}

bool reflock_is_locked(reflock_t *lock) {
	return reflock_get_private_ptr(lock)->data.refcount > 0 &&
	       reflock_validate_magic(lock);
}

void reflock_force_unlock(reflock_t *lock) {
	struct reflock_private *private = reflock_get_private_ptr(lock);

	if (!lock->allow_force_unlock) {
		panic("Attempted disallowed force-unlock of a reflock");
	}

	private->data.refcount = 0;
	lock->on_unlock();
}
