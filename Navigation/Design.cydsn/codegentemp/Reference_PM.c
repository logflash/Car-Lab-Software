/*******************************************************************************
* File Name: Reference_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
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

#include "Reference.h"

static Reference_backupStruct Reference_backup;


/*******************************************************************************
* Function Name: Reference_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void Reference_SaveConfig(void) 
{
    if (!((Reference_CR1 & Reference_SRC_MASK) == Reference_SRC_UDB))
    {
        Reference_backup.data_value = Reference_Data;
    }
}


/*******************************************************************************
* Function Name: Reference_RestoreConfig
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
*******************************************************************************/
void Reference_RestoreConfig(void) 
{
    if (!((Reference_CR1 & Reference_SRC_MASK) == Reference_SRC_UDB))
    {
        if((Reference_Strobe & Reference_STRB_MASK) == Reference_STRB_EN)
        {
            Reference_Strobe &= (uint8)(~Reference_STRB_MASK);
            Reference_Data = Reference_backup.data_value;
            Reference_Strobe |= Reference_STRB_EN;
        }
        else
        {
            Reference_Data = Reference_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: Reference_Sleep
********************************************************************************
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
*  Reference_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void Reference_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(Reference_ACT_PWR_EN == (Reference_PWRMGR & Reference_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        Reference_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        Reference_backup.enableState = 0u;
    }
    
    Reference_Stop();
    Reference_SaveConfig();
}


/*******************************************************************************
* Function Name: Reference_Wakeup
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
*  Reference_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Reference_Wakeup(void) 
{
    Reference_RestoreConfig();
    
    if(Reference_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        Reference_Enable();

        /* Restore the data register */
        Reference_SetValue(Reference_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
