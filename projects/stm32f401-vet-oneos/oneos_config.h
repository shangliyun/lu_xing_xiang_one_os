#ifndef __ONEOS_CONFIG_H__
#define __ONEOS_CONFIG_H__

#define BOARD_STM32F401RE
#define ARCH_ARM
#define ARCH_ARM_CORTEX_M
#define ARCH_ARM_CORTEX_M4

/* Kernel */

#define OS_NAME_MAX_15
#define OS_NAME_MAX 15
#define OS_ALIGN_SIZE 4
#define OS_TASK_PRIORITY_32
#define OS_TASK_PRIORITY_MAX 32
#define OS_TICK_PER_SECOND 100
#define OS_USING_OVERFLOW_CHECK
#define OS_MAIN_TASK_STACK_SIZE 2048
#define OS_USING_HOOK
#define OS_USING_IDLE_HOOK
#define OS_IDLE_HOOK_LIST_SIZE 4
#define OS_IDLE_TASK_STACK_SIZE 2048
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
#define OS_CONSOLE_DEVICE_NAME "uart6"
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
#define SOC_SERIES_STM32F4
#define SOC_STM32F4XX

/* Configure base hal in STM32CubeMX */

/* end of HAL */

/* Audio */

/* end of Audio */

/* MISC */

#define OS_USING_PUSH_BUTTON
#define OS_USING_LED
#define OS_USING_BUZZER
/* end of MISC */

/* PIN */

#define OS_USING_PIN
#define OS_PIN_MAX_CHIP 1
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
/* end of I2C */

/* SPI */

#define OS_USING_SPI
#define OS_USING_SPI_MSD
#define OS_USING_SFUD
#define OS_SFUD_USING_SFDP
#define OS_SFUD_USING_FLASH_INFO_TABLE
#define OS_SFUD_USING_SPI
#define OS_SPI_FLASH_BUS_NAME "spi4"
#define OS_SPI_FLASH_CS_PIN 75
#define OS_EXTERN_FLASH_PORT_CFG
#define OS_EXTERN_FLASH_DEV_NAME "W25Q64"
#define OS_EXTERN_FLASH_BUS_NAME "sfud_bus"
#define OS_EXTERN_FLASH_NAME "nor_flash"
#define OS_EXTERN_FLASH_SIZE 8388608
#define OS_EXTERN_FLASH_BLOCK_SIZE 4096
#define OS_EXTERN_FLASH_PAGE_SIZE 4096
#define BSP_USING_W25QXX
#define BSP_USING_SDCARD
#define BSP_SDCARD_SPI_DEV "spi3"
#define BSP_SDCARD_SPI_CS_PIN 15
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

/* end of SDIO */

/* WLAN */

/* end of WLAN */

/* Graphic */

#define OS_USING_GRAPHIC
#define OS_GRAPHIC_WIDTH 240
#define OS_GRAPHIC_HEIGHT 240
#define OS_USING_ST7789VW
#define OS_ST7789VW_SPI_BUS_NAME "spi1"
#define OS_ST7789VW_SPI_BUS_MODE 3
#define OS_ST7789VW_SPI_CS_PIN 4
#define OS_ST7789VW_PWR_PIN 6
#define OS_ST7789VW_PWR_PIN_ACTIVE 0
#define OS_ST7789VW_DC_PIN 59
#define OS_ST7789VW_RES_PIN 60
/* end of Graphic */

/* Touch */

/* end of Touch */

/* Sensors */

#define OS_USING_SENSOR
#define OS_USING_AHT10
#define OS_AHT10_I2C_BUS_NAME "hard_i2c1"
#define OS_AHT10_I2C_ADDR 0x38
#define OS_USING_MPU6XXX
#define OS_MPU6XXX_BUS_NAME "hard_i2c1"
#define OS_MPU6XXX_ADDR 0x68
#define OS_MPU6XXX_INT_PIN 21
#define PKG_USING_MPU6XXX
#define PKG_USING_MPU6XXX_ACCE
#define PKG_USING_MPU6XXX_GYRO
#define OS_USING_ICM20602
#define OS_USING_AP3216C
#define OS_AP3216C_I2C_BUS_NAME "hard_i2c1"
#define OS_AP3216C_I2C_ADDR 0x1e
/* end of Sensors */

/* USB */

/* end of USB */

/* Infrared */

#define OS_USING_INFRARED
#define BSP_USING_RMT_CTL_ATK_TX
#define BSP_USING_RMT_CTL_ATK_TX_PIN 9
#define BSP_USING_RMT_CTL_ATK_RX
#define BSP_USING_RMT_CTL_ATK_RX_PIN 16
/* end of Infrared */

/* Low power manager */

/* end of Low power manager */

/* NAND */

/* end of NAND */
/* end of Drivers */

/* Components */

/* Atest */

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
#define DLOG_OUTPUT_LVL_I
#define DLOG_GLOBAL_LEVEL 6

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

#define NET_USING_MOLINK
#define MOLINK_PLATFORM_MCU

/* Modules */

/* 4G Modules Support */

/* end of 4G Modules Support */

/* NB-IOT Modules Support */

/* end of NB-IOT Modules Support */

/* WiFi Modules Support */

#define MOLINK_USING_ESP8266

/* ESP8266 Config */

#define ESP8266_AUTO_CREATE
#define ESP8266_DEVICE_NAME "uart1"
#define ESP8266_DEVICE_RATE 115200
#define ESP8266_RECV_BUFF_LEN 512
#define ESP8266_AUTO_CONNECT_AP
#define ESP8266_CONNECT_SSID "Tenda_56D088"
#define ESP8266_CONNECT_PASSWORD "12345678"
#define ESP8266_USING_GENERAL_OPS
#define ESP8266_USING_WIFI_OPS
#define ESP8266_USING_PING_OPS
#define ESP8266_USING_IFCONFIG_OPS
#define ESP8266_USING_NETCONN_OPS
/* end of ESP8266 Config */
/* end of WiFi Modules Support */
/* end of Modules */

/* Parser */

#define MOLINK_USING_PARSER
#define AT_PARSER_TASK_STACK_SIZE 2048
#define AT_CMD_LEN_MAX 128
/* end of Parser */
#define MOLINK_USING_GENERAL_OPS
#define MOLINK_USING_PING_OPS
#define MOLINK_USING_IFCONFIG_OPS
#define MOLINK_USING_NETCONN_OPS
#define MOLINK_USING_WIFI_OPS
#define MOLINK_USING_IP
#define MOLINK_USING_IPV4
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

#define NET_USING_TOOLS
#define MODULE_USING_IFCONFIG
#define MODULE_USING_PING
#define MO_PING_MAX_TIMES_CONFIG 50
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
#define OS_USING_VFS_FATFS

/* Elm-ChaN's FatFs, generic FAT filesystem module */

#define OS_VFS_FAT_CODE_PAGE 437
#define OS_VFS_FAT_USE_LFN_3
#define OS_VFS_FAT_USE_LFN 3
#define OS_VFS_FAT_MAX_LFN 255
#define OS_VFS_FAT_DRIVES 2
#define OS_VFS_FAT_MAX_SECTOR_SIZE 4096
#define OS_VFS_FAT_REENTRANT
/* end of Elm-ChaN's FatFs, generic FAT filesystem module */
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

