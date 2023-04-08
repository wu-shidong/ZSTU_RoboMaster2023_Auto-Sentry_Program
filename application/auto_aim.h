#ifndef __AUTO_AIM_H
#define __AUTO_AIM_H
#include "pid.h"
#include "main.h"
#define AUTO_AIM_PID_KP 1.0f
#define AUTO_AIM_PID_KI 0.0f
#define AUTO_AIM_PID_KD 0.0001f

#define AUTO_AIM_PITCH_PID_KP 1.0f    //自瞄PITCH轴的比例参数P值
#define AUTO_AIM_PITCH_PID_KI 0.0f    //自瞄PITCH轴的积分参数I值
#define AUTO_AIM_PITCH_PID_KD 0.0f //自瞄PITCH轴的微分参数D值

#define AUTO_AIM_YAW_PID_KP 1.0f       //自瞄YAW轴PID的P值
#define AUTO_AIM_YAW_PID_KI 0.0f       //自瞄YAW轴PID的I值
#define AUTO_AIM_YAW_PID_KD 0.0f    //自瞄YAW轴PID的D值

#define AUTO_AIM_PID_MAX_OUT 660       //自瞄PID输出值最大不能超过660（遥控器通道最大值）
#define AUTO_AIM_PID_MAX_IOUT 10       //自瞄PID积分限幅

#define AUTO_AIM_DEADBAND 5            //自瞄死区设置

#define AUTO_AIM_YAW_SEN    -0.000002f
#define AUTO_AIM_PITCH_SEN  -0.000006f //0.005


#define AIM_TRIG_OFF  auto_aim_ctrl.aim_trigger=0  //自瞄拨弹关
#define AIM_TRIG_ON  auto_aim_ctrl.aim_trigger=1   //自瞄拨弹开

#define AIM_FRIC_OFF auto_aim_ctrl.aim_fric=0    //自瞄摩擦轮关
#define AIM_FRIC_ON auto_aim_ctrl.aim_fric=1     //自瞄摩擦轮开


//自瞄控制输出结构体，可以根据需要自行添加参数
typedef struct
{
	uint8_t aim_flag;        //自瞄标志位         [0]:失能自瞄。[1]：使能自瞄,打击对象是红方  [2]：使能自瞄,打击对象是蓝方
	uint8_t aim_trigger;     //自瞄发射弹丸标志位  [0]:失能发射。[1]：使能发射
	uint8_t aim_fric;      	  //自瞄摩擦轮标志位   [0]:失能摩擦。[1]：使能摩擦
	int16_t aim_pitch_channel;
	int16_t aim_yaw_channel;
}Auto_Aim_Control;

extern void auto_aim_init (void);
extern void auto_aim_pid_clear (void);
extern void auto_aim_control (void);
extern Auto_Aim_Control auto_aim_ctrl;
#endif
