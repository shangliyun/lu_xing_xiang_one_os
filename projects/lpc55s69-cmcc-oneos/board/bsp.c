/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 * Copyright (c) 2019-2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 * 2010-02-04     Magicoe      ported to LPC17xx
 * 2010-05-02     Aozima       update CMSIS to 130
 * 2017-08-02     XiaoYang     porting to LPC54608 bsp
 * 2019-08-05     Magicoe      porting to LPC55S69-EVK bsp
 * 2020-01-01     Karl         Add PKG_USING_TFM support
 */


#include "bsp.h"
#include <drv_gpio.h>

#include <os_hw.h>
#include <os_device.h>
#include <os_task.h>
#include <os_errno.h>
#include <os_assert.h>
#include <os_irq.h>
#include <os_clock.h>
#include <os_memory.h>

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    os_interrupt_enter();

    os_tick_increase();

    /* leave interrupt */
    os_interrupt_leave();
}

/**
 * This function will initial LPC55Sxx board.
 */
void os_hw_board_init()
{
    /* Hardware Initialization */
    BOARD_InitPins();
    
    CLOCK_EnableClock(kCLOCK_InputMux);
    
    CLOCK_EnableClock(kCLOCK_Gpio0);
    CLOCK_EnableClock(kCLOCK_Gpio1);
    
    GPIO_PortInit(GPIO, 0);
    GPIO_PortInit(GPIO, 1);
    
    /* NVIC Configuration */
#define NVIC_VTOR_MASK              0x3FFFFF80
#ifdef  VECT_TAB_RAM
    /* Set the Vector Table base location at 0x10000000 */
    SCB->VTOR  = (0x10000000 & NVIC_VTOR_MASK);
#else  /* VECT_TAB_FLASH  */

#ifdef PKG_USING_TFM
    /* Set the Vector Table base location at 0x00020000 when RTT with TF-M*/
    SCB->VTOR  = (0x00020000 & NVIC_VTOR_MASK);
#else
    /* Set the Vector Table base location at 0x00000000 */
    SCB->VTOR  = (0x00000000 & NVIC_VTOR_MASK);
#endif
#endif

#ifndef PKG_USING_TFM
    /* This init has finished in secure side of TF-M  */
    BOARD_BootClockPLL150M();
#endif
    //BOARD_BootClockFROHF96M();
    
    /* init systick  1 systick = 1/(100M / 100) 100��systick = 1s*/
    SysTick_Config(SystemCoreClock / 1000);
    /* set pend exception priority */
    NVIC_SetPriority(PendSV_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

    /*init uart device*/
//    rt_hw_uart_init();
    
#ifdef RT_USING_CONSOLE    
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    /* initialization board with RT-Thread Components */
    rt_components_board_init();
#endif

//#ifdef RT_USING_HEAP
    os_kprintf("sram heap, begin: 0x%p, end: 0x%p\n", HEAP_BEGIN, HEAP_END);
    os_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
//#endif
}

/**
 * This function will called when memory fault.
 */
void MemManage_Handler(void)
{
    extern void HardFault_Handler(void);

    os_kprintf("Memory Fault!\n");
    HardFault_Handler();
}
