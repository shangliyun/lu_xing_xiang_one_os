#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <board.h>

/* enable SFUD flash driver sample */
#define FAL_FLASH_PORT_DRIVER_SFUD

/* ====================== Partition Configuration ========================== */
#define FAL_PART_HAS_TABLE_CFG

/* bootloader partition name */
#define OS_BL_PART_NAME          "bootloader"
#define OS_CFG_NAME              "cfg"
#define OS_APP_NAME              "app"
#define OS_DL_PART_NAME          "download"
#define OS_DF_PART_NAME          "diff_patch"
#define OS_BK_PART_NAME          "backup"             /* backup */
#define OS_EF_PART_NAME          "easyflash"          /* easyflash */
#define OS_RF_PART_NAME          "wifi_image"         /* wifi_image */
#define OS_FF_PART_NAME          "font"               /* font */
#define OS_FS_PART_NAME          "filesystem"         /* filesystem */

/* ===================== Flash device Configuration ========================= */
#define OS_ONCHIP_FLASH_NAME     "onchip_flash"
#define OS_EXTERN_FLASH_NAME     "nor_flash"

#define MCU_SRAM_BEGIN           ((uint32_t)0x20000000)
#define MCU_SRAM_SIZE            ((128-32) * 1024)                      // unit: bytes, total 96Kbytes
#define MCU_SRAM_END             (MCU_SRAM_BEGIN + MCU_SRAM_SIZE)

#define MCU_ROM_BEGIN            ((uint32_t)0x08000000)
#define MCU_ROM_SIZE             (512 * 1024)                           // unit: bytes, total 512Kbytes
#define MCU_ROM_END              (MCU_ROM_BEGIN + MCU_ROM_SIZE)

#define MCU_SPI_FLASH_BEGIN      ((uint32_t)0x00)
#define MCU_SPI_FLASH_SIZE       (16 * 1024 * 1024)                     // unit: bytes, total 16Mbytes
#define MCU_SPI_FLASH_END        (MCU_SPI_FLASH_BEGIN + MCU_SPI_FLASH_SIZE)

/* bootloader */
#define MCU_BOOT_ENTRY           MCU_ROM_BEGIN                          // 0x08000000
#define MCU_BOOT_SIZE            (96 * 1024)                            // unit: bytes, total 64Kbytes
#define MCU_BOOT_END             (MCU_BOOT_ENTRY + MCU_BOOT_SIZE)

/* cfg */
#define MCU_CFG_ENTRY            ((uint32_t)MCU_BOOT_END)               // 0x08018000
#define MCU_CFG_SIZE             (32 * 1024)                            // unit: bytes, total 64Kbytes
#define MCU_CFG_END              (MCU_CFG_ENTRY + MCU_CFG_SIZE)

/* app */
#define OS_APP_PART_ADDR         ((uint32_t)MCU_CFG_END)                // 0x08020000
#define OS_APP_PART_SIZE         (2 * 128 * 1024)                       // unit: bytes, total 384Kbytes
#define OS_APP_PART_END_ADDR     (OS_APP_PART_ADDR + OS_APP_PART_SIZE)

#define USER_APP_ENTRY           OS_APP_PART_ADDR

/* download */
#define OS_DL_PART_ADDR          ((uint32_t)OS_APP_PART_END_ADDR)       // 0x08080000
#define OS_DL_PART_SIZE          (1 * 128 * 1024)                       // unit: bytes, total 512Kbytes 0x100000
#define OS_DL_PART_END_ADDR      (OS_DL_PART_ADDR + OS_DL_PART_SIZE)    // 0x00180000

/* diff_patch */
#define OS_DF_PART_ADDR          ((uint32_t)MCU_SPI_FLASH_BEGIN)        // 0x00
#define OS_DF_PART_SIZE          (1024 * 1024)                          // unit: bytes, total 1024Kbytes 0x100000
#define OS_DF_PART_END_ADDR      (OS_DF_PART_ADDR + OS_DF_PART_SIZE)    

