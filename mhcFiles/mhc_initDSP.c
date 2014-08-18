#include "mhc.h"
#include "GlobalVariables.h"

void initDSP()
{
	Uint16 i;

	// Step 1. Initialize System Control: PLL, WatchDog, enable Peripheral Clocks, This example function is found in the F2806x_SysCtrl.c file.
	   InitSysCtrl();
	   InitPll2(PLL2SRC_INTOSC1, 1, PLL2_SYSCLK2DIV2DIS);

	   initGlobalVariables();

	// Step 2. Initalize GPIO:  This example function is found in the F2806x_Gpio.c file and
	   InitI2CGpio();
	   InitECap1Gpio();
//	   InitECap2Gpio();
//	   InitECap3Gpio();
	   InitSciaGpio();
	   InitScibGpio();
	   InitEPwm1Gpio();
	   InitEPwm2Gpio();
	   InitEPwm3Gpio();
	   InitEPwm4Gpio();
	   InitEPwm5Gpio();
	   InitSpiaGpio();

	   EALLOW;
	   GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0; //����GPIO34ΪGPout
	   GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;
		GpioDataRegs.GPBDAT.bit.GPIO34 = 1;
//	   GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 3;//ϵͳʱ�����
	    EDIS;


	// Step 3. Clear all interrupts and initialize PIE vector table:
	// Disable CPU interrupts
	   DINT;

	// Initialize the PIE control registers to their default state.
	// The default state is all PIE interrupts disabled and flags are cleared.
	// This function is found in the F2806x_PieCtrl.c file.
	   InitPieCtrl();

	// Disable CPU interrupts and clear all CPU interrupt flags:
	   IER = 0x0000;
	   IFR = 0x0000;

	// Initialize the PIE vector table with pointers to the shell Interrupt
	// Service Routines (ISR).
	// This will populate the entire table, even if the interrupt
	// is not used in this example.  This is useful for debug purposes.
	// The shell ISR routines are found in F2806x_DefaultIsr.c.
	// This function is found in F2806x_PieVect.c.
	   InitPieVectTable();

	// Interrupts that are used in this example are re-mapped to
	// ISR functions found within this file.
	   EALLOW;  // This is needed to write to EALLOW protected registers
	   PieVectTable.SCIRXINTA = &sciaRxFifoIsr;
	   PieVectTable.SCITXINTA = &sciaTxFifoIsr;
	   PieVectTable.SCIRXINTB = &scibRxFifoIsr;
	   PieVectTable.SCITXINTB = &scibTxFifoIsr;
	   PieVectTable.ECAP1_INT = &ecap1_isr;
//	   PieVectTable.ECAP2_INT = &ecap2_isr;
//	   PieVectTable.ECAP3_INT = &ecap3_isr;
//	   PieVectTable.I2CINT1A = &i2c_int1a_isr;
	   PieVectTable.TINT0 = &cpu_timer0_isr;
	   PieVectTable.SPIRXINTA = &spiaRxIsr;  //������FIFOʱ�������ݣ�������ɣ�����������ô��ж�
//	   PieVectTable.SPITXINTA = &spiaTxIsr;
	//   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	   EDIS;    // This is needed to disable write to EALLOW protected registers

	// Step 4. Initialize all the Device Peripherals:
	// This function is found in F2806x_InitPeripherals.c
	// InitPeripherals();  // Not required for this example
	   InitCpuTimers();
	   ConfigCpuTimer(&CpuTimer0, 90, 2500);
	   CpuTimer0Regs.TCR.all = 0x4000;

//	   I2CA_Init();
	   scia_mhc_init();
	   scib_mhc_init();
	   InitECapture();
	   InitEPwm1Example();
	   InitEPwm2Example();
	   InitEPwm3Example();
	   InitEPwm4Example();
	   InitEPwm5Example();
	   initSPI();



	   EALLOW;
	   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	   EDIS;


	// Enable global Interrupts and higher priority real-time debug events:
	   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
	   PieCtrlRegs.PIEIER9.bit.INTx1=1;     // PIE Group 9, INT1 SCIA
	   PieCtrlRegs.PIEIER9.bit.INTx2=1;     // PIE Group 9, INT2
	   PieCtrlRegs.PIEIER9.bit.INTx3=1;//SCIB
	   PieCtrlRegs.PIEIER9.bit.INTx4=1;
	   PieCtrlRegs.PIEIER4.bit.INTx1 = 1;//ecap1
//	   PieCtrlRegs.PIEIER4.bit.INTx2 = 1;//ecap2
//	   PieCtrlRegs.PIEIER4.bit.INTx3 = 1;//ecap3
//	   PieCtrlRegs.PIEIER8.bit.INTx1 = 1;//I2C
	   PieCtrlRegs.PIEIER1.bit.INTx7 = 1;//CPUtimer0
	   PieCtrlRegs.PIEIER6.bit.INTx1=1;     // Enable PIE Group 6, INT 1 , SPI
//	   PieCtrlRegs.PIEIER6.bit.INTx2=1;     // Enable PIE Group 6, INT 2 , SPI

	   IER = 0x100; // Enable CPU INT ������SCI��
	   IER |= M_INT6;        //SPI
	   IER |= M_INT8;		//I2C
	   IER |= M_INT4;    // Enable CPU INT4,  ecap1 2 3
	   IER |= M_INT1;				//CPUtimer0
	   EINT;   // Enable Global interrupt INTM
	   ERTM;   // Enable Global realtime interrupt DBGM


	   setPwm(1,0);//�������Ϊ0
	   setPwm(2,0);
	   setPwm(3,0);
	   setPwm(4,0);
	   setPwm(5,0);


	   for(i=0;i<128;i++)
		   sciBReadBuffer[i]=0;
	   for(i=0;i<16;i++)
		   channelsData2048[i]=0;
	   for(i=0;i<16;i++)
		   channelsData1000[i]=0;


	   for(delay=2000000;delay>0;delay--);//��ʱ
}

