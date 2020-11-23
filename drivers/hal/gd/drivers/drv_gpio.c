/**
 ***********************************************************************************************************************
 * Copyright (c) 2020, China Mobile Communications Group Co.,Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with 
 * the License. You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 *
 * @file        drv_gpio.c
 *
 * @brief       This file implements gpio driver for stm32.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-20   OneOS Team      First Version
 ***********************************************************************************************************************
 */

#include <os_irq.h>
#include "drv_gpio.h"
#include "gd32f30x.h"
#include "gd32f30x_exti.h"

#include <os_irq.h>

#define __GD32_PIN(index, port, pin) {index, RCU_GPIO##port, GPIO##port, \
        GPIO_PIN_##pin, GPIO_PORT_SOURCE_GPIO##port, GPIO_PIN_SOURCE_##pin}
#define __GD32_PIN_DEFAULT {-1, (rcu_periph_enum)0, 0, 0, 0, 0}

static const struct pin_index pins[] =
{
    __GD32_PIN_DEFAULT,
    __GD32_PIN(1, E, 2),
    __GD32_PIN(2, E, 3),
    __GD32_PIN(3, E, 4),
    __GD32_PIN(4, E, 5),
    __GD32_PIN(5, E, 6),
    __GD32_PIN_DEFAULT,
    __GD32_PIN(7, C, 13),
    __GD32_PIN(8, C, 14),
    __GD32_PIN(9, C, 15),
    __GD32_PIN(10, F, 0),
    __GD32_PIN(11, F, 1),
    __GD32_PIN(12, F, 2),
    __GD32_PIN(13, F, 3),
    __GD32_PIN(14, F, 4),
    __GD32_PIN(15, F, 5),
    __GD32_PIN_DEFAULT,
    __GD32_PIN_DEFAULT,
    __GD32_PIN(18, F, 6),
    __GD32_PIN(19, F, 7),
    __GD32_PIN(20, F, 8),
    __GD32_PIN(21, F, 9),
    __GD32_PIN(22, F, 10),
    __GD32_PIN_DEFAULT,
    __GD32_PIN_DEFAULT,
    __GD32_PIN_DEFAULT,
    __GD32_PIN(26, C, 0),
    __GD32_PIN(27, C, 1),
    __GD32_PIN(28, C, 2),
    __GD32_PIN(29, C, 3),
    __GD32_PIN_DEFAULT,
    __GD32_PIN_DEFAULT,
    __GD32_PIN_DEFAULT,
    __GD32_PIN_DEFAULT,
    __GD32_PIN(34, A, 0),
    __GD32_PIN(35, A, 1),
    __GD32_PIN(36, A, 2),
    __GD32_PIN(37, A, 3),
    __GD32_PIN_DEFAULT,
    __GD32_PIN_DEFAULT,
    __GD32_PIN(40, A, 4),
    __GD32_PIN(41, A, 5),
    __GD32_PIN(42, A, 6),
    __GD32_PIN(43, A, 7),
    __GD32_PIN(44, C, 4),
    __GD32_PIN(45, C, 5),
    __GD32_PIN(46, B, 0),
    __GD32_PIN(47, B, 1),
    __GD32_PIN(48, B, 2),
    __GD32_PIN(49, F, 11),
    __GD32_PIN(50, F, 12),
    __GD32_PIN_DEFAULT,
    __GD32_PIN_DEFAULT,
    __GD32_PIN(53, F, 13),
    __GD32_PIN(54, F, 14),
    __GD32_PIN(55, F, 15),
    __GD32_PIN(56, G, 0),
    __GD32_PIN(57, G, 1),
    __GD32_PIN(58, E, 7),
    __GD32_PIN(59, E, 8),
    __GD32_PIN(60, E, 9),
    __GD32_PIN_DEFAULT,
    __GD32_PIN_DEFAULT,
    __GD32_PIN(63, E, 10),
    __GD32_PIN(64, E, 11),
    __GD32_PIN(65, E, 12),
    __GD32_PIN(66, E, 13),
    __GD32_PIN(67, E, 14),
    __GD32_PIN(68, E, 15),
    __GD32_PIN(69, B, 10),
    __GD32_PIN(70, B, 11),
    __GD32_PIN_DEFAULT,
    __GD32_PIN_DEFAULT,
    __GD32_PIN(73, B, 12),
    __GD32_PIN(74, B, 13),
    __GD32_PIN(75, B, 14),
    __GD32_PIN(76, B, 15),
    __GD32_PIN(77, D, 8),
    __GD32_PIN(78, D, 9),
    __GD32_PIN(79, D, 10),
    __GD32_PIN(80, D, 11),
    __GD32_PIN(81, D, 12),
    __GD32_PIN(82, D, 13),
    __GD32_PIN_DEFAULT,
    __GD32_PIN_DEFAULT,
    __GD32_PIN(85, D, 14),
    __GD32_PIN(86, D, 15),
    __GD32_PIN(87, G, 2),
    __GD32_PIN(88, G, 3),
    __GD32_PIN(89, G, 4),
    __GD32_PIN(90, G, 5),
    __GD32_PIN(91, G, 6),
    __GD32_PIN(92, G, 7),
    __GD32_PIN(93, G, 8),
    __GD32_PIN_DEFAULT,
    __GD32_PIN_DEFAULT,
    __GD32_PIN(96, C, 6),
    __GD32_PIN(97, C, 7),
    __GD32_PIN(98, C, 8),
    __GD32_PIN(99, C, 9),
    __GD32_PIN(100, A, 8),
    __GD32_PIN(101, A, 9),
    __GD32_PIN(102, A, 10),
    __GD32_PIN(103, A, 11),
    __GD32_PIN(104, A, 12),
    __GD32_PIN(105, A, 13),
    __GD32_PIN_DEFAULT,
    __GD32_PIN_DEFAULT,
    __GD32_PIN_DEFAULT,
    __GD32_PIN(109, A, 14),
    __GD32_PIN(110, A, 15),
    __GD32_PIN(111, C, 10),
    __GD32_PIN(112, C, 11),
    __GD32_PIN(113, C, 12),
    __GD32_PIN(114, D, 0),
    __GD32_PIN(115, D, 1),
    __GD32_PIN(116, D, 2),
    __GD32_PIN(117, D, 3),
    __GD32_PIN(118, D, 4),
    __GD32_PIN(119, D, 5),
    __GD32_PIN_DEFAULT,
    __GD32_PIN_DEFAULT,
    __GD32_PIN(122, D, 6),
    __GD32_PIN(123, D, 7),
    __GD32_PIN(124, G, 9),
    __GD32_PIN(125, G, 10),
    __GD32_PIN(126, G, 11),
    __GD32_PIN(127, G, 12),
    __GD32_PIN(128, G, 13),
    __GD32_PIN(129, G, 14),
    __GD32_PIN_DEFAULT,
    __GD32_PIN_DEFAULT,
    __GD32_PIN(132, G, 15),
    __GD32_PIN(133, B, 3),
    __GD32_PIN(134, B, 4),
    __GD32_PIN(135, B, 5),
    __GD32_PIN(136, B, 6),
    __GD32_PIN(137, B, 7),
    __GD32_PIN_DEFAULT,
    __GD32_PIN(139, B, 8),
    __GD32_PIN(140, B, 9),
    __GD32_PIN(141, E, 0),
    __GD32_PIN(142, E, 1),
    __GD32_PIN_DEFAULT,
    __GD32_PIN_DEFAULT,
};

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])
const struct pin_index *get_pin(os_uint8_t pin)
{
    const struct pin_index *index;

    if (pin < ITEM_NUM(pins))
    {
        index = &pins[pin];
        if (index->index == -1)
        index = OS_NULL;
    }
    else
    {
        index = OS_NULL;
    }

    return index;
};

