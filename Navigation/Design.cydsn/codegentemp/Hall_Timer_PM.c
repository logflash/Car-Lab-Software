/*******************************************************************************
* File Name: Hall_Timer_PM.c
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

#include "Hall_Timer.h"

static Hall_Timer_backupStruct Hall_Timer_backup;


/*******************************************************************************
* Function Name: Hall_Timer_SaveConfig
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
*  Hall_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Hall_Timer_SaveConfig(void) 
{
    #if (!Hall_Timer_UsingFixedFunction)
        Hall_Timer_backup.TimerUdb = Hall_Timer_ReadCounter();
        Hall_Timer_backup.InterruptMaskValue = Hall_Timer_STATUS_MASK;
        #if (Hall_Timer_UsingHWCaptureCounter)
            Hall_Timer_backup.TimerCaptureCounter = Hall_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Hall_Timer_UDB_CONTROL_REG_REMOVED)
            Hall_Timer_backup.TimerControlRegister = Hall_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Hall_Timer_RestoreConfig
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
*  Hall_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Hall_Timer_RestoreConfig(void) 
{   
    #if (!Hall_Timer_UsingFixedFunction)

        Hall_Timer_WriteCounter(Hall_Timer_backup.TimerUdb);
        Hall_Timer_STATUS_MASK =Hall_Timer_backup.InterruptMaskValue;
        #if (Hall_Timer_UsingHWCaptureCounter)
            Hall_Timer_SetCaptureCount(Hall_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Hall_Timer_UDB_CONTROL_REG_REMOVED)
            Hall_Timer_WriteControlRegister(Hall_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Hall_Timer_Sleep
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
*  Hall_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Hall_Timer_Sleep(void) 
{
    #if(!Hall_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Hall_Timer_CTRL_ENABLE == (Hall_Timer_CONTROL & Hall_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Hall_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Hall_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Hall_Timer_Stop();
    Hall_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: Hall_Timer_Wakeup
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
*  Hall_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Hall_Timer_Wakeup(void) 
{
    Hall_Timer_RestoreConfig();
    #if(!Hall_Timer_UDB_CONTROL_REG_REMOVED)
        if(Hall_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Hall_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
