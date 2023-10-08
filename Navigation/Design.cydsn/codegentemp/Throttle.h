/*******************************************************************************
* File Name: Throttle.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Throttle_H) /* Pins Throttle_H */
#define CY_PINS_Throttle_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Throttle_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Throttle__PORT == 15 && ((Throttle__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Throttle_Write(uint8 value);
void    Throttle_SetDriveMode(uint8 mode);
uint8   Throttle_ReadDataReg(void);
uint8   Throttle_Read(void);
void    Throttle_SetInterruptMode(uint16 position, uint16 mode);
uint8   Throttle_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Throttle_SetDriveMode() function.
     *  @{
     */
        #define Throttle_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Throttle_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Throttle_DM_RES_UP          PIN_DM_RES_UP
        #define Throttle_DM_RES_DWN         PIN_DM_RES_DWN
        #define Throttle_DM_OD_LO           PIN_DM_OD_LO
        #define Throttle_DM_OD_HI           PIN_DM_OD_HI
        #define Throttle_DM_STRONG          PIN_DM_STRONG
        #define Throttle_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Throttle_MASK               Throttle__MASK
#define Throttle_SHIFT              Throttle__SHIFT
#define Throttle_WIDTH              1u

/* Interrupt constants */
#if defined(Throttle__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Throttle_SetInterruptMode() function.
     *  @{
     */
        #define Throttle_INTR_NONE      (uint16)(0x0000u)
        #define Throttle_INTR_RISING    (uint16)(0x0001u)
        #define Throttle_INTR_FALLING   (uint16)(0x0002u)
        #define Throttle_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Throttle_INTR_MASK      (0x01u) 
#endif /* (Throttle__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Throttle_PS                     (* (reg8 *) Throttle__PS)
/* Data Register */
#define Throttle_DR                     (* (reg8 *) Throttle__DR)
/* Port Number */
#define Throttle_PRT_NUM                (* (reg8 *) Throttle__PRT) 
/* Connect to Analog Globals */                                                  
#define Throttle_AG                     (* (reg8 *) Throttle__AG)                       
/* Analog MUX bux enable */
#define Throttle_AMUX                   (* (reg8 *) Throttle__AMUX) 
/* Bidirectional Enable */                                                        
#define Throttle_BIE                    (* (reg8 *) Throttle__BIE)
/* Bit-mask for Aliased Register Access */
#define Throttle_BIT_MASK               (* (reg8 *) Throttle__BIT_MASK)
/* Bypass Enable */
#define Throttle_BYP                    (* (reg8 *) Throttle__BYP)
/* Port wide control signals */                                                   
#define Throttle_CTL                    (* (reg8 *) Throttle__CTL)
/* Drive Modes */
#define Throttle_DM0                    (* (reg8 *) Throttle__DM0) 
#define Throttle_DM1                    (* (reg8 *) Throttle__DM1)
#define Throttle_DM2                    (* (reg8 *) Throttle__DM2) 
/* Input Buffer Disable Override */
#define Throttle_INP_DIS                (* (reg8 *) Throttle__INP_DIS)
/* LCD Common or Segment Drive */
#define Throttle_LCD_COM_SEG            (* (reg8 *) Throttle__LCD_COM_SEG)
/* Enable Segment LCD */
#define Throttle_LCD_EN                 (* (reg8 *) Throttle__LCD_EN)
/* Slew Rate Control */
#define Throttle_SLW                    (* (reg8 *) Throttle__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Throttle_PRTDSI__CAPS_SEL       (* (reg8 *) Throttle__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Throttle_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Throttle__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Throttle_PRTDSI__OE_SEL0        (* (reg8 *) Throttle__PRTDSI__OE_SEL0) 
#define Throttle_PRTDSI__OE_SEL1        (* (reg8 *) Throttle__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Throttle_PRTDSI__OUT_SEL0       (* (reg8 *) Throttle__PRTDSI__OUT_SEL0) 
#define Throttle_PRTDSI__OUT_SEL1       (* (reg8 *) Throttle__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Throttle_PRTDSI__SYNC_OUT       (* (reg8 *) Throttle__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Throttle__SIO_CFG)
    #define Throttle_SIO_HYST_EN        (* (reg8 *) Throttle__SIO_HYST_EN)
    #define Throttle_SIO_REG_HIFREQ     (* (reg8 *) Throttle__SIO_REG_HIFREQ)
    #define Throttle_SIO_CFG            (* (reg8 *) Throttle__SIO_CFG)
    #define Throttle_SIO_DIFF           (* (reg8 *) Throttle__SIO_DIFF)
#endif /* (Throttle__SIO_CFG) */

/* Interrupt Registers */
#if defined(Throttle__INTSTAT)
    #define Throttle_INTSTAT            (* (reg8 *) Throttle__INTSTAT)
    #define Throttle_SNAP               (* (reg8 *) Throttle__SNAP)
    
	#define Throttle_0_INTTYPE_REG 		(* (reg8 *) Throttle__0__INTTYPE)
#endif /* (Throttle__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Throttle_H */


/* [] END OF FILE */
