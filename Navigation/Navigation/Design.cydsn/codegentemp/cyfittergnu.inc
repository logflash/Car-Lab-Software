/*******************************************************************************
* File Name: cyfittergnu.inc
* 
* PSoC Creator  4.4
*
* Description:
* 
* This file is automatically generated by PSoC Creator.
*
********************************************************************************
* Copyright (c) 2007-2020 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

.ifndef INCLUDED_CYFITTERGNU_INC
.set INCLUDED_CYFITTERGNU_INC, 1
.include "cydevicegnu.inc"
.include "cydevicegnu_trm.inc"

/* LCD */
.set LCD_LCDPort__0__INTTYPE, CYREG_PICU2_INTTYPE0
.set LCD_LCDPort__0__MASK, 0x01
.set LCD_LCDPort__0__PC, CYREG_PRT2_PC0
.set LCD_LCDPort__0__PORT, 2
.set LCD_LCDPort__0__SHIFT, 0
.set LCD_LCDPort__1__INTTYPE, CYREG_PICU2_INTTYPE1
.set LCD_LCDPort__1__MASK, 0x02
.set LCD_LCDPort__1__PC, CYREG_PRT2_PC1
.set LCD_LCDPort__1__PORT, 2
.set LCD_LCDPort__1__SHIFT, 1
.set LCD_LCDPort__2__INTTYPE, CYREG_PICU2_INTTYPE2
.set LCD_LCDPort__2__MASK, 0x04
.set LCD_LCDPort__2__PC, CYREG_PRT2_PC2
.set LCD_LCDPort__2__PORT, 2
.set LCD_LCDPort__2__SHIFT, 2
.set LCD_LCDPort__3__INTTYPE, CYREG_PICU2_INTTYPE3
.set LCD_LCDPort__3__MASK, 0x08
.set LCD_LCDPort__3__PC, CYREG_PRT2_PC3
.set LCD_LCDPort__3__PORT, 2
.set LCD_LCDPort__3__SHIFT, 3
.set LCD_LCDPort__4__INTTYPE, CYREG_PICU2_INTTYPE4
.set LCD_LCDPort__4__MASK, 0x10
.set LCD_LCDPort__4__PC, CYREG_PRT2_PC4
.set LCD_LCDPort__4__PORT, 2
.set LCD_LCDPort__4__SHIFT, 4
.set LCD_LCDPort__5__INTTYPE, CYREG_PICU2_INTTYPE5
.set LCD_LCDPort__5__MASK, 0x20
.set LCD_LCDPort__5__PC, CYREG_PRT2_PC5
.set LCD_LCDPort__5__PORT, 2
.set LCD_LCDPort__5__SHIFT, 5
.set LCD_LCDPort__6__INTTYPE, CYREG_PICU2_INTTYPE6
.set LCD_LCDPort__6__MASK, 0x40
.set LCD_LCDPort__6__PC, CYREG_PRT2_PC6
.set LCD_LCDPort__6__PORT, 2
.set LCD_LCDPort__6__SHIFT, 6
.set LCD_LCDPort__AG, CYREG_PRT2_AG
.set LCD_LCDPort__AMUX, CYREG_PRT2_AMUX
.set LCD_LCDPort__BIE, CYREG_PRT2_BIE
.set LCD_LCDPort__BIT_MASK, CYREG_PRT2_BIT_MASK
.set LCD_LCDPort__BYP, CYREG_PRT2_BYP
.set LCD_LCDPort__CTL, CYREG_PRT2_CTL
.set LCD_LCDPort__DM0, CYREG_PRT2_DM0
.set LCD_LCDPort__DM1, CYREG_PRT2_DM1
.set LCD_LCDPort__DM2, CYREG_PRT2_DM2
.set LCD_LCDPort__DR, CYREG_PRT2_DR
.set LCD_LCDPort__INP_DIS, CYREG_PRT2_INP_DIS
.set LCD_LCDPort__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU2_BASE
.set LCD_LCDPort__LCD_COM_SEG, CYREG_PRT2_LCD_COM_SEG
.set LCD_LCDPort__LCD_EN, CYREG_PRT2_LCD_EN
.set LCD_LCDPort__MASK, 0x7F
.set LCD_LCDPort__PORT, 2
.set LCD_LCDPort__PRT, CYREG_PRT2_PRT
.set LCD_LCDPort__PRTDSI__CAPS_SEL, CYREG_PRT2_CAPS_SEL
.set LCD_LCDPort__PRTDSI__DBL_SYNC_IN, CYREG_PRT2_DBL_SYNC_IN
.set LCD_LCDPort__PRTDSI__OE_SEL0, CYREG_PRT2_OE_SEL0
.set LCD_LCDPort__PRTDSI__OE_SEL1, CYREG_PRT2_OE_SEL1
.set LCD_LCDPort__PRTDSI__OUT_SEL0, CYREG_PRT2_OUT_SEL0
.set LCD_LCDPort__PRTDSI__OUT_SEL1, CYREG_PRT2_OUT_SEL1
.set LCD_LCDPort__PRTDSI__SYNC_OUT, CYREG_PRT2_SYNC_OUT
.set LCD_LCDPort__PS, CYREG_PRT2_PS
.set LCD_LCDPort__SHIFT, 0
.set LCD_LCDPort__SLW, CYREG_PRT2_SLW

/* Rx_1 */
.set Rx_1__0__INTTYPE, CYREG_PICU6_INTTYPE6
.set Rx_1__0__MASK, 0x40
.set Rx_1__0__PC, CYREG_PRT6_PC6
.set Rx_1__0__PORT, 6
.set Rx_1__0__SHIFT, 6
.set Rx_1__AG, CYREG_PRT6_AG
.set Rx_1__AMUX, CYREG_PRT6_AMUX
.set Rx_1__BIE, CYREG_PRT6_BIE
.set Rx_1__BIT_MASK, CYREG_PRT6_BIT_MASK
.set Rx_1__BYP, CYREG_PRT6_BYP
.set Rx_1__CTL, CYREG_PRT6_CTL
.set Rx_1__DM0, CYREG_PRT6_DM0
.set Rx_1__DM1, CYREG_PRT6_DM1
.set Rx_1__DM2, CYREG_PRT6_DM2
.set Rx_1__DR, CYREG_PRT6_DR
.set Rx_1__INP_DIS, CYREG_PRT6_INP_DIS
.set Rx_1__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU6_BASE
.set Rx_1__LCD_COM_SEG, CYREG_PRT6_LCD_COM_SEG
.set Rx_1__LCD_EN, CYREG_PRT6_LCD_EN
.set Rx_1__MASK, 0x40
.set Rx_1__PORT, 6
.set Rx_1__PRT, CYREG_PRT6_PRT
.set Rx_1__PRTDSI__CAPS_SEL, CYREG_PRT6_CAPS_SEL
.set Rx_1__PRTDSI__DBL_SYNC_IN, CYREG_PRT6_DBL_SYNC_IN
.set Rx_1__PRTDSI__OE_SEL0, CYREG_PRT6_OE_SEL0
.set Rx_1__PRTDSI__OE_SEL1, CYREG_PRT6_OE_SEL1
.set Rx_1__PRTDSI__OUT_SEL0, CYREG_PRT6_OUT_SEL0
.set Rx_1__PRTDSI__OUT_SEL1, CYREG_PRT6_OUT_SEL1
.set Rx_1__PRTDSI__SYNC_OUT, CYREG_PRT6_SYNC_OUT
.set Rx_1__PS, CYREG_PRT6_PS
.set Rx_1__SHIFT, 6
.set Rx_1__SLW, CYREG_PRT6_SLW

