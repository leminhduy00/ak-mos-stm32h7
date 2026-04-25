/*****************************************************************************/
/* Kernel Includes
 *****************************************************************************/
#include "fsm.h"
#include "message.h"
#include "port.h"
#include "timer.h"

/*****************************************************************************/
/* Application Includes
 *****************************************************************************/
#include "app.h"
#include "app_dbg.h"

#include "task_display.h"
#include "task_list.h"

scr_mng_t scr_mng_app;

void task_display(ak_msg_t* msg) {
	scr_mng_dispatch(msg);
}
