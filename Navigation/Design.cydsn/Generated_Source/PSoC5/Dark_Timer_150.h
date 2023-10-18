/*******************************************************************************
* File Name: Dark_Timer_150.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_Dark_Timer_150_H)
#define CY_TIMER_Dark_Timer_150_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Dark_Timer_150_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define Dark_Timer_150_Resolution                 32u
#define Dark_Timer_150_UsingFixedFunction         0u
#define Dark_Timer_150_UsingHWCaptureCounter      0u
#define Dark_Timer_150_SoftwareCaptureMode        0u
#define Dark_Timer_150_SoftwareTriggerMode        0u
#define Dark_Timer_150_UsingHWEnable              0u
#define Dark_Timer_150_EnableTriggerMode          0u
#define Dark_Timer_150_InterruptOnCaptureCount    1u
#define Dark_Timer_150_RunModeUsed                0u
#define Dark_Timer_150_ControlRegRemoved          0u

#if defined(Dark_Timer_150_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define Dark_Timer_150_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (Dark_Timer_150_UsingFixedFunction)
    #define Dark_Timer_150_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define Dark_Timer_150_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End Dark_Timer_150_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!Dark_Timer_150_UsingFixedFunction)

        uint32 TimerUdb;
        uint8 InterruptMaskValue;
        #if (Dark_Timer_150_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!Dark_Timer_150_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}Dark_Timer_150_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    Dark_Timer_150_Start(void) ;
void    Dark_Timer_150_Stop(void) ;

void    Dark_Timer_150_SetInterruptMode(uint8 interruptMode) ;
uint8   Dark_Timer_150_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define Dark_Timer_150_GetInterruptSource() Dark_Timer_150_ReadStatusRegister()

#if(!Dark_Timer_150_UDB_CONTROL_REG_REMOVED)
    uint8   Dark_Timer_150_ReadControlRegister(void) ;
    void    Dark_Timer_150_WriteControlRegister(uint8 control) ;
#endif /* (!Dark_Timer_150_UDB_CONTROL_REG_REMOVED) */

uint32  Dark_Timer_150_ReadPeriod(void) ;
void    Dark_Timer_150_WritePeriod(uint32 period) ;
uint32  Dark_Timer_150_ReadCounter(void) ;
void    Dark_Timer_150_WriteCounter(uint32 counter) ;
uint32  Dark_Timer_150_ReadCapture(void) ;
void    Dark_Timer_150_SoftwareCapture(void) ;

#if(!Dark_Timer_150_UsingFixedFunction) /* UDB Prototypes */
    #if (Dark_Timer_150_SoftwareCaptureMode)
        void    Dark_Timer_150_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!Dark_Timer_150_UsingFixedFunction) */

    #if (Dark_Timer_150_SoftwareTriggerMode)
        void    Dark_Timer_150_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (Dark_Timer_150_SoftwareTriggerMode) */

    #if (Dark_Timer_150_EnableTriggerMode)
        void    Dark_Timer_150_EnableTrigger(void) ;
        void    Dark_Timer_150_DisableTrigger(void) ;
    #endif /* (Dark_Timer_150_EnableTriggerMode) */


    #if(Dark_Timer_150_InterruptOnCaptureCount)
        void    Dark_Timer_150_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (Dark_Timer_150_InterruptOnCaptureCount) */

    #if (Dark_Timer_150_UsingHWCaptureCounter)
        void    Dark_Timer_150_SetCaptureCount(uint8 captureCount) ;
        uint8   Dark_Timer_150_ReadCaptureCount(void) ;
    #endif /* (Dark_Timer_150_UsingHWCaptureCounter) */

    void Dark_Timer_150_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void Dark_Timer_150_Init(void)          ;
