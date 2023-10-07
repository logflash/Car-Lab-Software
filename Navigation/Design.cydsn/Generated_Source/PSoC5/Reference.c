/*******************************************************************************
* File Name: Reference.c  
* Version 1.90
*
* Description:
*  This file provides the source code to the API for the 8-bit Voltage DAC 
*  (VDAC8) User Module.
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Reference.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 Reference_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 Reference_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static Reference_backupStruct Reference_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: Reference_Init
********************************************************************************
* Summary:
*  Initialize to the schematic state.
* 
* Parameters:
*  void:
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Reference_Init(void) 
{
    Reference_CR0 = (Reference_MODE_V );

    /* Set default data source */
    #if(Reference_DEFAULT_DATA_SRC != 0 )
        Reference_CR1 = (Reference_DEFAULT_CNTL | Reference_DACBUS_ENABLE) ;
    #else
        Reference_CR1 = (Reference_DEFAULT_CNTL | Reference_DACBUS_DISABLE) ;
    #endif /* (Reference_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(Reference_DEFAULT_STRB != 0)
        Reference_Strobe |= Reference_STRB_EN ;
    #endif/* (Reference_DEFAULT_STRB != 0) */

    /* Set default range */
    Reference_SetRange(Reference_DEFAULT_RANGE); 

    /* Set default speed */
    Reference_SetSpeed(Reference_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: Reference_Enable
********************************************************************************
* Summary:
*  Enable the VDAC8
* 
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Reference_Enable(void) 
{
    Reference_PWRMGR |= Reference_ACT_PWR_EN;
    Reference_STBY_PWRMGR |= Reference_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(Reference_restoreVal == 1u) 
        {
             Reference_CR0 = Reference_backup.data_value;
             Reference_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Reference_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as
*  executing the stop function.
*
* Parameters:
*  Power: Sets power level between off (0) and (3) high power
*
* Return:
*  void 
*
* Global variables:
*  Reference_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Reference_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(Reference_initVar == 0u)
    { 
        Reference_Init();
        Reference_initVar = 1u;
    }

    /* Enable power to DAC */
    Reference_Enable();

    /* Set default value */
    Reference_SetValue(Reference_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: Reference_Stop
********************************************************************************
*
* Summary:
*  Powers down DAC to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Reference_Stop(void) 
{
    /* Disble power to DAC */
    Reference_PWRMGR &= (uint8)(~Reference_ACT_PWR_EN);
    Reference_STBY_PWRMGR &= (uint8)(~Reference_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        Reference_backup.data_value = Reference_CR0;
        Reference_CR0 = Reference_CUR_MODE_OUT_OFF;
        Reference_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Reference_SetSpeed
********************************************************************************
*
* Summary:
*  Set DAC speed
*
* Parameters:
*  power: Sets speed value
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Reference_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    Reference_CR0 &= (uint8)(~Reference_HS_MASK);
    Reference_CR0 |=  (speed & Reference_HS_MASK);
}


/*******************************************************************************
* Function Name: Reference_SetRange
********************************************************************************
*
* Summary:
*  Set one of three current ranges.
*
* Parameters:
*  Range: Sets one of Three valid ranges.
*
* Return:
*  void 
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Reference_SetRange(uint8 range) 
{
    Reference_CR0 &= (uint8)(~Reference_RANGE_MASK);      /* Clear existing mode */
    Reference_CR0 |= (range & Reference_RANGE_MASK);      /*  Set Range  */
    Reference_DacTrim();
}


/*******************************************************************************
* Function Name: Reference_SetValue
********************************************************************************
*
* Summary:
*  Set 8-bit DAC value
*
* Parameters:  
*  value:  Sets DAC value between 0 and 255.
*
* Return: 
*  void 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void Reference_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 Reference_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    Reference_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        Reference_Data = value;
        CyExitCriticalSection(Reference_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Reference_DacTrim
********************************************************************************
*
* Summary:
*  Set the trim value for the given range.
*
* Parameters:
*  range:  1V or 4V range.  See constants.
*
* Return:
*  void
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void Reference_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((Reference_CR0 & Reference_RANGE_MASK) >> 2) + Reference_TRIM_M7_1V_RNG_OFFSET;
    Reference_TR = CY_GET_XTND_REG8((uint8 *)(Reference_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
