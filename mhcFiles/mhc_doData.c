#include "mhc.h"
#include "GlobalVariables.h"
#include "math.h"


void dataConverse()//i2c数据转为-1~1
{
	MPU6050Data[0]= -( (int16)(((i2cData[0]<<8) | i2cData[1] )- acceXDrift ) )*AcceXK;
	MPU6050Data[1]= ( (int16)(((i2cData[2]<<8) | i2cData[3] )- acceYDrift ) )*AcceYK ;
	MPU6050Data[2]= ( (int16)(((i2cData[4]<<8) | i2cData[5] )- acceZDrift ) )*AcceZK ;

	MPU6050Data[4]= ( (int16)(((i2cData[8]  <<8) | i2cData[9]  )- gyroXDrift ) ) / Gkx;
	MPU6050Data[5]= -( (int16)(((i2cData[10]<<8) | i2cData[11] )- gyroYDrift ) ) /Gky;
	MPU6050Data[6]= -( (int16)(((i2cData[12]<<8) | i2cData[13] )- gyroZDrift ) ) /Gkz;

	pitch_Gy += dp*dt;// MPU6050Data[5] * dt;
	roll_Gx   += dr*dt;// MPU6050Data[4] * dt ;
	yaw_Gz  += dy*dt;// MPU6050Data[6] * dt;
}


/***************************************************************************************
函数原型：void low_pass(float32 *lp_data,float32 source_data,float32 G,float32 T)
功    能：低通滤波函数
参    数：float32 *lp_data：指向滤波后的数据的指针
		  float32 source_data  ：源数据
		  float32 G			  ：滤波系数
		  float32 T			  ：调用周期
返    回：无
作    者: 肖熙吉
版	  本：1.0
时    间：2013—12-5
****************************************************************************************/
void low_pass(float32 *lp_data,float32 source_data,float32 G,float32 T)
{
 *lp_data=(*lp_data+G*source_data*T)/(1+T*G);
}



/***************************************************************************************
函数原型：Posture_calculate
功    能：由传感器数据计算姿态
****************************************************************************************/
void Posture_calculate(void)
{

	float32 Au_lp=MPU6050Data[0] , Av_lp=MPU6050Data[1] , Aw_lp=MPU6050Data[2]  ;//暂时未加低通滤波

	if(Au_lp>0.999)			 //限制范围，防止计算结果出现溢出
	  Au_lp=0.999;
	if(Au_lp<(-0.999))
	  Au_lp=-0.999;
	if(Av_lp>0.999)
	  Av_lp=0.999;
	if(Av_lp<(-0.999))
	  Av_lp=-0.999;
	if(Aw_lp<0.001&&Aw_lp>-0.001)//限制范围，防止出现除0
	  Aw_lp=0.001;

	pitch_Au=-atan(Au_lp/sqrt(Av_lp*Av_lp+Aw_lp*Aw_lp));//俯仰正向，机头抬高
	if(Aw_lp>0) 	   			//将范围扩展到-180°到180°
		roll_Av=atan(Av_lp/Aw_lp);//横滚横滚正向，机身右倾
	if((Aw_lp<0)&&(Av_lp>0))
		 roll_Av=PI+atan(Av_lp/Aw_lp);
	if((Aw_lp<0)&&(Av_lp<0))
		 roll_Av=-PI+atan(Av_lp/Aw_lp);

	 //俯仰横滚计算
//	    low_pass(&Au_lp,Au,100,dt);//30
//	    low_pass(&Av_lp,Av,100,dt);
//	    low_pass(&Aw_lp,Aw,100,dt);

		dp=Gv*cos(posture_now.roll)-Gw*sin(posture_now.roll);
		dr=Gu+(Gv*sin(posture_now.roll)+Gw*cos(posture_now.roll))*tan(posture_now.pitch);
		dy=(Gv*sin(posture_now.roll)+Gw*cos(posture_now.roll))/cos(posture_now.pitch);

//		G_pos_p=0.1;
//		G_pos_r=0.1;

		posture_now.pitch=(posture_now.pitch+dp*dt+G_pos_p*pitch_Au*dt)/(1+dt*G_pos_p); //互补滤波
		posture_now.roll=(posture_now.roll+dr*dt+G_pos_r*roll_Av*dt)/(1+dt*G_pos_r);    //互补滤波
		posture_now.yaw=yaw_Gz ; //暂时用陀螺仪积分

		if(posture_now.pitch>(PI/2))							   //限制范围到-90°到90°
			posture_now.pitch = PI/2;
		if(posture_now.pitch<(-PI/2))
			posture_now.pitch = -PI/2;
		if(posture_now.roll>PI)							   			 //限制范围到-PI°到PI°
			posture_now.roll = PI;
		if(posture_now.roll<(-PI))
			posture_now.roll = -PI;

}
