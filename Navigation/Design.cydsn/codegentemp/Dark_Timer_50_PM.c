/*******************************************************************************
* File Name: Dark_Timer_50_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Dark_Timer_50.h"

static Dark_Timer_50_backupStruct Dark_Timer_50_backup;


/*******************************************************************************
* Function Name: Dark_Timer_50_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Dark_Timer_50_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Dark_Timer_50_SaveConfig(void) 
{
    #if (!Dark_Timer_50_UsingFixedFunction)
        Dark_Timer_50_backup.TimerUdb = Dark_Timer_50_ReadCounter();
        Dark_Timer_50_backup.InterruptMaskValue = Dark_Timer_50_STATUS_MASK;
        #if (Dark_Timer_50_UsingHWCaptureCounter)
            Dark_Timer_50_backup.TimerCaptureCounter = Dark_Timer_50_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Dark_Timer_50_UDB_CONTROL_REG_REMOVED)
            Dark_Timer_50_backup.TimerControlRegister = Dark_Timer_50_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Dark_Timer_50_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Dark_Timer_50_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Dark_Timer_50_RestoreConfig(void) 
{   
    #if (!Dark_Timer_50_UsingFixedFunction)

        Dark_Timer_50_WriteCounter(Dark_Timer_50_backup.TimerUdb);
        Dark_Timer_50_STATUS_MASK =Dark_Timer_50_backup.InterruptMaskValue;
        #if (Dark_Timer_50_UsingHWCaptureCounter)
            Dark_Timer_50_SetCaptureCount(Dark_Timer_50_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Dark_Timer_50_UDB_CONTROL_REG_REMOVED)
            Dark_Timer_50_WriteControlRegister(Dark_Timer_50_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Dark_Timer_50_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Dark_Timer_50_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Dark_Timer_50_Sleep(void) 
{
    #if(!Dark_Timer_50_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Dark_Timer_50_CTRL_ENABLE == (Dark_Timer_50_CONTROL & Dark_Timer_50_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Dark_Timer_50_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Dark_Timer_50_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Dark_Timer_50_Stop();
    Dark_Timer_50_SaveConfig();
}


/*******************************************************************************
* Function Name: Dark_Timer_50_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Dark_Timer_50_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Dark_Timer_50_Wakeup(void) 
{
    Dark_Timer_50_RestoreConfig();
    #if(!Dark_Timer_50_UDB_CONTROL_REG_REMOVED)
        if(Dark_Timer_50_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Dark_Timer_50_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