/* Tx_1 */
.set Tx_1__0__INTTYPE, CYREG_PICU6_INTTYPE0
.set Tx_1__0__MASK, 0x01
.set Tx_1__0__PC, CYREG_PRT6_PC0
.set Tx_1__0__PORT, 6
.set Tx_1__0__SHIFT, 0
.set Tx_1__AG, CYREG_PRT6_AG
.set Tx_1__AMUX, CYREG_PRT6_AMUX
.set Tx_1__BIE, CYREG_PRT6_BIE
.set Tx_1__BIT_MASK, CYREG_PRT6_BIT_MASK
.set Tx_1__BYP, CYREG_PRT6_BYP
.set Tx_1__CTL, CYREG_PRT6_CTL
.set Tx_1__DM0, CYREG_PRT6_DM0
.set Tx_1__DM1, CYREG_PRT6_DM1
.set Tx_1__DM2, CYREG_PRT6_DM2
.set Tx_1__DR, CYREG_PRT6_DR
.set Tx_1__INP_DIS, CYREG_PRT6_INP_DIS
.set Tx_1__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU6_BASE
.set Tx_1__LCD_COM_SEG, CYREG_PRT6_LCD_COM_SEG
.set Tx_1__LCD_EN, CYREG_PRT6_LCD_EN
.set Tx_1__MASK, 0x01
.set Tx_1__PORT, 6
.set Tx_1__PRT, CYREG_PRT6_PRT
.set Tx_1__PRTDSI__CAPS_SEL, CYREG_PRT6_CAPS_SEL
.set Tx_1__PRTDSI__DBL_SYNC_IN, CYREG_PRT6_DBL_SYNC_IN
.set Tx_1__PRTDSI__OE_SEL0, CYREG_PRT6_OE_SEL0
.set Tx_1__PRTDSI__OE_SEL1, CYREG_PRT6_OE_SEL1
.set Tx_1__PRTDSI__OUT_SEL0, CYREG_PRT6_OUT_SEL0
.set Tx_1__PRTDSI__OUT_SEL1, CYREG_PRT6_OUT_SEL1
.set Tx_1__PRTDSI__SYNC_OUT, CYREG_PRT6_SYNC_OUT
.set Tx_1__PS, CYREG_PRT6_PS
.set Tx_1__SHIFT, 0
.set Tx_1__SLW, CYREG_PRT6_SLW

