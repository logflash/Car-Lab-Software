/*******************************************************************************
* File Name: Throttle_PWM.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Throttle_PWM.h"

/* Error message for removed <resource> through optimization */
#ifdef Throttle_PWM_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* Throttle_PWM_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 Throttle_PWM_initVar = 0u;


/*******************************************************************************
* Function Name: Throttle_PWM_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Throttle_PWM_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Throttle_PWM_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(Throttle_PWM_initVar == 0u)
    {
        Throttle_PWM_Init();
        Throttle_PWM_initVar = 1u;
    }
    Throttle_PWM_Enable();

}


/*******************************************************************************
* Function Name: Throttle_PWM_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  Throttle_PWM_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Throttle_PWM_Init(void) 
{
    #if (Throttle_PWM_UsingFixedFunction || Throttle_PWM_UseControl)
        uint8 ctrl;
    #endif /* (Throttle_PWM_UsingFixedFunction || Throttle_PWM_UseControl) */

    #if(!Throttle_PWM_UsingFixedFunction)
        #if(Throttle_PWM_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 Throttle_PWM_interruptState;
        #endif /* (Throttle_PWM_UseStatus) */
    #endif /* (!Throttle_PWM_UsingFixedFunction) */

    #if (Throttle_PWM_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        Throttle_PWM_CONTROL |= Throttle_PWM_CFG0_MODE;
        #if (Throttle_PWM_DeadBand2_4)
            Throttle_PWM_CONTROL |= Throttle_PWM_CFG0_DB;
        #endif /* (Throttle_PWM_DeadBand2_4) */

        ctrl = Throttle_PWM_CONTROL3 & ((uint8 )(~Throttle_PWM_CTRL_CMPMODE1_MASK));
        Throttle_PWM_CONTROL3 = ctrl | Throttle_PWM_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        Throttle_PWM_RT1 &= ((uint8)(~Throttle_PWM_RT1_MASK));
        Throttle_PWM_RT1 |= Throttle_PWM_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        Throttle_PWM_RT1 &= ((uint8)(~Throttle_PWM_SYNCDSI_MASK));
        Throttle_PWM_RT1 |= Throttle_PWM_SYNCDSI_EN;

    #elif (Throttle_PWM_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = Throttle_PWM_CONTROL & ((uint8)(~Throttle_PWM_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~Throttle_PWM_CTRL_CMPMODE1_MASK));
        Throttle_PWM_CONTROL = ctrl | Throttle_PWM_DEFAULT_COMPARE2_MODE |
                                   Throttle_PWM_DEFAULT_COMPARE1_MODE;
    #endif /* (Throttle_PWM_UsingFixedFunction) */

    #if (!Throttle_PWM_UsingFixedFunction)
        #if (Throttle_PWM_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            Throttle_PWM_AUX_CONTROLDP0 |= (Throttle_PWM_AUX_CTRL_FIFO0_CLR);
        #else /* (Throttle_PWM_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            Throttle_PWM_AUX_CONTROLDP0 |= (Throttle_PWM_AUX_CTRL_FIFO0_CLR);
            Throttle_PWM_AUX_CONTROLDP1 |= (Throttle_PWM_AUX_CTRL_FIFO0_CLR);
        #endif /* (Throttle_PWM_Resolution == 8) */

        Throttle_PWM_WriteCounter(Throttle_PWM_INIT_PERIOD_VALUE);
    #endif /* (!Throttle_PWM_UsingFixedFunction) */

    Throttle_PWM_WritePeriod(Throttle_PWM_INIT_PERIOD_VALUE);

        #if (Throttle_PWM_UseOneCompareMode)
            Throttle_PWM_WriteCompare(Throttle_PWM_INIT_COMPARE_VALUE1);
        #else
            Throttle_PWM_WriteCompare1(Throttle_PWM_INIT_COMPARE_VALUE1);
            Throttle_PWM_WriteCompare2(Throttle_PWM_INIT_COMPARE_VALUE2);
        #endif /* (Throttle_PWM_UseOneCompareMode) */

        #if (Throttle_PWM_KillModeMinTime)
            Throttle_PWM_WriteKillTime(Throttle_PWM_MinimumKillTime);
        #endif /* (Throttle_PWM_KillModeMinTime) */

        #if (Throttle_PWM_DeadBandUsed)
            Throttle_PWM_WriteDeadTime(Throttle_PWM_INIT_DEAD_TIME);
        #endif /* (Throttle_PWM_DeadBandUsed) */

    #if (Throttle_PWM_UseStatus || Throttle_PWM_UsingFixedFunction)
        Throttle_PWM_SetInterruptMode(Throttle_PWM_INIT_INTERRUPTS_MODE);
    #endif /* (Throttle_PWM_UseStatus || Throttle_PWM_UsingFixedFunction) */

    #if (Throttle_PWM_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        Throttle_PWM_GLOBAL_ENABLE |= Throttle_PWM_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        Throttle_PWM_CONTROL2 |= Throttle_PWM_CTRL2_IRQ_SEL;
    #else
        #if(Throttle_PWM_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Throttle_PWM_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            Throttle_PWM_STATUS_AUX_CTRL |= Throttle_PWM_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(Throttle_PWM_interruptState);

            /* Clear the FIFO to enable the Throttle_PWM_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            Throttle_PWM_ClearFIFO();
        #endif /* (Throttle_PWM_UseStatus) */
    #endif /* (Throttle_PWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Throttle_PWM_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void Throttle_PWM_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (Throttle_PWM_UsingFixedFunction)
        Throttle_PWM_GLOBAL_ENABLE |= Throttle_PWM_BLOCK_EN_MASK;
        Throttle_PWM_GLOBAL_STBY_ENABLE |= Throttle_PWM_BLOCK_STBY_EN_MASK;
    #endif /* (Throttle_PWM_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (Throttle_PWM_UseControl || Throttle_PWM_UsingFixedFunction)
        Throttle_PWM_CONTROL |= Throttle_PWM_CTRL_ENABLE;
    #endif /* (Throttle_PWM_UseControl || Throttle_PWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Throttle_PWM_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void Throttle_PWM_Stop(void) 
{
    #if (Throttle_PWM_UseControl || Throttle_PWM_UsingFixedFunction)
        Throttle_PWM_CONTROL &= ((uint8)(~Throttle_PWM_CTRL_ENABLE));
    #endif /* (Throttle_PWM_UseControl || Throttle_PWM_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (Throttle_PWM_UsingFixedFunction)
        Throttle_PWM_GLOBAL_ENABLE &= ((uint8)(~Throttle_PWM_BLOCK_EN_MASK));
        Throttle_PWM_GLOBAL_STBY_ENABLE &= ((uint8)(~Throttle_PWM_BLOCK_STBY_EN_MASK));
    #endif /* (Throttle_PWM_UsingFixedFunction) */
}

