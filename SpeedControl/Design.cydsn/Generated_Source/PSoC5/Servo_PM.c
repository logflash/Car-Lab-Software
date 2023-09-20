/*******************************************************************************
* File Name: Servo_PM.c
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

#include "Servo.h"

static Servo_backupStruct Servo_backup;


/*******************************************************************************
* Function Name: Servo_SaveConfig
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
*  Servo_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Servo_SaveConfig(void) 
{

    #if(!Servo_UsingFixedFunction)
        #if(!Servo_PWMModeIsCenterAligned)
            Servo_backup.PWMPeriod = Servo_ReadPeriod();
        #endif /* (!Servo_PWMModeIsCenterAligned) */
        Servo_backup.PWMUdb = Servo_ReadCounter();
        #if (Servo_UseStatus)
            Servo_backup.InterruptMaskValue = Servo_STATUS_MASK;
        #endif /* (Servo_UseStatus) */

        #if(Servo_DeadBandMode == Servo__B_PWM__DBM_256_CLOCKS || \
            Servo_DeadBandMode == Servo__B_PWM__DBM_2_4_CLOCKS)
            Servo_backup.PWMdeadBandValue = Servo_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Servo_KillModeMinTime)
             Servo_backup.PWMKillCounterPeriod = Servo_ReadKillTime();
        #endif /* (Servo_KillModeMinTime) */

        #if(Servo_UseControl)
            Servo_backup.PWMControlRegister = Servo_ReadControlRegister();
        #endif /* (Servo_UseControl) */
    #endif  /* (!Servo_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Servo_RestoreConfig
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
*  Servo_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Servo_RestoreConfig(void) 
{
        #if(!Servo_UsingFixedFunction)
            #if(!Servo_PWMModeIsCenterAligned)
                Servo_WritePeriod(Servo_backup.PWMPeriod);
            #endif /* (!Servo_PWMModeIsCenterAligned) */

            Servo_WriteCounter(Servo_backup.PWMUdb);

            #if (Servo_UseStatus)
                Servo_STATUS_MASK = Servo_backup.InterruptMaskValue;
            #endif /* (Servo_UseStatus) */

            #if(Servo_DeadBandMode == Servo__B_PWM__DBM_256_CLOCKS || \
                Servo_DeadBandMode == Servo__B_PWM__DBM_2_4_CLOCKS)
                Servo_WriteDeadTime(Servo_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Servo_KillModeMinTime)
                Servo_WriteKillTime(Servo_backup.PWMKillCounterPeriod);
            #endif /* (Servo_KillModeMinTime) */

            #if(Servo_UseControl)
                Servo_WriteControlRegister(Servo_backup.PWMControlRegister);
            #endif /* (Servo_UseControl) */
        #endif  /* (!Servo_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Servo_Sleep
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
*  Servo_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Servo_Sleep(void) 
{
    #if(Servo_UseControl)
        if(Servo_CTRL_ENABLE == (Servo_CONTROL & Servo_CTRL_ENABLE))
        {
            /*Component is enabled */
            Servo_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Servo_backup.PWMEnableState = 0u;
        }
    #endif /* (Servo_UseControl) */

    /* Stop component */
    Servo_Stop();

    /* Save registers configuration */
    Servo_SaveConfig();
}


/*******************************************************************************
* Function Name: Servo_Wakeup
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
*  Servo_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Servo_Wakeup(void) 
{
     /* Restore registers values */
    Servo_RestoreConfig();

    if(Servo_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Servo_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