/* XBee */
.set XBee_BUART_sRX_RxBitCounter__16BIT_CONTROL_AUX_CTL_REG, CYREG_B1_UDB07_08_ACTL
.set XBee_BUART_sRX_RxBitCounter__16BIT_CONTROL_CONTROL_REG, CYREG_B1_UDB07_08_CTL
.set XBee_BUART_sRX_RxBitCounter__16BIT_CONTROL_COUNT_REG, CYREG_B1_UDB07_08_CTL
.set XBee_BUART_sRX_RxBitCounter__16BIT_COUNT_CONTROL_REG, CYREG_B1_UDB07_08_CTL
.set XBee_BUART_sRX_RxBitCounter__16BIT_COUNT_COUNT_REG, CYREG_B1_UDB07_08_CTL
.set XBee_BUART_sRX_RxBitCounter__16BIT_MASK_MASK_REG, CYREG_B1_UDB07_08_MSK
.set XBee_BUART_sRX_RxBitCounter__16BIT_MASK_PERIOD_REG, CYREG_B1_UDB07_08_MSK
.set XBee_BUART_sRX_RxBitCounter__16BIT_PERIOD_MASK_REG, CYREG_B1_UDB07_08_MSK
.set XBee_BUART_sRX_RxBitCounter__16BIT_PERIOD_PERIOD_REG, CYREG_B1_UDB07_08_MSK
.set XBee_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG, CYREG_B1_UDB07_ACTL
.set XBee_BUART_sRX_RxBitCounter__CONTROL_REG, CYREG_B1_UDB07_CTL
.set XBee_BUART_sRX_RxBitCounter__CONTROL_ST_REG, CYREG_B1_UDB07_ST_CTL
.set XBee_BUART_sRX_RxBitCounter__COUNT_REG, CYREG_B1_UDB07_CTL
.set XBee_BUART_sRX_RxBitCounter__COUNT_ST_REG, CYREG_B1_UDB07_ST_CTL
.set XBee_BUART_sRX_RxBitCounter__MASK_CTL_AUX_CTL_REG, CYREG_B1_UDB07_MSK_ACTL
.set XBee_BUART_sRX_RxBitCounter__PER_CTL_AUX_CTL_REG, CYREG_B1_UDB07_MSK_ACTL
.set XBee_BUART_sRX_RxBitCounter__PERIOD_REG, CYREG_B1_UDB07_MSK
.set XBee_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_AUX_CTL_REG, CYREG_B1_UDB07_08_ACTL
.set XBee_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_REG, CYREG_B1_UDB07_08_ST
.set XBee_BUART_sRX_RxBitCounter_ST__MASK_REG, CYREG_B1_UDB07_MSK
.set XBee_BUART_sRX_RxBitCounter_ST__MASK_ST_AUX_CTL_REG, CYREG_B1_UDB07_MSK_ACTL
.set XBee_BUART_sRX_RxBitCounter_ST__PER_ST_AUX_CTL_REG, CYREG_B1_UDB07_MSK_ACTL
.set XBee_BUART_sRX_RxBitCounter_ST__STATUS_AUX_CTL_REG, CYREG_B1_UDB07_ACTL
.set XBee_BUART_sRX_RxBitCounter_ST__STATUS_CNT_REG, CYREG_B1_UDB07_ST_CTL
.set XBee_BUART_sRX_RxBitCounter_ST__STATUS_CONTROL_REG, CYREG_B1_UDB07_ST_CTL
.set XBee_BUART_sRX_RxBitCounter_ST__STATUS_REG, CYREG_B1_UDB07_ST
.set XBee_BUART_sRX_RxShifter_u0__16BIT_A0_REG, CYREG_B0_UDB03_04_A0
.set XBee_BUART_sRX_RxShifter_u0__16BIT_A1_REG, CYREG_B0_UDB03_04_A1
.set XBee_BUART_sRX_RxShifter_u0__16BIT_D0_REG, CYREG_B0_UDB03_04_D0
.set XBee_BUART_sRX_RxShifter_u0__16BIT_D1_REG, CYREG_B0_UDB03_04_D1
.set XBee_BUART_sRX_RxShifter_u0__16BIT_DP_AUX_CTL_REG, CYREG_B0_UDB03_04_ACTL
.set XBee_BUART_sRX_RxShifter_u0__16BIT_F0_REG, CYREG_B0_UDB03_04_F0
.set XBee_BUART_sRX_RxShifter_u0__16BIT_F1_REG, CYREG_B0_UDB03_04_F1
.set XBee_BUART_sRX_RxShifter_u0__A0_A1_REG, CYREG_B0_UDB03_A0_A1
.set XBee_BUART_sRX_RxShifter_u0__A0_REG, CYREG_B0_UDB03_A0
.set XBee_BUART_sRX_RxShifter_u0__A1_REG, CYREG_B0_UDB03_A1
.set XBee_BUART_sRX_RxShifter_u0__D0_D1_REG, CYREG_B0_UDB03_D0_D1
.set XBee_BUART_sRX_RxShifter_u0__D0_REG, CYREG_B0_UDB03_D0
.set XBee_BUART_sRX_RxShifter_u0__D1_REG, CYREG_B0_UDB03_D1
.set XBee_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG, CYREG_B0_UDB03_ACTL
.set XBee_BUART_sRX_RxShifter_u0__F0_F1_REG, CYREG_B0_UDB03_F0_F1
.set XBee_BUART_sRX_RxShifter_u0__F0_REG, CYREG_B0_UDB03_F0
.set XBee_BUART_sRX_RxShifter_u0__F1_REG, CYREG_B0_UDB03_F1
.set XBee_BUART_sRX_RxShifter_u0__MSK_DP_AUX_CTL_REG, CYREG_B0_UDB03_MSK_ACTL
.set XBee_BUART_sRX_RxShifter_u0__PER_DP_AUX_CTL_REG, CYREG_B0_UDB03_MSK_ACTL
.set XBee_BUART_sRX_RxSts__16BIT_STATUS_AUX_CTL_REG, CYREG_B0_UDB07_08_ACTL
.set XBee_BUART_sRX_RxSts__16BIT_STATUS_REG, CYREG_B0_UDB07_08_ST
.set XBee_BUART_sRX_RxSts__3__MASK, 0x08
.set XBee_BUART_sRX_RxSts__3__POS, 3
.set XBee_BUART_sRX_RxSts__4__MASK, 0x10
.set XBee_BUART_sRX_RxSts__4__POS, 4
.set XBee_BUART_sRX_RxSts__5__MASK, 0x20
.set XBee_BUART_sRX_RxSts__5__POS, 5
.set XBee_BUART_sRX_RxSts__MASK, 0x38
.set XBee_BUART_sRX_RxSts__MASK_REG, CYREG_B0_UDB07_MSK
.set XBee_BUART_sRX_RxSts__STATUS_AUX_CTL_REG, CYREG_B0_UDB07_ACTL
.set XBee_BUART_sRX_RxSts__STATUS_REG, CYREG_B0_UDB07_ST
.set XBee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A0_REG, CYREG_B0_UDB00_01_A0
.set XBee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A1_REG, CYREG_B0_UDB00_01_A1
.set XBee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D0_REG, CYREG_B0_UDB00_01_D0
.set XBee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D1_REG, CYREG_B0_UDB00_01_D1
.set XBee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_DP_AUX_CTL_REG, CYREG_B0_UDB00_01_ACTL
.set XBee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F0_REG, CYREG_B0_UDB00_01_F0
.set XBee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F1_REG, CYREG_B0_UDB00_01_F1
.set XBee_BUART_sTX_sCLOCK_TxBitClkGen__A0_A1_REG, CYREG_B0_UDB00_A0_A1
.set XBee_BUART_sTX_sCLOCK_TxBitClkGen__A0_REG, CYREG_B0_UDB00_A0
.set XBee_BUART_sTX_sCLOCK_TxBitClkGen__A1_REG, CYREG_B0_UDB00_A1
.set XBee_BUART_sTX_sCLOCK_TxBitClkGen__D0_D1_REG, CYREG_B0_UDB00_D0_D1
.set XBee_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG, CYREG_B0_UDB00_D0
.set XBee_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG, CYREG_B0_UDB00_D1
.set XBee_BUART_sTX_sCLOCK_TxBitClkGen__DP_AUX_CTL_REG, CYREG_B0_UDB00_ACTL
.set XBee_BUART_sTX_sCLOCK_TxBitClkGen__F0_F1_REG, CYREG_B0_UDB00_F0_F1
.set XBee_BUART_sTX_sCLOCK_TxBitClkGen__F0_REG, CYREG_B0_UDB00_F0
.set XBee_BUART_sTX_sCLOCK_TxBitClkGen__F1_REG, CYREG_B0_UDB00_F1
.set XBee_BUART_sTX_TxShifter_u0__16BIT_A0_REG, CYREG_B1_UDB07_08_A0
.set XBee_BUART_sTX_TxShifter_u0__16BIT_A1_REG, CYREG_B1_UDB07_08_A1
.set XBee_BUART_sTX_TxShifter_u0__16BIT_D0_REG, CYREG_B1_UDB07_08_D0
.set XBee_BUART_sTX_TxShifter_u0__16BIT_D1_REG, CYREG_B1_UDB07_08_D1
.set XBee_BUART_sTX_TxShifter_u0__16BIT_DP_AUX_CTL_REG, CYREG_B1_UDB07_08_ACTL
.set XBee_BUART_sTX_TxShifter_u0__16BIT_F0_REG, CYREG_B1_UDB07_08_F0
.set XBee_BUART_sTX_TxShifter_u0__16BIT_F1_REG, CYREG_B1_UDB07_08_F1
.set XBee_BUART_sTX_TxShifter_u0__A0_A1_REG, CYREG_B1_UDB07_A0_A1
.set XBee_BUART_sTX_TxShifter_u0__A0_REG, CYREG_B1_UDB07_A0
.set XBee_BUART_sTX_TxShifter_u0__A1_REG, CYREG_B1_UDB07_A1
.set XBee_BUART_sTX_TxShifter_u0__D0_D1_REG, CYREG_B1_UDB07_D0_D1
.set XBee_BUART_sTX_TxShifter_u0__D0_REG, CYREG_B1_UDB07_D0
.set XBee_BUART_sTX_TxShifter_u0__D1_REG, CYREG_B1_UDB07_D1
.set XBee_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG, CYREG_B1_UDB07_ACTL
.set XBee_BUART_sTX_TxShifter_u0__F0_F1_REG, CYREG_B1_UDB07_F0_F1
.set XBee_BUART_sTX_TxShifter_u0__F0_REG, CYREG_B1_UDB07_F0
.set XBee_BUART_sTX_TxShifter_u0__F1_REG, CYREG_B1_UDB07_F1
.set XBee_BUART_sTX_TxShifter_u0__MSK_DP_AUX_CTL_REG, CYREG_B1_UDB07_MSK_ACTL
.set XBee_BUART_sTX_TxShifter_u0__PER_DP_AUX_CTL_REG, CYREG_B1_UDB07_MSK_ACTL
.set XBee_BUART_sTX_TxSts__0__MASK, 0x01
.set XBee_BUART_sTX_TxSts__0__POS, 0
.set XBee_BUART_sTX_TxSts__1__MASK, 0x02
.set XBee_BUART_sTX_TxSts__1__POS, 1
.set XBee_BUART_sTX_TxSts__16BIT_STATUS_AUX_CTL_REG, CYREG_B0_UDB04_05_ACTL
.set XBee_BUART_sTX_TxSts__16BIT_STATUS_REG, CYREG_B0_UDB04_05_ST
.set XBee_BUART_sTX_TxSts__2__MASK, 0x04
.set XBee_BUART_sTX_TxSts__2__POS, 2
.set XBee_BUART_sTX_TxSts__3__MASK, 0x08
.set XBee_BUART_sTX_TxSts__3__POS, 3
.set XBee_BUART_sTX_TxSts__MASK, 0x0F
.set XBee_BUART_sTX_TxSts__MASK_REG, CYREG_B0_UDB04_MSK
.set XBee_BUART_sTX_TxSts__STATUS_AUX_CTL_REG, CYREG_B0_UDB04_ACTL
.set XBee_BUART_sTX_TxSts__STATUS_REG, CYREG_B0_UDB04_ST
.set XBee_IntClock__CFG0, CYREG_CLKDIST_DCFG1_CFG0
.set XBee_IntClock__CFG1, CYREG_CLKDIST_DCFG1_CFG1
.set XBee_IntClock__CFG2, CYREG_CLKDIST_DCFG1_CFG2
.set XBee_IntClock__CFG2_SRC_SEL_MASK, 0x07
.set XBee_IntClock__INDEX, 0x01
.set XBee_IntClock__PM_ACT_CFG, CYREG_PM_ACT_CFG2
.set XBee_IntClock__PM_ACT_MSK, 0x02
.set XBee_IntClock__PM_STBY_CFG, CYREG_PM_STBY_CFG2
.set XBee_IntClock__PM_STBY_MSK, 0x02

