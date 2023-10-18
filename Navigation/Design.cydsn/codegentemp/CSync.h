/*******************************************************************************
* File Name: CSync.h  
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

#if !defined(CY_PINS_CSync_H) /* Pins CSync_H */
#define CY_PINS_CSync_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CSync_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CSync__PORT == 15 && ((CSync__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    CSync_Write(uint8 value);
void    CSync_SetDriveMode(uint8 mode);
uint8   CSync_ReadDataReg(void);
uint8   CSync_Read(void);
void    CSync_SetInterruptMode(uint16 position, uint16 mode);
uint8   CSync_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the CSync_SetDriveMode() function.
     *  @{
     */
        #define CSync_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define CSync_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define CSync_DM_RES_UP          PIN_DM_RES_UP
        #define CSync_DM_RES_DWN         PIN_DM_RES_DWN
        #define CSync_DM_OD_LO           PIN_DM_OD_LO
        #define CSync_DM_OD_HI           PIN_DM_OD_HI
        #define CSync_DM_STRONG          PIN_DM_STRONG
        #define CSync_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define CSync_MASK               CSync__MASK
#define CSync_SHIFT              CSync__SHIFT
#define CSync_WIDTH              1u

/* Interrupt constants */
#if defined(CSync__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CSync_SetInterruptMode() function.
     *  @{
     */
        #define CSync_INTR_NONE      (uint16)(0x0000u)
        #define CSync_INTR_RISING    (uint16)(0x0001u)
        #define CSync_INTR_FALLING   (uint16)(0x0002u)
        #define CSync_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define CSync_INTR_MASK      (0x01u) 
#endif /* (CSync__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CSync_PS                     (* (reg8 *) CSync__PS)
/* Data Register */
#define CSync_DR                     (* (reg8 *) CSync__DR)
/* Port Number */
#define CSync_PRT_NUM                (* (reg8 *) CSync__PRT) 
/* Connect to Analog Globals */                                                  
#define CSync_AG                     (* (reg8 *) CSync__AG)                       
/* Analog MUX bux enable */
#define CSync_AMUX                   (* (reg8 *) CSync__AMUX) 
/* Bidirectional Enable */                                                        
#define CSync_BIE                    (* (reg8 *) CSync__BIE)
/* Bit-mask for Aliased Register Access */
#define CSync_BIT_MASK               (* (reg8 *) CSync__BIT_MASK)
/* Bypass Enable */
#define CSync_BYP                    (* (reg8 *) CSync__BYP)
/* Port wide control signals */                                                   
#define CSync_CTL                    (* (reg8 *) CSync__CTL)
/* Drive Modes */
#define CSync_DM0                    (* (reg8 *) CSync__DM0) 
#define CSync_DM1                    (* (reg8 *) CSync__DM1)
#define CSync_DM2                    (* (reg8 *) CSync__DM2) 
/* Input Buffer Disable Override */
#define CSync_INP_DIS                (* (reg8 *) CSync__INP_DIS)
/* LCD Common or Segment Drive */
#define CSync_LCD_COM_SEG            (* (reg8 *) CSync__LCD_COM_SEG)
/* Enable Segment LCD */
#define CSync_LCD_EN                 (* (reg8 *) CSync__LCD_EN)
/* Slew Rate Control */
#define CSync_SLW                    (* (reg8 *) CSync__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CSync_PRTDSI__CAPS_SEL       (* (reg8 *) CSync__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CSync_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CSync__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CSync_PRTDSI__OE_SEL0        (* (reg8 *) CSync__PRTDSI__OE_SEL0) 
#define CSync_PRTDSI__OE_SEL1        (* (reg8 *) CSync__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CSync_PRTDSI__OUT_SEL0       (* (reg8 *) CSync__PRTDSI__OUT_SEL0) 
#define CSync_PRTDSI__OUT_SEL1       (* (reg8 *) CSync__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CSync_PRTDSI__SYNC_OUT       (* (reg8 *) CSync__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(CSync__SIO_CFG)
    #define CSync_SIO_HYST_EN        (* (reg8 *) CSync__SIO_HYST_EN)
    #define CSync_SIO_REG_HIFREQ     (* (reg8 *) CSync__SIO_REG_HIFREQ)
    #define CSync_SIO_CFG            (* (reg8 *) CSync__SIO_CFG)
    #define CSync_SIO_DIFF           (* (reg8 *) CSync__SIO_DIFF)
#endif /* (CSync__SIO_CFG) */

/* Interrupt Registers */
#if defined(CSync__INTSTAT)
    #define CSync_INTSTAT            (* (reg8 *) CSync__INTSTAT)
    #define CSync_SNAP               (* (reg8 *) CSync__SNAP)
    
	#define CSync_0_INTTYPE_REG 		(* (reg8 *) CSync__0__INTTYPE)
#endif /* (CSync__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CSync_H */


/* [] END OF FILE */
