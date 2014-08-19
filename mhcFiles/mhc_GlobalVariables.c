#include "mhc.h"     // Device Headerfile and Examples Include File

Uint16 sciASendBuffer[128]={0};
Uint16 sciASendBufferPointer=0;
Uint16 sciAReadBuffer[128]={0};
Uint16 sciAReadBufferPointer=0;
Uint16 sciBSendBuffer[128]={0};
Uint16 sciBSendBufferPointer=0;
Uint16 sciBReadBuffer[128]={0};
Uint16 sciBReadBufferPointer=0;

Uint16 sciBReadAByte=0;//S.BUS
Uint8 sBusReadDataCopied=1;

Uint8 digitalChannel1=0,digitalChannel2=0,wireLessLost=0,sBusReadData[24];
Uint16 channelsData2048[16]={0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
float32 channelsData1000[16]={0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
Uint8 channelsData4[16]={0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};



//Uint16 i2c_Send_Complete=0;
//Uint16 i2cDataPointer=0;
//int16 i2cData[32]={0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0};
//Uint16 i2cSlaves[32]={0x68,0x68,0x68,0x68,	0x68,0x68,0x68,0x68,	0x68,0x68,0x68,0x68, 	0x68,0x68,0x68,0x68,
//								0x68,0x68,0x68,0x68, 	0x68,0x68,0x68,0x68, 	0x68,0x68,0x68,0x68, 	0x68,0x68,0x68,0x68};
//Uint16 i2cRegAddr[32]={ACCEL_XOUT_H , ACCEL_XOUT_L , ACCEL_YOUT_H , ACCEL_YOUT_L , ACCEL_ZOUT_H , ACCEL_ZOUT_L , TEMP_OUT_H , TEMP_OUT_L ,
//									GYRO_XOUT_H , GYRO_XOUT_L , GYRO_YOUT_H , GYRO_YOUT_L , GYRO_ZOUT_H , GYRO_ZOUT_L,0,0,0,0,0,0,0,0,0,0,
//									0,0,0,0,0,0,0,0};
//float32 MPU6050Data[7];
//Uint16 i2c_Send_Data=0;
//Uint16 i2c_Slave_Addr=0;
//Uint16 i2c_Reg_Addr=0;

//Uint16 i2cStatus=0;
// 0 什么都不做
// 12 I2C正在发送地址，之后要接收一个数据
// 13 I2C发完了Reg地址，正在接收一个数据
// 21 命令I2C正在发送地址和数据

// 31 读数据时从器件非应答
// 32 写数据时从器件非应答






Uint8 doCalulate=0 , doSCI=0 , doSBusDecode=0; //应该计算  应该发串口  S.Bus收完一帧且已复制,应该计算

Uint8 fly_enable=0;
//0 没有准备好，不能起飞
//1 保护开关关闭，不能起飞
//2 准备起飞，油为零
//3 飞
//Uint16 cpuTimerInterruptsWithoutSBusDecode;


int16 acceXDrift = 285;//加速度零点偏移
int16 acceYDrift = (16300-16620)/2;
int16 acceZDrift = (16580-17200)/2-295;
float32 AcceXK = ((float32)200.0)/(16050l+16090l)/1.02/100;//加速度系数
float32 AcceYK = ((float32)200.0)/(16300l+16620l)/100;
float32 AcceZK = ((float32)200.0)/(16580l+17200l)*1.018/100;
float32 gyroXDrift;//陀螺仪零点偏移
float32 gyroYDrift;
float32 gyroZDrift;
float32 Gkx=930.0 , Gky=930.0 , Gkz=930.0 ;//陀螺仪系数


float32 PIT_D=60;
float32 PIT_P=200;
float32 PIT_I=0;
float32 PIT_V=0;
float32  PIT_A=0;
float32 PIT_K=1047;

float32  ROL_D=60;
float32  ROL_P=200;
float32 ROL_I=0;
float32 ROL_V=0;
float32  ROL_A=0;
float32 ROL_K=1047;

float32  YAW_D=60;
float32  YAW_P=1146;
float32  YAW_I=57;
float32  YAW_K=1;



//float32 tmpf;
//int16 tmpi;

Uint16 cpuTime=0;

Uint32 delay;//大约10000000=7s

float32 G_pos_p=0.05 , G_pos_r=0.05 ;

float32 pitch_Au,roll_Av;
float32 pitch_Gy = 0 , roll_Gx = 0 , yaw_Gz = 0 ;
float32 dp = 0 , dr =  0 , dy = 0;//p、r、y：俯仰、横滚、偏航

float32 speed_pitch_lp=0,speed_roll_lp=0,speed_yaw_lp=0;



struct POSTURE posture_expected={0,0,0,0};
struct POSTURE posture_now={0,0,0,0};
struct POSTURE posture_error={0,0,0,0};
struct POSTURE posture_adjust={0,0,0,0};
struct POSTURE posture_speed={0,0,0,0};
struct POSTURE posture_before={0,0,0,0};


float32 height_ultrasonic=0;	//超声测距
float32 height_ultrasonic_lp=0;//超声测距低通滤波

float32 MOTOR1_PULSE=0,MOTOR2_PULSE=0,MOTOR3_PULSE=0,MOTOR4_PULSE=0,pulse_temp;


Uint16 spiPointer=0;
Uint16 spiASendData[56]=/*{0x37 ,0xbc, 0x37|0x80, 0xff,0xf5, 0xff,0xbb,0xff,0xff,0xff,0xFf, 0xff,0xff,0xff,0xFf, 0xFf,0xFf,0xFf,0xFf,0xFf*/
{
		MPU6500_PWR_MGMT_1,				0x01/*80*/,      	// Reset Device
		0x80 | MPU6500_WHO_AM_I,					0xFF,      	// check Device ID
		MPU6500_PWR_MGMT_1,				0x01,      	// Clock Source
		0x80 | MPU6500_PWR_MGMT_1,				0xFF,      	// check Clock Source
		MPU6500_PWR_MGMT_2, 				0x00,     	// Enable Acc & Gyro
		0x80 | MPU6500_PWR_MGMT_2, 				0xFF,     	// check Enable Acc & Gyro
		MPU6500_CONFIG, 						0x07,     	//
		0x80 | MPU6500_CONFIG, 						0xFF,     	// check
		0x80 | MPU6500_GYRO_CONFIG, 			0xFF,    		// check +-2000dps
		MPU6500_GYRO_CONFIG, 				0x18,    		// +-2000dps
		0x80 | MPU6500_ACCEL_CONFIG, 			0xFF,   		// check +-4G
		MPU6500_ACCEL_CONFIG, 				0x08,   		// +-4G
		0x80 | MPU6500_ACCEL_CONFIG_2,			0xFF, 		// check Set Acc Data Rates
		MPU6500_ACCEL_CONFIG_2,			0x00, 		// Set Acc Data Rates
		0x80 | MPU6500_INT_PIN_CFG,				0xFF,     	// check
		MPU6500_INT_PIN_CFG,					0x30,     	//
		0x80 | MPU6500_I2C_MST_CTRL, 				0xFF,  		// check I2C Speed 348 kHz
		MPU6500_I2C_MST_CTRL, 				0x40,  		// I2C Speed 348 kHz
		0x80 | MPU6500_USER_CTRL, 					0xFF,   	 	// check Enable AUX
		MPU6500_USER_CTRL, 					0x20,   	 	// Enable AUX
		// Set Slave to Read AK8963
		0x80 | MPU6500_I2C_SLV0_ADDR,			0xFF,   		// check AK8963_I2C_ADDR ( 7'b000_1100 )
		MPU6500_I2C_SLV0_ADDR,				0x8C,   		// AK8963_I2C_ADDR ( 7'b000_1100 )
		0x80 | MPU6500_I2C_SLV0_REG, 				0xFF,   		// check AK8963_WIA ( 0xFF )
		MPU6500_I2C_SLV0_REG, 				0x00,   		// AK8963_WIA ( 0x00 )
		0x80 | MPU6500_I2C_SLV0_CTRL,				0xFF,   		// check Enable
		MPU6500_I2C_SLV0_CTRL,				0x81,   		// Enable
		0x80 | MPU6500_I2C_MST_DELAY_CTRL, 	0xFF,			// check
		MPU6500_I2C_MST_DELAY_CTRL, 	0x01
};
Uint16 spiAReadData[56]=	{0};
Uint16 spiAStop[56]=       	{1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1, 0,1,0,1,0,   1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1, 0,1,0,1,0,   1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1, 0};

