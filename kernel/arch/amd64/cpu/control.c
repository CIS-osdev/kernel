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

#include "arch/cpu/control.h"
#include "kreflock.h"
#include "kstdlib.h"

static inline void __cpu_enable_interrupt() {
	asm volatile("sti");
}

static inline void __cpu_disable_interrupt() {
	asm volatile("cli");
}

static reflock_t lock =
    NEW_REFLOCK(__cpu_disable_interrupt, __cpu_enable_interrupt, false, true);

bool cpu_interrupt_lock_acquired() {
	if (unlikely(!reflock_validate(&lock))) {
		reflock_make(&lock);
	}

	return reflock_is_locked(&lock);
}

void cpu_interrupt_lock_acquire() {
	if (unlikely(!reflock_validate(&lock))) {
		reflock_make(&lock);
	}

	reflock_acquire(&lock);
}

void cpu_interrupt_lock_release() {
	if (unlikely(!reflock_validate(&lock))) {
		reflock_make(&lock);
	}

	reflock_release(&lock);
}

void cpu_interrupt_lock_force_release() {
	if (unlikely(!reflock_validate(&lock))) {
		reflock_make(&lock);
	}

	reflock_force_unlock(&lock);
}

void cpu_halt() {
	asm volatile ("hlt");
}

void cpu_full_halt() {
    reflock_acquire(&lock);
    lock.allow_force_unlock = false;
    cpu_halt();
}