/* CSync */
.set CSync__0__INTTYPE, CYREG_PICU0_INTTYPE6
.set CSync__0__MASK, 0x40
.set CSync__0__PC, CYREG_PRT0_PC6
.set CSync__0__PORT, 0
.set CSync__0__SHIFT, 6
.set CSync__AG, CYREG_PRT0_AG
.set CSync__AMUX, CYREG_PRT0_AMUX
.set CSync__BIE, CYREG_PRT0_BIE
.set CSync__BIT_MASK, CYREG_PRT0_BIT_MASK
.set CSync__BYP, CYREG_PRT0_BYP
.set CSync__CTL, CYREG_PRT0_CTL
.set CSync__DM0, CYREG_PRT0_DM0
.set CSync__DM1, CYREG_PRT0_DM1
.set CSync__DM2, CYREG_PRT0_DM2
.set CSync__DR, CYREG_PRT0_DR
.set CSync__INP_DIS, CYREG_PRT0_INP_DIS
.set CSync__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU0_BASE
.set CSync__LCD_COM_SEG, CYREG_PRT0_LCD_COM_SEG
.set CSync__LCD_EN, CYREG_PRT0_LCD_EN
.set CSync__MASK, 0x40
.set CSync__PORT, 0
.set CSync__PRT, CYREG_PRT0_PRT
.set CSync__PRTDSI__CAPS_SEL, CYREG_PRT0_CAPS_SEL
.set CSync__PRTDSI__DBL_SYNC_IN, CYREG_PRT0_DBL_SYNC_IN
.set CSync__PRTDSI__OE_SEL0, CYREG_PRT0_OE_SEL0
.set CSync__PRTDSI__OE_SEL1, CYREG_PRT0_OE_SEL1
.set CSync__PRTDSI__OUT_SEL0, CYREG_PRT0_OUT_SEL0
.set CSync__PRTDSI__OUT_SEL1, CYREG_PRT0_OUT_SEL1
.set CSync__PRTDSI__SYNC_OUT, CYREG_PRT0_SYNC_OUT
.set CSync__PS, CYREG_PRT0_PS
.set CSync__SHIFT, 6
.set CSync__SLW, CYREG_PRT0_SLW

/* VSync */
.set VSync__0__INTTYPE, CYREG_PICU0_INTTYPE4
.set VSync__0__MASK, 0x10
.set VSync__0__PC, CYREG_PRT0_PC4
.set VSync__0__PORT, 0
.set VSync__0__SHIFT, 4
.set VSync__AG, CYREG_PRT0_AG
.set VSync__AMUX, CYREG_PRT0_AMUX
.set VSync__BIE, CYREG_PRT0_BIE
.set VSync__BIT_MASK, CYREG_PRT0_BIT_MASK
.set VSync__BYP, CYREG_PRT0_BYP
.set VSync__CTL, CYREG_PRT0_CTL
.set VSync__DM0, CYREG_PRT0_DM0
.set VSync__DM1, CYREG_PRT0_DM1
.set VSync__DM2, CYREG_PRT0_DM2
.set VSync__DR, CYREG_PRT0_DR
.set VSync__INP_DIS, CYREG_PRT0_INP_DIS
.set VSync__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU0_BASE
.set VSync__LCD_COM_SEG, CYREG_PRT0_LCD_COM_SEG
.set VSync__LCD_EN, CYREG_PRT0_LCD_EN
.set VSync__MASK, 0x10
.set VSync__PORT, 0
.set VSync__PRT, CYREG_PRT0_PRT
.set VSync__PRTDSI__CAPS_SEL, CYREG_PRT0_CAPS_SEL
.set VSync__PRTDSI__DBL_SYNC_IN, CYREG_PRT0_DBL_SYNC_IN
.set VSync__PRTDSI__OE_SEL0, CYREG_PRT0_OE_SEL0
.set VSync__PRTDSI__OE_SEL1, CYREG_PRT0_OE_SEL1
.set VSync__PRTDSI__OUT_SEL0, CYREG_PRT0_OUT_SEL0
.set VSync__PRTDSI__OUT_SEL1, CYREG_PRT0_OUT_SEL1
.set VSync__PRTDSI__SYNC_OUT, CYREG_PRT0_SYNC_OUT
.set VSync__PS, CYREG_PRT0_PS
.set VSync__SHIFT, 4
.set VSync__SLW, CYREG_PRT0_SLW

/* Video */
.set Video__0__INTTYPE, CYREG_PICU4_INTTYPE2
.set Video__0__MASK, 0x04
.set Video__0__PC, CYREG_PRT4_PC2
.set Video__0__PORT, 4
.set Video__0__SHIFT, 2
.set Video__AG, CYREG_PRT4_AG
.set Video__AMUX, CYREG_PRT4_AMUX
.set Video__BIE, CYREG_PRT4_BIE
.set Video__BIT_MASK, CYREG_PRT4_BIT_MASK
.set Video__BYP, CYREG_PRT4_BYP
.set Video__CTL, CYREG_PRT4_CTL
.set Video__DM0, CYREG_PRT4_DM0
.set Video__DM1, CYREG_PRT4_DM1
.set Video__DM2, CYREG_PRT4_DM2
.set Video__DR, CYREG_PRT4_DR
.set Video__INP_DIS, CYREG_PRT4_INP_DIS
.set Video__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU4_BASE
.set Video__LCD_COM_SEG, CYREG_PRT4_LCD_COM_SEG
.set Video__LCD_EN, CYREG_PRT4_LCD_EN
.set Video__MASK, 0x04
.set Video__PORT, 4
.set Video__PRT, CYREG_PRT4_PRT
.set Video__PRTDSI__CAPS_SEL, CYREG_PRT4_CAPS_SEL
.set Video__PRTDSI__DBL_SYNC_IN, CYREG_PRT4_DBL_SYNC_IN
.set Video__PRTDSI__OE_SEL0, CYREG_PRT4_OE_SEL0
.set Video__PRTDSI__OE_SEL1, CYREG_PRT4_OE_SEL1
.set Video__PRTDSI__OUT_SEL0, CYREG_PRT4_OUT_SEL0
.set Video__PRTDSI__OUT_SEL1, CYREG_PRT4_OUT_SEL1
.set Video__PRTDSI__SYNC_OUT, CYREG_PRT4_SYNC_OUT
.set Video__PS, CYREG_PRT4_PS
.set Video__SHIFT, 2
.set Video__SLW, CYREG_PRT4_SLW

/* Reference */
.set Reference_viDAC8__CR0, CYREG_DAC2_CR0
.set Reference_viDAC8__CR1, CYREG_DAC2_CR1
.set Reference_viDAC8__D, CYREG_DAC2_D
.set Reference_viDAC8__PM_ACT_CFG, CYREG_PM_ACT_CFG8
.set Reference_viDAC8__PM_ACT_MSK, 0x04
.set Reference_viDAC8__PM_STBY_CFG, CYREG_PM_STBY_CFG8
.set Reference_viDAC8__PM_STBY_MSK, 0x04
.set Reference_viDAC8__STROBE, CYREG_DAC2_STROBE
.set Reference_viDAC8__SW0, CYREG_DAC2_SW0
.set Reference_viDAC8__SW2, CYREG_DAC2_SW2
.set Reference_viDAC8__SW3, CYREG_DAC2_SW3
.set Reference_viDAC8__SW4, CYREG_DAC2_SW4
.set Reference_viDAC8__TR, CYREG_DAC2_TR
.set Reference_viDAC8__TRIM__M1, CYREG_FLSHID_CUST_TABLES_DAC2_M1
.set Reference_viDAC8__TRIM__M2, CYREG_FLSHID_CUST_TABLES_DAC2_M2
.set Reference_viDAC8__TRIM__M3, CYREG_FLSHID_CUST_TABLES_DAC2_M3
.set Reference_viDAC8__TRIM__M4, CYREG_FLSHID_CUST_TABLES_DAC2_M4
.set Reference_viDAC8__TRIM__M5, CYREG_FLSHID_CUST_TABLES_DAC2_M5
.set Reference_viDAC8__TRIM__M6, CYREG_FLSHID_CUST_TABLES_DAC2_M6
.set Reference_viDAC8__TRIM__M7, CYREG_FLSHID_CUST_TABLES_DAC2_M7
.set Reference_viDAC8__TRIM__M8, CYREG_FLSHID_CUST_TABLES_DAC2_M8
.set Reference_viDAC8__TST, CYREG_DAC2_TST

