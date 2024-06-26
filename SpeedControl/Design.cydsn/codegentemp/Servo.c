/*******************************************************************************
* File Name: Servo.c
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

#include "Servo.h"

/* Error message for removed <resource> through optimization */
#ifdef Servo_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* Servo_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 Servo_initVar = 0u;


/*******************************************************************************
* Function Name: Servo_Start
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
*  Servo_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Servo_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(Servo_initVar == 0u)
    {
        Servo_Init();
        Servo_initVar = 1u;
    }
    Servo_Enable();

}


/*******************************************************************************
* Function Name: Servo_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  Servo_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Servo_Init(void) 
{
    #if (Servo_UsingFixedFunction || Servo_UseControl)
        uint8 ctrl;
    #endif /* (Servo_UsingFixedFunction || Servo_UseControl) */

    #if(!Servo_UsingFixedFunction)
        #if(Servo_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 Servo_interruptState;
        #endif /* (Servo_UseStatus) */
    #endif /* (!Servo_UsingFixedFunction) */

    #if (Servo_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        Servo_CONTROL |= Servo_CFG0_MODE;
        #if (Servo_DeadBand2_4)
            Servo_CONTROL |= Servo_CFG0_DB;
        #endif /* (Servo_DeadBand2_4) */

        ctrl = Servo_CONTROL3 & ((uint8 )(~Servo_CTRL_CMPMODE1_MASK));
        Servo_CONTROL3 = ctrl | Servo_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        Servo_RT1 &= ((uint8)(~Servo_RT1_MASK));
        Servo_RT1 |= Servo_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        Servo_RT1 &= ((uint8)(~Servo_SYNCDSI_MASK));
        Servo_RT1 |= Servo_SYNCDSI_EN;

    #elif (Servo_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = Servo_CONTROL & ((uint8)(~Servo_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~Servo_CTRL_CMPMODE1_MASK));
        Servo_CONTROL = ctrl | Servo_DEFAULT_COMPARE2_MODE |
                                   Servo_DEFAULT_COMPARE1_MODE;
    #endif /* (Servo_UsingFixedFunction) */

    #if (!Servo_UsingFixedFunction)
        #if (Servo_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            Servo_AUX_CONTROLDP0 |= (Servo_AUX_CTRL_FIFO0_CLR);
        #else /* (Servo_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            Servo_AUX_CONTROLDP0 |= (Servo_AUX_CTRL_FIFO0_CLR);
            Servo_AUX_CONTROLDP1 |= (Servo_AUX_CTRL_FIFO0_CLR);
        #endif /* (Servo_Resolution == 8) */

        Servo_WriteCounter(Servo_INIT_PERIOD_VALUE);
    #endif /* (!Servo_UsingFixedFunction) */

    Servo_WritePeriod(Servo_INIT_PERIOD_VALUE);

        #if (Servo_UseOneCompareMode)
            Servo_WriteCompare(Servo_INIT_COMPARE_VALUE1);
        #else
            Servo_WriteCompare1(Servo_INIT_COMPARE_VALUE1);
            Servo_WriteCompare2(Servo_INIT_COMPARE_VALUE2);
        #endif /* (Servo_UseOneCompareMode) */

        #if (Servo_KillModeMinTime)
            Servo_WriteKillTime(Servo_MinimumKillTime);
        #endif /* (Servo_KillModeMinTime) */

        #if (Servo_DeadBandUsed)
            Servo_WriteDeadTime(Servo_INIT_DEAD_TIME);
        #endif /* (Servo_DeadBandUsed) */

    #if (Servo_UseStatus || Servo_UsingFixedFunction)
        Servo_SetInterruptMode(Servo_INIT_INTERRUPTS_MODE);
    #endif /* (Servo_UseStatus || Servo_UsingFixedFunction) */

    #if (Servo_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        Servo_GLOBAL_ENABLE |= Servo_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        Servo_CONTROL2 |= Servo_CTRL2_IRQ_SEL;
    #else
        #if(Servo_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Servo_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            Servo_STATUS_AUX_CTRL |= Servo_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(Servo_interruptState);

            /* Clear the FIFO to enable the Servo_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            Servo_ClearFIFO();
        #endif /* (Servo_UseStatus) */
    #endif /* (Servo_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Servo_Enable
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
void Servo_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (Servo_UsingFixedFunction)
        Servo_GLOBAL_ENABLE |= Servo_BLOCK_EN_MASK;
        Servo_GLOBAL_STBY_ENABLE |= Servo_BLOCK_STBY_EN_MASK;
    #endif /* (Servo_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (Servo_UseControl || Servo_UsingFixedFunction)
        Servo_CONTROL |= Servo_CTRL_ENABLE;
    #endif /* (Servo_UseControl || Servo_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Servo_Stop
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
void Servo_Stop(void) 
{
    #if (Servo_UseControl || Servo_UsingFixedFunction)
        Servo_CONTROL &= ((uint8)(~Servo_CTRL_ENABLE));
    #endif /* (Servo_UseControl || Servo_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (Servo_UsingFixedFunction)
        Servo_GLOBAL_ENABLE &= ((uint8)(~Servo_BLOCK_EN_MASK));
        Servo_GLOBAL_STBY_ENABLE &= ((uint8)(~Servo_BLOCK_STBY_EN_MASK));
    #endif /* (Servo_UsingFixedFunction) */
}

