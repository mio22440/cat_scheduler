/**
 * @file cat_scheduler.c
 * @author 文佳源 (648137125@qq.com)
 * @brief 调度器源文件
 * @version 0.1
 * @date 2023-07-01
 * 
 * Copyright (c) 2023
 * 
 * @par 修订历史
 * <table>
 * <tr><th>版本 <th>作者 <th>日期 <th>修改内容
 * <tr><td>v1.0 <td>文佳源 <td>2023-07-01 <td>创建
 * </table>
 */
#include "cat_scheduler.h"


void cat_scheduler_register(cat_scheduler_t *scheduler)
{
    (void)scheduler;
    printf("%s\n", __func__);
}

cat_scheduler_t *cat_scheduler_get_by_strategy(cat_uint8_t strategy)
{
    (void)strategy;

    printf("%s\n", __func__);

    return NULL;
}


void cat_scheduler_init_all_scheduler(void)
{
    printf("%s\n", __func__);
}

void cat_scheduler_create_task_static(cat_uint8_t strategy, void *task_config)
{
    (void)strategy;
    (void)task_config;

    printf("%s\n", __func__);
}

void cat_scheduler_deal_in_tick(void)
{
    printf("%s\n", __func__);
}


void cat_scheduler_schedule(void)
{
    printf("%s\n", __func__);
}


void cat_scheduler_task_rdy(struct _cat_task_t *task)
{
    (void)task;
    
    printf("%s\n", __func__);
}

void cat_scheduler_task_unrdy(struct _cat_task_t *task)
{
    (void)task;

    printf("%s\n", __func__);
}

void cat_scheduler_task_delay(cat_uint32_t tick)
{
    (void)tick;

    printf("%s\n", __func__);
}

void cat_scheduler_task_delay_wakeup(struct _cat_task_t *task)
{
    (void)task;

    printf("%s\n", __func__);
}

void cat_scheduler_task_suspend(struct _cat_task_t *task)
{
    (void)task;

    printf("%s\n", __func__);
}

void cat_scheduler_task_suspend_wakeup(struct _cat_task_t *task)
{
    (void)task;
    
    printf("%s\n", __func__);
}