/* Analog_CMP */
.set Analog_CMP_ctComp__CLK, CYREG_CMP0_CLK
.set Analog_CMP_ctComp__CMP_MASK, 0x01
.set Analog_CMP_ctComp__CMP_NUMBER, 0
.set Analog_CMP_ctComp__CR, CYREG_CMP0_CR
.set Analog_CMP_ctComp__LUT__CR, CYREG_LUT0_CR
.set Analog_CMP_ctComp__LUT__MSK, CYREG_LUT_MSK
.set Analog_CMP_ctComp__LUT__MSK_MASK, 0x01
.set Analog_CMP_ctComp__LUT__MSK_SHIFT, 0
.set Analog_CMP_ctComp__LUT__MX, CYREG_LUT0_MX
.set Analog_CMP_ctComp__LUT__SR, CYREG_LUT_SR
.set Analog_CMP_ctComp__LUT__SR_MASK, 0x01
.set Analog_CMP_ctComp__LUT__SR_SHIFT, 0
.set Analog_CMP_ctComp__PM_ACT_CFG, CYREG_PM_ACT_CFG7
.set Analog_CMP_ctComp__PM_ACT_MSK, 0x01
.set Analog_CMP_ctComp__PM_STBY_CFG, CYREG_PM_STBY_CFG7
.set Analog_CMP_ctComp__PM_STBY_MSK, 0x01
.set Analog_CMP_ctComp__SW0, CYREG_CMP0_SW0
.set Analog_CMP_ctComp__SW2, CYREG_CMP0_SW2
.set Analog_CMP_ctComp__SW3, CYREG_CMP0_SW3
.set Analog_CMP_ctComp__SW4, CYREG_CMP0_SW4
.set Analog_CMP_ctComp__SW6, CYREG_CMP0_SW6
.set Analog_CMP_ctComp__TR0, CYREG_CMP0_TR0
.set Analog_CMP_ctComp__TR1, CYREG_CMP0_TR1
.set Analog_CMP_ctComp__TRIM__TR0, CYREG_FLSHID_MFG_CFG_CMP0_TR0
.set Analog_CMP_ctComp__TRIM__TR0_HS, CYREG_FLSHID_CUST_TABLES_CMP0_TR0_HS
.set Analog_CMP_ctComp__TRIM__TR1, CYREG_FLSHID_MFG_CFG_CMP0_TR1
.set Analog_CMP_ctComp__TRIM__TR1_HS, CYREG_FLSHID_CUST_TABLES_CMP0_TR1_HS
.set Analog_CMP_ctComp__WRK, CYREG_CMP_WRK
.set Analog_CMP_ctComp__WRK_MASK, 0x01
.set Analog_CMP_ctComp__WRK_SHIFT, 0

