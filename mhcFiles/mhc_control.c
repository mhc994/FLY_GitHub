#include "mhc.h"
#include "GlobalVariables.h"
#include "math.h"

void pid()
{
	float32 temp;
/*姿态控制程序开始 **************************************************************************************/

//根据旋钮设置PD参数
	PIT_D=posture_D_STD*( 0.00074404762*channelsData2048[10]+0.238095238 );
	PIT_P=posture_P_STD*( 0.00074404762*channelsData2048[11]+0.238095238 );

//从遥控器读数

	temp=channelsData1000[2];
	posture_expected.throttle= ( (0.0000044*temp - 0.0065)*temp + 3.6273) * temp - 281.7;
	posture_expected.roll=(channelsData1000[0]-offset_roll)/500*MAX_PITCH_ROLL;
	posture_expected.pitch=(offset_pitch-channelsData1000[1])/500*MAX_PITCH_ROLL;

//限制范围
	 if(posture_expected.throttle<230.0)
	 {
		 posture_expected.throttle=0;
		 posture_expected.yaw=posture_now.yaw;
	 }
	 else if(posture_expected.throttle>999)
		 posture_expected.throttle=999;

	 if(posture_expected.pitch>MAX_PITCH_ROLL)
		 posture_expected.pitch=MAX_PITCH_ROLL;
	 else if(posture_expected.pitch<-MAX_PITCH_ROLL)
		 posture_expected.pitch=-MAX_PITCH_ROLL;

	 if(posture_expected.roll>MAX_PITCH_ROLL)
		 posture_expected.roll=MAX_PITCH_ROLL;
	 else if(posture_expected.roll<-MAX_PITCH_ROLL)
		 posture_expected.roll=-MAX_PITCH_ROLL;

//计算error
	  posture_error.pitch =posture_expected.pitch-posture_now.pitch; //误差计算:目标值减去当前值
	  posture_error.roll  = posture_expected.roll-posture_now.roll;
	  posture_error.yaw   = posture_expected.yaw-posture_now.yaw;

//角速度speed计算
	  posture_speed.pitch=(posture_now.pitch-posture_before.pitch)/dt;
	  posture_speed.roll=(posture_now.roll-posture_before.roll)/dt;
	  posture_speed.yaw=(posture_now.yaw-posture_before.yaw)/dt;

 //计算低通滤波Speed
	  low_pass(&speed_pitch_lp,posture_speed.pitch,50,dt);
	  low_pass(&speed_roll_lp,posture_speed.roll,50,dt);
	  low_pass(&speed_yaw_lp,posture_speed.yaw,50,dt);

	  posture_adjust.yaw = ( -YAW_D*speed_yaw_lp+YAW_P*posture_error.yaw)*posture_expected.throttle/1000.0;
	  posture_adjust.pitch = ( -PIT_D*speed_pitch_lp+PIT_P*posture_error.pitch)*posture_expected.throttle/1000.0;//+PIT_I*posture_error.pitch_I+PIT_V*Vx-PIT_A*Ax_lp //当俯仰为正产生正值，当速度为负产生正值
	  posture_adjust. roll  = (-ROL_D*speed_roll_lp  +ROL_P*posture_error.roll) *posture_expected.throttle/1000.0;//+ROL_I*posture_error.roll_I-ROL_V*Vy+ROL_A*Ay_lp
//每个adjust都要限制范围，要改

	  posture_before  = posture_now;	//更新姿态
//	 /********************************************************
//	 姿态控制程序结束*/
}

void setMotor()
{

	if(fly_enable!=0)
	{
		if( channelsData4[9]==0 )
		{
			if(posture_expected.throttle>230 )
				fly_enable=3;
			else
				fly_enable=2;
		}
		else
			fly_enable=1;
	}

	pulse_temp = posture_expected.throttle+posture_adjust.pitch+posture_adjust.roll-posture_adjust.yaw;//电机一
	if(pulse_temp>999)									   //限制范围在电调设定的接受范围之内
		pulse_temp=999;
	if(pulse_temp<0)
		pulse_temp=0;
	MOTOR1_PULSE= pulse_temp;

	pulse_temp = posture_expected.throttle+posture_adjust.pitch-posture_adjust.roll+posture_adjust.yaw;//电机二
	if(pulse_temp>999)
		pulse_temp=999;
	if(pulse_temp<0)
		pulse_temp=0;
	MOTOR2_PULSE= pulse_temp;

	pulse_temp = posture_expected.throttle-posture_adjust.pitch-posture_adjust.roll-posture_adjust.yaw;//电机三
	if(pulse_temp>999)
		pulse_temp=999;
	if(pulse_temp<0)
		pulse_temp=0;
	MOTOR3_PULSE=pulse_temp;

	pulse_temp = posture_expected.throttle-posture_adjust.pitch+posture_adjust.roll+posture_adjust.yaw;//电机四
	if(pulse_temp>999)
		pulse_temp=999;
	if(pulse_temp<0)
		pulse_temp=0;
	MOTOR4_PULSE= pulse_temp;


	if(fly_enable==3 )  //可以起飞，否则不给马达输出
	{
		setPwm(1,MOTOR1_PULSE) ;
		setPwm(2,MOTOR2_PULSE) ;
		setPwm(3,MOTOR3_PULSE) ;
		setPwm(4,MOTOR4_PULSE) ;
	 }
	else
	{
		setPwm(1,0) ;
		setPwm(2,0) ;
		setPwm(3,0) ;
		setPwm(4,0) ;
	}
	/************************************************************************
	电机操作程序结束
	*************************************************************************/
}
