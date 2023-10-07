/*******************************************************************************
* File Name: Analog_CMP.c
* Version 2.0
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Analog Comparator User Module.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_COMP_Analog_CMP_H) 
#define CY_COMP_Analog_CMP_H

#include "cytypes.h"
#include "CyLib.h"
#include "cyfitter.h" 


#define Analog_CMP_RECALMODE (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Comp_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*       Type defines
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
   /* uint8 compCRReg; */
}Analog_CMP_backupStruct;

#if (CY_PSOC5A)
    /* Stop API changes for PSoC5A */
    typedef struct
    {
        uint8 compCRReg;
    }   Analog_CMP_LOWPOWER_BACKUP_STRUCT;
#endif /* CY_PSOC5A */

/* component init state */
extern uint8 Analog_CMP_initVar;


/**************************************
*        Function Prototypes 
**************************************/

void    Analog_CMP_Start(void)                  ;
void    Analog_CMP_Stop(void)                   ;
void    Analog_CMP_SetSpeed(uint8 speed)        ;
uint8   Analog_CMP_GetCompare(void)             ;
uint16  Analog_CMP_ZeroCal(void)                ;
void    Analog_CMP_LoadTrim(uint16 trimVal)     ;
void Analog_CMP_Init(void)                      ; 
void Analog_CMP_Enable(void)                    ;
void Analog_CMP_SaveConfig(void)                ;
void Analog_CMP_RestoreConfig(void)             ;
void Analog_CMP_Sleep(void)                     ;
void Analog_CMP_Wakeup(void)                    ;
/* Below APIs are valid only for PSoC3, PSoC5LP silicons.*/
#if (CY_PSOC3 || CY_PSOC5LP) 
    void Analog_CMP_PwrDwnOverrideEnable(void)  ;
    void Analog_CMP_PwrDwnOverrideDisable(void) ;
#endif /* CY_PSOC3 || CY_PSOC5LP */


/**************************************
*           API Constants        
**************************************/

/* Power constants for SetSpeed() function */
#define Analog_CMP_SLOWSPEED   (0x00u)
#define Analog_CMP_HIGHSPEED   (0x01u)
#define Analog_CMP_LOWPOWER    (0x02u)


/**************************************
*           Parameter Defaults        
**************************************/

#define Analog_CMP_DEFAULT_SPEED       (1u) 
#define Analog_CMP_DEFAULT_HYSTERESIS  (1u)
#define Analog_CMP_DEFAULT_POLARITY    (0u)
#define Analog_CMP_DEFAULT_BYPASS_SYNC (1u)
#define Analog_CMP_DEFAULT_PWRDWN_OVRD (0u)


/**************************************
*             Registers        
**************************************/
#define Analog_CMP_CR_REG            (* (reg8 *) Analog_CMP_ctComp__CR )               /* Config register */
#define Analog_CMP_CR_PTR            (  (reg8 *) Analog_CMP_ctComp__CR )
#define Analog_CMP_CLK_REG           (* (reg8 *) Analog_CMP_ctComp__CLK )  /* Comp clock control register */
#define Analog_CMP_CLK_PTR           (  (reg8 *) Analog_CMP_ctComp__CLK )
#define Analog_CMP_SW0_REG           (* (reg8 *) Analog_CMP_ctComp__SW0 )            /* Routing registers */
#define Analog_CMP_SW0_PTR           (  (reg8 *) Analog_CMP_ctComp__SW0 )
#define Analog_CMP_SW2_REG           (* (reg8 *) Analog_CMP_ctComp__SW2 )
#define Analog_CMP_SW2_PTR           (  (reg8 *) Analog_CMP_ctComp__SW2 )
#define Analog_CMP_SW3_REG           (* (reg8 *) Analog_CMP_ctComp__SW3 )
#define Analog_CMP_SW3_PTR           (  (reg8 *) Analog_CMP_ctComp__SW3 )
#define Analog_CMP_SW4_REG           (* (reg8 *) Analog_CMP_ctComp__SW4 )
#define Analog_CMP_SW4_PTR           (  (reg8 *) Analog_CMP_ctComp__SW4 )
#define Analog_CMP_SW6_REG           (* (reg8 *) Analog_CMP_ctComp__SW6 )
#define Analog_CMP_SW6_PTR           (  (reg8 *) Analog_CMP_ctComp__SW6 )

/* Trim registers */
/* PSoC5A */
#if (CY_PSOC5A)
    #define Analog_CMP_TR_REG        (* (reg8 *) Analog_CMP_ctComp__TR )                /* Trim registers */
    #define Analog_CMP_TR_PTR        (  (reg8 *) Analog_CMP_ctComp__TR )
#endif /* CY_PSOC5A */