/* Dark_Timer */
.set Dark_Timer_TimerUDB_rstSts_stsreg__0__MASK, 0x01
.set Dark_Timer_TimerUDB_rstSts_stsreg__0__POS, 0
.set Dark_Timer_TimerUDB_rstSts_stsreg__1__MASK, 0x02
.set Dark_Timer_TimerUDB_rstSts_stsreg__1__POS, 1
.set Dark_Timer_TimerUDB_rstSts_stsreg__16BIT_STATUS_AUX_CTL_REG, CYREG_B0_UDB03_04_ACTL
.set Dark_Timer_TimerUDB_rstSts_stsreg__16BIT_STATUS_REG, CYREG_B0_UDB03_04_ST
.set Dark_Timer_TimerUDB_rstSts_stsreg__2__MASK, 0x04
.set Dark_Timer_TimerUDB_rstSts_stsreg__2__POS, 2
.set Dark_Timer_TimerUDB_rstSts_stsreg__3__MASK, 0x08
.set Dark_Timer_TimerUDB_rstSts_stsreg__3__POS, 3
.set Dark_Timer_TimerUDB_rstSts_stsreg__MASK, 0x0F
.set Dark_Timer_TimerUDB_rstSts_stsreg__MASK_REG, CYREG_B0_UDB03_MSK
.set Dark_Timer_TimerUDB_rstSts_stsreg__MASK_ST_AUX_CTL_REG, CYREG_B0_UDB03_MSK_ACTL
.set Dark_Timer_TimerUDB_rstSts_stsreg__PER_ST_AUX_CTL_REG, CYREG_B0_UDB03_MSK_ACTL
.set Dark_Timer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG, CYREG_B0_UDB03_ACTL
.set Dark_Timer_TimerUDB_rstSts_stsreg__STATUS_CNT_REG, CYREG_B0_UDB03_ST_CTL
.set Dark_Timer_TimerUDB_rstSts_stsreg__STATUS_CONTROL_REG, CYREG_B0_UDB03_ST_CTL
.set Dark_Timer_TimerUDB_rstSts_stsreg__STATUS_REG, CYREG_B0_UDB03_ST
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__0__MASK, 0x01
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__0__POS, 0
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__1__MASK, 0x02
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__1__POS, 1
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_CONTROL_AUX_CTL_REG, CYREG_B0_UDB03_04_ACTL
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_CONTROL_CONTROL_REG, CYREG_B0_UDB03_04_CTL
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_CONTROL_COUNT_REG, CYREG_B0_UDB03_04_CTL
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_COUNT_CONTROL_REG, CYREG_B0_UDB03_04_CTL
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_COUNT_COUNT_REG, CYREG_B0_UDB03_04_CTL
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_MASK_MASK_REG, CYREG_B0_UDB03_04_MSK
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_MASK_PERIOD_REG, CYREG_B0_UDB03_04_MSK
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_PERIOD_MASK_REG, CYREG_B0_UDB03_04_MSK
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_PERIOD_PERIOD_REG, CYREG_B0_UDB03_04_MSK
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__7__MASK, 0x80
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__7__POS, 7
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_AUX_CTL_REG, CYREG_B0_UDB03_ACTL
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG, CYREG_B0_UDB03_CTL
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_ST_REG, CYREG_B0_UDB03_ST_CTL
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__COUNT_REG, CYREG_B0_UDB03_CTL
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__COUNT_ST_REG, CYREG_B0_UDB03_ST_CTL
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__MASK, 0x83
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__MASK_CTL_AUX_CTL_REG, CYREG_B0_UDB03_MSK_ACTL
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__PER_CTL_AUX_CTL_REG, CYREG_B0_UDB03_MSK_ACTL
.set Dark_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__PERIOD_REG, CYREG_B0_UDB03_MSK
.set Dark_Timer_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG, CYREG_B0_UDB04_05_A0
.set Dark_Timer_TimerUDB_sT32_timerdp_u0__16BIT_A1_REG, CYREG_B0_UDB04_05_A1
.set Dark_Timer_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG, CYREG_B0_UDB04_05_D0
.set Dark_Timer_TimerUDB_sT32_timerdp_u0__16BIT_D1_REG, CYREG_B0_UDB04_05_D1
.set Dark_Timer_TimerUDB_sT32_timerdp_u0__16BIT_DP_AUX_CTL_REG, CYREG_B0_UDB04_05_ACTL
.set Dark_Timer_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG, CYREG_B0_UDB04_05_F0
.set Dark_Timer_TimerUDB_sT32_timerdp_u0__16BIT_F1_REG, CYREG_B0_UDB04_05_F1
.set Dark_Timer_TimerUDB_sT32_timerdp_u0__A0_A1_REG, CYREG_B0_UDB04_A0_A1
.set Dark_Timer_TimerUDB_sT32_timerdp_u0__A0_REG, CYREG_B0_UDB04_A0
.set Dark_Timer_TimerUDB_sT32_timerdp_u0__A1_REG, CYREG_B0_UDB04_A1
.set Dark_Timer_TimerUDB_sT32_timerdp_u0__D0_D1_REG, CYREG_B0_UDB04_D0_D1
.set Dark_Timer_TimerUDB_sT32_timerdp_u0__D0_REG, CYREG_B0_UDB04_D0
.set Dark_Timer_TimerUDB_sT32_timerdp_u0__D1_REG, CYREG_B0_UDB04_D1
.set Dark_Timer_TimerUDB_sT32_timerdp_u0__DP_AUX_CTL_REG, CYREG_B0_UDB04_ACTL
.set Dark_Timer_TimerUDB_sT32_timerdp_u0__F0_F1_REG, CYREG_B0_UDB04_F0_F1
.set Dark_Timer_TimerUDB_sT32_timerdp_u0__F0_REG, CYREG_B0_UDB04_F0
.set Dark_Timer_TimerUDB_sT32_timerdp_u0__F1_REG, CYREG_B0_UDB04_F1
.set Dark_Timer_TimerUDB_sT32_timerdp_u1__16BIT_A0_REG, CYREG_B0_UDB05_06_A0
.set Dark_Timer_TimerUDB_sT32_timerdp_u1__16BIT_A1_REG, CYREG_B0_UDB05_06_A1
.set Dark_Timer_TimerUDB_sT32_timerdp_u1__16BIT_D0_REG, CYREG_B0_UDB05_06_D0
.set Dark_Timer_TimerUDB_sT32_timerdp_u1__16BIT_D1_REG, CYREG_B0_UDB05_06_D1
.set Dark_Timer_TimerUDB_sT32_timerdp_u1__16BIT_DP_AUX_CTL_REG, CYREG_B0_UDB05_06_ACTL
.set Dark_Timer_TimerUDB_sT32_timerdp_u1__16BIT_F0_REG, CYREG_B0_UDB05_06_F0
.set Dark_Timer_TimerUDB_sT32_timerdp_u1__16BIT_F1_REG, CYREG_B0_UDB05_06_F1
.set Dark_Timer_TimerUDB_sT32_timerdp_u1__A0_A1_REG, CYREG_B0_UDB05_A0_A1
.set Dark_Timer_TimerUDB_sT32_timerdp_u1__A0_REG, CYREG_B0_UDB05_A0
.set Dark_Timer_TimerUDB_sT32_timerdp_u1__A1_REG, CYREG_B0_UDB05_A1
.set Dark_Timer_TimerUDB_sT32_timerdp_u1__D0_D1_REG, CYREG_B0_UDB05_D0_D1
.set Dark_Timer_TimerUDB_sT32_timerdp_u1__D0_REG, CYREG_B0_UDB05_D0
.set Dark_Timer_TimerUDB_sT32_timerdp_u1__D1_REG, CYREG_B0_UDB05_D1
.set Dark_Timer_TimerUDB_sT32_timerdp_u1__DP_AUX_CTL_REG, CYREG_B0_UDB05_ACTL
.set Dark_Timer_TimerUDB_sT32_timerdp_u1__F0_F1_REG, CYREG_B0_UDB05_F0_F1
.set Dark_Timer_TimerUDB_sT32_timerdp_u1__F0_REG, CYREG_B0_UDB05_F0
.set Dark_Timer_TimerUDB_sT32_timerdp_u1__F1_REG, CYREG_B0_UDB05_F1
.set Dark_Timer_TimerUDB_sT32_timerdp_u2__16BIT_A0_REG, CYREG_B0_UDB06_07_A0
.set Dark_Timer_TimerUDB_sT32_timerdp_u2__16BIT_A1_REG, CYREG_B0_UDB06_07_A1
.set Dark_Timer_TimerUDB_sT32_timerdp_u2__16BIT_D0_REG, CYREG_B0_UDB06_07_D0
.set Dark_Timer_TimerUDB_sT32_timerdp_u2__16BIT_D1_REG, CYREG_B0_UDB06_07_D1
.set Dark_Timer_TimerUDB_sT32_timerdp_u2__16BIT_DP_AUX_CTL_REG, CYREG_B0_UDB06_07_ACTL
.set Dark_Timer_TimerUDB_sT32_timerdp_u2__16BIT_F0_REG, CYREG_B0_UDB06_07_F0
.set Dark_Timer_TimerUDB_sT32_timerdp_u2__16BIT_F1_REG, CYREG_B0_UDB06_07_F1
.set Dark_Timer_TimerUDB_sT32_timerdp_u2__A0_A1_REG, CYREG_B0_UDB06_A0_A1
.set Dark_Timer_TimerUDB_sT32_timerdp_u2__A0_REG, CYREG_B0_UDB06_A0
.set Dark_Timer_TimerUDB_sT32_timerdp_u2__A1_REG, CYREG_B0_UDB06_A1
.set Dark_Timer_TimerUDB_sT32_timerdp_u2__D0_D1_REG, CYREG_B0_UDB06_D0_D1
.set Dark_Timer_TimerUDB_sT32_timerdp_u2__D0_REG, CYREG_B0_UDB06_D0
.set Dark_Timer_TimerUDB_sT32_timerdp_u2__D1_REG, CYREG_B0_UDB06_D1
.set Dark_Timer_TimerUDB_sT32_timerdp_u2__DP_AUX_CTL_REG, CYREG_B0_UDB06_ACTL
.set Dark_Timer_TimerUDB_sT32_timerdp_u2__F0_F1_REG, CYREG_B0_UDB06_F0_F1
.set Dark_Timer_TimerUDB_sT32_timerdp_u2__F0_REG, CYREG_B0_UDB06_F0
.set Dark_Timer_TimerUDB_sT32_timerdp_u2__F1_REG, CYREG_B0_UDB06_F1
.set Dark_Timer_TimerUDB_sT32_timerdp_u3__16BIT_A0_REG, CYREG_B0_UDB07_08_A0
.set Dark_Timer_TimerUDB_sT32_timerdp_u3__16BIT_A1_REG, CYREG_B0_UDB07_08_A1
.set Dark_Timer_TimerUDB_sT32_timerdp_u3__16BIT_D0_REG, CYREG_B0_UDB07_08_D0
.set Dark_Timer_TimerUDB_sT32_timerdp_u3__16BIT_D1_REG, CYREG_B0_UDB07_08_D1
.set Dark_Timer_TimerUDB_sT32_timerdp_u3__16BIT_DP_AUX_CTL_REG, CYREG_B0_UDB07_08_ACTL
.set Dark_Timer_TimerUDB_sT32_timerdp_u3__16BIT_F0_REG, CYREG_B0_UDB07_08_F0
.set Dark_Timer_TimerUDB_sT32_timerdp_u3__16BIT_F1_REG, CYREG_B0_UDB07_08_F1
.set Dark_Timer_TimerUDB_sT32_timerdp_u3__A0_A1_REG, CYREG_B0_UDB07_A0_A1
.set Dark_Timer_TimerUDB_sT32_timerdp_u3__A0_REG, CYREG_B0_UDB07_A0
.set Dark_Timer_TimerUDB_sT32_timerdp_u3__A1_REG, CYREG_B0_UDB07_A1
.set Dark_Timer_TimerUDB_sT32_timerdp_u3__D0_D1_REG, CYREG_B0_UDB07_D0_D1
.set Dark_Timer_TimerUDB_sT32_timerdp_u3__D0_REG, CYREG_B0_UDB07_D0
.set Dark_Timer_TimerUDB_sT32_timerdp_u3__D1_REG, CYREG_B0_UDB07_D1
.set Dark_Timer_TimerUDB_sT32_timerdp_u3__DP_AUX_CTL_REG, CYREG_B0_UDB07_ACTL
.set Dark_Timer_TimerUDB_sT32_timerdp_u3__F0_F1_REG, CYREG_B0_UDB07_F0_F1
.set Dark_Timer_TimerUDB_sT32_timerdp_u3__F0_REG, CYREG_B0_UDB07_F0
.set Dark_Timer_TimerUDB_sT32_timerdp_u3__F1_REG, CYREG_B0_UDB07_F1

