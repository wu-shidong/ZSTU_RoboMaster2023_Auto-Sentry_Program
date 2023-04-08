/**
 * @file auto_aim.c/h
 * @author Epsilon Wu 
 * @brief �ڱ��Զ���׼����
 * @version 0.1
 * @date 2023-04-06
 * @copyright Copyright (c) 2023
 * 
 */
#include "auto_aim.h"
#include "vision.h"
static const fp32 auto_aim_pitch_pid_set[3] = {AUTO_AIM_PITCH_PID_KP, AUTO_AIM_PITCH_PID_KI, AUTO_AIM_PITCH_PID_KD};
static const fp32 auto_aim_yaw_pid_set[3] = {AUTO_AIM_YAW_PID_KP, AUTO_AIM_YAW_PID_KI, AUTO_AIM_YAW_PID_KD};
pid_type_def auto_aim_pitch_pid; //����pitch��pid�ṹ��
pid_type_def auto_aim_yaw_pid; //����yaw��pid�ṹ��
Auto_Aim_Control auto_aim_ctrl; //�����������ṹ��


/**
  * @brief auto_aim_init
   ���������ʼ������  ����λ��ʽpid����;
	 �����������λ��Ϊgimbal_task.c�е�gimbal_init����
   ��Լ��gimbal_task.c��665�У�

  * @param[out]    none
  * @retva   none
  */
void auto_aim_init (void)
{
	PID_init(&auto_aim_pitch_pid,PID_POSITION,auto_aim_pitch_pid_set,AUTO_AIM_PID_MAX_OUT,AUTO_AIM_PID_MAX_IOUT);
	PID_init(&auto_aim_yaw_pid,PID_POSITION,auto_aim_yaw_pid_set,AUTO_AIM_PID_MAX_OUT,AUTO_AIM_PID_MAX_IOUT);
  auto_aim_ctrl.aim_flag=1;
}



/**
  * @brief 
����PID���ã���գ�
�����������λ��Ϊgimbal_task.c�е�gimbal_init����
��Լ��gimbal_task.c��671�У�
  * @param[out]    none
  * @retva   none
  */
void auto_aim_pid_clear (void)
{
	PID_clear(&auto_aim_pitch_pid);
	PID_clear(&auto_aim_yaw_pid);
}


/**
  * @brief  ����PID���㣬�ο�����ֵΪ�Ӿ����յ��ľ������ĵ�ľ��룬�趨ֵΪ0
  * @param[out]    none
  * @retva   none
  */
void auto_aim_follow(void)
{
  auto_aim_ctrl.aim_pitch_channel=(int16_t)PID_calc(&auto_aim_pitch_pid,-vision_info[auto_aim_ctrl.aim_flag-1].y,0);
  auto_aim_ctrl.aim_yaw_channel=(int16_t)PID_calc(&auto_aim_yaw_pid,-vision_info[auto_aim_ctrl.aim_flag-1].x,0);     
  
}

/**
  * @brief 
�����������λ��Ϊgimbal_task.c�е�gimbal_control_loop����
��Լ��gimbal_task.c��999�У�
  * @param[out]    none
  * @retva   none
  */
void auto_aim_control (void)
{
  if(auto_aim_ctrl.aim_flag)//ʹ�ܺ����б��γ���
  {
    if(vision_info[auto_aim_ctrl.aim_flag-1].Data_CMD==0)//û�д�������Ŀ�꣬������ֵ����һ��������ת��ѰĿ��
    {
      AIM_TRIG_OFF;//������
      AIM_FRIC_OFF;//Ħ���ֹ�
      auto_aim_ctrl.aim_pitch_channel=0;//PITCH��ƽ���ӽ�
      auto_aim_ctrl.aim_yaw_channel=-50;//YAW��ת
    }
    else
    {
      auto_aim_follow();//��Ŀ����и���
      if (vision_info[auto_aim_ctrl.aim_flag-1].Data_CMD==1)//ʶ�𵽻�����󣬿�ʼ����
      {
        AIM_FRIC_ON;//Ħ���ֿ�
        AIM_TRIG_OFF;//������
      }
      else if(vision_info[auto_aim_ctrl.aim_flag-1].Data_CMD==2) //��ʶ�������󣬲��ҿɻ���    
      {
        AIM_TRIG_ON;//������
      }
    }
  }
}