#ifdef OS_USING_PIN
struct pin_irq_map
{
    os_uint16_t pinbit;
    IRQn_Type irqno;
};
static const struct pin_irq_map pin_irq_map[] =
{
    {GPIO_PIN_0, EXTI0_IRQn},
    {GPIO_PIN_1, EXTI1_IRQn},
    {GPIO_PIN_2, EXTI2_IRQn},
    {GPIO_PIN_3, EXTI3_IRQn},
    {GPIO_PIN_4, EXTI4_IRQn},
    {GPIO_PIN_5, EXTI5_9_IRQn},
    {GPIO_PIN_6, EXTI5_9_IRQn},
    {GPIO_PIN_7, EXTI5_9_IRQn},
    {GPIO_PIN_8, EXTI5_9_IRQn},
    {GPIO_PIN_9, EXTI5_9_IRQn},
    {GPIO_PIN_10, EXTI10_15_IRQn},
    {GPIO_PIN_11, EXTI10_15_IRQn},
    {GPIO_PIN_12, EXTI10_15_IRQn},
    {GPIO_PIN_13, EXTI10_15_IRQn},
    {GPIO_PIN_14, EXTI10_15_IRQn},
    {GPIO_PIN_15, EXTI10_15_IRQn},
};

struct os_pin_irq_hdr pin_irq_hdr_tab[] =
{
    {-1, 0, OS_NULL, OS_NULL},
    {-1, 0, OS_NULL, OS_NULL},
    {-1, 0, OS_NULL, OS_NULL},
    {-1, 0, OS_NULL, OS_NULL},
    {-1, 0, OS_NULL, OS_NULL},
    {-1, 0, OS_NULL, OS_NULL},
    {-1, 0, OS_NULL, OS_NULL},
    {-1, 0, OS_NULL, OS_NULL},
    {-1, 0, OS_NULL, OS_NULL},
    {-1, 0, OS_NULL, OS_NULL},
    {-1, 0, OS_NULL, OS_NULL},
    {-1, 0, OS_NULL, OS_NULL},
    {-1, 0, OS_NULL, OS_NULL},
    {-1, 0, OS_NULL, OS_NULL},
    {-1, 0, OS_NULL, OS_NULL},
    {-1, 0, OS_NULL, OS_NULL},
};