/* timer_clock */
.set timer_clock__CFG0, CYREG_CLKDIST_DCFG0_CFG0
.set timer_clock__CFG1, CYREG_CLKDIST_DCFG0_CFG1
.set timer_clock__CFG2, CYREG_CLKDIST_DCFG0_CFG2
.set timer_clock__CFG2_SRC_SEL_MASK, 0x07
.set timer_clock__INDEX, 0x00
.set timer_clock__PM_ACT_CFG, CYREG_PM_ACT_CFG2
.set timer_clock__PM_ACT_MSK, 0x01
.set timer_clock__PM_STBY_CFG, CYREG_PM_STBY_CFG2
.set timer_clock__PM_STBY_MSK, 0x01

/* Dark_Interrupt */
.set Dark_Interrupt__INTC_CLR_EN_REG, CYREG_NVIC_CLRENA0
.set Dark_Interrupt__INTC_CLR_PD_REG, CYREG_NVIC_CLRPEND0
.set Dark_Interrupt__INTC_MASK, 0x01
.set Dark_Interrupt__INTC_NUMBER, 0
.set Dark_Interrupt__INTC_PRIOR_NUM, 7
.set Dark_Interrupt__INTC_PRIOR_REG, CYREG_NVIC_PRI_0
.set Dark_Interrupt__INTC_SET_EN_REG, CYREG_NVIC_SETENA0
.set Dark_Interrupt__INTC_SET_PD_REG, CYREG_NVIC_SETPEND0

/* Frame_Interrupt */
.set Frame_Interrupt__INTC_CLR_EN_REG, CYREG_NVIC_CLRENA0
.set Frame_Interrupt__INTC_CLR_PD_REG, CYREG_NVIC_CLRPEND0
.set Frame_Interrupt__INTC_MASK, 0x02
.set Frame_Interrupt__INTC_NUMBER, 1
.set Frame_Interrupt__INTC_PRIOR_NUM, 7
.set Frame_Interrupt__INTC_PRIOR_REG, CYREG_NVIC_PRI_1
.set Frame_Interrupt__INTC_SET_EN_REG, CYREG_NVIC_SETENA0
.set Frame_Interrupt__INTC_SET_PD_REG, CYREG_NVIC_SETPEND0

/* Target_Interrupt */
.set Target_Interrupt__INTC_CLR_EN_REG, CYREG_NVIC_CLRENA0
.set Target_Interrupt__INTC_CLR_PD_REG, CYREG_NVIC_CLRPEND0
.set Target_Interrupt__INTC_MASK, 0x04
.set Target_Interrupt__INTC_NUMBER, 2
.set Target_Interrupt__INTC_PRIOR_NUM, 7
.set Target_Interrupt__INTC_PRIOR_REG, CYREG_NVIC_PRI_2
.set Target_Interrupt__INTC_SET_EN_REG, CYREG_NVIC_SETENA0
.set Target_Interrupt__INTC_SET_PD_REG, CYREG_NVIC_SETPEND0

