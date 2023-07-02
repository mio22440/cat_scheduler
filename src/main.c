#include <stdio.h>
#include "cat_scheduler.h"

int main(void)
{
    printf("sizeof(scheduler_t)=%d\r\n", sizeof(struct _cat_scheduler_t));

    cat_scheduler_register(NULL);
    
    cat_scheduler_get_by_strategy(0);

    cat_scheduler_init_all_scheduler();

    cat_scheduler_create_task_static(0, NULL);

    cat_scheduler_deal_in_tick();

    cat_scheduler_schedule();

    cat_scheduler_task_rdy(NULL);

    cat_scheduler_task_unrdy(NULL);

    cat_scheduler_task_delay(0);

    cat_scheduler_task_delay_wakeup(NULL);

    cat_scheduler_task_suspend(NULL);

    cat_scheduler_task_suspend_wakeup(NULL);

    return 0;
}