/* PSoC3, PSoC5LP or later */
#if (CY_PSOC3 || CY_PSOC5LP) 
    #define Analog_CMP_TR0_REG       (* (reg8 *) Analog_CMP_ctComp__TR0 )/* Trim register for P-type load */
    #define Analog_CMP_TR0_PTR       (  (reg8 *) Analog_CMP_ctComp__TR0 ) 
    #define Analog_CMP_TR1_REG       (* (reg8 *) Analog_CMP_ctComp__TR1 )/* Trim register for N-type load */
    #define Analog_CMP_TR1_PTR       (  (reg8 *) Analog_CMP_ctComp__TR1 ) 
#endif /* CY_PSOC3 || CY_PSOC5LP */

#define Analog_CMP_WRK_REG           (* (reg8 *) Analog_CMP_ctComp__WRK )    /* Working register - output */
#define Analog_CMP_WRK_PTR           (  (reg8 *) Analog_CMP_ctComp__WRK )
#define Analog_CMP_PWRMGR_REG        (* (reg8 *) Analog_CMP_ctComp__PM_ACT_CFG )  /* Active Power manager */
#define Analog_CMP_PWRMGR_PTR        (  (reg8 *) Analog_CMP_ctComp__PM_ACT_CFG )
#define Analog_CMP_STBY_PWRMGR_REG   (* (reg8 *) Analog_CMP_ctComp__PM_STBY_CFG )/* Standby Power manager */
#define Analog_CMP_STBY_PWRMGR_PTR   (  (reg8 *) Analog_CMP_ctComp__PM_STBY_CFG )

/*      Trim Locations      */
#define Analog_CMP_ctComp__TRIM__TR0_HS_PTR     ((void CYFAR *) Analog_CMP_ctComp__TRIM__TR0_HS)
#define Analog_CMP_ctComp__TRIM__TR0_HS_REG     CY_GET_XTND_REG8(Analog_CMP_ctComp__TRIM__TR0_HS_PTR)
#if (CY_PSOC3 || CY_PSOC5LP)
    #define Analog_CMP_ctComp__TRIM__TR1_HS_PTR ((void CYFAR *) Analog_CMP_ctComp__TRIM__TR1_HS)
    #define Analog_CMP_ctComp__TRIM__TR1_HS_REG CY_GET_XTND_REG8(Analog_CMP_ctComp__TRIM__TR1_HS_PTR)
#endif /* (CY_PSOC3 || CY_PSOC5LP) */
#define Analog_CMP_ctComp__TRIM__TR0_LS_PTR     ((void CYFAR *) ((uint32)Analog_CMP_ctComp__TRIM__TR0 + 1u))
#define Analog_CMP_ctComp__TRIM__TR0_LS_REG     CY_GET_XTND_REG8(Analog_CMP_ctComp__TRIM__TR0_LS_PTR)
#if (CY_PSOC3 || CY_PSOC5LP)
    #define Analog_CMP_ctComp__TRIM__TR1_LS_PTR ((void CYFAR *) ((uint32)Analog_CMP_ctComp__TRIM__TR1 + 1u))
    #define Analog_CMP_ctComp__TRIM__TR1_LS_REG CY_GET_XTND_REG8(Analog_CMP_ctComp__TRIM__TR1_LS_PTR)
#endif /* CY_PSOC3 || CY_PSOC5LP */


/***************************************
*  Registers definitions
* for backward capability        
***************************************/
#define Analog_CMP_CR                (* (reg8 *) Analog_CMP_ctComp__CR )               /* Config register */
#define Analog_CMP_CLK               (* (reg8 *) Analog_CMP_ctComp__CLK )  /* Comp clock control register */
#define Analog_CMP_SW0               (* (reg8 *) Analog_CMP_ctComp__SW0 )            /* Routing registers */
#define Analog_CMP_SW2               (* (reg8 *) Analog_CMP_ctComp__SW2 )
#define Analog_CMP_SW3               (* (reg8 *) Analog_CMP_ctComp__SW3 )
#define Analog_CMP_SW4               (* (reg8 *) Analog_CMP_ctComp__SW4 )
#define Analog_CMP_SW6               (* (reg8 *) Analog_CMP_ctComp__SW6 )

/* Trim registers */
/* PSoC5A */
#if (CY_PSOC5A)
    #define Analog_CMP_TR            (* (reg8 *) Analog_CMP_ctComp__TR )                /* Trim registers */
#endif /* CY_PSOC5A */

/* PSoC3, PSoC5LP or later */
#if (CY_PSOC3 || CY_PSOC5LP) 
    #define Analog_CMP_TR0           (* (reg8 *) Analog_CMP_ctComp__TR0 )/* Trim register for P-type load */
    #define Analog_CMP_TR1           (* (reg8 *) Analog_CMP_ctComp__TR1 )/* Trim register for N-type load */
#endif /* CY_PSOC3 || CY_PSOC5LP */

#define Analog_CMP_WRK               (* (reg8 *) Analog_CMP_ctComp__WRK )    /* Working register - output */
#define Analog_CMP_PWRMGR            (* (reg8 *) Analog_CMP_ctComp__PM_ACT_CFG )  /* Active Power manager */
#define Analog_CMP_STBY_PWRMGR       (* (reg8 *) Analog_CMP_ctComp__PM_STBY_CFG )/* Standby Power manager */

