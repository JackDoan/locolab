/***************************************************************************//**
 *   @file   Communication.c
 *   @brief  Implementation of Communication Driver.
 *   @author DBogdan (dragos.bogdan@analog.com)
********************************************************************************
 * Copyright 2012(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *  - The use of this software may or may not infringe the patent rights
 *    of one or more patent holders.  This license does not release you
 *    from the requirement that you obtain separate licenses from these
 *    patent holders to use this software.
 *  - Use of the software either in source or binary form, must be run
 *    on or directly connected to an Analog Devices Inc. component.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
********************************************************************************
 *   SVN Revision: 801
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "ad5933.h"
#include "Communication.h"

/***************************************************************************//**
 * @brief Initializes the I2C communication peripheral.
 *
 * @param clockFreq - I2C clock frequency (Hz).
 *                    Example: 100000 - I2C clock frequency is 100 kHz.
 * @return status - Result of the initialization procedure.
 *                  Example: 1 - if initialization was successful;
 *                           0 - if initialization was unsuccessful.
*******************************************************************************/
void I2C_Init(void)
{
    // Add your code here.
	// Initialize I2C
	I2caRegs.I2CSAR = 0x90;		//ad7414 addr //AD5933_ADDR_SLAVE;        // Slave address
	// I2CCLK = SYSCLK/(I2CPSC+1)
	#if (CPU_FRQ_40MHZ||CPU_FRQ_50MHZ)
		I2caRegs.I2CPSC.all = 4;       // Prescaler - need 7-12 Mhz on module clk
	#endif

	#if (CPU_FRQ_60MHZ)
		I2caRegs.I2CPSC.all = 6;       // Prescaler - need 7-12 Mhz on module clk
	#endif
	I2caRegs.I2CCLKL = 10;           // NOTE: must be non zero
	I2caRegs.I2CCLKH = 5;            // NOTE: must be non zero
	//I2caRegs.I2CIER.all = 0x26;      // Enable SCD & ARDY & NACK interrupts

	I2caRegs.I2CMDR.all = 0x0020;    // Take I2C out of reset
	                                    // Stop I2C when suspended

	I2caRegs.I2CFFTX.all = 0x6000;   // Enable FIFO mode and TXFIFO
	I2caRegs.I2CFFRX.all = 0x2040;   // Enable RXFIFO, clear RXFFINT,
}

/***************************************************************************//**
 * @brief Writes data to a slave device.
 *
 * @param slaveAddress - Adress of the slave device.
 * @param dataBuffer - Pointer to a buffer storing the transmission data.
 * @param bytesNumber - Number of bytes to write.
 * @param stopBit - Stop condition control.
 *                  Example: 0 - A stop condition will not be sent;
 *                           1 - A stop condition will be sent.
 *
 * @return status - Number of written bytes.
*******************************************************************************/
Uint16 I2C_Write(Uint16 DestAddr, Uint16 DataValue)
{
    // Add your code here.
	I2caRegs.I2CSAR = 0x48;        // Slave address

	if(I2caRegs.I2CMDR.bit.STP == 1)
	{
		return(I2C_STP_NOT_READY_ERROR);
	}
	if(I2caRegs.I2CSTR.bit.BB == 1)
	{
		return(I2C_BUS_BUSY_ERROR);
	}
	I2caRegs.I2CCNT = 2;        // 2 addi tional  bytes  being transfe rre d
	//28035 has 4-level FIFO, so we can process up to 4 da ta one  time .
	I2caRegs.I2CDXR = DestAddr & 0xff;  	// Address should be  8 bi t
	I2caRegs.I2CDXR = DataValue & 0xff;    	// 8bit datavalue

	I2caRegs.I2CMDR.all = 0x6E20;        	// bit 14 FREE = 1
	                						// bit 13 STT = 1    (Start condition)
	                						// bit 11 STP =1    (Stop condition after transfer of bytes .)
	                						// bit 10 MST = 1    Master
	                						// bit  9 TRX = 1    Transmit
	                						// bit  5 IRS = 1 to Reset I2C bus .

	while( !( I2caRegs.I2CSTR.all & 0x0030 ) );	//ARDY
	if( I2caRegs.I2CSTR.bit.NACK == 1){
		I2caRegs.I2CMDR.bit.STP = 1;
		I2caRegs.I2CSTR.bit.NACK = 0;
	}
	return(I2C_SUCCESS);
}

/***************************************************************************//**
 * @brief Reads data from a slave device.
 *
 * @param DestAddr - Adress of the slave device.
 * @param DataValue - Pointer to a buffer that will store the received data.
 *
 * @return status - Number of read bytes.
*******************************************************************************/
Uint16 I2C_Read(Uint16 SourceAddr)
{
    // Add your code here.
	//g_enRD_Mode = Read_Byte ;
	if(I2caRegs .I2CMDR.bit.STP == 1)
	{
		return(I2C_STP_NOT_READY_ERROR);
	}
	if(I2caRegs.I2CSTR.bit.BB == 1)
	{
		return(I2C_BUS_BUSY_ERROR);
	}
	I2caRegs.I2CCNT = 1;
	I2caRegs.I2CDXR = SourceAddr;
	I2caRegs.I2CMDR.all = 0x6620;	//bit 14 FREE = 1
	                				//bit 13 STT = 1    (Start condition)
	               	   	   	   	   	// bit 11 STP =0    (No Stop condi tion afte r transfe r of 17 bytes .)
	                						// bi t 10 MST = 1    Maste r
	                						// bi t    9 TRX = 1    Transmi t
	               	   	   	   	   	   	   // bi t    5 IRS = 1 to Rese t I 2C bus .
	DELAY_US(50);    // Dela y 50us , wait
	I2caRegs.I2CCNT = 1;  //Se t up re ce vie  of 1 byte
	I2caRegs.I2CMDR.all = 0x6c20;          // bi t 14 FREE = 1
	               // bi t 13 STT = 1    (Re Sta rt condi tion)
	                // bi t 11 STP =1    (Stop condi tion a fte r transfe r of bytes .)
	                // bi t 10 MST = 1    Maste r
	                // bi t    9 TRX = 0    Re cei ve r
	               // bi t    5 IRS = 1 to Rese t I 2C bus .
	//II CA_Wait();
	return(1);
}