/* BK: backup */
#define OS_BK_PART_ADDR          ((uint32_t)OS_DF_PART_END_ADDR)        // 0x00100000
#define OS_BK_PART_SIZE          (1024 * 1024)                          // unit: bytes, total 1024Kbytes
#define OS_BK_PART_END_ADDR      (OS_BK_PART_ADDR + OS_BK_PART_SIZE)  

/* ef: easyflash */
#define OS_EF_PART_ADDR          ((uint32_t)OS_BK_PART_END_ADDR)        // 0x00200000
#define OS_EF_PART_SIZE          (512 * 1024)                           // unit: bytes, total 512Kbytes
#define OS_EF_PART_END_ADDR      (OS_EF_PART_ADDR + OS_EF_PART_SIZE)    

/* wf: wifi image */
#define OS_RF_PART_ADDR          ((uint32_t)OS_EF_PART_END_ADDR)        // 0x00280000
#define OS_RF_PART_SIZE          (512 * 1024)                           // unit: bytes, total 512Kbytes
#define OS_RF_PART_END_ADDR      (OS_RF_PART_ADDR + OS_RF_PART_SIZE)    

/* ff: font */
#define OS_FF_PART_ADDR          ((uint32_t)OS_RF_PART_END_ADDR)        // 0x00300000
#define OS_FF_PART_SIZE          (7 * 1024 * 1024)                      // unit: bytes, total 7Mbytes
#define OS_FF_PART_END_ADDR      (OS_FF_PART_ADDR + OS_FF_PART_SIZE)    

/* fs: filesystem */
#define OS_FS_PART_ADDR          ((uint32_t)OS_FF_PART_END_ADDR)        // 0x00A00000
#define OS_FS_PART_SIZE          (6 * 1024 * 1024)                      // unit: bytes, total 6Mbytes
#define OS_FS_PART_END_ADDR      (OS_FS_PART_ADDR + OS_FS_PART_SIZE)

/* partition table */
#define FAL_PART_TABLE                                                                                                         \
{                                                                                                                              \
    {OS_BL_PART_NAME, OS_ONCHIP_FLASH_NAME,        (MCU_BOOT_ENTRY - MCU_ROM_BEGIN),    MCU_BOOT_SIZE, FAL_PART_INFO_FLAGS_LOCK}, \
    {    OS_CFG_NAME, OS_ONCHIP_FLASH_NAME,        (MCU_CFG_ENTRY  - MCU_ROM_BEGIN),     MCU_CFG_SIZE, FAL_PART_INFO_FLAGS_LOCK}, \
    {    OS_APP_NAME, OS_ONCHIP_FLASH_NAME,      (OS_APP_PART_ADDR - MCU_ROM_BEGIN), OS_APP_PART_SIZE, 0}, \
    {OS_DL_PART_NAME, OS_ONCHIP_FLASH_NAME,       (OS_DL_PART_ADDR - MCU_ROM_BEGIN),  OS_DL_PART_SIZE, 0}, \
    {OS_DF_PART_NAME, OS_EXTERN_FLASH_NAME, (OS_DF_PART_ADDR - MCU_SPI_FLASH_BEGIN),  OS_DF_PART_SIZE, 0}, \
    {OS_BK_PART_NAME, OS_EXTERN_FLASH_NAME, (OS_BK_PART_ADDR - MCU_SPI_FLASH_BEGIN),  OS_BK_PART_SIZE, 0}, \
    {OS_EF_PART_NAME, OS_EXTERN_FLASH_NAME, (OS_EF_PART_ADDR - MCU_SPI_FLASH_BEGIN),  OS_EF_PART_SIZE, 0}, \
    {OS_RF_PART_NAME, OS_EXTERN_FLASH_NAME, (OS_RF_PART_ADDR - MCU_SPI_FLASH_BEGIN),  OS_RF_PART_SIZE, 0}, \
    {OS_FF_PART_NAME, OS_EXTERN_FLASH_NAME, (OS_FF_PART_ADDR - MCU_SPI_FLASH_BEGIN),  OS_FF_PART_SIZE, 0}, \
    {OS_FS_PART_NAME, OS_EXTERN_FLASH_NAME, (OS_FS_PART_ADDR - MCU_SPI_FLASH_BEGIN),  OS_FS_PART_SIZE, 0}, \
}

#endif /* _FAL_CFG_H_ */

