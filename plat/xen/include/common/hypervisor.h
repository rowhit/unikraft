/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Authors: K A Fraser
 *          Grzegorz Milos
 *          Aravindh Puthiyaparambil <aravindh.puthiyaparambil@unisys.com>
 *
 * Copyright (c) 2002, K A Fraser
 * Copyright (c) 2005, Grzegorz Milos
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
/*
 * Hypervisor handling.
 * Ported from Mini-OS
 */

#ifndef _HYPERVISOR_H_
#define _HYPERVISOR_H_

#include <stdint.h>
#include <xen/xen.h>
#if defined(__X86_32__) || defined(__x86_64__)
#include <xen-x86/hypercall.h>
#include <xen-x86/traps.h>
#include <xen-x86/smp.h>
#elif (defined __ARM_32__) || (defined __ARM_64__)
#include <xen-arm/hypercall.h>
#include <xen-arm/smp.h>
#else
#error "Unsupported architecture"
#endif
#include <xen/hvm/hvm_op.h>
#include <uk/arch/lcpu.h>
#include <uk/plat/lcpu.h>

#if 0 //TODO: cleanup
/*
 * a placeholder for the start of day information passed up from the hypervisor
 */
union start_info_union {
	start_info_t start_info;
	char padding[512];
};
extern union start_info_union start_info_union;
#define start_info (start_info_union.start_info)
#else
int hvm_get_parameter(int idx, uint64_t *value);
int hvm_set_parameter(int idx, uint64_t value);
#endif
shared_info_t *map_shared_info(void *p);

//TODO START from here on we have to cleanup/refactor/move stuff
/* hypervisor.c */
void do_hypervisor_callback(struct __regs *regs);
void mask_evtchn(uint32_t port);
void unmask_evtchn(uint32_t port);
void clear_evtchn(uint32_t port);
//TODO END

extern int in_callback;

extern struct shared_info *HYPERVISOR_shared_info;

#endif /* __HYPERVISOR_H__ */
