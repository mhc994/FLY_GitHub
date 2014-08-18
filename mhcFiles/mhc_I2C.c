#include "mhc.h"
#include "GlobalVariables.h"

void init_I2C_devices()
{
	   // ��ʼ��MPU6050����ÿ�����ݷ�����д��һ����i2c�������³�ʼ�����������
	       while( iicWriteByte(MPU6050ADDR,PWR_MGMT_1	, 0x01) != I2C_SUCCESS);
	       while( iicWriteByte(MPU6050ADDR,SMPLRT_DIV	, 0x00) != I2C_SUCCESS);
	       while( iicWriteByte(MPU6050ADDR,CONFIG 			, 0x00) != I2C_SUCCESS);
	       while( iicWriteByte(MPU6050ADDR,GYRO_CONFIG, 0x18) != I2C_SUCCESS);
	       while( iicWriteByte(MPU6050ADDR,ACCEL_CONFIG, 0x01) != I2C_SUCCESS);
}

void init_I2C_devices_flying()//���³�ʼ��I2C ����ʱI2C��������� ��ʼ�����ɹ������iiC_broken
{
	   // ��ʱû��,Ҫ��
    while( iicWriteByte(MPU6050ADDR,PWR_MGMT_1	, 0x01) != I2C_SUCCESS);
    while(i2c_Send_Complete==0);
    while( iicWriteByte(MPU6050ADDR,SMPLRT_DIV	, 0x00) != I2C_SUCCESS);
    while(i2c_Send_Complete==0);
    while( iicWriteByte(MPU6050ADDR,CONFIG 			, 0x00) != I2C_SUCCESS);
    while(i2c_Send_Complete==0);
    while( iicWriteByte(MPU6050ADDR,GYRO_CONFIG, 0x18) != I2C_SUCCESS);
    while(i2c_Send_Complete==0);
    while( iicWriteByte(MPU6050ADDR,ACCEL_CONFIG, 0x01) != I2C_SUCCESS);
    while(i2c_Send_Complete==0);
}

void iiC_broken()//I2C����ʧ��
{
	//����ʽ̫SB��Ҫ��
	while(1)//�������Ϊ0
	{
		setPwm(1,0);
		setPwm(2,0);
		setPwm(3,0);
		setPwm(4,0);
		setPwm(5,0);
	}
}



__interrupt void i2c_int1a_isr(void)     // I2C-A
{
   Uint16 IntSource = I2caRegs.I2CISRC.all;   // Read interrupt source

   if(IntSource == I2C_SCD_ISRC)   // ��ֹͣλ Interrupt source = stop condition detected
   {
	   switch(i2cStatus)
	   {
	   case 21:// �������If completed message was writing data, reset msg to inactive state
		   i2c_Send_Complete=1;
		   i2cStatus=0;
		   break;

	   case 31:  // If a message receives a NACK during the address setup portion of the
		   // EEPROM read, the code further below included in the register access ready
		   // interrupt source code will generate a stop condition. After the stop
		   // condition is received (here), set the message status to try again.
		   // User may want to limit the number of retries before generating an error.
		   iicStartRead();
		   break;

	   case 32:  // If a message receives a NACK during the address setup portion of the
		   // EEPROM read, the code further below included in the register access ready
		   // interrupt source code will generate a stop condition. After the stop
		   // condition is received (here), set the message status to try again.
		   // User may want to limit the number of retries before generating an error.
		   init_I2C_devices_flying();//����Ҫ��
		   break;


	   case 13://�յ����豸����������
//	       	  i2cStatus=0;
	       	  i2cData[i2cDataPointer]=I2caRegs.I2CDRR;//�����ݴӼĴ����ŵ�i2c��������
	       	  if( (++i2cDataPointer)>15)//����������һ������ָ��ص���һ�����ӱ���豸Ҫ������͵�ַ
	       	  {
	       		  i2cDataPointer=0;
	       	  }
	          I2caRegs.I2CSAR = i2cSlaves[i2cDataPointer];
	          i2cStatus=12;
	          I2caRegs.I2CCNT = 1;
	          I2caRegs.I2CDXR = i2cRegAddr[i2cDataPointer];
	          I2caRegs.I2CMDR.all = 0x2620;			// Send data to setup EEPROM address
	       	  break;
	   }



   }  // end of stop condition detected


   // Interrupt source = Register Access Ready
   // This interrupt is used to determine when the EEPROM address setup portion of the
   // read data communication is complete. Since no stop bit is commanded, this flag
   // tells us when the message has been sent instead of the SCD flag. If a NACK is
   // received, clear the NACK bit and command a stop. Otherwise, move on to the read
   // data portion of the communication.
   else if(IntSource == I2C_ARDY_ISRC)
   {
      if(I2caRegs.I2CSTR.bit.NACK == 1)//�����Ӧ��
      {
         I2caRegs.I2CMDR.bit.STP = 1;
         I2caRegs.I2CSTR.all = I2C_CLR_NACK_BIT;
         if(i2cStatus==12)
        	 i2cStatus=31;
         if(i2cStatus==21)
        	 i2cStatus=32;
      }

      else if(i2cStatus==12)//��ַ�����ˣ�����һ������
      {
    	  I2caRegs.I2CSAR = i2cSlaves[i2cDataPointer];
    	  I2caRegs.I2CCNT = 1;	// Setup how many bytes to expect
    	  I2caRegs.I2CMDR.all = 0x2C20;			// Send restart as master receiver
    	  i2cStatus=13;//����������
      }

   }  // end of register access ready

   PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
}