/* Miscellaneous */
.set BCLK__BUS_CLK__HZ, 24000000
.set BCLK__BUS_CLK__KHZ, 24000
.set BCLK__BUS_CLK__MHZ, 24
.set CYDEV_CHIP_DIE_LEOPARD, 1
.set CYDEV_CHIP_DIE_PSOC4A, 26
.set CYDEV_CHIP_DIE_PSOC5LP, 2
.set CYDEV_CHIP_DIE_PSOC5TM, 3
.set CYDEV_CHIP_DIE_TMA4, 4
.set CYDEV_CHIP_DIE_UNKNOWN, 0
.set CYDEV_CHIP_FAMILY_FM0P, 5
.set CYDEV_CHIP_FAMILY_FM3, 6
.set CYDEV_CHIP_FAMILY_FM4, 7
.set CYDEV_CHIP_FAMILY_PSOC3, 1
.set CYDEV_CHIP_FAMILY_PSOC4, 2
.set CYDEV_CHIP_FAMILY_PSOC5, 3
.set CYDEV_CHIP_FAMILY_PSOC6, 4
.set CYDEV_CHIP_FAMILY_UNKNOWN, 0
.set CYDEV_CHIP_FAMILY_USED, CYDEV_CHIP_FAMILY_PSOC5
.set CYDEV_CHIP_JTAG_ID, 0x2E123069
.set CYDEV_CHIP_MEMBER_3A, 1
.set CYDEV_CHIP_MEMBER_4A, 26
.set CYDEV_CHIP_MEMBER_4AA, 25
.set CYDEV_CHIP_MEMBER_4AB, 30
.set CYDEV_CHIP_MEMBER_4AC, 14
.set CYDEV_CHIP_MEMBER_4AD, 15
.set CYDEV_CHIP_MEMBER_4AE, 16
.set CYDEV_CHIP_MEMBER_4D, 20
.set CYDEV_CHIP_MEMBER_4E, 6
.set CYDEV_CHIP_MEMBER_4F, 27
.set CYDEV_CHIP_MEMBER_4G, 4
.set CYDEV_CHIP_MEMBER_4H, 24
.set CYDEV_CHIP_MEMBER_4I, 32
.set CYDEV_CHIP_MEMBER_4J, 21
.set CYDEV_CHIP_MEMBER_4K, 22
.set CYDEV_CHIP_MEMBER_4L, 31
.set CYDEV_CHIP_MEMBER_4M, 29
.set CYDEV_CHIP_MEMBER_4N, 11
.set CYDEV_CHIP_MEMBER_4O, 8
.set CYDEV_CHIP_MEMBER_4P, 28
.set CYDEV_CHIP_MEMBER_4Q, 17
.set CYDEV_CHIP_MEMBER_4R, 9
.set CYDEV_CHIP_MEMBER_4S, 12
.set CYDEV_CHIP_MEMBER_4T, 10
.set CYDEV_CHIP_MEMBER_4U, 5
.set CYDEV_CHIP_MEMBER_4V, 23
.set CYDEV_CHIP_MEMBER_4W, 13
.set CYDEV_CHIP_MEMBER_4X, 7
.set CYDEV_CHIP_MEMBER_4Y, 18
.set CYDEV_CHIP_MEMBER_4Z, 19
.set CYDEV_CHIP_MEMBER_5A, 3
.set CYDEV_CHIP_MEMBER_5B, 2
.set CYDEV_CHIP_MEMBER_6A, 33
.set CYDEV_CHIP_MEMBER_FM3, 37
.set CYDEV_CHIP_MEMBER_FM4, 38
.set CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE1, 34
.set CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE2, 35
.set CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE3, 36
.set CYDEV_CHIP_MEMBER_UNKNOWN, 0
.set CYDEV_CHIP_MEMBER_USED, CYDEV_CHIP_MEMBER_5B
.set CYDEV_CHIP_DIE_EXPECT, CYDEV_CHIP_MEMBER_USED
.set CYDEV_CHIP_DIE_ACTUAL, CYDEV_CHIP_DIE_EXPECT
.set CYDEV_CHIP_REV_LEOPARD_ES1, 0
.set CYDEV_CHIP_REV_LEOPARD_ES2, 1
.set CYDEV_CHIP_REV_LEOPARD_ES3, 3
.set CYDEV_CHIP_REV_LEOPARD_PRODUCTION, 3
.set CYDEV_CHIP_REV_PSOC4A_ES0, 17
.set CYDEV_CHIP_REV_PSOC4A_PRODUCTION, 17
.set CYDEV_CHIP_REV_PSOC5LP_ES0, 0
.set CYDEV_CHIP_REV_PSOC5LP_PRODUCTION, 0
.set CYDEV_CHIP_REV_PSOC5TM_ES0, 0
.set CYDEV_CHIP_REV_PSOC5TM_ES1, 1
.set CYDEV_CHIP_REV_PSOC5TM_PRODUCTION, 1
.set CYDEV_CHIP_REV_TMA4_ES, 17
.set CYDEV_CHIP_REV_TMA4_ES2, 33
.set CYDEV_CHIP_REV_TMA4_PRODUCTION, 17
.set CYDEV_CHIP_REVISION_3A_ES1, 0
.set CYDEV_CHIP_REVISION_3A_ES2, 1
.set CYDEV_CHIP_REVISION_3A_ES3, 3
.set CYDEV_CHIP_REVISION_3A_PRODUCTION, 3
.set CYDEV_CHIP_REVISION_4A_ES0, 17
.set CYDEV_CHIP_REVISION_4A_PRODUCTION, 17
.set CYDEV_CHIP_REVISION_4AA_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4AB_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4AC_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4AD_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4AE_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4D_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4E_CCG2_NO_USBPD, 0
.set CYDEV_CHIP_REVISION_4E_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4F_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA, 0
.set CYDEV_CHIP_REVISION_4F_PRODUCTION_256K, 0
.set CYDEV_CHIP_REVISION_4G_ES, 17
.set CYDEV_CHIP_REVISION_4G_ES2, 33
.set CYDEV_CHIP_REVISION_4G_PRODUCTION, 17
.set CYDEV_CHIP_REVISION_4H_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4I_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4J_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4K_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4L_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4M_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4N_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4O_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4P_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4Q_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4R_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4S_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4T_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4U_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4V_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4W_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4X_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4Y_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4Z_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_5A_ES0, 0
.set CYDEV_CHIP_REVISION_5A_ES1, 1
.set CYDEV_CHIP_REVISION_5A_PRODUCTION, 1
.set CYDEV_CHIP_REVISION_5B_ES0, 0
.set CYDEV_CHIP_REVISION_5B_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_6A_ES, 17
.set CYDEV_CHIP_REVISION_6A_NO_UDB, 33
.set CYDEV_CHIP_REVISION_6A_PRODUCTION, 33
.set CYDEV_CHIP_REVISION_FM3_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_FM4_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_PDL_FM0P_TYPE1_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_PDL_FM0P_TYPE2_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_PDL_FM0P_TYPE3_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_USED, CYDEV_CHIP_REVISION_5B_PRODUCTION
.set CYDEV_CHIP_REV_EXPECT, CYDEV_CHIP_REVISION_USED
.set CYDEV_CONFIG_FASTBOOT_ENABLED, 1
.set CYDEV_CONFIG_UNUSED_IO_AllowButWarn, 0
.set CYDEV_CONFIG_UNUSED_IO, CYDEV_CONFIG_UNUSED_IO_AllowButWarn
.set CYDEV_CONFIG_UNUSED_IO_AllowWithInfo, 1
.set CYDEV_CONFIG_UNUSED_IO_Disallowed, 2
.set CYDEV_CONFIGURATION_COMPRESSED, 1
.set CYDEV_CONFIGURATION_DMA, 0
.set CYDEV_CONFIGURATION_ECC, 1
.set CYDEV_CONFIGURATION_IMOENABLED, CYDEV_CONFIG_FASTBOOT_ENABLED
.set CYDEV_CONFIGURATION_MODE_COMPRESSED, 0
.set CYDEV_CONFIGURATION_MODE, CYDEV_CONFIGURATION_MODE_COMPRESSED
.set CYDEV_CONFIGURATION_MODE_DMA, 2
.set CYDEV_CONFIGURATION_MODE_UNCOMPRESSED, 1
.set CYDEV_DEBUG_ENABLE_MASK, 0x20
.set CYDEV_DEBUG_ENABLE_REGISTER, CYREG_MLOGIC_DEBUG
.set CYDEV_DEBUGGING_DPS_Disable, 3
.set CYDEV_DEBUGGING_DPS_JTAG_4, 1
.set CYDEV_DEBUGGING_DPS_JTAG_5, 0
.set CYDEV_DEBUGGING_DPS_SWD, 2
.set CYDEV_DEBUGGING_DPS_SWD_SWV, 6
.set CYDEV_DEBUGGING_DPS, CYDEV_DEBUGGING_DPS_SWD_SWV
.set CYDEV_DEBUGGING_ENABLE, 1
.set CYDEV_DEBUGGING_XRES, 0
.set CYDEV_DMA_CHANNELS_AVAILABLE, 24
.set CYDEV_ECC_ENABLE, 0
.set CYDEV_HEAP_SIZE, 0x80
.set CYDEV_INSTRUCT_CACHE_ENABLED, 1
.set CYDEV_INTR_RISING, 0x00000007
.set CYDEV_IS_EXPORTING_CODE, 0
.set CYDEV_IS_IMPORTING_CODE, 0
.set CYDEV_PROJ_TYPE, 0
.set CYDEV_PROJ_TYPE_BOOTLOADER, 1
.set CYDEV_PROJ_TYPE_LAUNCHER, 5
.set CYDEV_PROJ_TYPE_LOADABLE, 2
.set CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER, 4
.set CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER, 3
.set CYDEV_PROJ_TYPE_STANDARD, 0
.set CYDEV_PROTECTION_ENABLE, 0
.set CYDEV_STACK_SIZE, 0x0800
.set CYDEV_USE_BUNDLED_CMSIS, 1
.set CYDEV_VARIABLE_VDDA, 0
.set CYDEV_VDDA_MV, 5000
.set CYDEV_VDDD_MV, 5000
.set CYDEV_VDDIO0_MV, 5000
.set CYDEV_VDDIO1_MV, 5000
.set CYDEV_VDDIO2_MV, 5000
.set CYDEV_VDDIO3_MV, 5000
.set CYDEV_VIO0_MV, 5000
.set CYDEV_VIO1_MV, 5000
.set CYDEV_VIO2_MV, 5000
.set CYDEV_VIO3_MV, 5000
.set CYIPBLOCK_ARM_CM3_VERSION, 0
.set CYIPBLOCK_P3_ANAIF_VERSION, 0
.set CYIPBLOCK_P3_CAN_VERSION, 0
.set CYIPBLOCK_P3_CAPSENSE_VERSION, 0
.set CYIPBLOCK_P3_COMP_VERSION, 0
.set CYIPBLOCK_P3_DECIMATOR_VERSION, 0
.set CYIPBLOCK_P3_DFB_VERSION, 0
.set CYIPBLOCK_P3_DMA_VERSION, 0
.set CYIPBLOCK_P3_DRQ_VERSION, 0
.set CYIPBLOCK_P3_DSM_VERSION, 0
.set CYIPBLOCK_P3_EMIF_VERSION, 0
.set CYIPBLOCK_P3_I2C_VERSION, 0
.set CYIPBLOCK_P3_LCD_VERSION, 0
.set CYIPBLOCK_P3_LPF_VERSION, 0
.set CYIPBLOCK_P3_OPAMP_VERSION, 0
.set CYIPBLOCK_P3_PM_VERSION, 0
.set CYIPBLOCK_P3_SCCT_VERSION, 0
.set CYIPBLOCK_P3_TIMER_VERSION, 0
.set CYIPBLOCK_P3_USB_VERSION, 0
.set CYIPBLOCK_P3_VIDAC_VERSION, 0
.set CYIPBLOCK_P3_VREF_VERSION, 0
.set CYIPBLOCK_S8_GPIO_VERSION, 0
.set CYIPBLOCK_S8_IRQ_VERSION, 0
.set CYIPBLOCK_S8_SAR_VERSION, 0
.set CYIPBLOCK_S8_SIO_VERSION, 0
.set CYIPBLOCK_S8_UDB_VERSION, 0
.set DMA_CHANNELS_USED__MASK0, 0x00000000
.set CYDEV_BOOTLOADER_ENABLE, 0
.endif