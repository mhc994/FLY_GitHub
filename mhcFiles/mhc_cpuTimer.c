#include "mhc.h"
#include "GlobalVariables.h"

__interrupt void cpu_timer0_isr(void)
{
	Uint16 i;
	if(cpuTime++>20000)
		cpuTime=0;

	if(cpuTime%80==0)
		doSCI=1;

	doCalulate=1;

	if(sciBReadAByte==0 && sBusReadDataCopied==0)//读完一帧
	{
		{
			   for(i=0;i<24;i++)
				   sBusReadData[i]=sciBReadBuffer[i];//复制24字节到sBusReadData

			   for(i=0;i<25;i++)
				   sciBReadBuffer[i]=0;//清零
			   sciBReadBufferPointer=0;//接收下一帧

			   sBusReadDataCopied=1;
			   doSBusDecode=1;
		}
	}
	else
		sciBReadAByte=0;

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
