/**
 ******************************************************************************
 * @Author: duy.leminh
 * @Date:   20/04/2026
 ******************************************************************************
**/

ENTRY	(reset_handler)

MEMORY
{
	/* RAM Layout*/
	DTCMRAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 128K
	RAM (xrw)          : ORIGIN = 0x24000000, LENGTH = 512K
	RAM_D2 (xrw)       : ORIGIN = 0x30000000, LENGTH = 256K
	/* FLASH Layout*/
	BSF (rx)           : ORIGIN = 0x08020000, LENGTH = 128K
	FLASH (rx)         : ORIGIN = 0x08040000, LENGTH = 1920K
}

/* heap size */
HEAP_SIZE = 8K;

/* Define output sections */
SECTIONS
{
	.start_boot_share_data_flash : {
		_start_boot_share_data_flash = .;
	} > BSF

	/* start of FLASH */
	.start_flash : {
		_start_flash = .;
	} > FLASH

	/* The startup code goes first into FLASH */
	.isr_vector :
	{
		_isr_vector = .;
		KEEP(*(.isr_vector)) /* Startup code */
		. = ALIGN(4);
	} >FLASH

	/* The program code and other data goes into FLASH */
	.text :
	{
		. = ALIGN(4);
		*(.text)           /* .text sections (code) */
		*(.text*)          /* .text* sections (code) */
		*(.rodata)         /* .rodata sections (constants, strings, etc.) */
		*(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
		*(.glue_7)         /* glue arm to thumb code */
		*(.glue_7t)        /* glue thumb to arm code */
		*(.eh_frame)

		KEEP (*(.init))
		KEEP (*(.fini))

		. = ALIGN(4);
		_etext = .;        /* define a global symbols at end of code */
	} >FLASH

	.ARM.extab (READONLY) : /* The "READONLY" keyword is only supported in GCC11 and later, remove it if using GCC10 or earlier. */
	{
		. = ALIGN(4);
		*(.ARM.extab* .gnu.linkonce.armextab.*)
		. = ALIGN(4);
	} >FLASH

	.ARM (READONLY) : /* The "READONLY" keyword is only supported in GCC11 and later, remove it if using GCC10 or earlier. */
	{
		. = ALIGN(4);
		__exidx_start = .;
		*(.ARM.exidx*)
		__exidx_end = .;
		. = ALIGN(4);
	} >FLASH

	.preinit_array :
	{
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(SORT(.preinit_array.*)))
		KEEP (*(.preinit_array*))
		PROVIDE_HIDDEN (__preinit_array_end = .);
	} >FLASH

	.init_array :
	{
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array*))
		PROVIDE_HIDDEN (__init_array_end = .);
	} >FLASH

	.fini_array :
	{
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(SORT(.fini_array.*)))
		KEEP (*(.fini_array*))
		PROVIDE_HIDDEN (__fini_array_end = .);
	} >FLASH

	/* end of FLASH */
	.end_flash : {
		_end_flash = .;
	} > FLASH

	/* start SRAM */
	.start_ram : {
		_start_ram = . ;
	} > RAM	

	_ldata = LOADADDR (.data);

	/* Initialized data sections go into AXI SRAM, load image from application FLASH */
	.data : AT(_end_flash) {
		. = ALIGN(4);
		_data = .;        /* create a global symbol at data start */
		*(vtable)
		*(.data)           /* .data sections */
		*(.data*)          /* .data* sections */
		*(.RamFunc)        /* .RamFunc sections */
		*(.RamFunc*)       /* .RamFunc* sections */

		. = ALIGN(4);
		_edata = .;        /* define a global symbol at data end */
	} >RAM


	/* Uninitialized data section in AXI SRAM */
	.bss :
	{
		/* This is used by the startup in order to initialize the .bss secion */
		. = ALIGN(4);
		_bss = .;         /* define a global symbol at bss start */
		__bss_start__ = _bss;
		*(.bss)
		*(.bss*)
		*(COMMON)

		. = ALIGN(4);
		_ebss = .;         /* define a global symbol at bss end */
		__bss_end__ = _ebss;
	} >RAM

	/* Heap in AXI SRAM, stack in DTCM */
	._user_heap_stack :
	{
		__heap_start__ = . ;
		. = . + HEAP_SIZE;
		. = ALIGN(8);
		__heap_end__ = . ;
	} >RAM

	/* end of SRAM */
	.end_ram : {
		_end_ram = . ;
	} > RAM

	/* Non-cacheable/shareable DMA buffers start at 0x30000000 */
	.dma_buffer (NOLOAD) :
	{
		. = ALIGN(32);
		__dma_buffer_start__ = .;
		*(.dma_buffer)
		*(.dma_buffer*)
		. = ALIGN(32);
		__dma_buffer_end__ = .;
	} >RAM_D2

	/* non clear RAM */
	.non_clear_ram (NOLOAD) : {
		. = ALIGN(4);
		_non_clear_ram = .;
		KEEP (*(.non_clear_ram))
		KEEP (*(.non_clear_ram*))
		. = ALIGN(4);
		_enon_clear_ram = .;
	} > RAM_D2

	.sstack : {
		_sstack = . ;
	} > DTCMRAM

	_estack = ORIGIN(DTCMRAM) + LENGTH(DTCMRAM);

	/* Remove information from the standard libraries */
	/DISCARD/ :
	{
		libc.a ( * )
		libm.a ( * )
		libgcc.a ( * )
	}
}

