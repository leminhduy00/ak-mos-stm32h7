#ifndef __TASK_LIST_H__
#define __TASK_LIST_H__

#include "os_task.h"

extern const task_t app_task_table[];
extern const task_polling_t app_task_polling_table[];

/*****************************************************************************/
/*  DECLARE: Internal Task ID
 *  Note: Task id MUST be increasing order.
 */
/*****************************************************************************/
enum
{
	// /* SYSTEM TASKS */

	// /* APP TASKS */
	// TASK_GUI_ID,
	// TASK_SCR_ID,	
	// TASK_TIMER_ID,
	// TASK_BTN_ID,
	// TASK_BUZZER_ID,
	// //TASK_OSC_ID,
	// /* EOT task ID (Size of task table)*/
	// TASK_EOT_ID,	/* SYSTEM TASKS */
	TASK_TIMER_TICK_ID,

	/* APP TASKS */
	AC_TASK_SYSTEM_ID,
	AC_TASK_SHELL_ID,
	AC_TASK_LIFE_ID,
	AC_TASK_DBG_ID,
	AC_TASK_DISPLAY_ID,

	/* EOT task ID */
	AK_TASK_EOT_ID,
};

/*****************************************************************************/
/*  DECLARE: Task function
 */
/*****************************************************************************/
/* APP TASKS */
extern void task_gui(void *p_arg);
extern void task_scr(void *p_arg);
extern void task_btn(void *p_arg);
extern void task_buzzer(void *p_arg);
extern void task_timer(void *p_arg);
extern void task_osc(void *p_arg);

#endif //__TASK_LIST_H__
