/*
 * Lowlevel hardware stuff for the MIPS based Cobalt microservers.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1997 Cobalt Microserver
 * Copyright (C) 1997 Ralf Baechle
 * Copyright (C) 2001 Liam Davies (ldavies@agile.tv)
 *
 */
#ifndef __ASM_MIPS_COBALT_H 
#define __ASM_MIPS_COBALT_H 

/*
 * COBALT interrupt enable bits
 */
#define COBALT_IE_PCI          (1 << 0)
#define COBALT_IE_FLOPPY       (1 << 1)
#define COBALT_IE_KEYBOARD     (1 << 2)
#define COBALT_IE_SERIAL1      (1 << 3)
#define COBALT_IE_SERIAL2      (1 << 4)
#define COBALT_IE_PARALLEL     (1 << 5)
#define COBALT_IE_GPIO         (1 << 6)
#define COBALT_IE_RTC          (1 << 7)

/*
 * PCI defines
 */
#define COBALT_IE_ETHERNET     (1 << 7)
#define COBALT_IE_SCSI         (1 << 7)

/*
 * COBALT Interrupt Level definitions.
 * These should match the request IRQ id's.
 */
#define COBALT_TIMER_IRQ       0
#define COBALT_KEYBOARD_IRQ    1
#define COBALT_QUBE_ETH_IRQ    13
#define COBALT_RAQ_ETH0_IRQ    4
#define COBALT_RAQ_ETH1_IRQ    13
#define COBALT_SCC_IRQ         4
#define COBALT_SERIAL2_IRQ     4
#define COBALT_PARALLEL_IRQ    5
#define COBALT_FLOPPY_IRQ      6 /* needs to be consistent with floppy driver! */
#define COBALT_SCSI_IRQ        7

/*
 * PCI configuration space manifest constants.  These are wired into
 * the board layout according to the PCI spec to enable the software
 * to probe the hardware configuration space in a well defined manner.
 *
 * The PCI_DEVSHFT() macro transforms these values into numbers
 * suitable for passing as the dev parameter to the various
 * pcibios_read/write_config routines.
 */
#define COBALT_PCICONF_CPU      0x06
#define COBALT_PCICONF_ETH0     0x07
#define COBALT_PCICONF_RAQSCSI  0x08
#define COBALT_PCICONF_VIA      0x09
#define COBALT_PCICONF_PCISLOT  0x0A
#define COBALT_PCICONF_ETH1     0x0C

/*
 * Handling the VIA ISA host bridge.
 */

#define        VIA_DELAY()                                             \
{                                                              \
       unsigned char ctr;                                      \
       for (ctr=0;ctr<1;ctr++);                                \
}

#define VIA_PORT_WRITE(x,y)                                    \
{                                                              \
       *((volatile unsigned char *) (0xb0000000 | x)) = y;     \
       VIA_DELAY();                                            \
}

#define VIA_PORT_READ(x)       (*((unsigned char *) (0xB0000000 | (x))))

#define RESET_VIA_TIMER()                                      \
       asm("sb\t%1,0x70(%0)\n\t"                               \
           "lb\$0,0x71(%0)"                                    \
           : /* No outputs */                                  \
           : "r" (0xb0000000), "i" (0x0c));

#define VIA_CMOS_ADDR 0x70
#define VIA_CMOS_DATA 0x71

/*
 * The Cobalt board id information.  The boards have an ID number wired
 * into the VIA that is available in the high nibble of register 94.
 * This register is available in the VIA configuration space through the
 * interface routines qube_pcibios_read/write_config. See cobalt/pci.c
 */
#define VIA_COBALT_BRD_ID_REG  0x94
#define VIA_COBALT_BRD_REG_to_ID(reg)  ((unsigned char) (reg) >> 4)
#define COBALT_BRD_ID_QUBE1    0x3
#define COBALT_BRD_ID_RAQ1     0x4
#define COBALT_BRD_ID_QUBE2    0x5
#define COBALT_BRD_ID_RAQ2     0x6

#endif /* __ASM_MIPS_COBALT_H */
