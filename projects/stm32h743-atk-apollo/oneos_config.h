#ifndef __ONEOS_CONFIG_H__
#define __ONEOS_CONFIG_H__

#define BOARD_ATK_APOLLO
#define ARCH_ARM
#define ARCH_ARM_CORTEX_M
#define ARCH_ARM_CORTEX_M7

/* Kernel */

#define OS_NAME_MAX_15
#define OS_NAME_MAX 15
#define OS_ALIGN_SIZE 4
#define OS_TASK_PRIORITY_32
#define OS_TASK_PRIORITY_MAX 32
#define OS_TICK_PER_SECOND 1000
#define OS_USING_OVERFLOW_CHECK
#define OS_MAIN_TASK_STACK_SIZE 2048
#define OS_USING_HOOK
#define OS_USING_IDLE_HOOK
#define OS_IDLE_HOOK_LIST_SIZE 4
#define OS_IDLE_TASK_STACK_SIZE 512
#define OS_USING_TIMER_SOFT
#define OS_TIMER_TASK_PRIO 0
#define OS_TIMER_TASK_STACK_SIZE 512
#define OS_USING_WORKQUEUE
#define OS_USING_SYSTEM_WORKQUEUE
#define OS_SYSTEM_WORKQUEUE_STACK_SIZE 2048
#define OS_SYSTEM_WORKQUEUE_PRIORITY 8

/* Task communication */

#define OS_USING_SEMAPHORE
#define OS_USING_MUTEX
#define OS_USING_EVENT
#define OS_USING_MAILBOX
#define OS_USING_MESSAGEQUEUE
#define OS_USING_COMPLETION
#define OS_USING_DATAQUEUE
#define OS_USING_WAITQUEUE
/* end of Task communication */

/* Memory management */

#define OS_USING_MEM_POOL
#define OS_USING_MEM_SMALL
#define OS_USING_HEAP
#define OS_MEM_STATS
/* end of Memory management */

/* Kernel console */

#define OS_USING_CONSOLE
#define OS_CONSOLE_DEVICE_NAME "uart1"
/* end of Kernel console */

/* Enable assert */

#define OS_USING_ASSERT
/* end of Enable assert */

/* Kernel debug */

#define OS_USING_KERNEL_DEBUG
#define KLOG_GLOBAL_LEVEL_WARNING
#define KLOG_GLOBAL_LEVEL 1
#define KLOG_USING_COLOR
/* end of Kernel debug */
/* end of Kernel */

/* C standard library */

#define OS_USING_LIBC
/* end of C standard library */

/* Osal */

/* POSIX compatibility layer */

#define OS_USING_POSIX
/* end of POSIX compatibility layer */

/* RT-Thread compatibility layer */

/* end of RT-Thread compatibility layer */

/* CMSIS compatibility layer */

/* end of CMSIS compatibility layer */

/* FreeRTOS compatibility layer */

/* end of FreeRTOS compatibility layer */
/* end of Osal */

/* Drivers */

#define OS_USING_DEVICE

/* HAL */

#define SOC_FAMILY_STM32
#define SOC_SERIES_STM32H7
#define SOC_SERIES_STM32H7_M7
#define SOC_STM32H743xx

/* Configure base hal in STM32CubeMX */

/* end of HAL */

/* Audio */

/* end of Audio */

/* MISC */

#define OS_USING_PUSH_BUTTON
#define OS_USING_LED
#define OS_USING_ADC
#define OS_USING_DAC
/* end of MISC */

/* PIN */

#define OS_USING_PIN
#define OS_PIN_MAX_CHIP 2
#define BSP_USING_PIN_PCF8574
#define OS_PCF8574_I2C_BUS_NAME "soft_i2c2"
#define OS_PCF8574_I2C_BUS_ADDR 0x20
#define OS_PCF8574_INT_PIN 28
#define OS_PCF8574_PIN_BASE 1000
/* end of PIN */

/* Serial */

#define OS_USING_SERIAL
#define OS_SERIAL_RX_BUFSZ 64
#define OS_SERIAL_TX_BUFSZ 64
/* end of Serial */

/* WDG */

#define OS_USING_WDG
/* end of WDG */

/* RTC */

#define OS_USING_RTC
/* end of RTC */

/* CAN */

/* end of CAN */

/* I2C */

#define OS_USING_I2C
#define OS_USING_I2C_BITOPS
#define SOFT_I2C_BUS_DELAY_US 10
#define BSP_USING_SOFT_I2C2
#define BSP_SOFT_I2C2_SCL_PIN 116
#define BSP_SOFT_I2C2_SDA_PIN 117
/* end of I2C */

/* SPI */

#define OS_USING_SPI
#define OS_USING_QSPI
#define OS_USING_SFUD
#define OS_SFUD_USING_SFDP
#define OS_SFUD_USING_FLASH_INFO_TABLE
#define OS_DEBUG_SFUD
#define OS_SFUD_USING_QSPI
#define OS_QSPI_FLASH_BUS_NAME "qspi"
#define OS_EXTERN_FLASH_PORT_CFG
#define OS_EXTERN_FLASH_DEV_NAME "W25Q256"
#define OS_EXTERN_FLASH_BUS_NAME "sfud_bus"
#define OS_EXTERN_FLASH_NAME "nor_flash"
#define OS_EXTERN_FLASH_SIZE 33554432
#define OS_EXTERN_FLASH_BLOCK_SIZE 4096
#define OS_EXTERN_FLASH_PAGE_SIZE 4096
#define BSP_USING_W25QXX
/* end of SPI */

/* FAL */

#define OS_USING_FAL
/* end of FAL */

/* RTT */

/* end of RTT */

/* Timer */

