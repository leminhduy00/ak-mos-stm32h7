/**
 ******************************************************************************
 * @author: GaoKong
 * @date:   05/09/2016
 ******************************************************************************
**/
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "sys_cfg.h"
#include "system.h"

#include "xprintf.h"
#include "ring_buffer.h"

#include "sys_dbg.h"
#include "sys_ctrl.h"
#include "sys_io.h"
#include "sys_dbg.h"
#include "ak.h"

#include "tim.h"
#include "iwdg.h"
#include "usart.h"
//#pragma GCC optimize ("O3")

#define RING_BUFFER_CHAR_SHELL_SEND_BUFFER_SIZE		512

/* Private define */
static volatile uint32_t delay_coeficient = 0;

static uint8_t ring_buffer_char_shell_send_buffer[RING_BUFFER_CHAR_SHELL_SEND_BUFFER_SIZE];
ring_buffer_char_t ring_buffer_char_shell_send;

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

void sys_cfg_console() {
	ring_buffer_char_init(&ring_buffer_char_shell_send, ring_buffer_char_shell_send_buffer, RING_BUFFER_CHAR_SHELL_SEND_BUFFER_SIZE);

	MX_USART1_UART_Init();

	sys_ctrl_shell_sw_to_block();
}

void sys_cfg_update_info() {
	extern uint32_t _start_flash;
	extern uint32_t _end_flash;
	extern uint32_t _start_ram;
	extern uint32_t _end_ram;
	extern uint32_t _data;
	extern uint32_t _edata;
	extern uint32_t _bss;
	extern uint32_t _ebss;
	extern uint32_t __heap_start__;
	extern uint32_t __heap_end__;
	extern uint32_t _estack;

	system_info.cpu_clock = HAL_RCC_GetHCLKFreq();
	system_info.tick      = 1;
	system_info.console_baudrate = SYS_CONSOLE_BAUDRATE;
	system_info.flash_used = ((uint32_t)&_end_flash - (uint32_t)&_start_flash) + ((uint32_t)&_edata - (uint32_t)&_data);
	system_info.ram_used = (uint32_t)&_estack - (uint32_t)&_start_ram;
	system_info.data_init_size = (uint32_t)&_edata - (uint32_t)&_data;
	system_info.data_non_init_size = (uint32_t)&_ebss - (uint32_t)&_bss;
	system_info.stack_avail = (uint32_t)&_estack - (uint32_t)&_end_ram;
	system_info.heap_avail = (uint32_t)&__heap_end__ - (uint32_t)&__heap_start__;
	system_info.ram_other = system_info.ram_used - (system_info.heap_avail + system_info.stack_avail + system_info.data_non_init_size + system_info.data_init_size);

	delay_coeficient = system_info.cpu_clock /1000000;

	/* kernel banner */
	SYS_PRINT("\n");
	SYS_PRINT("   __    _  _ \n");
	SYS_PRINT("  /__\\  ( )/ )\n");
	SYS_PRINT(" /(__)\\ (   ( \n");
	SYS_PRINT("(__)(__)(_)\\_)\n");
	SYS_PRINT("Wellcome to Active Kernel %s\n", AK_VERSION);
	SYS_PRINT("\n");

#if 0
	/* system banner */
	SYS_PRINT("system information:\n");
	SYS_PRINT("\tFLASH used:\t%d bytes\n", system_info.flash_used);
	SYS_PRINT("\tSRAM used:\t%d bytes\n", system_info.ram_used);
	SYS_PRINT("\t\tdata init size:\t\t%d bytes\n", system_info.data_init_size);
	SYS_PRINT("\t\tdata non_init size:\t%d bytes\n", system_info.data_non_init_size);
	SYS_PRINT("\t\tstack avail:\t\t%d bytes\n", system_info.stack_avail);
	SYS_PRINT("\t\theap avail:\t\t%d bytes\n", system_info.heap_avail);
	SYS_PRINT("\t\tother:\t\t\t%d bytes\n", system_info.ram_other);
	SYS_PRINT("\n");
	SYS_PRINT("\tcpu clock:\t%d Hz\n", system_info.cpu_clock);
	SYS_PRINT("\ttime tick:\t%d ms\n", system_info.tick);
	SYS_PRINT("\tconsole:\t%d bps\n", system_info.console_baudrate);
	SYS_PRINT("\n\n");
#endif
}

/******************************************************************************
* system utilities function
*******************************************************************************/
void sys_ctrl_shell_put_char(uint8_t c) {
	bool _flag_trigger = false;

	ENTRY_CRITICAL();

	if (ring_buffer_char_is_empty(&ring_buffer_char_shell_send)) {
		_flag_trigger = true;
	}

	ring_buffer_char_put(&ring_buffer_char_shell_send, c);

	EXIT_CRITICAL();

	if (_flag_trigger) {
		uart_switch_to_non_block();
	}
}

void sys_ctrl_shell_put_char_block(uint8_t c) {
	uart_put_char_block(c);
}

void sys_ctrl_shell_sw_to_block() {
    ENTRY_CRITICAL();

    xfunc_output = (void(*)(int))sys_ctrl_shell_put_char_block;

    uart_switch_to_block();

    EXIT_CRITICAL();
}

void sys_ctrl_shell_sw_to_nonblock() {
    ENTRY_CRITICAL();

    xfunc_output = (void(*)(int))sys_ctrl_shell_put_char;

    uart_switch_to_non_block();

    EXIT_CRITICAL();
}

uint8_t sys_ctrl_shell_get_char() {
	return uart_get_char();
}

void sys_ctrl_reset() {
	NVIC_SystemReset();
}

void sys_ctr_sleep_wait_for_irq() {
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}

void sys_ctr_stop_mcu() {
	/* Enable GPIOs clock */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Pin = GPIO_PIN_All;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

	/* Optional: disable clock lại */
	__HAL_RCC_GPIOA_CLK_DISABLE();
	__HAL_RCC_GPIOB_CLK_DISABLE();
	__HAL_RCC_GPIOC_CLK_DISABLE();
	__HAL_RCC_GPIOD_CLK_DISABLE();
	__HAL_RCC_GPIOE_CLK_DISABLE();
	__HAL_RCC_GPIOH_CLK_DISABLE();

	__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);

	HAL_PWREx_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI, PWR_D1_DOMAIN);

	while(1){}
}

uint32_t sys_ctr_get_exception_number() {
	volatile uint32_t exception_number = (uint32_t)__get_IPSR();
	return exception_number;
}

void sys_ctr_restart_app() {
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated"
void sys_cfg_restore_app() {
	extern uint32_t _isr_vector;
	volatile uint32_t normal_stack_pointer	=	(uint32_t) *(volatile uint32_t*)(APP_START_ADDR);
	volatile uint32_t normal_jump_address	=	(uint32_t) *(volatile uint32_t*)(APP_START_ADDR + 4);

	p_jump_func jump_to_normal = (p_jump_func)normal_jump_address;

	/* update interrupt vertor table */
	SCB->VTOR = (uint32_t)&_isr_vector; /* Vector Table Relocation in Internal FLASH. */

	/* set stack pointer */
	__DSB();
	__asm volatile ("MSR msp, %0\n" : : "r" (normal_stack_pointer) : "sp");
	__DSB();

	/* jump to normal program */
	jump_to_normal();

	while(1);
}
#pragma GCC diagnostic pop

void sys_ctrl_independent_watchdog_init() {
	MX_IWDG1_Init();
}

void sys_ctrl_independent_watchdog_reset() {
	ENTRY_CRITICAL();
	iwdg_feed();
	EXIT_CRITICAL();
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

