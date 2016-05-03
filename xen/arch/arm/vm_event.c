/*
 * arch/arm/vm_event.c
 *
 * Architecture-specific vm_event handling routines
 *
 * Copyright (c) 2016 Tamas K Lengyel (tamas@tklengyel.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License v2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; If not, see <http://www.gnu.org/licenses/>.
 */

#include <xen/sched.h>
#include <asm/vm_event.h>

void vm_event_fill_regs(vm_event_request_t *req)
{
    const struct cpu_user_regs *regs = guest_cpu_user_regs();

    req->data.regs.arm.cpsr = regs->cpsr;
    req->data.regs.arm.ttbr0 = READ_SYSREG64(TTBR0_EL1);
    req->data.regs.arm.ttbr1 = READ_SYSREG64(TTBR1_EL1);

    if ( psr_mode_is_32bit(regs->cpsr) )
    {
        req->data.regs.arm.arch.arm32.r0 = regs->r0;
        req->data.regs.arm.arch.arm32.r1 = regs->r1;
        req->data.regs.arm.arch.arm32.r2 = regs->r2;
        req->data.regs.arm.arch.arm32.r3 = regs->r3;
        req->data.regs.arm.arch.arm32.r4 = regs->r4;
        req->data.regs.arm.arch.arm32.r5 = regs->r5;
        req->data.regs.arm.arch.arm32.r6 = regs->r6;
        req->data.regs.arm.arch.arm32.r7 = regs->r7;
        req->data.regs.arm.arch.arm32.r8 = regs->r8;
        req->data.regs.arm.arch.arm32.r9 = regs->r9;
        req->data.regs.arm.arch.arm32.r10 = regs->r10;
        req->data.regs.arm.arch.arm32.r11 = regs->fp;
        req->data.regs.arm.arch.arm32.r12 = regs->r12;
        req->data.regs.arm.arch.arm32.r13 = regs->sp;
        req->data.regs.arm.arch.arm32.r14 = regs->lr;
        req->data.regs.arm.arch.arm32.pc = regs->pc32;
    }
#ifdef CONFIG_ARM_64
    else
    {
        req->data.regs.arm.arch.arm64.x0 = regs->x0;
        req->data.regs.arm.arch.arm64.x1 = regs->x1;
        req->data.regs.arm.arch.arm64.x2 = regs->x2;
        req->data.regs.arm.arch.arm64.x3 = regs->x3;
        req->data.regs.arm.arch.arm64.x4 = regs->x4;
        req->data.regs.arm.arch.arm64.x5 = regs->x5;
        req->data.regs.arm.arch.arm64.x6 = regs->x6;
        req->data.regs.arm.arch.arm64.x7 = regs->x7;
        req->data.regs.arm.arch.arm64.x8 = regs->x8;
        req->data.regs.arm.arch.arm64.x9 = regs->x9;
        req->data.regs.arm.arch.arm64.x10 = regs->x10;
        req->data.regs.arm.arch.arm64.x11 = regs->x11;
        req->data.regs.arm.arch.arm64.x12 = regs->x12;
        req->data.regs.arm.arch.arm64.x13 = regs->x13;
        req->data.regs.arm.arch.arm64.x14 = regs->x14;
        req->data.regs.arm.arch.arm64.x15 = regs->x15;
        req->data.regs.arm.arch.arm64.x16 = regs->x16;
        req->data.regs.arm.arch.arm64.x17 = regs->x17;
        req->data.regs.arm.arch.arm64.x18 = regs->x18;
        req->data.regs.arm.arch.arm64.x19 = regs->x19;
        req->data.regs.arm.arch.arm64.x20 = regs->x20;
        req->data.regs.arm.arch.arm64.x21 = regs->x21;
        req->data.regs.arm.arch.arm64.x22 = regs->x22;
        req->data.regs.arm.arch.arm64.x23 = regs->x23;
        req->data.regs.arm.arch.arm64.x24 = regs->x24;
        req->data.regs.arm.arch.arm64.x25 = regs->x25;
        req->data.regs.arm.arch.arm64.x26 = regs->x26;
        req->data.regs.arm.arch.arm64.x27 = regs->x27;
        req->data.regs.arm.arch.arm64.x28 = regs->x28;
        req->data.regs.arm.arch.arm64.x29 = regs->fp;
        req->data.regs.arm.arch.arm64.x30 = regs->lr;
        req->data.regs.arm.arch.arm64.pc = regs->pc;
    }
#endif
}

