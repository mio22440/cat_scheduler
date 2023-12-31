/**
 * @file cat_task.h
 * @author mio (648137125@qq.com)
 * @brief 任务控制的用户接口
 * @version 0.1
 * @date 2022-07-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CAT_TASK_H
#define CAT_TASK_H

#include "cat_list.h"

/** 宏定义 */
/* 任务状态 */
#define CATOS_TASK_STATE_RDY        0               //目前不具备判断功能
#define CATOS_TASK_STATE_DESTROYED  (1 << 1)        //删除
#define CATOS_TASK_STATE_DELAYED    (1 << 2)        //延时
#define CATOS_TASK_STATE_SUSPEND    (1 << 3)        //挂起
#define CATOS_TASK_EVENT_MASK       (0xff << 16)    //高16位用作事件相关的状态

/* 调度策略 */
#define SCHED_STRATEGY_STATIC_PRIO  0               /**< 固定优先级调度 */

/** 数据结构定义 */
/* 任务控制块 */
struct _cat_task_t
{
    void               *sp;                             /**< 栈顶(堆栈指针)*/
    cat_uint8_t        *task_name;                      /**< 任务名称*/
    cat_uint8_t         sched_strategy;                 /**< 调度策略 */


    void               *entry;                          /**< 入口函数 */
    void               *arg;                            /**< 入口函数的参数 */
    void               *stack_start_addr;               /**< 堆栈起始地址*/
    cat_uint32_t        stack_size;                     /**< 堆栈大小*/

    struct _cat_node_t  link_node;                      /**< 任务表中的链表节点，也用于delay链表*/
    cat_uint32_t        delay;                          /**< 延时剩余tick数*/

    cat_uint32_t        state;                          /**< 当前状态*/

    cat_uint8_t         prio;                           /**< priority of task*/
    cat_uint32_t        slice;                          /**< 时间片(剩余时间)*/
    cat_uint32_t        suspend_cnt;                    /**< 被挂起的次数*/

    cat_uint32_t        sched_times;                    /**< 调度次数*/

    struct _cat_node_t *manage_node;                    /**< 用于管理的链表节点 */
};


/** 函数声明 */

/**
 * @brief                       初始化任务，仅根据参数初始化数据结构，并不进行策略特定的操作(如挂就绪队列)
 * 
 * 
 * @param task                  任务控制块指针
 * @param entry                 入口函数指针
 * @param arg                   入口函数的参数
 * @param prio                  任务优先级
 * @param stack_start_addr      堆栈起始地址
 * @param stack_size            堆栈大小
 */
void cat_task_init(
    const cat_uint8_t *task_name,
    struct _cat_task_t *task, 
    void (*entry)(void *), 
    void *arg, 
    cat_uint8_t prio, 
    void *stack_start_addr,
    cat_uint32_t stack_size,
    cat_uint8_t sched_strategy
);

#endif