void initGlobalVariables()
{
	Uint16 i;

	for(i=0;i<128;i++)
	{
		sciASendBuffer[i]=0;
		sciAReadBuffer[i]=0;
		sciBSendBuffer[i]=0;
		sciBReadBuffer[i]=0;
	}


	sciBReadAByte=0;//S.BUS
	sBusReadDataCopied=1;
	digitalChannel1=0;
	digitalChannel2=0;
	wireLessLost=0;

	for(i=0;i<16;i++)
	{
		channelsData2048[i]=0;
		channelsData1000[i]=0;
		channelsData4[i]=0;
	}
	for(i=0;i<24;i++)
		sBusReadData[i]=0;


//	i2c_Send_Complete=0;
//	i2cDataPointer=0;
//	int16 i2cData[32]={0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0};//���ø��� Ҫ�ģ�����
//	Uint16 i2cSlaves[32]={0x68,0x68,0x68,0x68,	0x68,0x68,0x68,0x68,	0x68,0x68,0x68,0x68, 	0x68,0x68,0x68,0x68,
//									0x68,0x68,0x68,0x68, 	0x68,0x68,0x68,0x68, 	0x68,0x68,0x68,0x68, 	0x68,0x68,0x68,0x68};
//	Uint16 i2cRegAddr[32]={ACCEL_XOUT_H , ACCEL_XOUT_L , ACCEL_YOUT_H , ACCEL_YOUT_L , ACCEL_ZOUT_H , ACCEL_ZOUT_L , TEMP_OUT_H , TEMP_OUT_L ,
//										GYRO_XOUT_H , GYRO_XOUT_L , GYRO_YOUT_H , GYRO_YOUT_L , GYRO_ZOUT_H , GYRO_ZOUT_L,0,0,0,0,0,0,0,0,0,0,
//										0,0,0,0,0,0,0,0};
//	float32 MPU6050Data[7];
//	i2c_Send_Data=0;
//	i2c_Slave_Addr=0;
//	i2c_Reg_Addr=0;



	i2cStatus=0;
	// 0 ʲô������
	// 12 I2C���ڷ��͵�ַ��֮��Ҫ����һ������
	// 13 I2C������Reg��ַ�����ڽ���һ������
	// 21 ����I2C���ڷ��͵�ַ������

	// 31 ������ʱ��������Ӧ��
	// 32 д����ʱ��������Ӧ��






	doCalulate=0 ;//Ӧ�ü���  Ӧ�÷�����  S.Bus����һ֡���Ѹ���,Ӧ�ü���
	doSCI=0;
	doSBusDecode=0;

	fly_enable=0; //3�������



	acceXDrift = 285;//���ٶ����ƫ��
//	acceYDrift = (16300-16620)/2;
//	acceZDrift = (16580-17200)/2-295;
	AcceXK = ((float32)200.0)/(16050l+16090l)/1.02/100;//���ٶ�ϵ��
	AcceYK = ((float32)200.0)/(16300l+16620l)/100;
	AcceZK = ((float32)200.0)/(16580l+17200l)*1.018/100;
	gyroXDrift=-24.6623;//���������ƫ��
	gyroYDrift=-13.71428571;
	gyroZDrift=5.25974026;
	Gkx=930.0;//������ϵ��
	Gky=930.0;
	Gkz=930.0;


	PIT_D=60;
	PIT_P=200;
	PIT_I=0;
	PIT_V=0;
	PIT_A=0;
	PIT_K=1047;

	ROL_D=60;
	ROL_P=200;
	ROL_I=0;
	ROL_V=0;
	ROL_A=0;
	ROL_K=1047;

	YAW_D=60;
	YAW_P=1146;
	YAW_I=57;
	YAW_K=1;


	cpuTime=0;

//	delay;//��Լ10000000=7s

	G_pos_p=0.1;
	G_pos_r=0.1 ;

//	float32 pitch_Au,roll_Av;
	pitch_Gy = 0;
	roll_Gx = 0 ;
	yaw_Gz = 0 ;
	dp = 0;
	dr =  0 ;
	dy = 0;//p��r��y�������������ƫ��

	speed_pitch_lp=0;
	speed_roll_lp=0;
	speed_yaw_lp=0;



//	posture_expected={0,0,0,0};
//	posture_now={0,0,0,0};
//	posture_error={0,0,0,0};
//	posture_adjust={0,0,0,0};
//	posture_speed={0,0,0,0};
//	posture_before={0,0,0,0};

	MOTOR1_PULSE=0;
	MOTOR2_PULSE=0;
	MOTOR3_PULSE=0;
	MOTOR4_PULSE=0;
//	pulse_temp;
}