void vm_event_set_registers(struct vcpu *v, vm_event_response_t *rsp)
{
    struct cpu_user_regs *regs = &v->arch.cpu_info->guest_cpu_user_regs;

    regs->cpsr = rsp->data.regs.arm.cpsr;
    v->arch.ttbr0 = rsp->data.regs.arm.ttbr0;
    v->arch.ttbr1 = rsp->data.regs.arm.ttbr1;

    if ( psr_mode_is_32bit(regs->cpsr) )
    {
        regs->r0 = rsp->data.regs.arm.arch.arm32.r0;
        regs->r1 = rsp->data.regs.arm.arch.arm32.r1;
        regs->r2 = rsp->data.regs.arm.arch.arm32.r2;
        regs->r3 = rsp->data.regs.arm.arch.arm32.r3;
        regs->r4 = rsp->data.regs.arm.arch.arm32.r4;
        regs->r5 = rsp->data.regs.arm.arch.arm32.r5;
        regs->r6 = rsp->data.regs.arm.arch.arm32.r6;
        regs->r7 = rsp->data.regs.arm.arch.arm32.r7;
        regs->r8 = rsp->data.regs.arm.arch.arm32.r8;
        regs->r9 = rsp->data.regs.arm.arch.arm32.r9;
        regs->r10 = rsp->data.regs.arm.arch.arm32.r10;
        regs->fp = rsp->data.regs.arm.arch.arm32.r11;
        regs->r12 = rsp->data.regs.arm.arch.arm32.r12;
        regs->sp = rsp->data.regs.arm.arch.arm32.r13;
        regs->lr = rsp->data.regs.arm.arch.arm32.r14;
        regs->pc32 = rsp->data.regs.arm.arch.arm32.pc;
    }
#ifdef CONFIG_ARM_64
    else
    {
        regs->x0 = rsp->data.regs.arm.arch.arm64.x0;
        regs->x1 = rsp->data.regs.arm.arch.arm64.x1;
        regs->x2 = rsp->data.regs.arm.arch.arm64.x2;
        regs->x3 = rsp->data.regs.arm.arch.arm64.x3;
        regs->x4 = rsp->data.regs.arm.arch.arm64.x4;
        regs->x5 = rsp->data.regs.arm.arch.arm64.x5;
        regs->x6 = rsp->data.regs.arm.arch.arm64.x6;
        regs->x7 = rsp->data.regs.arm.arch.arm64.x7;
        regs->x8 = rsp->data.regs.arm.arch.arm64.x8;
        regs->x9 = rsp->data.regs.arm.arch.arm64.x9;
        regs->x10 = rsp->data.regs.arm.arch.arm64.x10;
        regs->x11 = rsp->data.regs.arm.arch.arm64.x11;
        regs->x12 = rsp->data.regs.arm.arch.arm64.x12;
        regs->x13 = rsp->data.regs.arm.arch.arm64.x13;
        regs->x14 = rsp->data.regs.arm.arch.arm64.x14;
        regs->x15 = rsp->data.regs.arm.arch.arm64.x15;
        regs->x16 = rsp->data.regs.arm.arch.arm64.x16;
        regs->x17 = rsp->data.regs.arm.arch.arm64.x17;
        regs->x18 = rsp->data.regs.arm.arch.arm64.x18;
        regs->x19 = rsp->data.regs.arm.arch.arm64.x19;
        regs->x20 = rsp->data.regs.arm.arch.arm64.x20;
        regs->x21 = rsp->data.regs.arm.arch.arm64.x21;
        regs->x22 = rsp->data.regs.arm.arch.arm64.x22;
        regs->x23 = rsp->data.regs.arm.arch.arm64.x23;
        regs->x24 = rsp->data.regs.arm.arch.arm64.x24;
        regs->x25 = rsp->data.regs.arm.arch.arm64.x25;
        regs->x26 = rsp->data.regs.arm.arch.arm64.x26;
        regs->x27 = rsp->data.regs.arm.arch.arm64.x27;
        regs->x28 = rsp->data.regs.arm.arch.arm64.x28;
        regs->fp = rsp->data.regs.arm.arch.arm64.x29;
        regs->lr = rsp->data.regs.arm.arch.arm64.x30;
        regs->pc = rsp->data.regs.arm.arch.arm64.pc;
    }
#endif
}

/*
 * Local variables:
 * mode: C
 * c-file-style: "BSD"
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
