#include "mhc.h"
#include "GlobalVariables.h"
#include "math.h"

void pid()
{
	float32 temp;
/*��̬���Ƴ���ʼ **************************************************************************************/

//������ť����PD����
	PIT_D=posture_D_STD*( 0.00074404762*channelsData2048[10]+0.238095238 );
	PIT_P=posture_P_STD*( 0.00074404762*channelsData2048[11]+0.238095238 );

//��ң��������

	temp=channelsData1000[2];
	posture_expected.throttle= ( (0.0000044*temp - 0.0065)*temp + 3.6273) * temp - 281.7;
	posture_expected.roll=(channelsData1000[0]-offset_roll)/500*MAX_PITCH_ROLL;
	posture_expected.pitch=(offset_pitch-channelsData1000[1])/500*MAX_PITCH_ROLL;

//���Ʒ�Χ
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

//����error
	  posture_error.pitch =posture_expected.pitch-posture_now.pitch; //������:Ŀ��ֵ��ȥ��ǰֵ
	  posture_error.roll  = posture_expected.roll-posture_now.roll;
	  posture_error.yaw   = posture_expected.yaw-posture_now.yaw;

//���ٶ�speed����
	  posture_speed.pitch=(posture_now.pitch-posture_before.pitch)/dt;
	  posture_speed.roll=(posture_now.roll-posture_before.roll)/dt;
	  posture_speed.yaw=(posture_now.yaw-posture_before.yaw)/dt;

 //�����ͨ�˲�Speed
	  low_pass(&speed_pitch_lp,posture_speed.pitch,50,dt);
	  low_pass(&speed_roll_lp,posture_speed.roll,50,dt);
	  low_pass(&speed_yaw_lp,posture_speed.yaw,50,dt);

	  posture_adjust.yaw = ( -YAW_D*speed_yaw_lp+YAW_P*posture_error.yaw)*posture_expected.throttle/1000.0;
	  posture_adjust.pitch = ( -PIT_D*speed_pitch_lp+PIT_P*posture_error.pitch)*posture_expected.throttle/1000.0;//+PIT_I*posture_error.pitch_I+PIT_V*Vx-PIT_A*Ax_lp //������Ϊ��������ֵ�����ٶ�Ϊ��������ֵ
	  posture_adjust. roll  = (-ROL_D*speed_roll_lp  +ROL_P*posture_error.roll) *posture_expected.throttle/1000.0;//+ROL_I*posture_error.roll_I-ROL_V*Vy+ROL_A*Ay_lp
//ÿ��adjust��Ҫ���Ʒ�Χ��Ҫ��

	  posture_before  = posture_now;	//������̬
//	 /********************************************************
//	 ��̬���Ƴ������*/
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

	pulse_temp = posture_expected.throttle+posture_adjust.pitch+posture_adjust.roll-posture_adjust.yaw;//���һ
	if(pulse_temp>999)									   //���Ʒ�Χ�ڵ���趨�Ľ��ܷ�Χ֮��
		pulse_temp=999;
	if(pulse_temp<0)
		pulse_temp=0;
	MOTOR1_PULSE= pulse_temp;

	pulse_temp = posture_expected.throttle+posture_adjust.pitch-posture_adjust.roll+posture_adjust.yaw;//�����
	if(pulse_temp>999)
		pulse_temp=999;
	if(pulse_temp<0)
		pulse_temp=0;
	MOTOR2_PULSE= pulse_temp;

	pulse_temp = posture_expected.throttle-posture_adjust.pitch-posture_adjust.roll-posture_adjust.yaw;//�����
	if(pulse_temp>999)
		pulse_temp=999;
	if(pulse_temp<0)
		pulse_temp=0;
	MOTOR3_PULSE=pulse_temp;

	pulse_temp = posture_expected.throttle-posture_adjust.pitch+posture_adjust.roll+posture_adjust.yaw;//�����
	if(pulse_temp>999)
		pulse_temp=999;
	if(pulse_temp<0)
		pulse_temp=0;
	MOTOR4_PULSE= pulse_temp;


	if(fly_enable==3 )  //������ɣ����򲻸�������
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
	��������������
	*************************************************************************/
}