void Dark_Timer_150_Enable(void)        ;
void Dark_Timer_150_SaveConfig(void)    ;
void Dark_Timer_150_RestoreConfig(void) ;
void Dark_Timer_150_Sleep(void)         ;
void Dark_Timer_150_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define Dark_Timer_150__B_TIMER__CM_NONE 0
#define Dark_Timer_150__B_TIMER__CM_RISINGEDGE 1
#define Dark_Timer_150__B_TIMER__CM_FALLINGEDGE 2
#define Dark_Timer_150__B_TIMER__CM_EITHEREDGE 3
#define Dark_Timer_150__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define Dark_Timer_150__B_TIMER__TM_NONE 0x00u
#define Dark_Timer_150__B_TIMER__TM_RISINGEDGE 0x04u
#define Dark_Timer_150__B_TIMER__TM_FALLINGEDGE 0x08u
#define Dark_Timer_150__B_TIMER__TM_EITHEREDGE 0x0Cu
#define Dark_Timer_150__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define Dark_Timer_150_INIT_PERIOD             4294967295u
#define Dark_Timer_150_INIT_CAPTURE_MODE       ((uint8)((uint8)2u << Dark_Timer_150_CTRL_CAP_MODE_SHIFT))
#define Dark_Timer_150_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << Dark_Timer_150_CTRL_TRIG_MODE_SHIFT))
#if (Dark_Timer_150_UsingFixedFunction)
    #define Dark_Timer_150_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << Dark_Timer_150_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)1 << Dark_Timer_150_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define Dark_Timer_150_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << Dark_Timer_150_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)1 << Dark_Timer_150_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << Dark_Timer_150_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (Dark_Timer_150_UsingFixedFunction) */
