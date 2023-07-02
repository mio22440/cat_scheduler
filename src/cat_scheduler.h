/**
 * @file cat_scheduler.h
 * @author 文佳源 (648137125@qq.com)
 * @brief 调度器头文件
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
#ifndef CAT_SCHEDULER_H
#define CAT_SCHEDULER_H

#include "catos_types.h"
#include "catos_config.h"

#include "cat_task.h"

#include <stdio.h>
#define CAT_SYS_PRINTF(_fmt, ...) \
        printf((const char *)_fmt, ##__VA_ARGS__)

/* 调度策略 */
#define SCHED_STRATEGY_STATIC_PRIO  0               /**< 固定优先级调度 */

typedef void (*cat_scheduler_init_func)(void);
typedef void (*cat_scheduler_task_create_static_func)(void *task_config);
typedef void (*cat_scheduler_deal_in_tick_func)(void);
typedef cat_uint8_t (*cat_scheduler_has_task_rdy_func)(void);
typedef void (*cat_scheduler_sched_func)(void);

typedef void (*cat_scheduler_task_rdy_func)(struct _cat_task_t *task);
typedef void (*cat_scheduler_task_unrdy_func)(struct _cat_task_t *task);
typedef void (*cat_scheduler_task_delay_func)(cat_uint32_t tick);
typedef void (*cat_scheduler_task_delay_wakeup_func)(struct _cat_task_t *task);
typedef void (*cat_scheduler_task_suspend_func)(struct _cat_task_t *task);
typedef void (*cat_scheduler_task_suspend_wakeup_func)(struct _cat_task_t *task);

typedef struct _cat_scheduler_t cat_scheduler_t;
struct _cat_scheduler_t
{
    cat_uint8_t                                 strategy;               /* 调度策略 */
    cat_uint8_t                                 scheduler_prio;         /* 调度器优先级 */
    cat_uint8_t                                 reserve2;               /* 保留 */
    cat_uint8_t                                 reserve3;               /* 保留 */

    cat_scheduler_init_func                     scheduler_init;         /* 初始化调度器 */
    cat_scheduler_task_create_static_func       task_create_static;     /* 静态创建任务(预分配资源) */
    cat_scheduler_deal_in_tick_func             deal_in_tick;           /* 每个tick调用一次 */
    cat_scheduler_has_task_rdy_func             has_task_rdy;           /* 有任务就绪可以调度 */
    cat_scheduler_sched_func                    schedule;               /* 进行调度 */

    cat_scheduler_task_rdy_func                 task_rdy;               /* 将任务放入就绪队列 */
    cat_scheduler_task_unrdy_func               task_unrdy;             /* 将任务从就绪队列取出 */
    cat_scheduler_task_delay_func               task_delay;             /* 当前任务等待tick个时钟 */
    cat_scheduler_task_delay_wakeup_func        task_delay_wakeup;      /* 从等待唤醒 */
    cat_scheduler_task_suspend_func             task_suspend;           /* 挂起任务 */
    cat_scheduler_task_suspend_wakeup_func      task_suspend_wakeup;    /* 从挂起唤醒 */

    void                                       *private_data;           /* 调度器私有数据 */
};

/**
 * @brief 注册调度器
 * 
 * @param  scheduler        调度器结构体指针
 */
void cat_scheduler_register(cat_scheduler_t *scheduler);
/**
 * @brief 根据策略获取调度器
 * 
 * @param  strategy         调度策略
 * @return cat_scheduler_t* 调度器结构体指针
 */
cat_scheduler_t *cat_scheduler_get_by_strategy(cat_uint8_t strategy);

/**
 * @brief 初始化所有调度器
 * 
 */
void cat_scheduler_init_all_scheduler(void);
/**
 * @brief 静态创建任务(提前分配空间和资源)
 * 
 * @param  strategy         策略
 * @param  task_config      任务创建参数
 */
void cat_scheduler_create_task_static(cat_uint8_t strategy, void *task_config);
/**
 * @brief 每个 tick 都会调用一次，调用所有调度器的 deal_in_tick 函数
 * 
 */
void cat_scheduler_deal_in_tick(void);

/**
 * @brief 进行一次调度
 * 
 */
void cat_scheduler_schedule(void);

/**
 * @brief 将任务放入就绪队列
 * 
 * @param  task             任务结构体指针
 */
void cat_scheduler_task_rdy(struct _cat_task_t *task);
/**
 * @brief 将任务从就绪队列取出
 * 
 * @param  task             任务结构体指针
 */
void cat_scheduler_task_unrdy(struct _cat_task_t *task);
/**
 * @brief 将当前任务放入等待队列等待 tick 个时钟周期
 * 
 * @param  tick             要等待的 tick 数
 */
void cat_scheduler_task_delay(cat_uint32_t tick);
/**
 * @brief 将任务从等待队列取出并就绪
 * 
 * @param  task             任务结构体指针
 */
void cat_scheduler_task_delay_wakeup(struct _cat_task_t *task);
/**
 * @brief 挂起任务
 * 
 * @param  task             任务结构体指针
 */
void cat_scheduler_task_suspend(struct _cat_task_t *task);
/**
 * @brief 将任务从挂起唤醒
 * 
 * @param  task             任务结构体指针
 */
void cat_scheduler_task_suspend_wakeup(struct _cat_task_t *task);



#endif