/*******************************************************************************
* File Name: Row_Counter_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Row_Counter.h"

static Row_Counter_backupStruct Row_Counter_backup;


/*******************************************************************************
* Function Name: Row_Counter_SaveConfig
********************************************************************************
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
*  Row_Counter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Row_Counter_SaveConfig(void) 
{
    #if (!Row_Counter_UsingFixedFunction)

        Row_Counter_backup.CounterUdb = Row_Counter_ReadCounter();

        #if(!Row_Counter_ControlRegRemoved)
            Row_Counter_backup.CounterControlRegister = Row_Counter_ReadControlRegister();
        #endif /* (!Row_Counter_ControlRegRemoved) */

    #endif /* (!Row_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Row_Counter_RestoreConfig
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
*  Row_Counter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Row_Counter_RestoreConfig(void) 
{      
    #if (!Row_Counter_UsingFixedFunction)

       Row_Counter_WriteCounter(Row_Counter_backup.CounterUdb);

        #if(!Row_Counter_ControlRegRemoved)
            Row_Counter_WriteControlRegister(Row_Counter_backup.CounterControlRegister);
        #endif /* (!Row_Counter_ControlRegRemoved) */

    #endif /* (!Row_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Row_Counter_Sleep
********************************************************************************
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
*  Row_Counter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Row_Counter_Sleep(void) 
{
    #if(!Row_Counter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Row_Counter_CTRL_ENABLE == (Row_Counter_CONTROL & Row_Counter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Row_Counter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Row_Counter_backup.CounterEnableState = 0u;
        }
    #else
        Row_Counter_backup.CounterEnableState = 1u;
        if(Row_Counter_backup.CounterEnableState != 0u)
        {
            Row_Counter_backup.CounterEnableState = 0u;
        }
    #endif /* (!Row_Counter_ControlRegRemoved) */
    
    Row_Counter_Stop();
    Row_Counter_SaveConfig();
}


/*******************************************************************************
* Function Name: Row_Counter_Wakeup
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
*  Row_Counter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Row_Counter_Wakeup(void) 
{
    Row_Counter_RestoreConfig();
    #if(!Row_Counter_ControlRegRemoved)
        if(Row_Counter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Row_Counter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Row_Counter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
