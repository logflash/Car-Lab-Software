/*******************************************************************************
* File Name: Burst.h  
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

#if !defined(CY_PINS_Burst_H) /* Pins Burst_H */
#define CY_PINS_Burst_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Burst_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Burst__PORT == 15 && ((Burst__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Burst_Write(uint8 value);
void    Burst_SetDriveMode(uint8 mode);
uint8   Burst_ReadDataReg(void);
uint8   Burst_Read(void);
void    Burst_SetInterruptMode(uint16 position, uint16 mode);
uint8   Burst_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Burst_SetDriveMode() function.
     *  @{
     */
        #define Burst_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Burst_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Burst_DM_RES_UP          PIN_DM_RES_UP
        #define Burst_DM_RES_DWN         PIN_DM_RES_DWN
        #define Burst_DM_OD_LO           PIN_DM_OD_LO
        #define Burst_DM_OD_HI           PIN_DM_OD_HI
        #define Burst_DM_STRONG          PIN_DM_STRONG
        #define Burst_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Burst_MASK               Burst__MASK
#define Burst_SHIFT              Burst__SHIFT
#define Burst_WIDTH              1u

/* Interrupt constants */
#if defined(Burst__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Burst_SetInterruptMode() function.
     *  @{
     */
        #define Burst_INTR_NONE      (uint16)(0x0000u)
        #define Burst_INTR_RISING    (uint16)(0x0001u)
        #define Burst_INTR_FALLING   (uint16)(0x0002u)
        #define Burst_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Burst_INTR_MASK      (0x01u) 
#endif /* (Burst__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Burst_PS                     (* (reg8 *) Burst__PS)
/* Data Register */
#define Burst_DR                     (* (reg8 *) Burst__DR)
/* Port Number */
#define Burst_PRT_NUM                (* (reg8 *) Burst__PRT) 
/* Connect to Analog Globals */                                                  
#define Burst_AG                     (* (reg8 *) Burst__AG)                       
/* Analog MUX bux enable */
#define Burst_AMUX                   (* (reg8 *) Burst__AMUX) 
/* Bidirectional Enable */                                                        
#define Burst_BIE                    (* (reg8 *) Burst__BIE)
/* Bit-mask for Aliased Register Access */
#define Burst_BIT_MASK               (* (reg8 *) Burst__BIT_MASK)
/* Bypass Enable */
#define Burst_BYP                    (* (reg8 *) Burst__BYP)
/* Port wide control signals */                                                   
#define Burst_CTL                    (* (reg8 *) Burst__CTL)
/* Drive Modes */
#define Burst_DM0                    (* (reg8 *) Burst__DM0) 
#define Burst_DM1                    (* (reg8 *) Burst__DM1)
#define Burst_DM2                    (* (reg8 *) Burst__DM2) 
/* Input Buffer Disable Override */
#define Burst_INP_DIS                (* (reg8 *) Burst__INP_DIS)
/* LCD Common or Segment Drive */
#define Burst_LCD_COM_SEG            (* (reg8 *) Burst__LCD_COM_SEG)
/* Enable Segment LCD */
#define Burst_LCD_EN                 (* (reg8 *) Burst__LCD_EN)
/* Slew Rate Control */
#define Burst_SLW                    (* (reg8 *) Burst__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Burst_PRTDSI__CAPS_SEL       (* (reg8 *) Burst__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Burst_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Burst__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Burst_PRTDSI__OE_SEL0        (* (reg8 *) Burst__PRTDSI__OE_SEL0) 
#define Burst_PRTDSI__OE_SEL1        (* (reg8 *) Burst__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Burst_PRTDSI__OUT_SEL0       (* (reg8 *) Burst__PRTDSI__OUT_SEL0) 
#define Burst_PRTDSI__OUT_SEL1       (* (reg8 *) Burst__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Burst_PRTDSI__SYNC_OUT       (* (reg8 *) Burst__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Burst__SIO_CFG)
    #define Burst_SIO_HYST_EN        (* (reg8 *) Burst__SIO_HYST_EN)
    #define Burst_SIO_REG_HIFREQ     (* (reg8 *) Burst__SIO_REG_HIFREQ)
    #define Burst_SIO_CFG            (* (reg8 *) Burst__SIO_CFG)
    #define Burst_SIO_DIFF           (* (reg8 *) Burst__SIO_DIFF)
#endif /* (Burst__SIO_CFG) */

/* Interrupt Registers */
#if defined(Burst__INTSTAT)
    #define Burst_INTSTAT            (* (reg8 *) Burst__INTSTAT)
    #define Burst_SNAP               (* (reg8 *) Burst__SNAP)
    
	#define Burst_0_INTTYPE_REG 		(* (reg8 *) Burst__0__INTTYPE)
#endif /* (Burst__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Burst_H */


/* [] END OF FILE */
