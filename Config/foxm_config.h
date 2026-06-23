#ifndef FOXM_CONFIG_H
#define FOXM_CONFIG_H

/* ============================================
 * FOX.M OS - Global Configuration
 * Version: 0.1
 * Target: STM32F4 (Cortex-M4)
 * ============================================ */

/* OS Info */
#define FOXM_OS_NAME       "FOX.M OS"
#define FOXM_OS_VERSION    "0.1.0"

/* Hardware Target */
#define FOXM_HW_STM32F4    1

/* Feature Flags */
#define FOXM_FEATURE_IR    1
#define FOXM_FEATURE_BT    1
#define FOXM_FEATURE_WIFI  1

/* FreeRTOS Task Priorities */
#define PRIORITY_EVENT     5
#define PRIORITY_IR        4
#define PRIORITY_BT        4
#define PRIORITY_WIFI      3
#define PRIORITY_UI        3
#define PRIORITY_POWER     1

/* FreeRTOS Stack Sizes */
#define STACK_EVENT        256
#define STACK_IR           256
#define STACK_BT           512
#define STACK_WIFI         512
#define STACK_UI           1024
#define STACK_POWER        128

#endif /* FOXM_CONFIG_H */