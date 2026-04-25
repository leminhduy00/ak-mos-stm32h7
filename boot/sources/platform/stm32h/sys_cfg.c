/**
 ******************************************************************************
 * @Author: GaoKong
 * @Date:   05/09/2016
 ******************************************************************************
**/
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "sys_cfg.h"
#include "system.h"
#include "stm32h.h"
// #include "stm32h7xx.h"
// #include "system_stm32h7xx.h"
// #include "core_cm7.h"
// #include "cmsis_gcc.h"

#include "sys_dbg.h"
#include "sys_def.h"
#include "sys_ctrl.h"

#include "system.h"

#include "app.h"

#include "tim.h"
#include "iwdg.h"
#include "usart.h"

/* Private define */
static uint32_t delay_coeficient = 0;
static void xputchar(uint8_t c);
/******************************************************************************
* system configure function
*******************************************************************************/
void MPU_Config(void)
{
	MPU_Region_InitTypeDef MPU_InitStruct = {0};

	/* Disables the MPU */
	HAL_MPU_Disable();

	/** Initializes and configures the Region and the memory to be protected
	 */
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER0;
	MPU_InitStruct.BaseAddress = 0x00000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
	MPU_InitStruct.SubRegionDisable = 0x00;
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
	MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/** Initializes and configures the Region and the memory to be protected
	 */
	MPU_InitStruct.Number = MPU_REGION_NUMBER1;
	MPU_InitStruct.BaseAddress = 0x08000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_2MB;
	MPU_InitStruct.SubRegionDisable = 0x0;
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/** Initializes and configures the Region and the memory to be protected
	 */
	MPU_InitStruct.Number = MPU_REGION_NUMBER3;
	MPU_InitStruct.BaseAddress = 0x20000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_128KB;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/** Initializes and configures the Region and the memory to be protected
	 */
	MPU_InitStruct.Number = MPU_REGION_NUMBER4;
	MPU_InitStruct.BaseAddress = 0x24000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_512KB;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/** Initializes and configures the Region and the memory to be protected
	 */
	MPU_InitStruct.Number = MPU_REGION_NUMBER5;
	MPU_InitStruct.BaseAddress = 0x30000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_256KB;
	MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/** Initializes and configures the Region and the memory to be protected
	 */
	MPU_InitStruct.Number = MPU_REGION_NUMBER6;
	MPU_InitStruct.BaseAddress = 0x40000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_512MB;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);
	/* Enables the MPU */
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

void sys_cfg_clock() {
RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Supply configuration update enable
	 */
	HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

	/** Configure the main internal regulator output voltage
	 */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

	while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 2;
	RCC_OscInitStruct.PLL.PLLN = 32;
	RCC_OscInitStruct.PLL.PLLP = 2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	RCC_OscInitStruct.PLL.PLLR = 2;
	RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
	RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
	RCC_OscInitStruct.PLL.PLLFRACN = 0;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		FATAL("RCC", 0x01);
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
								|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
								|RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV4;
	RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
	{
		FATAL("RCC", 0x02);
	}
}

void sys_cfg_tick() {
	HAL_InitTick(1);
}

void sys_cfg_console() {
	MX_USART1_UART_Init();

	xfunc_out = xputchar;
}

void sys_cfg_svc() {
	HAL_NVIC_SetPriority(SVCall_IRQn, 3, 0);
	HAL_NVIC_EnableIRQ(SVCall_IRQn);
}

void sys_cfg_update_info() {
}

/******************************************************************************
* system utilities function
*******************************************************************************/
void xputchar(uint8_t c) {
	uart_put_char_block(c);
}

void sys_ctrl_shell_put_char(uint8_t c) {
	uart_put_char_block(c);
}

uint8_t sys_ctrl_shell_get_char() {
	return uart_get_char();
}

void sys_ctrl_reset() {
	NVIC_SystemReset();
}

void sys_ctrl_delay_us(volatile uint32_t count) {
	volatile uint32_t delay_value = 0;
	delay_value = count*delay_coeficient / 8;
	while(delay_value--);
}

void sys_ctrl_delay_ms(volatile uint32_t count) {
#if 0
	volatile uint32_t current_time = 0;
	volatile uint32_t current;
	volatile int32_t start = sys_ctrl_millis();

	while(current_time < count) {
		current = sys_ctrl_millis();

		if (current < start) {
			current_time += ((uint32_t)0xFFFFFFFF - start) + current;
		}
		else {
			current_time += current - start;
		}

		start = current;
	}
#else
	volatile uint32_t delay = 1000 * count;
	sys_ctrl_delay_us(delay);
#endif
}

void sys_ctrl_independent_watchdog_init() {
	MX_IWDG1_Init();
}

void sys_ctrl_independent_watchdog_reset() {
	ENTRY_CRITICAL();
	iwdg_feed();
	EXIT_CRITICAL();
}

static uint32_t sys_ctrl_soft_counter = 0;
static uint32_t sys_ctrl_soft_time_out;

void sys_ctrl_soft_watchdog_init(uint32_t time_out) {
	sys_ctrl_soft_time_out = time_out;

	MX_TIM7_Init();
}

void sys_ctrl_soft_watchdog_reset() {
	ENTRY_CRITICAL();
	sys_ctrl_soft_counter = 0;
	EXIT_CRITICAL();
}

void sys_ctrl_soft_watchdog_enable() {
	ENTRY_CRITICAL();
	HAL_TIM_Base_Start_IT(&htim7);
	EXIT_CRITICAL();
}

void sys_ctrl_soft_watchdog_disable() {
	ENTRY_CRITICAL();
	HAL_TIM_Base_Stop_IT(&htim7);
	EXIT_CRITICAL();
}

void sys_ctrl_soft_watchdog_increase_counter() {
	sys_ctrl_soft_counter++;
	if (sys_ctrl_soft_counter >= sys_ctrl_soft_time_out) {
		/* FATAL("SWDG", 0x01); */
	}
}

void sys_ctrl_get_firmware_info(firmware_header_t* header) {
	extern uint32_t _start_flash;
	extern uint32_t _end_flash;
	extern uint32_t _data;
	extern uint32_t _edata;

	uint32_t check_sum = 0;
	uint32_t len_of_flash = (uint32_t)&_end_flash - (uint32_t)&_start_flash + ((uint32_t)&_edata - (uint32_t)&_data) + sizeof(uint32_t);

	for (uint32_t index = (uint32_t)&(_start_flash); index < ((uint32_t)&(_start_flash) + len_of_flash); index += sizeof(uint32_t)) {
		check_sum += *((uint32_t*)index);
	}

	header->psk = FIRMWARE_PSK;
	header->checksum = (check_sum & 0xFFFF);
	header->bin_len = len_of_flash;
}

uint32_t sys_ctrl_jump_to_app_req;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated"
void sys_ctrl_jump_to_app() {
	volatile uint32_t normal_stack_pointer	=	(uint32_t) *(volatile uint32_t*)(NORMAL_START_ADDRESS);
	volatile uint32_t normal_jump_address	=	(uint32_t) *(volatile uint32_t*)(NORMAL_START_ADDRESS + 4);

	p_jump_func jump_to_normal = (p_jump_func)normal_jump_address;

	/* Disable interrupt */
	DISABLE_INTERRUPTS();

	/* set stack pointer */
	__DMB();
	__asm volatile ("MSR msp, %0\n" : : "r" (normal_stack_pointer) : "sp");
	__DSB();

	/* jump to normal program */
	jump_to_normal();
}
#pragma GCC diagnostic pop
