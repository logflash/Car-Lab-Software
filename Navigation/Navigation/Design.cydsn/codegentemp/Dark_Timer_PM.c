/*******************************************************************************
* File Name: Dark_Timer_PM.c
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

#include "Dark_Timer.h"

static Dark_Timer_backupStruct Dark_Timer_backup;


/*******************************************************************************
* Function Name: Dark_Timer_SaveConfig
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
*  Dark_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Dark_Timer_SaveConfig(void) 
{
    #if (!Dark_Timer_UsingFixedFunction)
        Dark_Timer_backup.TimerUdb = Dark_Timer_ReadCounter();
        Dark_Timer_backup.InterruptMaskValue = Dark_Timer_STATUS_MASK;
        #if (Dark_Timer_UsingHWCaptureCounter)
            Dark_Timer_backup.TimerCaptureCounter = Dark_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Dark_Timer_UDB_CONTROL_REG_REMOVED)
            Dark_Timer_backup.TimerControlRegister = Dark_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Dark_Timer_RestoreConfig
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
*  Dark_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Dark_Timer_RestoreConfig(void) 
{   
    #if (!Dark_Timer_UsingFixedFunction)

        Dark_Timer_WriteCounter(Dark_Timer_backup.TimerUdb);
        Dark_Timer_STATUS_MASK =Dark_Timer_backup.InterruptMaskValue;
        #if (Dark_Timer_UsingHWCaptureCounter)
            Dark_Timer_SetCaptureCount(Dark_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Dark_Timer_UDB_CONTROL_REG_REMOVED)
            Dark_Timer_WriteControlRegister(Dark_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Dark_Timer_Sleep
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
*  Dark_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Dark_Timer_Sleep(void) 
{
    #if(!Dark_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Dark_Timer_CTRL_ENABLE == (Dark_Timer_CONTROL & Dark_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Dark_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Dark_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Dark_Timer_Stop();
    Dark_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: Dark_Timer_Wakeup
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
*  Dark_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Dark_Timer_Wakeup(void) 
{
    Dark_Timer_RestoreConfig();
    #if(!Dark_Timer_UDB_CONTROL_REG_REMOVED)
        if(Dark_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Dark_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
