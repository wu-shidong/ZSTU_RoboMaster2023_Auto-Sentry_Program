#ifndef __VISION_H
#define __VISION_H
#include "main.h"
void usart1_vision_init (void);
typedef struct
{
  /* data */
	uint8_t Frame_Header; //�Ӿ�֡ͷ
	uint8_t Data_ID;      //ʶ�����
	uint8_t Data_CMD;     //
	uint8_t Data_Length;  //����֡����
	int32_t x;            //����x���� 
	int32_t y;            //����y����
	int32_t z;            //�������
	int32_t time_interval;//ʱ����
	int32_t x_c;          //x����ת�Ƕ�
	int32_t y_c;          //y����ת�Ƕ�
	uint8_t crc1;         //crcУ��λ1
	uint8_t crc2;         //crcУ��λ2
	uint8_t end1;         //֡β1
	uint8_t end2;         //֡β2
}Vision_Data;
extern Vision_Data vision_info[2];
#endif
