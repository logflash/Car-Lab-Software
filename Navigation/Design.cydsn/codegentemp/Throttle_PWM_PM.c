/*******************************************************************************
* File Name: Throttle_PWM_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Throttle_PWM.h"

static Throttle_PWM_backupStruct Throttle_PWM_backup;


/*******************************************************************************
* Function Name: Throttle_PWM_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Throttle_PWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Throttle_PWM_SaveConfig(void) 
{

    #if(!Throttle_PWM_UsingFixedFunction)
        #if(!Throttle_PWM_PWMModeIsCenterAligned)
            Throttle_PWM_backup.PWMPeriod = Throttle_PWM_ReadPeriod();
        #endif /* (!Throttle_PWM_PWMModeIsCenterAligned) */
        Throttle_PWM_backup.PWMUdb = Throttle_PWM_ReadCounter();
        #if (Throttle_PWM_UseStatus)
            Throttle_PWM_backup.InterruptMaskValue = Throttle_PWM_STATUS_MASK;
        #endif /* (Throttle_PWM_UseStatus) */

        #if(Throttle_PWM_DeadBandMode == Throttle_PWM__B_PWM__DBM_256_CLOCKS || \
            Throttle_PWM_DeadBandMode == Throttle_PWM__B_PWM__DBM_2_4_CLOCKS)
            Throttle_PWM_backup.PWMdeadBandValue = Throttle_PWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Throttle_PWM_KillModeMinTime)
             Throttle_PWM_backup.PWMKillCounterPeriod = Throttle_PWM_ReadKillTime();
        #endif /* (Throttle_PWM_KillModeMinTime) */

        #if(Throttle_PWM_UseControl)
            Throttle_PWM_backup.PWMControlRegister = Throttle_PWM_ReadControlRegister();
        #endif /* (Throttle_PWM_UseControl) */
    #endif  /* (!Throttle_PWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Throttle_PWM_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Throttle_PWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Throttle_PWM_RestoreConfig(void) 
{
        #if(!Throttle_PWM_UsingFixedFunction)
            #if(!Throttle_PWM_PWMModeIsCenterAligned)
                Throttle_PWM_WritePeriod(Throttle_PWM_backup.PWMPeriod);
            #endif /* (!Throttle_PWM_PWMModeIsCenterAligned) */

            Throttle_PWM_WriteCounter(Throttle_PWM_backup.PWMUdb);

            #if (Throttle_PWM_UseStatus)
                Throttle_PWM_STATUS_MASK = Throttle_PWM_backup.InterruptMaskValue;
            #endif /* (Throttle_PWM_UseStatus) */

            #if(Throttle_PWM_DeadBandMode == Throttle_PWM__B_PWM__DBM_256_CLOCKS || \
                Throttle_PWM_DeadBandMode == Throttle_PWM__B_PWM__DBM_2_4_CLOCKS)
                Throttle_PWM_WriteDeadTime(Throttle_PWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Throttle_PWM_KillModeMinTime)
                Throttle_PWM_WriteKillTime(Throttle_PWM_backup.PWMKillCounterPeriod);
            #endif /* (Throttle_PWM_KillModeMinTime) */

            #if(Throttle_PWM_UseControl)
                Throttle_PWM_WriteControlRegister(Throttle_PWM_backup.PWMControlRegister);
            #endif /* (Throttle_PWM_UseControl) */
        #endif  /* (!Throttle_PWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Throttle_PWM_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Throttle_PWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Throttle_PWM_Sleep(void) 
{
    #if(Throttle_PWM_UseControl)
        if(Throttle_PWM_CTRL_ENABLE == (Throttle_PWM_CONTROL & Throttle_PWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            Throttle_PWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Throttle_PWM_backup.PWMEnableState = 0u;
        }
    #endif /* (Throttle_PWM_UseControl) */

    /* Stop component */
    Throttle_PWM_Stop();

    /* Save registers configuration */
    Throttle_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: Throttle_PWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Throttle_PWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Throttle_PWM_Wakeup(void) 
{
     /* Restore registers values */
    Throttle_PWM_RestoreConfig();

    if(Throttle_PWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Throttle_PWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
