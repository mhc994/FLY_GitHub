#ifndef _MHC_H_
#define _MHC_H_

//#pragma once

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "F2806x_Device.h"         // F2806x Headerfile
#include "F2806x_Examples.h"       // F2806x Examples Headerfile
#include "F2806x_EPwm_defines.h" 	 // useful defines for initialization
#include "string.h"





#define PLL2SRC_INTOSC1 0

#define MPU6050ADDR		0x68
#define BMP085Addr

// 定义MPU6050内部地址
#define		SMPLRT_DIV			0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define		CONFIG					0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define		GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define		ACCEL_CONFIG		0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define		PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define		WHO_AM_I			0x75	//IIC地址寄存器(默认数值0x68，只读)
#define		ACCEL_XOUT_H		0x3B
#define		ACCEL_XOUT_L		0x3C
#define		ACCEL_YOUT_H		0x3D
#define		ACCEL_YOUT_L		0x3E
#define		ACCEL_ZOUT_H		0x3F
#define		ACCEL_ZOUT_L		0x40
#define		TEMP_OUT_H			0x41
#define		TEMP_OUT_L			0x42
#define		GYRO_XOUT_H		0x43
#define		GYRO_XOUT_L		0x44
#define		GYRO_YOUT_H		0x45
#define		GYRO_YOUT_L		0x46
#define		GYRO_ZOUT_H		0x47
#define		GYRO_ZOUT_L		0x48

#define SEPARATE		   '\t'	   //数据之间的间隔符，目前只支持单字符
#define RECEIVE_SEPARATE   ','



#define PI       3.14159265358979
#define g        9.806				//重力加速度
#define DEG_TO_RAD 0.017453292519943

#define PWM_PERIOD 56608 //PWM周期7086 400HZ        56608 50HZ

#define G_pa     5.0			    //气压计低通滤波
#define G_v1     0.5					//速度高通滤波
#define G_v2     0.002			  //速度高通滤波(积分)
#define G_alt1	 3.0					//超声高度融合
#define G_alt2   0.2					//气压高度融合
#define G_posi	 0.5					//位置融合
#define dt       0.0025			  //积分周期，暂时使用的是400Hz
#define Light_flux_K  0.02
#define G_height_ultrasonic_lp 2 //超声波传感器低通滤波




#define offset_roll 500.
#define offset_pitch 500.
#define MAX_PITCH_ROLL 0.500 //弧度

#define Au MPU6050Data[0]//加速度前
#define Av MPU6050Data[1]//加速度右
#define Aw MPU6050Data[2]//加速度下
#define Gu MPU6050Data[4]//陀螺仪
#define Gv MPU6050Data[5]
#define Gw MPU6050Data[6]

#define posture_D_STD 92//默认姿态控制D参数
#define posture_P_STD 280//默认姿态控制K参数














void int16_to_string(int16 data, char *string);
void uint32_to_string(Uint32 data, char *string);
void double_to_string(double data,char *string);
void double_to_string3(double data,char *string);
void string_to_one_double(char *string,double *data);
void string_to_one_int32(char *string,int32 *data);

void InitEPwm1Example(void);
void InitEPwm2Example(void);
void InitEPwm3Example(void);
void InitEPwm4Example(void);
void InitEPwm5Example(void);
void setPwm(Uint16 pwmNum,float32 pwmValue);

void scia_mhc_init(void);
void scib_mhc_init(void);
__interrupt void sciaTxFifoIsr(void);
__interrupt void sciaRxFifoIsr(void);
__interrupt void scibTxFifoIsr(void);
__interrupt void scibRxFifoIsr(void);

void sciASendData();
void uint16strcpy(Uint16* dst,Uint16* rsc);

void sbusDecode();


__interrupt void ecap1_isr(void);
//__interrupt void ecap2_isr(void);
//__interrupt void ecap3_isr(void);
void InitECapture(void);


void I2CA_Init(void);
__interrupt void i2c_int1a_isr(void);
Uint16 iicWriteByte(Uint16 slaveAddr,Uint16 regAddr,Uint16 data);
//Uint16 iicReadByte(Uint16 slaveAddr,Uint16 regAddr);
void init_I2C_devices();
void init_I2C_devices_flying();//重新初始化I2C 飞行时I2C出错则调用 初始化不成功则调用iiC_broken
void iiC_broken();//I2C配置失败
Uint16 iicStartRead();
void dataConverse();


void initDSP();
void initGlobalVariables();

__interrupt void cpu_timer0_isr(void);

void Posture_calculate(void);
void low_pass(float32 *lp_data,float32 source_data,float32 G,float32 T);
void pid();
void setMotor();


//SPI
//__interrupt void spiaTxIsr(void);
__interrupt void spiaRxIsr(void);//不使用FIFO时接收数据，发送完成，接收溢出共用此中断
void initSPI();




struct POSTURE
{
	float32 throttle;
	float32 pitch;
	float32 roll;
	float32 yaw;

};


#endif
