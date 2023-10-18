/*******************************************************************************
* File Name: Video.h  
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

#if !defined(CY_PINS_Video_H) /* Pins Video_H */
#define CY_PINS_Video_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Video_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Video__PORT == 15 && ((Video__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Video_Write(uint8 value);
void    Video_SetDriveMode(uint8 mode);
uint8   Video_ReadDataReg(void);
uint8   Video_Read(void);
void    Video_SetInterruptMode(uint16 position, uint16 mode);
uint8   Video_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Video_SetDriveMode() function.
     *  @{
     */
        #define Video_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Video_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Video_DM_RES_UP          PIN_DM_RES_UP
        #define Video_DM_RES_DWN         PIN_DM_RES_DWN
        #define Video_DM_OD_LO           PIN_DM_OD_LO
        #define Video_DM_OD_HI           PIN_DM_OD_HI
        #define Video_DM_STRONG          PIN_DM_STRONG
        #define Video_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Video_MASK               Video__MASK
#define Video_SHIFT              Video__SHIFT
#define Video_WIDTH              1u

/* Interrupt constants */
#if defined(Video__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Video_SetInterruptMode() function.
     *  @{
     */
        #define Video_INTR_NONE      (uint16)(0x0000u)
        #define Video_INTR_RISING    (uint16)(0x0001u)
        #define Video_INTR_FALLING   (uint16)(0x0002u)
        #define Video_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Video_INTR_MASK      (0x01u) 
#endif /* (Video__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Video_PS                     (* (reg8 *) Video__PS)
/* Data Register */
#define Video_DR                     (* (reg8 *) Video__DR)
/* Port Number */
#define Video_PRT_NUM                (* (reg8 *) Video__PRT) 
/* Connect to Analog Globals */                                                  
#define Video_AG                     (* (reg8 *) Video__AG)                       
/* Analog MUX bux enable */
#define Video_AMUX                   (* (reg8 *) Video__AMUX) 
/* Bidirectional Enable */                                                        
#define Video_BIE                    (* (reg8 *) Video__BIE)
/* Bit-mask for Aliased Register Access */
#define Video_BIT_MASK               (* (reg8 *) Video__BIT_MASK)
/* Bypass Enable */
#define Video_BYP                    (* (reg8 *) Video__BYP)
/* Port wide control signals */                                                   
#define Video_CTL                    (* (reg8 *) Video__CTL)
/* Drive Modes */
#define Video_DM0                    (* (reg8 *) Video__DM0) 
#define Video_DM1                    (* (reg8 *) Video__DM1)
#define Video_DM2                    (* (reg8 *) Video__DM2) 
/* Input Buffer Disable Override */
#define Video_INP_DIS                (* (reg8 *) Video__INP_DIS)
/* LCD Common or Segment Drive */
#define Video_LCD_COM_SEG            (* (reg8 *) Video__LCD_COM_SEG)
/* Enable Segment LCD */
#define Video_LCD_EN                 (* (reg8 *) Video__LCD_EN)
/* Slew Rate Control */
#define Video_SLW                    (* (reg8 *) Video__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Video_PRTDSI__CAPS_SEL       (* (reg8 *) Video__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Video_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Video__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Video_PRTDSI__OE_SEL0        (* (reg8 *) Video__PRTDSI__OE_SEL0) 
#define Video_PRTDSI__OE_SEL1        (* (reg8 *) Video__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Video_PRTDSI__OUT_SEL0       (* (reg8 *) Video__PRTDSI__OUT_SEL0) 
#define Video_PRTDSI__OUT_SEL1       (* (reg8 *) Video__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Video_PRTDSI__SYNC_OUT       (* (reg8 *) Video__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Video__SIO_CFG)
    #define Video_SIO_HYST_EN        (* (reg8 *) Video__SIO_HYST_EN)
    #define Video_SIO_REG_HIFREQ     (* (reg8 *) Video__SIO_REG_HIFREQ)
    #define Video_SIO_CFG            (* (reg8 *) Video__SIO_CFG)
    #define Video_SIO_DIFF           (* (reg8 *) Video__SIO_DIFF)
#endif /* (Video__SIO_CFG) */

/* Interrupt Registers */
#if defined(Video__INTSTAT)
    #define Video_INTSTAT            (* (reg8 *) Video__INTSTAT)
    #define Video_SNAP               (* (reg8 *) Video__SNAP)
    
	#define Video_0_INTTYPE_REG 		(* (reg8 *) Video__0__INTTYPE)
#endif /* (Video__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Video_H */


/* [] END OF FILE */