static void gd32_pin_mode(os_device_t *dev, os_base_t pin, os_base_t mode)
{
    const struct pin_index *index;
    os_uint32_t pin_mode;
    index = get_pin(pin);
    if (index == OS_NULL)
    {
        return;
    }

    /* GPIO Periph clock enable */
    rcu_periph_clock_enable(index->clk);
    pin_mode = GPIO_MODE_OUT_PP;
    
   switch(mode)
   {
   case PIN_MODE_OUTPUT:
        /* output setting */
        pin_mode = GPIO_MODE_OUT_PP;
        break;
   case PIN_MODE_OUTPUT_OD:
        /* output setting: od. */
        pin_mode = GPIO_MODE_OUT_OD;
        break;
   case PIN_MODE_INPUT:
        /* input setting: not pull. */
        pin_mode = GPIO_MODE_IN_FLOATING;
        break;
   case PIN_MODE_INPUT_PULLUP:
        /* input setting: pull up. */
        pin_mode = GPIO_MODE_IPU;
        break;
   case PIN_MODE_INPUT_PULLDOWN:
        /* input setting: pull down. */
        pin_mode = GPIO_MODE_IPD;
        break;
   default:
        break;
   }

    gpio_init(index->gpio_periph, pin_mode, GPIO_OSPEED_50MHZ, index->pin);
}

static void gd32_pin_write(os_device_t *dev, os_base_t pin, os_base_t value)
{
    const struct pin_index *index;

    index = get_pin(pin);
    if (index == OS_NULL)
    {
        return;
    }

    gpio_bit_write(index->gpio_periph, index->pin, (bit_status)value);
}

static int gd32_pin_read(os_device_t *dev, os_base_t pin)
{
    int value;
    const struct pin_index *index;

    value = PIN_LOW;

    index = get_pin(pin);
    if (index == OS_NULL)
    {
        return value;
    }

    value = gpio_input_bit_get(index->gpio_periph, index->pin);

    return value;
}