#if (Throttle_PWM_UseOneCompareMode)
    #if (Throttle_PWM_CompareMode1SW)


        /*******************************************************************************
        * Function Name: Throttle_PWM_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Throttle_PWM_SetCompareMode(uint8 comparemode) 
        {
            #if(Throttle_PWM_UsingFixedFunction)

                #if(0 != Throttle_PWM_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << Throttle_PWM_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != Throttle_PWM_CTRL_CMPMODE1_SHIFT) */

                Throttle_PWM_CONTROL3 &= ((uint8)(~Throttle_PWM_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                Throttle_PWM_CONTROL3 |= comparemodemasked;

            #elif (Throttle_PWM_UseControl)

                #if(0 != Throttle_PWM_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << Throttle_PWM_CTRL_CMPMODE1_SHIFT)) &
                                                Throttle_PWM_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & Throttle_PWM_CTRL_CMPMODE1_MASK;
                #endif /* (0 != Throttle_PWM_CTRL_CMPMODE1_SHIFT) */

                #if(0 != Throttle_PWM_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << Throttle_PWM_CTRL_CMPMODE2_SHIFT)) &
                                               Throttle_PWM_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & Throttle_PWM_CTRL_CMPMODE2_MASK;
                #endif /* (0 != Throttle_PWM_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                Throttle_PWM_CONTROL &= ((uint8)(~(Throttle_PWM_CTRL_CMPMODE1_MASK |
                                            Throttle_PWM_CTRL_CMPMODE2_MASK)));
                Throttle_PWM_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (Throttle_PWM_UsingFixedFunction) */
        }
    #endif /* Throttle_PWM_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (Throttle_PWM_CompareMode1SW)


        /*******************************************************************************
        * Function Name: Throttle_PWM_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Throttle_PWM_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != Throttle_PWM_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << Throttle_PWM_CTRL_CMPMODE1_SHIFT)) &
                                           Throttle_PWM_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & Throttle_PWM_CTRL_CMPMODE1_MASK;
            #endif /* (0 != Throttle_PWM_CTRL_CMPMODE1_SHIFT) */

            #if (Throttle_PWM_UseControl)
                Throttle_PWM_CONTROL &= ((uint8)(~Throttle_PWM_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                Throttle_PWM_CONTROL |= comparemodemasked;
            #endif /* (Throttle_PWM_UseControl) */
        }
    #endif /* Throttle_PWM_CompareMode1SW */

#if (Throttle_PWM_CompareMode2SW)


    /*******************************************************************************
    * Function Name: Throttle_PWM_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Throttle_PWM_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != Throttle_PWM_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << Throttle_PWM_CTRL_CMPMODE2_SHIFT)) &
                                                 Throttle_PWM_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & Throttle_PWM_CTRL_CMPMODE2_MASK;
        #endif /* (0 != Throttle_PWM_CTRL_CMPMODE2_SHIFT) */

        #if (Throttle_PWM_UseControl)
            Throttle_PWM_CONTROL &= ((uint8)(~Throttle_PWM_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            Throttle_PWM_CONTROL |= comparemodemasked;
        #endif /* (Throttle_PWM_UseControl) */
    }
    #endif /*Throttle_PWM_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!Throttle_PWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Throttle_PWM_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void Throttle_PWM_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(Throttle_PWM_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: Throttle_PWM_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint16 Throttle_PWM_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(Throttle_PWM_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(Throttle_PWM_CAPTURE_LSB_PTR));
    }

    #if (Throttle_PWM_UseStatus)


        /*******************************************************************************
        * Function Name: Throttle_PWM_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Throttle_PWM_ClearFIFO(void) 
        {
            while(0u != (Throttle_PWM_ReadStatusRegister() & Throttle_PWM_STATUS_FIFONEMPTY))
            {
                (void)Throttle_PWM_ReadCapture();
            }
        }

    #endif /* Throttle_PWM_UseStatus */

#endif /* !Throttle_PWM_UsingFixedFunction */


/*******************************************************************************
* Function Name: Throttle_PWM_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void Throttle_PWM_WritePeriod(uint16 period) 
{
    #if(Throttle_PWM_UsingFixedFunction)
        CY_SET_REG16(Throttle_PWM_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(Throttle_PWM_PERIOD_LSB_PTR, period);
    #endif /* (Throttle_PWM_UsingFixedFunction) */
}

