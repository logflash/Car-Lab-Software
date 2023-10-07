/*******************************************************************************
* File Name: Analog_CMP.c
* Version 2.0
*
* Description:
*  This file provides the power management source code APIs for the
*  Comparator.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Analog_CMP.h"

static Analog_CMP_backupStruct Analog_CMP_backup;


/*******************************************************************************
* Function Name: Analog_CMP_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
*******************************************************************************/
void Analog_CMP_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: Analog_CMP_RestoreConfig
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
********************************************************************************/
void Analog_CMP_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: Analog_CMP_Sleep
********************************************************************************
*
* Summary:
*  Stop and Save the user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
* Global variables:
*  Analog_CMP_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void Analog_CMP_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(Analog_CMP_ACT_PWR_EN == (Analog_CMP_PWRMGR & Analog_CMP_ACT_PWR_EN))
    {
        /* Comp is enabled */
        Analog_CMP_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        Analog_CMP_backup.enableState = 0u;
    }    
    
    Analog_CMP_Stop();
    Analog_CMP_SaveConfig();
}


/*******************************************************************************
* Function Name: Analog_CMP_Wakeup
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
*  Analog_CMP_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Analog_CMP_Wakeup(void) 
{
    Analog_CMP_RestoreConfig();
    
    if(Analog_CMP_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        Analog_CMP_Enable();

    } /* Do nothing if Comp was disabled before */ 
}


/* [] END OF FILE */
