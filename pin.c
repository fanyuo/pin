/**
 * @file pin.c
 * @brief Pin_Read&Write
 * @anchor fanyuo
 * @version 1.0
 * @date 2025-2-5
 *
 * @attention
 * 基于HAL库研发，优化HAL库读取和写入指定引脚电平的函数
 * 在其他平台或驱动芯片上使用可能需要进行移植
 *
 * @note
 * 使用流程:
 * 1. HAL_GPIO_ReadPin(GPIOx,GPIO_Pin_x); --> Pin_Read(PXX);
 * 2. HAL_GPIO_WritePin(GPIOx,GPIO_Pin_x,GPIO_PinState0; --> Pin_Write(PXX,State);
 *
 * @note
 * 为保证中文显示正常 请将编译器的字符集设置为UTF-8
 *
 */

#include "pin.h"

const char* PXX_to_string(PXX value) {
    static const char* names[] = {
        "PA0", "PA1", "PA2", "PA3", "PA4", "PA5", "PA6", "PA7",
        "PA8", "PA9", "PA10", "PA11", "PA12", "PA13", "PA14", "PA15",
        "PB0", "PB1", "PB2", "PB3", "PB4", "PB5", "PB6", "PB7",
        "PB8", "PB9", "PB10", "PB11", "PB12", "PB13", "PB14", "PB15",
        "PC0", "PC1", "PC2", "PC3", "PC4", "PC5", "PC6", "PC7",
        "PC8", "PC9", "PC10", "PC11", "PC12", "PC13", "PC14", "PC15"
    };

    return names[value];
}

uint16_t gpio_pin[]={	GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3,
											GPIO_PIN_4,GPIO_PIN_5,GPIO_PIN_6,GPIO_PIN_7,
											GPIO_PIN_8,GPIO_PIN_9,GPIO_PIN_10,GPIO_PIN_11,
											GPIO_PIN_12,GPIO_PIN_13,GPIO_PIN_14,GPIO_PIN_15};

typedef struct{
	GPIO_TypeDef* GPIO_Temp;
	uint16_t PIN_Temp;
}ReturnValues;

ReturnValues Pin_Judge(PXX pxx){
	ReturnValues result;
	
	const char* value;
	value=PXX_to_string(pxx);
	
	if(value[1]=='A'){
		result.GPIO_Temp=GPIOA;
	}else if(value[1]=='B'){
		result.GPIO_Temp=GPIOB;
	}else if(value[1]=='C'){
		result.GPIO_Temp=GPIOC;
	}
	
	char value_num[3]={0};
	if(strlen(value)==3){
		value_num[0]=value[2];
	}else if(strlen(value)==4){
		value_num[0]=value[2];
		value_num[1]=value[3];
	}
	int value_num2;
	value_num2=atoi(value_num);
	result.PIN_Temp=gpio_pin[value_num2];
	
	return result;
}

GPIO_PinState Pin_Read(PXX pxx){
	ReturnValues result;
	result=Pin_Judge(pxx);

	return HAL_GPIO_ReadPin(result.GPIO_Temp,result.PIN_Temp);
}

void Pin_Write(PXX pxx,GPIO_PinState State){
	ReturnValues result;
	result=Pin_Judge(pxx);
	
	HAL_GPIO_WritePin(result.GPIO_Temp,result.PIN_Temp,State);
}