#if (Throttle_PWM_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: Throttle_PWM_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void Throttle_PWM_WriteCompare(uint16 compare) \
                                       
    {
        #if(Throttle_PWM_UsingFixedFunction)
            CY_SET_REG16(Throttle_PWM_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(Throttle_PWM_COMPARE1_LSB_PTR, compare);
        #endif /* (Throttle_PWM_UsingFixedFunction) */

        #if (Throttle_PWM_PWMMode == Throttle_PWM__B_PWM__DITHER)
            #if(Throttle_PWM_UsingFixedFunction)
                CY_SET_REG16(Throttle_PWM_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(Throttle_PWM_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (Throttle_PWM_UsingFixedFunction) */
        #endif /* (Throttle_PWM_PWMMode == Throttle_PWM__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: Throttle_PWM_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Throttle_PWM_WriteCompare1(uint16 compare) \
                                        
    {
        #if(Throttle_PWM_UsingFixedFunction)
            CY_SET_REG16(Throttle_PWM_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(Throttle_PWM_COMPARE1_LSB_PTR, compare);
        #endif /* (Throttle_PWM_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: Throttle_PWM_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Throttle_PWM_WriteCompare2(uint16 compare) \
                                        
    {
        #if(Throttle_PWM_UsingFixedFunction)
            CY_SET_REG16(Throttle_PWM_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(Throttle_PWM_COMPARE2_LSB_PTR, compare);
        #endif /* (Throttle_PWM_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (Throttle_PWM_DeadBandUsed)


    /*******************************************************************************
    * Function Name: Throttle_PWM_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Throttle_PWM_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!Throttle_PWM_DeadBand2_4)
            CY_SET_REG8(Throttle_PWM_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            Throttle_PWM_DEADBAND_COUNT &= ((uint8)(~Throttle_PWM_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(Throttle_PWM_DEADBAND_COUNT_SHIFT)
                Throttle_PWM_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << Throttle_PWM_DEADBAND_COUNT_SHIFT)) &
                                                    Throttle_PWM_DEADBAND_COUNT_MASK;
            #else
                Throttle_PWM_DEADBAND_COUNT |= deadtime & Throttle_PWM_DEADBAND_COUNT_MASK;
            #endif /* (Throttle_PWM_DEADBAND_COUNT_SHIFT) */

        #endif /* (!Throttle_PWM_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: Throttle_PWM_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 Throttle_PWM_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!Throttle_PWM_DeadBand2_4)
            return (CY_GET_REG8(Throttle_PWM_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(Throttle_PWM_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(Throttle_PWM_DEADBAND_COUNT & Throttle_PWM_DEADBAND_COUNT_MASK)) >>
                                                                           Throttle_PWM_DEADBAND_COUNT_SHIFT));
            #else
                return (Throttle_PWM_DEADBAND_COUNT & Throttle_PWM_DEADBAND_COUNT_MASK);
            #endif /* (Throttle_PWM_DEADBAND_COUNT_SHIFT) */
        #endif /* (!Throttle_PWM_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (Throttle_PWM_UseStatus || Throttle_PWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Throttle_PWM_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Throttle_PWM_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(Throttle_PWM_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: Throttle_PWM_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 Throttle_PWM_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(Throttle_PWM_STATUS_PTR));
    }

#endif /* (Throttle_PWM_UseStatus || Throttle_PWM_UsingFixedFunction) */


#if (Throttle_PWM_UseControl)


    /*******************************************************************************
    * Function Name: Throttle_PWM_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 Throttle_PWM_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(Throttle_PWM_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: Throttle_PWM_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Throttle_PWM_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(Throttle_PWM_CONTROL_PTR, control);
    }

#endif /* (Throttle_PWM_UseControl) */


#if (!Throttle_PWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Throttle_PWM_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint16 Throttle_PWM_ReadCapture(void) 
    {
        return (CY_GET_REG16(Throttle_PWM_CAPTURE_LSB_PTR));
    }

#endif /* (!Throttle_PWM_UsingFixedFunction) */


#if (Throttle_PWM_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: Throttle_PWM_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint16 Throttle_PWM_ReadCompare(void) 
    {
        #if(Throttle_PWM_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(Throttle_PWM_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(Throttle_PWM_COMPARE1_LSB_PTR));
        #endif /* (Throttle_PWM_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: Throttle_PWM_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 Throttle_PWM_ReadCompare1(void) 
    {
        return (CY_GET_REG16(Throttle_PWM_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: Throttle_PWM_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 Throttle_PWM_ReadCompare2(void) 
    {
        return (CY_GET_REG16(Throttle_PWM_COMPARE2_LSB_PTR));
    }

#endif /* (Throttle_PWM_UseOneCompareMode) */


/*******************************************************************************
* Function Name: Throttle_PWM_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint16 Throttle_PWM_ReadPeriod(void) 
{
    #if(Throttle_PWM_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(Throttle_PWM_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(Throttle_PWM_PERIOD_LSB_PTR));
    #endif /* (Throttle_PWM_UsingFixedFunction) */
}

#if ( Throttle_PWM_KillModeMinTime)


    /*******************************************************************************
    * Function Name: Throttle_PWM_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Throttle_PWM_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(Throttle_PWM_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: Throttle_PWM_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 Throttle_PWM_ReadKillTime(void) 
    {
        return (CY_GET_REG8(Throttle_PWM_KILLMODEMINTIME_PTR));
    }

#endif /* ( Throttle_PWM_KillModeMinTime) */

/* [] END OF FILE */
