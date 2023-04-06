#ifndef __VISION_H
#define __VISION_H
#include "main.h"
void usart1_vision_init (void);
typedef struct
{
  /* data */
	uint8_t Frame_Header; //视觉帧头
	uint8_t Data_ID;      //识别对象
	uint8_t Data_CMD;     //
	uint8_t Data_Length;  //数据帧长度
	int32_t x;            //对象x坐标 
	int32_t y;            //对象y坐标
	int32_t z;            //对象深度
	int32_t time_interval;//时间间隔
	int32_t x_c;          //x轴旋转角度
	int32_t y_c;          //y轴旋转角度
	uint8_t crc1;         //crc校验位1
	uint8_t crc2;         //crc校验位2
	uint8_t end1;         //帧尾1
	uint8_t end2;         //帧尾2
}Vision_Data;
extern Vision_Data vision_info;
#endif
