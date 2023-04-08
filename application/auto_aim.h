#ifndef __AUTO_AIM_H
#define __AUTO_AIM_H
#include "pid.h"
#include "main.h"
#define AUTO_AIM_PID_KP 1.0f
#define AUTO_AIM_PID_KI 0.0f
#define AUTO_AIM_PID_KD 0.0001f

#define AUTO_AIM_PITCH_PID_KP 1.0f    //����PITCH��ı�������Pֵ
#define AUTO_AIM_PITCH_PID_KI 0.0f    //����PITCH��Ļ��ֲ���Iֵ
#define AUTO_AIM_PITCH_PID_KD 0.0f //����PITCH���΢�ֲ���Dֵ

#define AUTO_AIM_YAW_PID_KP 1.0f       //����YAW��PID��Pֵ
#define AUTO_AIM_YAW_PID_KI 0.0f       //����YAW��PID��Iֵ
#define AUTO_AIM_YAW_PID_KD 0.0f    //����YAW��PID��Dֵ

#define AUTO_AIM_PID_MAX_OUT 660       //����PID���ֵ����ܳ���660��ң����ͨ�����ֵ��
#define AUTO_AIM_PID_MAX_IOUT 10       //����PID�����޷�

#define AUTO_AIM_DEADBAND 5            //������������

#define AUTO_AIM_YAW_SEN    -0.000002f
#define AUTO_AIM_PITCH_SEN  -0.000006f //0.005


#define AIM_TRIG_OFF  auto_aim_ctrl.aim_trigger=0  //���鲦����
#define AIM_TRIG_ON  auto_aim_ctrl.aim_trigger=1   //���鲦����

#define AIM_FRIC_OFF auto_aim_ctrl.aim_fric=0    //����Ħ���ֹ�
#define AIM_FRIC_ON auto_aim_ctrl.aim_fric=1     //����Ħ���ֿ�


//�����������ṹ�壬���Ը�����Ҫ������Ӳ���
typedef struct
{
	uint8_t aim_flag;        //�����־λ         [0]:ʧ�����顣[1]��ʹ������,��������Ǻ췽  [2]��ʹ������,�������������
	uint8_t aim_trigger;     //���鷢�䵯���־λ  [0]:ʧ�ܷ��䡣[1]��ʹ�ܷ���
	uint8_t aim_fric;      	  //����Ħ���ֱ�־λ   [0]:ʧ��Ħ����[1]��ʹ��Ħ��
	int16_t aim_pitch_channel;
	int16_t aim_yaw_channel;
}Auto_Aim_Control;

extern void auto_aim_init (void);
extern void auto_aim_pid_clear (void);
extern void auto_aim_control (void);
extern Auto_Aim_Control auto_aim_ctrl;
#endif
