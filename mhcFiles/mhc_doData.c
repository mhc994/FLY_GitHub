#include "mhc.h"
#include "GlobalVariables.h"
#include "math.h"


void dataConverse()//i2c����תΪ-1~1
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
����ԭ�ͣ�void low_pass(float32 *lp_data,float32 source_data,float32 G,float32 T)
��    �ܣ���ͨ�˲�����
��    ����float32 *lp_data��ָ���˲�������ݵ�ָ��
		  float32 source_data  ��Դ����
		  float32 G			  ���˲�ϵ��
		  float32 T			  ����������
��    �أ���
��    ��: Ф����
��	  ����1.0
ʱ    �䣺2013��12-5
****************************************************************************************/
void low_pass(float32 *lp_data,float32 source_data,float32 G,float32 T)
{
 *lp_data=(*lp_data+G*source_data*T)/(1+T*G);
}



/***************************************************************************************
����ԭ�ͣ�Posture_calculate
��    �ܣ��ɴ��������ݼ�����̬
****************************************************************************************/
void Posture_calculate(void)
{

	float32 Au_lp=MPU6050Data[0] , Av_lp=MPU6050Data[1] , Aw_lp=MPU6050Data[2]  ;//��ʱδ�ӵ�ͨ�˲�

	if(Au_lp>0.999)			 //���Ʒ�Χ����ֹ�������������
	  Au_lp=0.999;
	if(Au_lp<(-0.999))
	  Au_lp=-0.999;
	if(Av_lp>0.999)
	  Av_lp=0.999;
	if(Av_lp<(-0.999))
	  Av_lp=-0.999;
	if(Aw_lp<0.001&&Aw_lp>-0.001)//���Ʒ�Χ����ֹ���ֳ�0
	  Aw_lp=0.001;

	pitch_Au=-atan(Au_lp/sqrt(Av_lp*Av_lp+Aw_lp*Aw_lp));//�������򣬻�ͷ̧��
	if(Aw_lp>0) 	   			//����Χ��չ��-180�㵽180��
		roll_Av=atan(Av_lp/Aw_lp);//���������򣬻�������
	if((Aw_lp<0)&&(Av_lp>0))
		 roll_Av=PI+atan(Av_lp/Aw_lp);
	if((Aw_lp<0)&&(Av_lp<0))
		 roll_Av=-PI+atan(Av_lp/Aw_lp);

	 //�����������
//	    low_pass(&Au_lp,Au,100,dt);//30
//	    low_pass(&Av_lp,Av,100,dt);
//	    low_pass(&Aw_lp,Aw,100,dt);

		dp=Gv*cos(posture_now.roll)-Gw*sin(posture_now.roll);
		dr=Gu+(Gv*sin(posture_now.roll)+Gw*cos(posture_now.roll))*tan(posture_now.pitch);
		dy=(Gv*sin(posture_now.roll)+Gw*cos(posture_now.roll))/cos(posture_now.pitch);

//		G_pos_p=0.1;
//		G_pos_r=0.1;

		posture_now.pitch=(posture_now.pitch+dp*dt+G_pos_p*pitch_Au*dt)/(1+dt*G_pos_p); //�����˲�
		posture_now.roll=(posture_now.roll+dr*dt+G_pos_r*roll_Av*dt)/(1+dt*G_pos_r);    //�����˲�
		posture_now.yaw=yaw_Gz ; //��ʱ�������ǻ���

		if(posture_now.pitch>(PI/2))							   //���Ʒ�Χ��-90�㵽90��
			posture_now.pitch = PI/2;
		if(posture_now.pitch<(-PI/2))
			posture_now.pitch = -PI/2;
		if(posture_now.roll>PI)							   			 //���Ʒ�Χ��-PI�㵽PI��
			posture_now.roll = PI;
		if(posture_now.roll<(-PI))
			posture_now.roll = -PI;

}