OS_INLINE os_int32_t bit2bitno(os_uint32_t bit)
{
    os_uint8_t i;
    for (i = 0; i < 32; i++)
    {
        if ((0x01 << i) == bit)
        {
            return i;
        }
    }
    return -1;
}
OS_INLINE const struct pin_irq_map *get_pin_irq_map(os_uint32_t pinbit)
{
    os_int32_t mapindex = bit2bitno(pinbit);
    if (mapindex < 0 || mapindex >= ITEM_NUM(pin_irq_map))
    {
        return OS_NULL;
    }
    return &pin_irq_map[mapindex];
};


static os_err_t gd32_pin_attach_irq(struct os_device   *device,
                                    os_int32_t          pin,
                                    os_uint32_t         mode,
                                    void (*hdr)(void *args), void *args)
{
    const struct pin_index *index;
    os_base_t               level;
    os_int32_t              irqindex = -1;

    index = get_pin(pin);
    if (index == OS_NULL)
    {
        return OS_ENOSYS;
    }
    irqindex = bit2bitno(index->pin);
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return OS_ENOSYS;
    }

    level = os_hw_interrupt_disable();

    if (pin_irq_hdr_tab[irqindex].pin == pin       &&
            pin_irq_hdr_tab[irqindex].hdr == hdr   &&
            pin_irq_hdr_tab[irqindex].mode == mode &&
            pin_irq_hdr_tab[irqindex].args == args)
    {
        os_hw_interrupt_enable(level);
        return OS_EOK;
    }
    if (pin_irq_hdr_tab[irqindex].pin != -1)
    {
        os_hw_interrupt_enable(level);
        return OS_EBUSY;
    }
    pin_irq_hdr_tab[irqindex].pin  = pin;
    pin_irq_hdr_tab[irqindex].hdr  = hdr;
    pin_irq_hdr_tab[irqindex].mode = mode;
    pin_irq_hdr_tab[irqindex].args = args;
    os_hw_interrupt_enable(level);

    return OS_EOK;
}

static os_err_t gd32_pin_dettach_irq(struct os_device *device, os_int32_t pin)
{
    const struct pin_index *index;
    os_base_t               level;
    os_int32_t              irqindex = -1;

    index = get_pin(pin);
    if (index == OS_NULL)
    {
        return OS_ENOSYS;
    }
    irqindex = bit2bitno(index->pin);
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return OS_ENOSYS;
    }

    level = os_hw_interrupt_disable();
    if (pin_irq_hdr_tab[irqindex].pin == -1)
    {
        os_hw_interrupt_enable(level);
        return OS_EOK;
    }
    pin_irq_hdr_tab[irqindex].pin  = -1;
    pin_irq_hdr_tab[irqindex].hdr  = OS_NULL;
    pin_irq_hdr_tab[irqindex].mode = 0;
    pin_irq_hdr_tab[irqindex].args = OS_NULL;
    os_hw_interrupt_enable(level);

    return OS_EOK;
}

static os_err_t gd32_pin_irq_enable(struct os_device *device, os_base_t pin, os_uint32_t enabled)
{
    const struct pin_index *index;
    const struct pin_irq_map *irqmap;
    os_base_t level;
    os_int32_t hdr_index = -1;
    exti_trig_type_enum trigger_mode;

    index = get_pin(pin);
    if (index == OS_NULL)
    {
        return OS_EINVAL;
    }
    if (enabled == PIN_IRQ_ENABLE)
    {
        hdr_index = bit2bitno(index->pin);
        if (hdr_index < 0 || hdr_index >= ITEM_NUM(pin_irq_map))
        {
            return OS_EINVAL;
        }
        level = os_hw_interrupt_disable();
        if (pin_irq_hdr_tab[hdr_index].pin == -1)
        {
            os_hw_interrupt_enable(level);
            return OS_EINVAL;
        }
        irqmap = &pin_irq_map[hdr_index];
   
        switch (pin_irq_hdr_tab[hdr_index].mode)
        {
            case PIN_IRQ_MODE_RISING:
                trigger_mode = EXTI_TRIG_RISING;
                break;
            case PIN_IRQ_MODE_FALLING:
                trigger_mode = EXTI_TRIG_FALLING;
                break;
            case PIN_IRQ_MODE_RISING_FALLING:
                trigger_mode = EXTI_TRIG_BOTH;
                break;
            default:
                os_hw_interrupt_enable(level);
                return OS_EINVAL;
        }

        rcu_periph_clock_enable(RCU_AF);

        /* enable and set interrupt priority */
        nvic_irq_enable(irqmap->irqno, 5U, 0U);
        
        /* connect EXTI line to  GPIO pin */
        gpio_exti_source_select(index->port_src, index->pin_src);

        /* configure EXTI line */
        exti_init((exti_line_enum)(index->pin), EXTI_INTERRUPT, trigger_mode);
        exti_interrupt_flag_clear((exti_line_enum)(index->pin));
        
        os_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(index->pin);
        if (irqmap == OS_NULL)
        {
            return OS_EINVAL;
        }
        nvic_irq_disable(irqmap->irqno);
    }
    else
    {
        return OS_EINVAL;
    }

    return OS_EOK;
}

