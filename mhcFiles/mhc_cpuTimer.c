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

	if(sciBReadAByte==0 && sBusReadDataCopied==0)//����һ֡
	{
		{
			   for(i=0;i<24;i++)
				   sBusReadData[i]=sciBReadBuffer[i];//����24�ֽڵ�sBusReadData

			   for(i=0;i<25;i++)
				   sciBReadBuffer[i]=0;//����
			   sciBReadBufferPointer=0;//������һ֡

			   sBusReadDataCopied=1;
			   doSBusDecode=1;
		}
	}
	else
		sciBReadAByte=0;

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
