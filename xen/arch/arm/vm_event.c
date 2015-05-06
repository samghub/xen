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

void vm_event_fill_regs(vm_event_request_t *req,
                        const struct cpu_user_regs *regs,
                        struct domain *d)
{
    if ( is_32bit_domain(d) )
    {
        req->data.regs.arm.x0 = regs->r0;
        req->data.regs.arm.x1 = regs->r1;
        req->data.regs.arm.x2 = regs->r2;
        req->data.regs.arm.x3 = regs->r3;
        req->data.regs.arm.x4 = regs->r4;
        req->data.regs.arm.x5 = regs->r5;
        req->data.regs.arm.x6 = regs->r6;
        req->data.regs.arm.x7 = regs->r7;
        req->data.regs.arm.x8 = regs->r8;
        req->data.regs.arm.x9 = regs->r9;
        req->data.regs.arm.x10 = regs->r10;
        req->data.regs.arm.pc = regs->pc32;
        req->data.regs.arm.sp_el0 = regs->sp_usr;
        req->data.regs.arm.sp_el1 = regs->sp_svc;
    }
#ifdef CONFIG_ARM_64
    else
    {
        req->data.regs.arm.x0 = regs->x0;
        req->data.regs.arm.x1 = regs->x1;
        req->data.regs.arm.x2 = regs->x2;
        req->data.regs.arm.x3 = regs->x3;
        req->data.regs.arm.x4 = regs->x4;
        req->data.regs.arm.x5 = regs->x5;
        req->data.regs.arm.x6 = regs->x6;
        req->data.regs.arm.x7 = regs->x7;
        req->data.regs.arm.x8 = regs->x8;
        req->data.regs.arm.x9 = regs->x9;
        req->data.regs.arm.x10 = regs->x10;
        req->data.regs.arm.pc = regs->pc;
        req->data.regs.arm.sp_el0 = regs->sp_el0;
        req->data.regs.arm.sp_el1 = regs->sp_el1;
    }
#endif
    req->data.regs.arm.fp = regs->fp;
    req->data.regs.arm.lr = regs->lr;
    req->data.regs.arm.cpsr = regs->cpsr;
    req->data.regs.arm.spsr_el1 = regs->spsr_svc;
    req->data.regs.arm.ttbr0 = READ_SYSREG64(TTBR0_EL1);
    req->data.regs.arm.ttbr1 = READ_SYSREG64(TTBR1_EL1);
}

void vm_event_set_registers(struct vcpu *v, vm_event_response_t *rsp)
{
    struct cpu_user_regs *regs = &v->arch.cpu_info->guest_cpu_user_regs;

    if ( is_32bit_domain(v->domain) )
    {
        regs->r0 = rsp->data.regs.arm.x0;
        regs->r1 = rsp->data.regs.arm.x1;
        regs->r2 = rsp->data.regs.arm.x2;
        regs->r3 = rsp->data.regs.arm.x3;
        regs->r4 = rsp->data.regs.arm.x4;
        regs->r5 = rsp->data.regs.arm.x5;
        regs->r6 = rsp->data.regs.arm.x6;
        regs->r7 = rsp->data.regs.arm.x7;
        regs->r8 = rsp->data.regs.arm.x8;
        regs->r9 = rsp->data.regs.arm.x9;
        regs->r10 = rsp->data.regs.arm.x10;
        regs->pc32 = rsp->data.regs.arm.pc;
        regs->sp_usr = rsp->data.regs.arm.sp_el0;
        regs->sp_svc = rsp->data.regs.arm.sp_el1;
    }
#ifdef CONFIG_ARM_64
    else
    {
        regs->x0 = rsp->data.regs.arm.x0;
        regs->x1 = rsp->data.regs.arm.x1;
        regs->x2 = rsp->data.regs.arm.x2;
        regs->x3 = rsp->data.regs.arm.x3;
        regs->x4 = rsp->data.regs.arm.x4;
        regs->x5 = rsp->data.regs.arm.x5;
        regs->x6 = rsp->data.regs.arm.x6;
        regs->x7 = rsp->data.regs.arm.x7;
        regs->x8 = rsp->data.regs.arm.x8;
        regs->x9 = rsp->data.regs.arm.x9;
        regs->x10 = rsp->data.regs.arm.x10;
        regs->pc = rsp->data.regs.arm.pc;
        regs->sp_el0 = rsp->data.regs.arm.sp_el0;
        regs->sp_el1 = rsp->data.regs.arm.sp_el1;
    }
#endif

    regs->fp = rsp->data.regs.arm.fp;
    regs->lr = rsp->data.regs.arm.lr;
    regs->cpsr = rsp->data.regs.arm.cpsr;
    v->arch.ttbr0 = rsp->data.regs.arm.ttbr0;
    v->arch.ttbr1 = rsp->data.regs.arm.ttbr1;
}

/*
 * Local variables:
 * mode: C
 * c-file-style: "BSD"
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
