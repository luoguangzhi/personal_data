/*
*********************************************************************************************************
*                                            EXAMPLE CODE
*
*               This file is provided as an example on how to use Micrium products.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only. This file can be modified as
*               required to meet the end-product requirements.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can find our product's user manual, API reference, release notes and
*               more information at https://doc.micrium.com.
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                             OS TICK BSP
*
* Filename : bsp_os.c
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu_core.h>
#include  <os.h>
#include  <lib_def.h>
#include  <stm32f7xx_hal.h>

#include  "bsp_os.h"
#include  "bsp_clk.h"
#include  "bsp_int.h"


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#ifndef  OS_CFG_DYN_TICK_EN                                     /* Dynamic tick only available for uCOS-III             */
#define  OS_CFG_DYN_TICK_EN          DEF_DISABLED
#endif

#if (OS_CFG_DYN_TICK_EN == DEF_ENABLED)
#define  TIMER_COUNT_HZ             (10000u)                    /* Timer counts per second.                             */
#define  TIMER_TO_OSTICK(count)     (((CPU_INT64U)(count)  * OS_CFG_TICK_RATE_HZ) /      TIMER_COUNT_HZ)
#define  OSTICK_TO_TIMER(ostick)    (((CPU_INT64U)(ostick) * TIMER_COUNT_HZ)      / OS_CFG_TICK_RATE_HZ)

                                                                /* The max timer count should end on a 1 tick boundary. */
#define  TIMER_COUNT_MAX            (DEF_INT_32U_MAX_VAL - (DEF_INT_32U_MAX_VAL % OSTICK_TO_TIMER(1u)))
#endif


/*
*********************************************************************************************************
*                                           LOCAL VARIABLES
*
* Note(s) : (1) BSP_OS_UnTick is used to keep track of any ticks that happen before the OS is ready to
*               awake some tasks.
*********************************************************************************************************
*/

#if (OS_CFG_DYN_TICK_EN == DEF_ENABLED)
static  OS_TICK  TickDelta = 0u;                                /* Stored in OS Tick units.                             */

TIM_HandleTypeDef  TimHandle;
#endif


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

#if (OS_CFG_DYN_TICK_EN == DEF_ENABLED)
static  void  BSP_OS_DynamicTickInit(void);
static  void  BSP_TIM5_ISRHandler   (void);
#endif


/*
*********************************************************************************************************
*********************************************************************************************************
*                                           GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          BSP_OS_TickInit()
*
* Description : Initializes the tick interrupt for the OS.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : (1) Must be called prior to OSStart() in main().
*
*               (2) This function ensures that the tick interrupt is disabled until BSP_OS_TickEn() is
*                   called in the startup task.
*********************************************************************************************************
*/

void  BSP_OS_TickInit (void)
{
#if (OS_CFG_DYN_TICK_EN != DEF_ENABLED)
    CPU_INT32U  cpu_freq;
    CPU_SR_ALLOC();


    cpu_freq = BSP_ClkFreqGet(CLK_ID_SYSCLK);                   /* Determine SysTick reference freq.                    */

    CPU_CRITICAL_ENTER();
    OS_CPU_SysTickInitFreq(cpu_freq);                           /* Init uC/OS periodic time src (SysTick).              */
    BSP_OS_TickDisable();                                       /* See Note #2.                                         */
    CPU_CRITICAL_EXIT();
#else
    BSP_OS_DynamicTickInit();                                   /* Initialize dynamic tick.                             */
#endif
}


/*
*********************************************************************************************************
*                                         BSP_OS_TickEnable()
*
* Description : Enable the OS tick interrupt.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none
*********************************************************************************************************
*/

void  BSP_OS_TickEnable (void)
{
#if (OS_CFG_DYN_TICK_EN != DEF_ENABLED)
    CPU_REG_SYST_CSR |= (CPU_REG_SYST_CSR_TICKINT |             /* Enables SysTick exception request                    */
                         CPU_REG_SYST_CSR_ENABLE);              /* Enables SysTick counter                              */
#else
    BSP_IntEnable(INT_ID_TIM5);                                 /* Enable Timer interrupt.                              */
    HAL_TIM_Base_Start(&TimHandle);                             /* Start the Timer count generation.                    */
#endif
}


/*
*********************************************************************************************************
*                                        BSP_OS_TickDisable()
*
* Description : Disable the OS tick interrupt.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none
*********************************************************************************************************
*/

