/**
 * @file auto_aim.c/h
 * @author Epsilon Wu 
 * @brief 哨兵自动瞄准程序
 * @version 0.1
 * @date 2023-04-06
 * @copyright Copyright (c) 2023
 * 
 */
#include "auto_aim.h"
#include "vision.h"
static const fp32 auto_aim_pitch_pid_set[3] = {AUTO_AIM_PITCH_PID_KP, AUTO_AIM_PITCH_PID_KI, AUTO_AIM_PITCH_PID_KD};
static const fp32 auto_aim_yaw_pid_set[3] = {AUTO_AIM_YAW_PID_KP, AUTO_AIM_YAW_PID_KI, AUTO_AIM_YAW_PID_KD};
pid_type_def auto_aim_pitch_pid; //自瞄pitch轴pid结构体
pid_type_def auto_aim_yaw_pid; //自瞄yaw轴pid结构体
Auto_Aim_Control auto_aim_ctrl; //自瞄控制输出结构体


/**
  * @brief auto_aim_init
   自瞄参数初始化函数  采用位置式pid计算;
	 插入主程序的位置为gimbal_task.c中的gimbal_init函数
   大约在gimbal_task.c（665行）

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
自瞄PID重置（清空）
插入主程序的位置为gimbal_task.c中的gimbal_init函数
大约在gimbal_task.c（671行）
  * @param[out]    none
  * @retva   none
  */
void auto_aim_pid_clear (void)
{
	PID_clear(&auto_aim_pitch_pid);
	PID_clear(&auto_aim_yaw_pid);
}


/**
  * @brief  自瞄PID计算，参考输入值为视觉接收到的距离中心点的距离，设定值为0
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
插入主程序的位置为gimbal_task.c中的gimbal_control_loop函数
大约在gimbal_task.c（999行）
  * @param[out]    none
  * @retva   none
  */
void auto_aim_control (void)
{
  if(auto_aim_ctrl.aim_flag)//使能后运行本段程序
  {
    if(vision_info[auto_aim_ctrl.aim_flag-1].Data_CMD==0)//没有打击对象的目标，持续给值，朝一个方向旋转搜寻目标
    {
      AIM_TRIG_OFF;//拨弹关
      AIM_FRIC_OFF;//摩擦轮关
      auto_aim_ctrl.aim_pitch_channel=0;//PITCH轴平行视角
      auto_aim_ctrl.aim_yaw_channel=-50;//YAW轴转
    }
    else
    {
      auto_aim_follow();//对目标进行跟踪
      if (vision_info[auto_aim_ctrl.aim_flag-1].Data_CMD==1)//识别到击打对象，开始跟踪
      {
        AIM_FRIC_ON;//摩擦轮开
        AIM_TRIG_OFF;//拨弹关
      }
      else if(vision_info[auto_aim_ctrl.aim_flag-1].Data_CMD==2) //已识别击打对象，并且可击打    
      {
        AIM_TRIG_ON;//拨弹开
      }
    }
  }
}
