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

#ifndef __K_REFLOCK
#define __K_REFLOCK

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
	void (*on_lock)();
	void (*on_unlock)();

	const bool strict; // if strict, panic if released empty lock
	const bool allow_force_unlock;

	uint8_t data[12];
} reflock_t;

#define NEW_REFLOCK(_on_lock, _on_unlock, _strict, _allow_force)               \
	{                                                                          \
		_on_lock, _on_unlock, _strict, _allow_force, {                         \
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0                                 \
		}                                                                      \
	}

void reflock_make(reflock_t *lock);
bool reflock_validate_magic(reflock_t *lock);

static inline bool reflock_validate(reflock_t *lock) {
	return reflock_validate_magic(lock);
}

void reflock_acquire(reflock_t *lock);
void reflock_release(reflock_t *lock);
bool reflock_is_locked(reflock_t *lock);
void reflock_force_unlock(reflock_t *lock);

#endif