/*      Trim Locations      */
#define Analog_CMP_HS_TRIM_TR0        CY_GET_XTND_REG8(Analog_CMP_ctComp__TRIM__TR0_HS_PTR)
#if (CY_PSOC3 || CY_PSOC5LP)
    #define Analog_CMP_HS_TRIM_TR1    CY_GET_XTND_REG8(Analog_CMP_ctComp__TRIM__TR1_HS_PTR)
#endif /* (CY_PSOC3 || CY_PSOC5LP) */
#define Analog_CMP_LS_TRIM_TR0        CY_GET_XTND_REG8(Analog_CMP_ctComp__TRIM__TR0_LS_PTR)
#if (CY_PSOC3 || CY_PSOC5LP)
    #define Analog_CMP_LS_TRIM_TR1    CY_GET_XTND_REG8(Analog_CMP_ctComp__TRIM__TR1_LS_PTR)
#endif /* CY_PSOC3 || CY_PSOC5LP */


/**************************************
*       Register Constants        
**************************************/

/* CR (Comp Control Register)             */
#define Analog_CMP_CFG_MODE_MASK      (0x78u)
#define Analog_CMP_FILTER_ON          (0x40u)
#define Analog_CMP_HYST_OFF           (0x20u)
#define Analog_CMP_CAL_ON             (0x10u)
#define Analog_CMP_MX_AO              (0x08u)
#define Analog_CMP_PWRDWN_OVRD        (0x04u)

#define Analog_CMP_PWR_MODE_SHIFT     (0x00u)
#define Analog_CMP_PWR_MODE_MASK      ((uint8)(0x03u << Analog_CMP_PWR_MODE_SHIFT))
#define Analog_CMP_PWR_MODE_SLOW      ((uint8)(0x00u << Analog_CMP_PWR_MODE_SHIFT))
#define Analog_CMP_PWR_MODE_FAST      ((uint8)(0x01u << Analog_CMP_PWR_MODE_SHIFT))
#define Analog_CMP_PWR_MODE_ULOW      ((uint8)(0x02u << Analog_CMP_PWR_MODE_SHIFT))

/* CLK (Comp Clock Control Register)      */
#define Analog_CMP_BYPASS_SYNC        (0x10u)
#define Analog_CMP_SYNC_CLK_EN        (0x08u)
#define Analog_CMP_SYNCCLK_MASK       (Analog_CMP_BYPASS_SYNC | Analog_CMP_SYNC_CLK_EN)

/* SW3 Routing Register definitions */
#define Analog_CMP_CMP_SW3_INPCTL_MASK (0x09u)   /* SW3 bits for inP routing control */

/* TR (Comp Trim Register)     */
#define Analog_CMP_DEFAULT_CMP_TRIM    (0x00u)

/* PSoC5A */
#if (CY_PSOC5A)
    #define Analog_CMP_CMP_TRIM1_DIR   (0x08u)   /* Trim direction for N-type load for offset calibration */
    #define Analog_CMP_CMP_TRIM1_MASK  (0x07u)   /* Trim for N-type load for offset calibration */
    #define Analog_CMP_CMP_TRIM2_DIR   (0x80u)   /* Trim direction for P-type load for offset calibration */
    #define Analog_CMP_CMP_TRIM2_MASK  (0x70u)   /* Trim for P-type load for offset calibration */
#endif /* CY_PSOC5A */

/* PSoC3, PSoC5LP or later */
#if (CY_PSOC3 || CY_PSOC5LP)
    #define Analog_CMP_CMP_TR0_DIR     (0x10u)   /* Trim direction for N-type load for offset calibration */
    #define Analog_CMP_CMP_TR0_MASK    (0x0Fu)   /* Trim for N-type load for offset calibration */
    #define Analog_CMP_CMP_TR1_DIR     (0x10u)   /* Trim direction for P-type load for offset calibration */
    #define Analog_CMP_CMP_TR1_MASK    (0x07u)   /* Trim for P-type load for offset calibration */ 
#endif /* CY_PSOC3 || CY_PSOC5LP */


/* WRK (Comp output working register)     */ 
#define Analog_CMP_CMP_OUT_MASK       Analog_CMP_ctComp__WRK_MASK /* Specific comparator out mask */

/* PM_ACT_CFG7 (Active Power Mode CFG Register)     */ 
#define Analog_CMP_ACT_PWR_EN         Analog_CMP_ctComp__PM_ACT_MSK /* Power enable mask */

/* PM_STBY_CFG7 (Standby Power Mode CFG Register)     */ 
#define Analog_CMP_STBY_PWR_EN        Analog_CMP_ctComp__PM_STBY_MSK /* Standby Power enable mask */

#if (CY_PSOC5A)
    /* For stop API changes mask to make the COMP register CR to 0X00  */
    #define Analog_CMP_COMP_REG_CLR   (0x00u)
#endif /* CY_PSOC5A */

#endif /* CY_COMP_Analog_CMP_H */


/* [] END OF FILE */