void  BSP_OS_TickDisable (void)
{
#if (OS_CFG_DYN_TICK_EN != DEF_ENABLED)
    CPU_REG_SYST_CSR &= ~(CPU_REG_SYST_CSR_TICKINT |            /* Disables SysTick exception request                   */
                          CPU_REG_SYST_CSR_ENABLE);             /* Disables SysTick counter                             */
#else
    HAL_TIM_Base_Stop(&TimHandle);                              /* Stop the Timer count generation.                     */
    BSP_IntDisable(INT_ID_TIM5);                                /* Disable Timer interrupt.                             */
#endif
}


/*
*********************************************************************************************************
*                                            HAL_InitTick()
*
* Description : This function has been overwritten from the STM32Cube HAL libraries because Micrium's RTOS
*               has its own Systick initialization and because it is recomended to initialize the tick
*               after multi-tasking has started.
*
* Argument(s) : TickPriority          Tick interrupt priority.
*
* Return(s)   : HAL_OK.
*
* Caller(s)   : HAL_InitTick ()) is called automatically at the beginning of the program after reset by
*               HAL_Init() or at any time when clock is configured, by HAL_RCC_ClockConfig().
*
* Note(s)     : none.
*********************************************************************************************************
*/

HAL_StatusTypeDef  HAL_InitTick (uint32_t TickPriority)
{
    (void)TickPriority;

    HAL_NVIC_SetPriorityGrouping(0);

    return (HAL_OK);
}


/*
*********************************************************************************************************
*                                            HAL_GetTick()
*
* Description : This function has been overwritten from the STM32Cube HAL libraries because Micrium's OS's
*               has their own Tick counter values.
*
* Argument(s) : None.
*
* Return(s)   : Tick current value.
*
* Caller(s)   : STM32Cube HAL driver files.
*
* Note(s)     : (1) Please ensure that the Tick Task has a higher priority than the App Start Task.
*********************************************************************************************************
*/

uint32_t  HAL_GetTick (void)
{
    CPU_INT32U  os_tick_ctr;
#if (OS_VERSION >= 30000u)
    OS_ERR      os_err;
#endif

#if (OS_VERSION >= 30000u)
    os_tick_ctr = OSTimeGet(&os_err);
#else
    os_tick_ctr = OSTimeGet();
#endif

    return os_tick_ctr;
}


/*
*********************************************************************************************************
*********************************************************************************************************
**                                      uC/OS-III DYNAMIC TICK
*********************************************************************************************************
*********************************************************************************************************
*/

#if (OS_CFG_DYN_TICK_EN == DEF_ENABLED)

/*
*********************************************************************************************************
*                                      BSP_OS_DynamicTickInit()
*
* Description : Initialize timer to use for dynamic tick.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : (1) If the APB prescaler is configured to a division factor of 1, the timer clock frequencies
*                   (TIMxCLK) are set to PCLKx. Otherwise, the timer clock frequencies are twice the frequency
*                   of the APB domain to which the timers are connected: TIMxCLK = 2 * PCLKx
*
*                       Prescaler = (TIMxCLK / TIM counter clock) - 1
*********************************************************************************************************
*/

static  void  BSP_OS_DynamicTickInit (void)
{
    HAL_StatusTypeDef   hal_stat;
    RCC_ClkInitTypeDef  rcc_clk_cfg;
    CPU_INT32U          per_clk;


    __HAL_RCC_TIM5_CLK_ENABLE();                                /* Enable TIMER5 interface clock.                       */

    DBGMCU->APB1FZ |= DBGMCU_APB1_FZ_DBG_TIM5_STOP;             /* Make sure TIMER5 is stop when core is halted.        */
    per_clk         = BSP_ClkFreqGet(CLK_ID_PCLK1);             /* Get TIMER5 clock frequency.                          */

    HAL_RCC_GetClockConfig(&rcc_clk_cfg, 0);                    /* Obtain current clock configuration                   */

                                                                /* -------- INITIALIZE TIMER BASE CONFIGURATION ------- */
    if (rcc_clk_cfg.APB1CLKDivider == RCC_HCLK_DIV1) {          /* Configure the timer prescaler. See Note (1).         */
        TimHandle.Init.Prescaler = ((per_clk)      / TIMER_COUNT_HZ) - 1u ;
    } else {
        TimHandle.Init.Prescaler = ((per_clk * 2u) / TIMER_COUNT_HZ) - 1u ;
    }
    TimHandle.Init.Period        = TIMER_COUNT_MAX;             /* Let timer run freely until the kernel sets a delay.  */
    TimHandle.Init.ClockDivision = 0u;
    TimHandle.Init.CounterMode   = TIM_COUNTERMODE_UP;
    TimHandle.Instance           = TIM5;
    hal_stat = HAL_TIM_Base_Init(&TimHandle);
    if (hal_stat != HAL_OK) {
        while(1u);                                              /* STOP if error                                        */
    }

    HAL_TIM_Base_Start_IT(&TimHandle);                          /* Start the timer interrupt mode generation.           */
    __HAL_TIM_SET_COUNTER(&TimHandle, 0u);                      /* Reset the timer counter value                        */

                                                                /* ----------- SET INTERRUPT REQUEST HANDLER ---------- */
    BSP_IntVectSet(INT_ID_TIM5,
                   CPU_CFG_KA_IPL_BOUNDARY,                     /* Make sure we are within the Kernel Aware boundary.   */
                   CPU_INT_KA,
                   BSP_TIM5_ISRHandler);
}