#if (Servo_UseOneCompareMode)
    #if (Servo_CompareMode1SW)


        /*******************************************************************************
        * Function Name: Servo_SetCompareMode
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
        void Servo_SetCompareMode(uint8 comparemode) 
        {
            #if(Servo_UsingFixedFunction)

                #if(0 != Servo_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << Servo_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != Servo_CTRL_CMPMODE1_SHIFT) */

                Servo_CONTROL3 &= ((uint8)(~Servo_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                Servo_CONTROL3 |= comparemodemasked;

            #elif (Servo_UseControl)

                #if(0 != Servo_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << Servo_CTRL_CMPMODE1_SHIFT)) &
                                                Servo_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & Servo_CTRL_CMPMODE1_MASK;
                #endif /* (0 != Servo_CTRL_CMPMODE1_SHIFT) */

                #if(0 != Servo_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << Servo_CTRL_CMPMODE2_SHIFT)) &
                                               Servo_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & Servo_CTRL_CMPMODE2_MASK;
                #endif /* (0 != Servo_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                Servo_CONTROL &= ((uint8)(~(Servo_CTRL_CMPMODE1_MASK |
                                            Servo_CTRL_CMPMODE2_MASK)));
                Servo_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (Servo_UsingFixedFunction) */
        }
    #endif /* Servo_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (Servo_CompareMode1SW)


        /*******************************************************************************
        * Function Name: Servo_SetCompareMode1
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
        void Servo_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != Servo_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << Servo_CTRL_CMPMODE1_SHIFT)) &
                                           Servo_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & Servo_CTRL_CMPMODE1_MASK;
            #endif /* (0 != Servo_CTRL_CMPMODE1_SHIFT) */

            #if (Servo_UseControl)
                Servo_CONTROL &= ((uint8)(~Servo_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                Servo_CONTROL |= comparemodemasked;
            #endif /* (Servo_UseControl) */
        }
    #endif /* Servo_CompareMode1SW */

#if (Servo_CompareMode2SW)


    /*******************************************************************************
    * Function Name: Servo_SetCompareMode2
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
    void Servo_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != Servo_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << Servo_CTRL_CMPMODE2_SHIFT)) &
                                                 Servo_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & Servo_CTRL_CMPMODE2_MASK;
        #endif /* (0 != Servo_CTRL_CMPMODE2_SHIFT) */

        #if (Servo_UseControl)
            Servo_CONTROL &= ((uint8)(~Servo_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            Servo_CONTROL |= comparemodemasked;
        #endif /* (Servo_UseControl) */
    }
    #endif /*Servo_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!Servo_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Servo_WriteCounter
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
    void Servo_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(Servo_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: Servo_ReadCounter
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
    uint16 Servo_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(Servo_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(Servo_CAPTURE_LSB_PTR));
    }

    #if (Servo_UseStatus)


        /*******************************************************************************
        * Function Name: Servo_ClearFIFO
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
        void Servo_ClearFIFO(void) 
        {
            while(0u != (Servo_ReadStatusRegister() & Servo_STATUS_FIFONEMPTY))
            {
                (void)Servo_ReadCapture();
            }
        }

    #endif /* Servo_UseStatus */

#endif /* !Servo_UsingFixedFunction */


/*******************************************************************************
* Function Name: Servo_WritePeriod
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
void Servo_WritePeriod(uint16 period) 
{
    #if(Servo_UsingFixedFunction)
        CY_SET_REG16(Servo_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(Servo_PERIOD_LSB_PTR, period);
    #endif /* (Servo_UsingFixedFunction) */
}

#if (Servo_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: Servo_WriteCompare
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
    void Servo_WriteCompare(uint16 compare) \
                                       
    {
        #if(Servo_UsingFixedFunction)
            CY_SET_REG16(Servo_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(Servo_COMPARE1_LSB_PTR, compare);
        #endif /* (Servo_UsingFixedFunction) */

        #if (Servo_PWMMode == Servo__B_PWM__DITHER)
            #if(Servo_UsingFixedFunction)
                CY_SET_REG16(Servo_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(Servo_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (Servo_UsingFixedFunction) */
        #endif /* (Servo_PWMMode == Servo__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: Servo_WriteCompare1
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
    void Servo_WriteCompare1(uint16 compare) \
                                        
    {
        #if(Servo_UsingFixedFunction)
            CY_SET_REG16(Servo_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(Servo_COMPARE1_LSB_PTR, compare);
        #endif /* (Servo_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: Servo_WriteCompare2
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
    void Servo_WriteCompare2(uint16 compare) \
                                        
    {
        #if(Servo_UsingFixedFunction)
            CY_SET_REG16(Servo_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(Servo_COMPARE2_LSB_PTR, compare);
        #endif /* (Servo_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (Servo_DeadBandUsed)


    /*******************************************************************************
    * Function Name: Servo_WriteDeadTime
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
    void Servo_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!Servo_DeadBand2_4)
            CY_SET_REG8(Servo_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            Servo_DEADBAND_COUNT &= ((uint8)(~Servo_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(Servo_DEADBAND_COUNT_SHIFT)
                Servo_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << Servo_DEADBAND_COUNT_SHIFT)) &
                                                    Servo_DEADBAND_COUNT_MASK;
            #else
                Servo_DEADBAND_COUNT |= deadtime & Servo_DEADBAND_COUNT_MASK;
            #endif /* (Servo_DEADBAND_COUNT_SHIFT) */

        #endif /* (!Servo_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: Servo_ReadDeadTime
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
    uint8 Servo_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!Servo_DeadBand2_4)
            return (CY_GET_REG8(Servo_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(Servo_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(Servo_DEADBAND_COUNT & Servo_DEADBAND_COUNT_MASK)) >>
                                                                           Servo_DEADBAND_COUNT_SHIFT));
            #else
                return (Servo_DEADBAND_COUNT & Servo_DEADBAND_COUNT_MASK);
            #endif /* (Servo_DEADBAND_COUNT_SHIFT) */
        #endif /* (!Servo_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (Servo_UseStatus || Servo_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Servo_SetInterruptMode
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
    void Servo_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(Servo_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: Servo_ReadStatusRegister
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
    uint8 Servo_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(Servo_STATUS_PTR));
    }

#endif /* (Servo_UseStatus || Servo_UsingFixedFunction) */


#if (Servo_UseControl)


    /*******************************************************************************
    * Function Name: Servo_ReadControlRegister
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
    uint8 Servo_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(Servo_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: Servo_WriteControlRegister
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
    void Servo_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(Servo_CONTROL_PTR, control);
    }

#endif /* (Servo_UseControl) */


#if (!Servo_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Servo_ReadCapture
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
    uint16 Servo_ReadCapture(void) 
    {
        return (CY_GET_REG16(Servo_CAPTURE_LSB_PTR));
    }

#endif /* (!Servo_UsingFixedFunction) */


#if (Servo_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: Servo_ReadCompare
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
    uint16 Servo_ReadCompare(void) 
    {
        #if(Servo_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(Servo_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(Servo_COMPARE1_LSB_PTR));
        #endif /* (Servo_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: Servo_ReadCompare1
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
    uint16 Servo_ReadCompare1(void) 
    {
        return (CY_GET_REG16(Servo_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: Servo_ReadCompare2
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
    uint16 Servo_ReadCompare2(void) 
    {
        return (CY_GET_REG16(Servo_COMPARE2_LSB_PTR));
    }

#endif /* (Servo_UseOneCompareMode) */


/*******************************************************************************
* Function Name: Servo_ReadPeriod
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
uint16 Servo_ReadPeriod(void) 
{
    #if(Servo_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(Servo_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(Servo_PERIOD_LSB_PTR));
    #endif /* (Servo_UsingFixedFunction) */
}

#if ( Servo_KillModeMinTime)


    /*******************************************************************************
    * Function Name: Servo_WriteKillTime
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
    void Servo_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(Servo_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: Servo_ReadKillTime
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
    uint8 Servo_ReadKillTime(void) 
    {
        return (CY_GET_REG8(Servo_KILLMODEMINTIME_PTR));
    }

#endif /* ( Servo_KillModeMinTime) */

/* [] END OF FILE */