const static struct os_pin_ops _gd32_pin_ops = {
    gd32_pin_mode,
    gd32_pin_write,
    gd32_pin_read,
    gd32_pin_attach_irq,
    gd32_pin_dettach_irq,
    gd32_pin_irq_enable,
};

OS_INLINE void pin_irq_hdr(int irqno)
{
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

void GD32_GPIO_EXTI_IRQHandler(os_int8_t exti_line)
{
    if (exti_interrupt_flag_get((exti_line_enum)(1 << exti_line)))
    {
        pin_irq_hdr(exti_line);
        exti_interrupt_flag_clear((exti_line_enum)(1 << exti_line));
    }
}
void EXTI0_IRQHandler(void)
{
    os_interrupt_enter();
    GD32_GPIO_EXTI_IRQHandler(0);
    os_interrupt_leave();
}
void EXTI1_IRQHandler(void)
{
    os_interrupt_enter();
    GD32_GPIO_EXTI_IRQHandler(1);
    os_interrupt_leave();
}
void EXTI2_IRQHandler(void)
{
    os_interrupt_enter();
    GD32_GPIO_EXTI_IRQHandler(2);
    os_interrupt_leave();
}
void EXTI3_IRQHandler(void)
{
    os_interrupt_enter();
    GD32_GPIO_EXTI_IRQHandler(3);
    os_interrupt_leave();
}
void EXTI4_IRQHandler(void)
{
    os_interrupt_enter();
    GD32_GPIO_EXTI_IRQHandler(4);
    os_interrupt_leave();
}
void EXTI5_9_IRQHandler(void)
{
    os_interrupt_enter();
    GD32_GPIO_EXTI_IRQHandler(5);
    GD32_GPIO_EXTI_IRQHandler(6);
    GD32_GPIO_EXTI_IRQHandler(7);
    GD32_GPIO_EXTI_IRQHandler(8);
    GD32_GPIO_EXTI_IRQHandler(9);
    os_interrupt_leave();
}
void EXTI10_15_IRQHandler(void)
{
    os_interrupt_enter();
    GD32_GPIO_EXTI_IRQHandler(10);
    GD32_GPIO_EXTI_IRQHandler(11);
    GD32_GPIO_EXTI_IRQHandler(12);
    GD32_GPIO_EXTI_IRQHandler(13);
    GD32_GPIO_EXTI_IRQHandler(14);
    GD32_GPIO_EXTI_IRQHandler(15);
    os_interrupt_leave();
}

/**
 ***********************************************************************************************************************
 * @brief           os_hw_pin_init:enable gpio clk,register pin device.
 *
 * @param[in]       none
 *
 * @return          Return init result.
 * @retval          OS_EOK       init success.
 * @retval          Others       init failed.
 ***********************************************************************************************************************
 */
int os_hw_pin_init(void)
{
#if defined(RCU_GPIOA)
   rcu_periph_clock_enable(RCU_GPIOA);
#endif

#if defined(RCU_GPIOB)
   rcu_periph_clock_enable(RCU_GPIOB);
#endif

#if defined(RCU_GPIOC)
   rcu_periph_clock_enable(RCU_GPIOC);
#endif

   return os_device_pin_register(0, &_gd32_pin_ops, OS_NULL);
}
#endif