/*
*********************************************************************************************************
*                                            OS_DynTickGet()
*
* Description : Get the number of ticks which have elapsed since the last delta was set.
*
* Argument(s) : none.
*
* Return(s)   : An unsigned integer between 0 and TickDelta, inclusive.
*
* Note(s)     : 1) This function is an INTERNAL uC/OS-III function & MUST NOT be called by the
*                  application.
*
*               2) This function is called with kernel-aware interrupts disabled.
*********************************************************************************************************
*/

OS_TICK  OS_DynTickGet (void)
{
    CPU_INT32U  tmrcnt;


    tmrcnt = __HAL_TIM_GET_COUNTER(&TimHandle);                 /* Get the timer counter value.                         */

    if (__HAL_TIM_GET_FLAG(&TimHandle, TIM_FLAG_UPDATE)) {      /* Counter value already overflowed.                    */
        return (TickDelta);
    }

    tmrcnt = TIMER_TO_OSTICK(tmrcnt);                           /* Otherwise, the value we read is valid.               */

    return ((OS_TICK)tmrcnt);
}


/*
*********************************************************************************************************
*                                            OS_DynTickSet()
*
* Description : Sets the number of ticks that the kernel wants to expire before the next interrupt.
*
* Argument(s) : ticks       number of ticks the kernel wants to delay.
*                           0 indicates an indefinite delay.
*
* Return(s)   : The actual number of ticks which will elapse before the next interrupt.
*               (See Note #3).
*
* Note(s)     : 1) This function is an INTERNAL uC/OS-III function & MUST NOT be called by the
*                  application.
*
*               2) This function is called with kernel-aware interrupts disabled.
*
*               3) It is possible for the kernel to specify a delay that is too large for our
*                  hardware timer, or an indefinite delay. In these cases, we should program the timer
*                  to count the maximum number of ticks possible. The value we return should then
*                  be the timer maximum converted into units of OS_TICK.
*********************************************************************************************************
*/

OS_TICK  OS_DynTickSet (OS_TICK  ticks)
{
    CPU_INT32U  tmrcnt;


    tmrcnt = OSTICK_TO_TIMER(ticks);

    if ((tmrcnt >= TIMER_COUNT_MAX) ||                          /* If the delay exceeds our timer's capacity,       ... */
        (tmrcnt ==              0u)) {                          /* ... or the kernel wants an indefinite delay.         */
        tmrcnt = TIMER_COUNT_MAX;                               /* Count as many ticks as we are able.                  */
    }

    TickDelta  = TIMER_TO_OSTICK(tmrcnt);                       /* Convert the timer count into OS_TICK units.          */

    HAL_TIM_Base_Stop       (&TimHandle);                       /* Stop the Timer count generation.                     */
    __HAL_TIM_CLEAR_IT      (&TimHandle, TIM_IT_UPDATE);        /* Clear the last delay's interrupt.                    */
    __HAL_TIM_SET_AUTORELOAD(&TimHandle,        tmrcnt);        /* Re-configure auto-reload register and period.        */
    __HAL_TIM_SET_COUNTER   (&TimHandle,            0u);        /* Reset the timer counter value                        */
    HAL_TIM_Base_Start      (&TimHandle);                       /* Start the Timer count generation.                    */

    return (TickDelta);                                         /* Return the number ticks that will elapse before  ... */
                                                                /* ... the next interrupt.                              */
}


/*
*********************************************************************************************************
*                                        BSP_TIM5_ISRHandler()
*
* Description : BSP-level ISR handler for TIM5.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_TIM5_ISRHandler (void)
{
    CPU_SR_ALLOC();


    CPU_CRITICAL_ENTER();
    OSIntEnter();
    CPU_CRITICAL_EXIT();

    OSTimeDynTick(TickDelta);                                   /* Next delta will be set by the kernel.                */

    OSIntExit();
}


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of uC/OS-III Dynamic Tick module.                */
