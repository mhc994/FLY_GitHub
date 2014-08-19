#ifndef __GlobalVar_h__
#define __GlobalVar_h__
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "F2806x_Device.h"         // F2806x Headerfile
#include "F2806x_Examples.h"       // F2806x Examples Headerfile
#include "F2806x_EPwm_defines.h" 	 // useful defines for initialization

extern Uint16 sciASendBuffer[128];
extern Uint16 sciASendBufferPointer;
extern Uint16 sciAReadBuffer[128];
extern Uint16 sciAReadBufferPointer;
extern Uint16 sciBSendBuffer[128];
extern Uint16 sciBSendBufferPointer;
extern Uint16 sciBReadBuffer[128];
extern Uint16 sciBReadBufferPointer;

extern Uint16 sciBReadAByte;//S.BUS
extern Uint8 sBusReadDataCopied,digitalChannel1,digitalChannel2,wireLessLost,sBusReadData[24];
extern Uint16 channelsData2048[16];
extern float32 channelsData1000[16];
extern Uint8 channelsData4[16];



//extern Uint16 i2cDataPointer;
//extern int16 i2cData[32];
//extern Uint16 i2cSlaves[32];
//extern Uint16 i2cRegAddr[32];
//extern float32 MPU6050Data[7];
//extern Uint16 i2cStatus;
//
//extern Uint16 i2c_Send_Data;
//extern Uint16 i2c_Slave_Addr;
//extern Uint16 i2c_Reg_Addr;
//extern Uint16 i2c_Send_Complete;



extern Uint8 doCalulate , doSCI , doSBusDecode ;
extern Uint8 fly_enable; //3可以起飞


extern Uint16 acceXDrift ;
extern Uint16 acceYDrift ;
extern Uint16 acceZDrift ;
extern float32 AcceXK ;
extern float32 AcceYK ;
extern float32 AcceZK ;
extern float32 Gkx , Gky , Gkz ;
extern float32 gyroXDrift;
extern float32 gyroYDrift;
extern float32 gyroZDrift;


extern float32 PIT_D;
extern float32 PIT_P;
extern float32 PIT_I;
extern float32 PIT_V;
extern float32  PIT_A;
extern float32 PIT_K;

extern float32  ROL_D;
extern float32  ROL_P;
extern float32 ROL_I;
extern float32 ROL_V;
extern float32  ROL_A;
extern float32 ROL_K;

extern float32  YAW_D;
extern float32  YAW_P;
extern float32  YAW_I;
extern float32  YAW_K;


//extern float32 tmpf;
//extern int16 tmpi;

extern Uint16 cpuTime;

extern Uint32 delay;//大约10000000=7s

extern float32 G_pos_p , G_pos_r ;

extern float32 pitch_Au,roll_Av;
extern float32 pitch_Gy , roll_Gx , yaw_Gz ;

extern float32 dp,dr,dy;//p、r、y：俯仰、横滚、偏航

extern float32 speed_pitch_lp,speed_roll_lp,speed_yaw_lp;//低通滤波数据


extern struct POSTURE posture_expected;//期望值
extern struct POSTURE posture_now;
extern struct POSTURE posture_error;
extern struct POSTURE posture_adjust;
extern struct POSTURE posture_speed;
extern struct POSTURE posture_before;


extern float32 height_ultrasonic;
extern float32 height_ultrasonic_lp;


extern float32 MOTOR1_PULSE,MOTOR2_PULSE,MOTOR3_PULSE,MOTOR4_PULSE,pulse_temp;

extern Uint16 spiPointer;
extern Uint16 spiASendData[56];
extern Uint16 spiAReadData[56];
extern Uint16 spiAStop[56];

#endif
