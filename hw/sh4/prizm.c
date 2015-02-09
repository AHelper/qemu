/*
 * fx-CG10/20 Device Emulation
 *
 * Copyright (c) 2015 Collin Eggert
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "exec/memory.h"
#include "exec/address-spaces.h"
#include "hw/hw.h"
#include "hw/sysbus.h"
#include "hw/boards.h"
#include "hw/loader.h"
#include "hw/sh4/sh.h"
#include "hw/block/flash.h"
#include "qemu/error-report.h"
#include "sysemu/qtest.h"
#include "sysemu/sysemu.h"


static void prizm_init(MachineState *machine)
{
    struct SH7305State *s;
    SuperHCPU *cpu;
    
    MemoryRegion *sysmem = get_system_memory();
    MemoryRegion *sdram = g_new(MemoryRegion, 1);
    MemoryRegion *flashalias = g_new(MemoryRegion, 1);
    MemoryRegion *flash0mem;
    DriveInfo *flash;
    
    const char *model = machine->cpu_model;
    
    if (!model)
    {
        model = "SH7305";
        printf("Unspecified CPU model, assuming SH7305\n");
    }

    cpu = cpu_sh4_init(model);
    if (cpu == NULL) 
    {
        fprintf(stderr, "Unable to find CPU definition\n");
        exit(1);
    }

//     cpu_reset(CPU(cpu));
    /* Allocate memory space */
//     nand = drive_get(IF_MTD, 0, 0);
//     if(!nand)
//     {
//       error_report("No valid MTD dump provided, see -mtdblock <file>");
//       exit(1);
//     }
//     nand_state.nand = nand_init(nand ? blk_by_legacy_dinfo(nand) : NULL,
//                                 NAND_MFR_FUJITSU, 0x43);
//     memory_region_init_io(&nand_state.iomem, NULL, &nand_ops, &nand_state,
//                           "nand", 0x2000000); //, &error_abort);
// 
//     vmstate_register_ram(&nand_state.iomem, nand_state.nand);
//     memory_region_add_subregion(sysmem, 0x00000000,
//                                 &nand_state.iomem);
//     sysbus_init_mmio(SYS_BUS_DEVICE(dev), &nand_state.iomem);
//     memory_region_set_readonly(&nand_state.iomem, true);
//     memory_region_init_alias(flashalias, NULL, "flash.alias",
//                               flash0mem, 0, FLASH_SIZE);
//     memory_region_add_subregion(sysmem, 0, flashalias);
    
    memory_region_init_ram(sdram, NULL, "sdram", 0x2000000, &error_abort);
    vmstate_register_ram_global(sdram);
    memory_region_add_subregion(sysmem, 0x08000000, sdram);
//     memory_region_init_ram(rom, NULL, "shix.rom", 0x4000, &error_abort);
//     vmstate_register_ram_global(rom);
//     memory_region_set_readonly(rom, true);
//     memory_region_add_subregion(sysmem, 0x00000000, rom);
//     memory_region_init_ram(&sdram[0], NULL, "shix.sdram1", 0x01000000,
//                            &error_abort);
//     vmstate_register_ram_global(&sdram[0]);
//     memory_region_add_subregion(sysmem, 0x08000000, &sdram[0]);
//     memory_region_init_ram(&sdram[1], NULL, "shix.sdram2", 0x01000000,
//                            &error_abort);
//     vmstate_register_ram_global(&sdram[1]);
//     memory_region_add_subregion(sysmem, 0x0c000000, &sdram[1]);

    s = sh7305_init(cpu, sysmem);
    
#define FLASH_SIZE 0x400000
    flash = drive_get(IF_PFLASH, 0, 0);
    if(!flash)
    {
      error_report("No valid flash dump provided, see -pflash <file>");
      exit(1);
    }
    pflash_t *pflash = pflash_cfi02_register(0x0, NULL, "flash", FLASH_SIZE,
                          blk_by_legacy_dinfo(flash),
                          0x20000, FLASH_SIZE >> 16,
                          1, 1, 0x0000, 0x0000, 0x0000, 0x0000,
                          0x555, 0x2aa, 1);
//     pflash_t *pflash = pflash_cfi01_register(0x0, NULL, "flash", FLASH_SIZE,
//                           blk_by_legacy_dinfo(flash),
//                           0x20000, FLASH_SIZE >> 16,
//                           12, 0x0000, 0x0000, 0x0000, 0x0000,
//                           1);
        flash0mem = sysbus_mmio_get_region(SYS_BUS_DEVICE(pflash), 0);
        memory_region_init_alias(flashalias, NULL, "flash.alias",
                                 flash0mem, 0, FLASH_SIZE);
        memory_region_add_subregion(sysmem, 0x02000000, flashalias);
//     flash0mem = sysbus_mmio_get_region(SYS_BUS_DEVICE(pflash), 0);
//     memory_region_set_readonly(flash0mem, 1);
//     printf("%d\n", memory_region_is_iommu(flash0mem));
//     printf("%d\n", memory_region_is_ram(flash0mem));
//     printf("%d\n", memory_region_is_romd(flash0mem));
//     printf("%d\n", memory_region_is_rom(flash0mem));
}

static QEMUMachine prizm_machine = {
    .name = "prizm",
    .desc = "Casio Prizm fx-CG10/20",
    .init = prizm_init,
    .is_default = 1,
};

static void prizm_machine_init(void)
{
    qemu_register_machine(&prizm_machine);
}

machine_init(prizm_machine_init);