#define OS_USING_TIMER_DRIVER
#define OS_USING_CLOCKSOURCE
#define OS_USING_CLOCKSOURCE_CORTEXM
#define OS_USING_CLOCKEVENT
#define OS_USING_HRTIMER
#define OS_USING_HRTIMER_FOR_SYSTICK
/* end of Timer */

/* HwCrypto */

/* end of HwCrypto */

/* SDIO */

#define OS_USING_SDIO
#define OS_SDIO_STACK_SIZE 512
#define OS_SDIO_TASK_PRIORITY 15
#define OS_MMCSD_STACK_SIZE 1024
#define OS_MMCSD_TASK_PREORITY 22
#define OS_MMCSD_MAX_PARTITION 16
/* end of SDIO */

/* WLAN */

/* end of WLAN */

/* Graphic */

/* end of Graphic */

/* Touch */

/* end of Touch */

/* Sensors */

#define OS_USING_SENSOR
#define OS_USING_MPU6XXX
#define OS_MPU6XXX_BUS_NAME "soft_i2c2"
#define OS_MPU6XXX_ADDR 0x68
#define OS_MPU6XXX_INT_PIN 21
#define PKG_USING_MPU6XXX
#define PKG_USING_MPU6XXX_ACCE
#define PKG_USING_MPU6XXX_GYRO
#define OS_USING_MPU9250
#define OS_USING_AK8963
#define OS_AK8963_I2C_BUS_NAME "soft_i2c2"
#define OS_AK8963_I2C_ADDR 0x0c
/* end of Sensors */

/* USB */

#define OS_USING_USB_DEVICE
#define OS_USBD_TASK_STACK_SZ 4096
#define USB_VENDOR_ID 0x0FFE
#define USB_PRODUCT_ID 0x0001
#define OS_USB_DEVICE_COMPOSITE
#define OS_USB_DEVICE_NONE
#define OS_USB_DEVICE_HID
#define OS_USB_DEVICE_HID_MOUSE
#define OS_USB_DEVICE_HID_GENERAL
#define OS_USB_DEVICE_HID_GENERAL_OUT_REPORT_LENGTH 63
#define OS_USB_DEVICE_HID_GENERAL_IN_REPORT_LENGTH 63
#define OS_USB_DEVICE_HID_MEDIA
/* end of USB */

/* Infrared */

/* end of Infrared */

/* Low power manager */

/* end of Low power manager */

/* NAND */

/* end of NAND */
/* end of Drivers */

/* Components */

/* Atest */

#define OS_USING_ATEST
#define ATEST_TASK_STACK_SIZE 4096
#define ATEST_TASK_PRIORITY 20
/* end of Atest */

/* BLE */

/* end of BLE */

/* Cloud */

/* OneNET */

/* MQTT kit */

/* end of MQTT kit */

/* NB-IoT kit */

/* end of NB-IoT kit */

/* EDP */

/* end of EDP */
/* end of OneNET */
/* end of Cloud */

/* Dlog */

#define OS_USING_DLOG
#define DLOG_OUTPUT_LVL_W
#define DLOG_GLOBAL_LEVEL 4

/* Dlog backend option */

#define DLOG_BACKEND_USING_CONSOLE
/* end of Dlog backend option */
#define DLOG_USING_FILTER

/* Log format */

#define DLOG_USING_COLOR
#define DLOG_OUTPUT_TIME_INFO
#define DLOG_OUTPUT_LEVEL_INFO
#define DLOG_OUTPUT_TAG_INFO
/* end of Log format */
/* end of Dlog */

/* Network */

/* LwIP */

/* end of LwIP */

/* Molink */

/* end of Molink */

/* OTA */

/* Fota by CMIOT */

/* end of Fota by CMIOT */
/* end of OTA */

/* Protocols */

/* CoAP */

/* end of CoAP */

/* MQTT */

/* end of MQTT */

/* Websocket */

/* end of Websocket */

/* Httpclient */

/* end of Httpclient */
/* end of Protocols */

/* Socket */

/* end of Socket */

/* Tools */

/* end of Tools */
/* end of Network */

/* Security */

/* end of Security */

/* Shell */

#define OS_USING_SHELL
#define SHELL_TASK_NAME "tshell"
#define SHELL_TASK_PRIORITY 20
#define SHELL_TASK_STACK_SIZE 2048
#define SHELL_USING_HISTORY
#define SHELL_HISTORY_LINES 5
#define SHELL_USING_DESCRIPTION
#define SHELL_CMD_SIZE 80
#define SHELL_ARG_MAX 10
/* end of Shell */

/* FileSystem */

#define OS_USING_VFS
#define VFS_USING_WORKDIR
#define VFS_FILESYSTEMS_MAX 2
#define VFS_FILESYSTEM_TYPES_MAX 2
#define VFS_FD_MAX 16
#define OS_USING_VFS_DEVFS
/* end of FileSystem */

/* GUI */

/* end of GUI */

/* OnePos */

/* end of OnePos */

/* Ramdisk */

/* end of Ramdisk */

/* Diagnose */

/* end of Diagnose */
/* end of Components */

/* Thirdparty */

/* cJSON */

/* end of cJSON */

/* Easyflash */

/* end of Easyflash */

/* NTP */

/* end of NTP */

/* WebClient */

/* end of WebClient */

/* Ali-iotkit */

/* end of Ali-iotkit */

/* MicroPython */

/* end of MicroPython */

/* Amazon-iot */

/* end of Amazon-iot */
/* end of Thirdparty */

/* Boot Config */

/* end of Boot Config */

/* Debug */

#define OS_DEBUG
#define OS_DEBUG_LOG_WITH_FUNC_LINE
#define LOG_BUFF_SIZE_256
#define OS_LOG_BUFF_SIZE 256
/* end of Debug */

#endif /* __ONEOS_CONFIG_H__ */

