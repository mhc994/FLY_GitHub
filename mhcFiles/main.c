#include "mhc.h"
#include "GlobalVariables.h"

void main(void)
{
//	Uint16 i;
	initDSP();
//	init_I2C_devices();
	GpioDataRegs.GPBDAT.bit.GPIO34 = 0;
	SpiaRegs.SPITXBUF=spiASendData[0];

//	while( iicStartRead() != I2C_SUCCESS );


//   uint16strcpy(sciASendBuffer,(Uint16*)"*****´®¿ÚAÕý³£*****");
//   sciAReadBufferPointer=0;
//   SciaRegs.SCIFFTX.bit.TXFFIENA=1;

//   fly_enable=2;
//   spiaRxIsr();
   for(;;)
   {
//	   fly_enable=0;
//	   if(doCalulate)
//	   {
//		 dataConverse();
//		 Posture_calculate();
//		 pid();
//		 setMotor();
//		 doCalulate=0;
//	   }
//
//	   if( doSCI && SciaRegs.SCIFFTX.bit.TXFFIENA==0)
//	   {
//		   sciASendData();
//		   doSCI =0;
//	   }
//
//	   if(doSBusDecode)
//	   {
//		   sbusDecode();
//		   doSBusDecode=0;
//	   }

   }

} 
