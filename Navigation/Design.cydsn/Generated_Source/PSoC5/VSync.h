/*******************************************************************************
* File Name: VSync.h  
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

#if !defined(CY_PINS_VSync_H) /* Pins VSync_H */
#define CY_PINS_VSync_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VSync_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 VSync__PORT == 15 && ((VSync__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    VSync_Write(uint8 value);
void    VSync_SetDriveMode(uint8 mode);
uint8   VSync_ReadDataReg(void);
uint8   VSync_Read(void);
void    VSync_SetInterruptMode(uint16 position, uint16 mode);
uint8   VSync_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the VSync_SetDriveMode() function.
     *  @{
     */
        #define VSync_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define VSync_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define VSync_DM_RES_UP          PIN_DM_RES_UP
        #define VSync_DM_RES_DWN         PIN_DM_RES_DWN
        #define VSync_DM_OD_LO           PIN_DM_OD_LO
        #define VSync_DM_OD_HI           PIN_DM_OD_HI
        #define VSync_DM_STRONG          PIN_DM_STRONG
        #define VSync_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define VSync_MASK               VSync__MASK
#define VSync_SHIFT              VSync__SHIFT
#define VSync_WIDTH              1u

/* Interrupt constants */
#if defined(VSync__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VSync_SetInterruptMode() function.
     *  @{
     */
        #define VSync_INTR_NONE      (uint16)(0x0000u)
        #define VSync_INTR_RISING    (uint16)(0x0001u)
        #define VSync_INTR_FALLING   (uint16)(0x0002u)
        #define VSync_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define VSync_INTR_MASK      (0x01u) 
#endif /* (VSync__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VSync_PS                     (* (reg8 *) VSync__PS)
/* Data Register */
#define VSync_DR                     (* (reg8 *) VSync__DR)
/* Port Number */
#define VSync_PRT_NUM                (* (reg8 *) VSync__PRT) 
/* Connect to Analog Globals */                                                  
#define VSync_AG                     (* (reg8 *) VSync__AG)                       
/* Analog MUX bux enable */
#define VSync_AMUX                   (* (reg8 *) VSync__AMUX) 
/* Bidirectional Enable */                                                        
#define VSync_BIE                    (* (reg8 *) VSync__BIE)
/* Bit-mask for Aliased Register Access */
#define VSync_BIT_MASK               (* (reg8 *) VSync__BIT_MASK)
/* Bypass Enable */
#define VSync_BYP                    (* (reg8 *) VSync__BYP)
/* Port wide control signals */                                                   
#define VSync_CTL                    (* (reg8 *) VSync__CTL)
/* Drive Modes */
#define VSync_DM0                    (* (reg8 *) VSync__DM0) 
#define VSync_DM1                    (* (reg8 *) VSync__DM1)
#define VSync_DM2                    (* (reg8 *) VSync__DM2) 
/* Input Buffer Disable Override */
#define VSync_INP_DIS                (* (reg8 *) VSync__INP_DIS)
/* LCD Common or Segment Drive */
#define VSync_LCD_COM_SEG            (* (reg8 *) VSync__LCD_COM_SEG)
/* Enable Segment LCD */
#define VSync_LCD_EN                 (* (reg8 *) VSync__LCD_EN)
/* Slew Rate Control */
#define VSync_SLW                    (* (reg8 *) VSync__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VSync_PRTDSI__CAPS_SEL       (* (reg8 *) VSync__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VSync_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VSync__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VSync_PRTDSI__OE_SEL0        (* (reg8 *) VSync__PRTDSI__OE_SEL0) 
#define VSync_PRTDSI__OE_SEL1        (* (reg8 *) VSync__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VSync_PRTDSI__OUT_SEL0       (* (reg8 *) VSync__PRTDSI__OUT_SEL0) 
#define VSync_PRTDSI__OUT_SEL1       (* (reg8 *) VSync__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VSync_PRTDSI__SYNC_OUT       (* (reg8 *) VSync__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(VSync__SIO_CFG)
    #define VSync_SIO_HYST_EN        (* (reg8 *) VSync__SIO_HYST_EN)
    #define VSync_SIO_REG_HIFREQ     (* (reg8 *) VSync__SIO_REG_HIFREQ)
    #define VSync_SIO_CFG            (* (reg8 *) VSync__SIO_CFG)
    #define VSync_SIO_DIFF           (* (reg8 *) VSync__SIO_DIFF)
#endif /* (VSync__SIO_CFG) */

/* Interrupt Registers */
#if defined(VSync__INTSTAT)
    #define VSync_INTSTAT            (* (reg8 *) VSync__INTSTAT)
    #define VSync_SNAP               (* (reg8 *) VSync__SNAP)
    
	#define VSync_0_INTTYPE_REG 		(* (reg8 *) VSync__0__INTTYPE)
#endif /* (VSync__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_VSync_H */


/* [] END OF FILE */
