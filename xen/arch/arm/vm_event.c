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
        req->data.regs.arm.aarch.arm32.r0_usr = regs->r0;
        req->data.regs.arm.aarch.arm32.r1_usr = regs->r1;
        req->data.regs.arm.aarch.arm32.r2_usr = regs->r2;
        req->data.regs.arm.aarch.arm32.r3_usr = regs->r3;
        req->data.regs.arm.aarch.arm32.r4_usr = regs->r4;
        req->data.regs.arm.aarch.arm32.r5_usr = regs->r5;
        req->data.regs.arm.aarch.arm32.r6_usr = regs->r6;
        req->data.regs.arm.aarch.arm32.r7_usr = regs->r7;
        req->data.regs.arm.aarch.arm32.r8_usr = regs->r8;
        req->data.regs.arm.aarch.arm32.r9_usr = regs->r9;
        req->data.regs.arm.aarch.arm32.r10_usr = regs->r10;
        req->data.regs.arm.aarch.arm32.pc = regs->pc32;
        req->data.regs.arm.aarch.arm32.sp_usr = regs->sp_usr;
        req->data.regs.arm.aarch.arm32.sp_svc = regs->sp_svc;
        req->data.regs.arm.aarch.arm32.fp = regs->fp;
        req->data.regs.arm.aarch.arm32.lr = regs->lr;
        req->data.regs.arm.aarch.arm32.cpsr = regs->cpsr;
        req->data.regs.arm.aarch.arm32.spsr_svc = regs->spsr_svc;
        req->data.regs.arm.aarch.arm32.ttbr0 = READ_SYSREG64(TTBR0_EL1);
        req->data.regs.arm.aarch.arm32.ttbr1 = READ_SYSREG64(TTBR1_EL1);
    }
#ifdef CONFIG_ARM_64
    else
    {
        req->data.regs.arm.aarch.arm64.x0 = regs->x0;
        req->data.regs.arm.aarch.arm64.x1 = regs->x1;
        req->data.regs.arm.aarch.arm64.x2 = regs->x2;
        req->data.regs.arm.aarch.arm64.x3 = regs->x3;
        req->data.regs.arm.aarch.arm64.x4 = regs->x4;
        req->data.regs.arm.aarch.arm64.x5 = regs->x5;
        req->data.regs.arm.aarch.arm64.x6 = regs->x6;
        req->data.regs.arm.aarch.arm64.x7 = regs->x7;
        req->data.regs.arm.aarch.arm64.x8 = regs->x8;
        req->data.regs.arm.aarch.arm64.x9 = regs->x9;
        req->data.regs.arm.aarch.arm64.x10 = regs->x10;
        req->data.regs.arm.aarch.arm64.pc = regs->pc;
        req->data.regs.arm.aarch.arm64.sp_el0 = regs->sp_el0;
        req->data.regs.arm.aarch.arm64.sp_el1 = regs->sp_el1;
        req->data.regs.arm.aarch.arm64.fp = regs->fp;
        req->data.regs.arm.aarch.arm64.lr = regs->lr;
        req->data.regs.arm.aarch.arm64.cpsr = regs->cpsr;
        req->data.regs.arm.aarch.arm64.spsr_el1 = regs->spsr_svc;
        req->data.regs.arm.aarch.arm64.ttbr0 = READ_SYSREG64(TTBR0_EL1);
        req->data.regs.arm.aarch.arm64.ttbr1 = READ_SYSREG64(TTBR1_EL1);
    }
#endif
}

void vm_event_set_registers(struct vcpu *v, vm_event_response_t *rsp)
{
    struct cpu_user_regs *regs = &v->arch.cpu_info->guest_cpu_user_regs;

    if ( is_32bit_domain(v->domain) )
    {
        regs->r0 = rsp->data.regs.arm.aarch.arm32.r0_usr;
        regs->r1 = rsp->data.regs.arm.aarch.arm32.r1_usr;
        regs->r2 = rsp->data.regs.arm.aarch.arm32.r2_usr;
        regs->r3 = rsp->data.regs.arm.aarch.arm32.r3_usr;
        regs->r4 = rsp->data.regs.arm.aarch.arm32.r4_usr;
        regs->r5 = rsp->data.regs.arm.aarch.arm32.r5_usr;
        regs->r6 = rsp->data.regs.arm.aarch.arm32.r6_usr;
        regs->r7 = rsp->data.regs.arm.aarch.arm32.r7_usr;
        regs->r8 = rsp->data.regs.arm.aarch.arm32.r8_usr;
        regs->r9 = rsp->data.regs.arm.aarch.arm32.r9_usr;
        regs->r10 = rsp->data.regs.arm.aarch.arm32.r10_usr;
        regs->pc32 = rsp->data.regs.arm.aarch.arm32.pc;
        regs->sp_usr = rsp->data.regs.arm.aarch.arm32.sp_usr;
        regs->sp_svc = rsp->data.regs.arm.aarch.arm32.sp_svc;
        regs->fp = rsp->data.regs.arm.aarch.arm32.fp;
        regs->lr = rsp->data.regs.arm.aarch.arm32.lr;
        regs->cpsr = rsp->data.regs.arm.aarch.arm32.cpsr;
        v->arch.ttbr0 = rsp->data.regs.arm.aarch.arm32.ttbr0;
        v->arch.ttbr1 = rsp->data.regs.arm.aarch.arm32.ttbr1;
    }
#ifdef CONFIG_ARM_64
    else
    {
        regs->x0 = rsp->data.regs.arm.aarch.arm64.x0;
        regs->x1 = rsp->data.regs.arm.aarch.arm64.x1;
        regs->x2 = rsp->data.regs.arm.aarch.arm64.x2;
        regs->x3 = rsp->data.regs.arm.aarch.arm64.x3;
        regs->x4 = rsp->data.regs.arm.aarch.arm64.x4;
        regs->x5 = rsp->data.regs.arm.aarch.arm64.x5;
        regs->x6 = rsp->data.regs.arm.aarch.arm64.x6;
        regs->x7 = rsp->data.regs.arm.aarch.arm64.x7;
        regs->x8 = rsp->data.regs.arm.aarch.arm64.x8;
        regs->x9 = rsp->data.regs.arm.aarch.arm64.x9;
        regs->x10 = rsp->data.regs.arm.aarch.arm64.x10;
        regs->pc = rsp->data.regs.arm.aarch.arm64.pc;
        regs->sp_el0 = rsp->data.regs.arm.aarch.arm64.sp_el0;
        regs->sp_el1 = rsp->data.regs.arm.aarch.arm64.sp_el1;
        regs->fp = rsp->data.regs.arm.aarch.arm64.fp;
        regs->lr = rsp->data.regs.arm.aarch.arm64.lr;
        regs->cpsr = rsp->data.regs.arm.aarch.arm64.cpsr;
        v->arch.ttbr0 = rsp->data.regs.arm.aarch.arm64.ttbr0;
        v->arch.ttbr1 = rsp->data.regs.arm.aarch.arm64.ttbr1;
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