void I2CA_Init(void)
{
   I2caRegs.I2CSAR = MPU6050ADDR	;		// Slave address - EEPROM control code

   I2caRegs.I2CPSC.all = 6;		    // Prescaler - need 7-12 Mhz on module clk
   I2caRegs.I2CCLKL = 10;			// NOTE: must be non zero
   I2caRegs.I2CCLKH = 5;			// NOTE: must be non zero
   I2caRegs.I2CIER.all = 0x24;		// Enable SCD & ARDY interrupts

   I2caRegs.I2CMDR.all = 0x0020;	// Take I2C out of reset  // Stop I2C when suspended
   I2caRegs.I2CFFTX.all = 0x6000;	// Enable FIFO mode and TXFIFO
   I2caRegs.I2CFFRX.all = 0x2040;	// Enable RXFIFO, clear RXFFINT,

   return;
}



Uint16 iicWriteByte(Uint16 slaveAddr,Uint16 regAddr,Uint16 data)
{
   // Wait until the STP bit is cleared from any previous master communication. Clearing of this bit by the module is delayed
   //until after the SCD bit is set. If this bit is not checked prior to initiating a new message, the I2C could get confused.
   if (I2caRegs.I2CMDR.bit.STP == 1)
   {
      return I2C_STP_NOT_READY_ERROR;
   }

   if (I2caRegs.I2CSTR.bit.BB == 1)   // Check if bus busy
   {
      return I2C_BUS_BUSY_ERROR;
   }

   I2caRegs.I2CSAR = slaveAddr;   // Setup slave address
   I2caRegs.I2CCNT = 2;// Setup number of bytes to send   // MsgBuffer + Address
   I2caRegs.I2CDXR = regAddr;   // Setup data to send
   I2caRegs.I2CDXR = data;

   i2c_Send_Complete=0;
   i2cStatus=21;
   I2caRegs.I2CMDR.all = 0x6E20;   // Send start as master transmitter
   return I2C_SUCCESS;
}


Uint16 iicStartRead()
{
   if (I2caRegs.I2CMDR.bit.STP == 1)   // Wait until the STP bit is cleared from any previous master communication. Clearing of this bit by the module is delayed until after the SCD bit is set. If this bit is not checked prior to initiating a new message, the I2C could get confused.
   {
      return I2C_STP_NOT_READY_ERROR;
   }
   if (I2caRegs.I2CSTR.bit.BB == 1) // Check if bus busy
   {
      return I2C_BUS_BUSY_ERROR;
   }

   i2cDataPointer=0;
   I2caRegs.I2CSAR = i2cSlaves[i2cDataPointer];
   i2cStatus=12;
   I2caRegs.I2CCNT = 1;
   I2caRegs.I2CDXR = i2cRegAddr[i2cDataPointer];
   I2caRegs.I2CMDR.all = 0x2620;			// Send data to setup EEPROM address
   return I2C_SUCCESS;
}


/***********************************************************************
 no more
 **********************************************************************/