#define Dark_Timer_150_INIT_CAPTURE_COUNT      (2u)
#define Dark_Timer_150_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << Dark_Timer_150_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (Dark_Timer_150_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define Dark_Timer_150_STATUS         (*(reg8 *) Dark_Timer_150_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define Dark_Timer_150_STATUS_MASK    (*(reg8 *) Dark_Timer_150_TimerHW__SR0 )
    #define Dark_Timer_150_CONTROL        (*(reg8 *) Dark_Timer_150_TimerHW__CFG0)
    #define Dark_Timer_150_CONTROL2       (*(reg8 *) Dark_Timer_150_TimerHW__CFG1)
    #define Dark_Timer_150_CONTROL2_PTR   ( (reg8 *) Dark_Timer_150_TimerHW__CFG1)
    #define Dark_Timer_150_RT1            (*(reg8 *) Dark_Timer_150_TimerHW__RT1)
    #define Dark_Timer_150_RT1_PTR        ( (reg8 *) Dark_Timer_150_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define Dark_Timer_150_CONTROL3       (*(reg8 *) Dark_Timer_150_TimerHW__CFG2)
        #define Dark_Timer_150_CONTROL3_PTR   ( (reg8 *) Dark_Timer_150_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define Dark_Timer_150_GLOBAL_ENABLE  (*(reg8 *) Dark_Timer_150_TimerHW__PM_ACT_CFG)
    #define Dark_Timer_150_GLOBAL_STBY_ENABLE  (*(reg8 *) Dark_Timer_150_TimerHW__PM_STBY_CFG)

    #define Dark_Timer_150_CAPTURE_LSB         (* (reg16 *) Dark_Timer_150_TimerHW__CAP0 )
    #define Dark_Timer_150_CAPTURE_LSB_PTR       ((reg16 *) Dark_Timer_150_TimerHW__CAP0 )
    #define Dark_Timer_150_PERIOD_LSB          (* (reg16 *) Dark_Timer_150_TimerHW__PER0 )
    #define Dark_Timer_150_PERIOD_LSB_PTR        ((reg16 *) Dark_Timer_150_TimerHW__PER0 )
    #define Dark_Timer_150_COUNTER_LSB         (* (reg16 *) Dark_Timer_150_TimerHW__CNT_CMP0 )
    #define Dark_Timer_150_COUNTER_LSB_PTR       ((reg16 *) Dark_Timer_150_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define Dark_Timer_150_BLOCK_EN_MASK                     Dark_Timer_150_TimerHW__PM_ACT_MSK
    #define Dark_Timer_150_BLOCK_STBY_EN_MASK                Dark_Timer_150_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define Dark_Timer_150_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define Dark_Timer_150_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define Dark_Timer_150_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define Dark_Timer_150_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define Dark_Timer_150_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define Dark_Timer_150_CTRL_ENABLE                        ((uint8)((uint8)0x01u << Dark_Timer_150_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Dark_Timer_150_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define Dark_Timer_150_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << Dark_Timer_150_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define Dark_Timer_150_CTRL_MODE_SHIFT                 0x01u
        #define Dark_Timer_150_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << Dark_Timer_150_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define Dark_Timer_150_CTRL_RCOD_SHIFT        0x02u
        #define Dark_Timer_150_CTRL_ENBL_SHIFT        0x00u
        #define Dark_Timer_150_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define Dark_Timer_150_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << Dark_Timer_150_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define Dark_Timer_150_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << Dark_Timer_150_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define Dark_Timer_150_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << Dark_Timer_150_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define Dark_Timer_150_CTRL_RCOD       ((uint8)((uint8)0x03u << Dark_Timer_150_CTRL_RCOD_SHIFT))
        #define Dark_Timer_150_CTRL_ENBL       ((uint8)((uint8)0x80u << Dark_Timer_150_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define Dark_Timer_150_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define Dark_Timer_150_RT1_MASK                        ((uint8)((uint8)0x03u << Dark_Timer_150_RT1_SHIFT))
    #define Dark_Timer_150_SYNC                            ((uint8)((uint8)0x03u << Dark_Timer_150_RT1_SHIFT))
    #define Dark_Timer_150_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define Dark_Timer_150_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << Dark_Timer_150_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define Dark_Timer_150_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << Dark_Timer_150_SYNCDSI_SHIFT))

    #define Dark_Timer_150_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << Dark_Timer_150_CTRL_MODE_SHIFT))
    #define Dark_Timer_150_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << Dark_Timer_150_CTRL_MODE_SHIFT))
    #define Dark_Timer_150_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << Dark_Timer_150_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define Dark_Timer_150_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define Dark_Timer_150_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define Dark_Timer_150_STATUS_TC_INT_MASK_SHIFT        (Dark_Timer_150_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define Dark_Timer_150_STATUS_CAPTURE_INT_MASK_SHIFT   (Dark_Timer_150_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define Dark_Timer_150_STATUS_TC                       ((uint8)((uint8)0x01u << Dark_Timer_150_STATUS_TC_SHIFT))
    #define Dark_Timer_150_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << Dark_Timer_150_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define Dark_Timer_150_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << Dark_Timer_150_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define Dark_Timer_150_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << Dark_Timer_150_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define Dark_Timer_150_STATUS              (* (reg8 *) Dark_Timer_150_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define Dark_Timer_150_STATUS_MASK         (* (reg8 *) Dark_Timer_150_TimerUDB_rstSts_stsreg__MASK_REG)
    #define Dark_Timer_150_STATUS_AUX_CTRL     (* (reg8 *) Dark_Timer_150_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define Dark_Timer_150_CONTROL             (* (reg8 *) Dark_Timer_150_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(Dark_Timer_150_Resolution <= 8u) /* 8-bit Timer */
        #define Dark_Timer_150_CAPTURE_LSB         (* (reg8 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define Dark_Timer_150_CAPTURE_LSB_PTR       ((reg8 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define Dark_Timer_150_PERIOD_LSB          (* (reg8 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define Dark_Timer_150_PERIOD_LSB_PTR        ((reg8 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define Dark_Timer_150_COUNTER_LSB         (* (reg8 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define Dark_Timer_150_COUNTER_LSB_PTR       ((reg8 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__A0_REG )
    #elif(Dark_Timer_150_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define Dark_Timer_150_CAPTURE_LSB         (* (reg16 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define Dark_Timer_150_CAPTURE_LSB_PTR       ((reg16 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define Dark_Timer_150_PERIOD_LSB          (* (reg16 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define Dark_Timer_150_PERIOD_LSB_PTR        ((reg16 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define Dark_Timer_150_COUNTER_LSB         (* (reg16 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define Dark_Timer_150_COUNTER_LSB_PTR       ((reg16 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define Dark_Timer_150_CAPTURE_LSB         (* (reg16 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define Dark_Timer_150_CAPTURE_LSB_PTR       ((reg16 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define Dark_Timer_150_PERIOD_LSB          (* (reg16 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define Dark_Timer_150_PERIOD_LSB_PTR        ((reg16 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define Dark_Timer_150_COUNTER_LSB         (* (reg16 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
            #define Dark_Timer_150_COUNTER_LSB_PTR       ((reg16 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(Dark_Timer_150_Resolution <= 24u)/* 24-bit Timer */
        #define Dark_Timer_150_CAPTURE_LSB         (* (reg32 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define Dark_Timer_150_CAPTURE_LSB_PTR       ((reg32 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define Dark_Timer_150_PERIOD_LSB          (* (reg32 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define Dark_Timer_150_PERIOD_LSB_PTR        ((reg32 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define Dark_Timer_150_COUNTER_LSB         (* (reg32 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define Dark_Timer_150_COUNTER_LSB_PTR       ((reg32 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define Dark_Timer_150_CAPTURE_LSB         (* (reg32 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define Dark_Timer_150_CAPTURE_LSB_PTR       ((reg32 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define Dark_Timer_150_PERIOD_LSB          (* (reg32 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define Dark_Timer_150_PERIOD_LSB_PTR        ((reg32 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define Dark_Timer_150_COUNTER_LSB         (* (reg32 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define Dark_Timer_150_COUNTER_LSB_PTR       ((reg32 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define Dark_Timer_150_CAPTURE_LSB         (* (reg32 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define Dark_Timer_150_CAPTURE_LSB_PTR       ((reg32 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define Dark_Timer_150_PERIOD_LSB          (* (reg32 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define Dark_Timer_150_PERIOD_LSB_PTR        ((reg32 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define Dark_Timer_150_COUNTER_LSB         (* (reg32 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
            #define Dark_Timer_150_COUNTER_LSB_PTR       ((reg32 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define Dark_Timer_150_COUNTER_LSB_PTR_8BIT       ((reg8 *) Dark_Timer_150_TimerUDB_sT32_timerdp_u0__A0_REG )
    
    #if (Dark_Timer_150_UsingHWCaptureCounter)
        #define Dark_Timer_150_CAP_COUNT              (*(reg8 *) Dark_Timer_150_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define Dark_Timer_150_CAP_COUNT_PTR          ( (reg8 *) Dark_Timer_150_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define Dark_Timer_150_CAPTURE_COUNT_CTRL     (*(reg8 *) Dark_Timer_150_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define Dark_Timer_150_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) Dark_Timer_150_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (Dark_Timer_150_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define Dark_Timer_150_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define Dark_Timer_150_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define Dark_Timer_150_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define Dark_Timer_150_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define Dark_Timer_150_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define Dark_Timer_150_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << Dark_Timer_150_CTRL_INTCNT_SHIFT))
    #define Dark_Timer_150_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << Dark_Timer_150_CTRL_TRIG_MODE_SHIFT))
    #define Dark_Timer_150_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << Dark_Timer_150_CTRL_TRIG_EN_SHIFT))
    #define Dark_Timer_150_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << Dark_Timer_150_CTRL_CAP_MODE_SHIFT))
    #define Dark_Timer_150_CTRL_ENABLE                    ((uint8)((uint8)0x01u << Dark_Timer_150_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define Dark_Timer_150_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define Dark_Timer_150_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define Dark_Timer_150_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define Dark_Timer_150_STATUS_TC_INT_MASK_SHIFT       Dark_Timer_150_STATUS_TC_SHIFT
    #define Dark_Timer_150_STATUS_CAPTURE_INT_MASK_SHIFT  Dark_Timer_150_STATUS_CAPTURE_SHIFT
    #define Dark_Timer_150_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define Dark_Timer_150_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define Dark_Timer_150_STATUS_FIFOFULL_INT_MASK_SHIFT Dark_Timer_150_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define Dark_Timer_150_STATUS_TC                      ((uint8)((uint8)0x01u << Dark_Timer_150_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define Dark_Timer_150_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << Dark_Timer_150_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define Dark_Timer_150_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << Dark_Timer_150_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define Dark_Timer_150_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << Dark_Timer_150_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define Dark_Timer_150_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << Dark_Timer_150_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define Dark_Timer_150_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << Dark_Timer_150_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define Dark_Timer_150_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << Dark_Timer_150_STATUS_FIFOFULL_SHIFT))

    #define Dark_Timer_150_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define Dark_Timer_150_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define Dark_Timer_150_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define Dark_Timer_150_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define Dark_Timer_150_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define Dark_Timer_150_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_Dark_Timer_150_H */


/* [] END OF FILE */
