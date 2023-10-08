/*******************************************************************************
* File Name: dc_motor_clock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_dc_motor_clock_H)
#define CY_CLOCK_dc_motor_clock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void dc_motor_clock_Start(void) ;
void dc_motor_clock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void dc_motor_clock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void dc_motor_clock_StandbyPower(uint8 state) ;
void dc_motor_clock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 dc_motor_clock_GetDividerRegister(void) ;
void dc_motor_clock_SetModeRegister(uint8 modeBitMask) ;
void dc_motor_clock_ClearModeRegister(uint8 modeBitMask) ;
uint8 dc_motor_clock_GetModeRegister(void) ;
void dc_motor_clock_SetSourceRegister(uint8 clkSource) ;
uint8 dc_motor_clock_GetSourceRegister(void) ;
#if defined(dc_motor_clock__CFG3)
void dc_motor_clock_SetPhaseRegister(uint8 clkPhase) ;
uint8 dc_motor_clock_GetPhaseRegister(void) ;
#endif /* defined(dc_motor_clock__CFG3) */

#define dc_motor_clock_Enable()                       dc_motor_clock_Start()
#define dc_motor_clock_Disable()                      dc_motor_clock_Stop()
#define dc_motor_clock_SetDivider(clkDivider)         dc_motor_clock_SetDividerRegister(clkDivider, 1u)
#define dc_motor_clock_SetDividerValue(clkDivider)    dc_motor_clock_SetDividerRegister((clkDivider) - 1u, 1u)
#define dc_motor_clock_SetMode(clkMode)               dc_motor_clock_SetModeRegister(clkMode)
#define dc_motor_clock_SetSource(clkSource)           dc_motor_clock_SetSourceRegister(clkSource)
#if defined(dc_motor_clock__CFG3)
#define dc_motor_clock_SetPhase(clkPhase)             dc_motor_clock_SetPhaseRegister(clkPhase)
#define dc_motor_clock_SetPhaseValue(clkPhase)        dc_motor_clock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(dc_motor_clock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define dc_motor_clock_CLKEN              (* (reg8 *) dc_motor_clock__PM_ACT_CFG)
#define dc_motor_clock_CLKEN_PTR          ((reg8 *) dc_motor_clock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define dc_motor_clock_CLKSTBY            (* (reg8 *) dc_motor_clock__PM_STBY_CFG)
#define dc_motor_clock_CLKSTBY_PTR        ((reg8 *) dc_motor_clock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define dc_motor_clock_DIV_LSB            (* (reg8 *) dc_motor_clock__CFG0)
#define dc_motor_clock_DIV_LSB_PTR        ((reg8 *) dc_motor_clock__CFG0)
#define dc_motor_clock_DIV_PTR            ((reg16 *) dc_motor_clock__CFG0)

/* Clock MSB divider configuration register. */
#define dc_motor_clock_DIV_MSB            (* (reg8 *) dc_motor_clock__CFG1)
#define dc_motor_clock_DIV_MSB_PTR        ((reg8 *) dc_motor_clock__CFG1)

/* Mode and source configuration register */
#define dc_motor_clock_MOD_SRC            (* (reg8 *) dc_motor_clock__CFG2)
#define dc_motor_clock_MOD_SRC_PTR        ((reg8 *) dc_motor_clock__CFG2)

#if defined(dc_motor_clock__CFG3)
/* Analog clock phase configuration register */
#define dc_motor_clock_PHASE              (* (reg8 *) dc_motor_clock__CFG3)
#define dc_motor_clock_PHASE_PTR          ((reg8 *) dc_motor_clock__CFG3)
#endif /* defined(dc_motor_clock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define dc_motor_clock_CLKEN_MASK         dc_motor_clock__PM_ACT_MSK
#define dc_motor_clock_CLKSTBY_MASK       dc_motor_clock__PM_STBY_MSK

/* CFG2 field masks */
#define dc_motor_clock_SRC_SEL_MSK        dc_motor_clock__CFG2_SRC_SEL_MASK
#define dc_motor_clock_MODE_MASK          (~(dc_motor_clock_SRC_SEL_MSK))

#if defined(dc_motor_clock__CFG3)
/* CFG3 phase mask */
#define dc_motor_clock_PHASE_MASK         dc_motor_clock__CFG3_PHASE_DLY_MASK
#endif /* defined(dc_motor_clock__CFG3) */

#endif /* CY_CLOCK_dc_motor_clock_H */


/* [] END OF FILE */
