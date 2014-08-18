#include "mhc.h"
#include "GlobalVariables.h"

__interrupt void scibTxFifoIsr(void)
{
	Uint16 i=0;
    for(i=0; i< 4; i++)
    {
    	if(sciBSendBuffer[sciBSendBufferPointer]  &&  sciBSendBufferPointer<128 )//Buffer��������
    	{
    		ScibRegs.SCITXBUF = sciBSendBuffer[sciBSendBufferPointer];//����һ����
    		sciBSendBufferPointer++;
    	}
    	else
    	{
    		ScibRegs.SCIFFTX.bit.TXFFIENA=0;//���ж�
    		break;
    	}
    }
    ScibRegs.SCIFFTX.bit.TXFFINTCLR=1;  // Clear SCI Interrupt flag
    PieCtrlRegs.PIEACK.all|=0x100;      // Issue PIE ACK
}

__interrupt void scibRxFifoIsr(void)
{
	if(sciBReadBufferPointer<128)
	{
		sciBReadBuffer[sciBReadBufferPointer]=ScibRegs.SCIRXBUF.all;
		sciBReadBufferPointer++;
	}

	sciBReadAByte=1;
	sBusReadDataCopied=0;

	ScibRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
	ScibRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag
	PieCtrlRegs.PIEACK.all|=0x100;       // Issue PIE ack
}

void scib_mhc_init()
{
//	ESTOP0;
//   ScibRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback, No parity,8 char bits, async mode, idle-line protocol
   ScibRegs.SCICCR.all =0x00E7;   // 2 stop bit,  No loopback, EVEN parity,8 char bits, async mode, idle-line protocol

   ScibRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                  // Disable RX ERR, SLEEP, TXWAKE
   ScibRegs.SCICTL2.bit.TXINTENA =1;
   ScibRegs.SCICTL2.bit.RXBKINTENA =0;

   ScibRegs.SCIHBAUD = 0x0000;//100000 baud @LSPCLK = 22.5MHz (90 MHz SYSCLK).
   ScibRegs.SCILBAUD = 0x001B;

   ScibRegs.SCICCR.bit.LOOPBKENA =0; // Enable loop back
   ScibRegs.SCIFFTX.all=0xC000;
   ScibRegs.SCIFFRX.all=0x0021;
   ScibRegs.SCIFFCT.all=0x00;

   ScibRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
   ScibRegs.SCIFFTX.bit.TXFIFOXRESET=1;
   ScibRegs.SCIFFRX.bit.RXFIFORESET=1;
}

//!sbusDecode,S.BUS����
/*!
	\param p_origin  ���������׵�ַ
	\param p_result  ��Ž���׵�ַ
	��p_originÿ��byte�ߵ�λ��������11λ�ָ�
	���ߣ�����ة
	�汾��1.0
*/
void sbusDecode()
{
	Uint8 *p_origin=sBusReadData;
	Uint16 *p_result=channelsData2048;
	int16 countOrigin=0,countResult=0,i;
	Uint8 filter=0x01;
	(*p_result)=0;	//p_result����
	p_result--;		//p_result��int[0]��ʼ��p_origin��char[1]��ʼ
	for(i=0; i<176; i++)
	{
		countOrigin--;countResult--;
		if(countOrigin<0)
		{
			countOrigin=7;	//Originÿ8λָ���ƶ�
			p_origin++;
		}
		if(countResult<0)
		{
			countResult=10;					//Resultÿ11λָ���ƶ�
			(*p_result)=(*p_result)<<1;		//�������һ����λ
			p_result++;
			(*p_result)=0;
		}
		(*p_result)|=(((*p_origin)&(filter))<<10);
		(*p_result)=(*p_result)>>1;
		(*p_origin)=(*p_origin)>>1;
	}

	p_origin++;
	wireLessLost=(*p_origin)&0x04;
	digitalChannel2=(*p_origin)&0x02;//��������ͨ��������һ��������
	digitalChannel1=(*p_origin)&0x01;

	for(countResult=0;countResult<16;countResult++)//
	{
		channelsData1000[countResult]=channelsData2048[countResult]/2048.*1000;
		if(channelsData2048[countResult]<360)
			channelsData4[countResult]=0;//��
		else 	if(channelsData2048[countResult]<1016)
			channelsData4[countResult]=1;//�е�
		else 	if(channelsData2048[countResult]<1032)
			channelsData4[countResult]=2;//��
		else 	if(channelsData2048[countResult]<1688)
			channelsData4[countResult]=3;//�и�
		else
			channelsData4[countResult]=4;//��
	}

}
