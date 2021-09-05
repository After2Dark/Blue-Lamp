#include "stm32f746xx.h"
#include "five_picture_1.h"
#include "four_picture_1.h"
#include "nine_picture_1.h"
#include "one_picture_1.h"
#include "seven_picture_1.h"
#include "six_picture_1.h"
#include "three_picture_1.h"
#include "two_picture_1.h"
#include "zero_picture_1.h"
#include "eigth_picture_1.h"
#include "five_picture_2.h"
#include "four_picture_2.h"
#include "nine_picture_2.h"
#include "one_picture_2.h"
#include "seven_picture_2.h"
#include "six_picture_2.h"
#include "three_picture_2.h"
#include "two_picture_2.h"
#include "zero_picture_2.h"
#include "eigth_picture_2.h"
#include "five_picture_3.h"
#include "four_picture_3.h"
#include "nine_picture_3.h"
#include "none_picture_3.h"
#include "one_picture_3.h"
#include "seven_picture_3.h"
#include "six_picture_3.h"
#include "three_picture_3.h"
#include "two_picture_3.h"
#include "zero_picture_3.h"
#include "eigth_picture_3.h"
#include "init_picture.h"
#include "main_picture.h"

#define  DISPLAY_HSYNC            ((uint16_t)30)
#define  DISPLAY_HBP              ((uint16_t)13)
#define  DISPLAY_HFP              ((uint16_t)32)
#define  DISPLAY_VSYNC            ((uint16_t)10)
#define  DISPLAY_VBP              ((uint16_t)2)
#define  DISPLAY_VFP              ((uint16_t)2)
#define  DISPLAY_WIDTH 			  ((uint16_t)480)
#define  DISPLAY_HEIGHT			  ((uint16_t)272)
#define  PIXEL_SIZE				  ((uint16_t)4)
#define  REFRESH_RATE 			  (1665)

static uint16_t screen[130560];
uint8_t flag = 0;
uint32_t cnt = 0;
uint8_t minute = 0;
uint8_t minute_2 = 0;
uint8_t hour = 0;
uint8_t hour_2 = 0;

void initialization()
{
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	RCC->APB2ENR |= RCC_APB2ENR_LTDCEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOKEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;

	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY));
	FLASH->ACR |= FLASH_ACR_LATENCY_5WS;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_0 | RCC_PLLCFGR_PLLM_3 | RCC_PLLCFGR_PLLM_4;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_4 | RCC_PLLCFGR_PLLN_5 | RCC_PLLCFGR_PLLN_7 | RCC_PLLCFGR_PLLN_8;
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN_6;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLP_0;
	RCC->CFGR |= RCC_CFGR_PPRE1_2 | RCC_CFGR_PPRE2_2;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC;
	RCC->CR |= RCC_CR_PLLON;
	while((RCC->CR & RCC_CR_PLLRDY) == 0);
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1);
	RCC->PLLSAICFGR |= RCC_PLLSAICFGR_PLLSAIN_6 | RCC_PLLSAICFGR_PLLSAIN_7;
	RCC->PLLSAICFGR |= RCC_PLLSAICFGR_PLLSAIR_0 | RCC_PLLSAICFGR_PLLSAIR_2;
	RCC->DCKCFGR1 	|= RCC_DCKCFGR1_PLLSAIDIVR_0;
	RCC->DCKCFGR1 	&= ~RCC_DCKCFGR1_PLLSAIDIVR_1;
	RCC->CR |= RCC_CR_PLLSAION;
	while ((RCC->CR & RCC_CR_PLLSAIRDY) == 0);

	//B0 PE4
	GPIOE->MODER   &= ~GPIO_MODER_MODER4;
	GPIOE->MODER   |= GPIO_MODER_MODER4_1;
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4_1;
	GPIOE->AFR[0] &= ~GPIO_AFRL_AFRL4_0;
	GPIOE->AFR[0] |= GPIO_AFRL_AFRL4_1 | GPIO_AFRL_AFRL4_2 | GPIO_AFRL_AFRL4_3;

	//B1 PJ13
	GPIOJ->MODER   &= ~GPIO_MODER_MODER13;
	GPIOJ->MODER   |= GPIO_MODER_MODER13_1;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13_1;
	GPIOJ->AFR[1] &= ~GPIO_AFRL_AFRL5_0;
	GPIOJ->AFR[1] |= GPIO_AFRL_AFRL5_1 | GPIO_AFRL_AFRL5_2 | GPIO_AFRL_AFRL5_3;

	//B2 PJ14
	GPIOJ->MODER   &= ~GPIO_MODER_MODER14;
	GPIOJ->MODER   |= GPIO_MODER_MODER14_1;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR14_1;
	GPIOJ->AFR[1] &= ~GPIO_AFRL_AFRL6_0;
	GPIOJ->AFR[1] |= GPIO_AFRL_AFRL6_1 | GPIO_AFRL_AFRL6_2 | GPIO_AFRL_AFRL6_3;

	//B3 PJ15
	GPIOJ->MODER   &= ~GPIO_MODER_MODER15;
	GPIOJ->MODER   |= GPIO_MODER_MODER15_1;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15_1;
	GPIOJ->AFR[1] &= ~GPIO_AFRL_AFRL7_0;
	GPIOJ->AFR[1] |= GPIO_AFRL_AFRL7_1 | GPIO_AFRL_AFRL7_2 | GPIO_AFRL_AFRL7_3;

	//B4 PJ12
	GPIOJ->MODER   &= ~GPIO_MODER_MODER12;
	GPIOJ->MODER   |= GPIO_MODER_MODER12_1;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR12_1;
	GPIOJ->AFR[1] &= ~GPIO_AFRL_AFRL4_0;
	GPIOJ->AFR[1] |= GPIO_AFRL_AFRL4_1 | GPIO_AFRL_AFRL4_2 | GPIO_AFRL_AFRL4_3;

	//B5 PK4
	GPIOK->MODER   &= ~GPIO_MODER_MODER4;
	GPIOK->MODER   |= GPIO_MODER_MODER4_1;
	GPIOK->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4_1;
	GPIOK->AFR[0] &= ~GPIO_AFRL_AFRL4_0;
	GPIOK->AFR[0] |= GPIO_AFRL_AFRL4_1 | GPIO_AFRL_AFRL4_2 | GPIO_AFRL_AFRL4_3;

	//B6 PK5
	GPIOK->MODER   &= ~GPIO_MODER_MODER5;
	GPIOK->MODER   |= GPIO_MODER_MODER5_1;
	GPIOK->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_1;
	GPIOK->AFR[0] &= ~GPIO_AFRL_AFRL5_0;
	GPIOK->AFR[0] |= GPIO_AFRL_AFRL5_1 | GPIO_AFRL_AFRL5_2 | GPIO_AFRL_AFRL5_3;

	//B7 PK6
	GPIOK->MODER   &= ~GPIO_MODER_MODER6;
	GPIOK->MODER   |= GPIO_MODER_MODER6_1;
	GPIOK->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_1;
	GPIOK->AFR[0] &= ~GPIO_AFRL_AFRL6_0;
	GPIOK->AFR[0] |= GPIO_AFRL_AFRL6_1 | GPIO_AFRL_AFRL6_2 | GPIO_AFRL_AFRL6_3;

	//R0 PI 15
	GPIOI->MODER   &= ~GPIO_MODER_MODER15;
	GPIOI->MODER   |= GPIO_MODER_MODER15_1;
	GPIOI->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15_1;
	GPIOI->AFR[1] &= ~GPIO_AFRL_AFRL7_0;
	GPIOI->AFR[1] |= GPIO_AFRL_AFRL7_1 | GPIO_AFRL_AFRL7_2 | GPIO_AFRL_AFRL7_3;

	//R1 PJ0
	GPIOJ->MODER   &= ~GPIO_MODER_MODER0;
	GPIOJ->MODER   |= GPIO_MODER_MODER0_1;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0_1;
	GPIOJ->AFR[0] &= ~GPIO_AFRL_AFRL0_0;
	GPIOJ->AFR[0] |= GPIO_AFRL_AFRL0_1 | GPIO_AFRL_AFRL0_2 | GPIO_AFRL_AFRL0_3;

	//R2 PJ1
	GPIOJ->MODER   &= ~GPIO_MODER_MODER1;
	GPIOJ->MODER   |= GPIO_MODER_MODER1_1;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1_1;
	GPIOJ->AFR[0] &= ~GPIO_AFRL_AFRL1_0;
	GPIOJ->AFR[0] |= GPIO_AFRL_AFRL1_1 | GPIO_AFRL_AFRL1_2 | GPIO_AFRL_AFRL1_3;

	//R3 PJ2
	GPIOJ->MODER   &= ~GPIO_MODER_MODER2;
	GPIOJ->MODER   |= GPIO_MODER_MODER2_1;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2_1;
	GPIOJ->AFR[0] &= ~GPIO_AFRL_AFRL2_0;
	GPIOJ->AFR[0] |= GPIO_AFRL_AFRL2_1 | GPIO_AFRL_AFRL2_2 | GPIO_AFRL_AFRL2_3;

	//R4 PJ3

	GPIOJ->MODER   &= ~GPIO_MODER_MODER3;
	GPIOJ->MODER   |= GPIO_MODER_MODER3_1;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3_1;
	GPIOJ->AFR[0] &= ~GPIO_AFRL_AFRL3_0;
	GPIOJ->AFR[0] |= GPIO_AFRL_AFRL3_1 | GPIO_AFRL_AFRL3_2 | GPIO_AFRL_AFRL3_3;

	//R5 PJ4
	GPIOJ->MODER   &= ~GPIO_MODER_MODER4;
	GPIOJ->MODER   |= GPIO_MODER_MODER4_1;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4_1;
	GPIOJ->AFR[0] &= ~GPIO_AFRL_AFRL4_0;
	GPIOJ->AFR[0] |= GPIO_AFRL_AFRL4_1 | GPIO_AFRL_AFRL4_2 | GPIO_AFRL_AFRL4_3;

	//R6 PJ5
	GPIOJ->MODER   &= ~GPIO_MODER_MODER5;
	GPIOJ->MODER   |= GPIO_MODER_MODER5_1;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_1;
	GPIOJ->AFR[0] &= ~GPIO_AFRL_AFRL5_0;
	GPIOJ->AFR[0] |= GPIO_AFRL_AFRL5_1 | GPIO_AFRL_AFRL5_2 | GPIO_AFRL_AFRL5_3;

	//R7 PJ6
	GPIOJ->MODER   &= ~GPIO_MODER_MODER6;
	GPIOJ->MODER   |= GPIO_MODER_MODER6_1;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_1;
	GPIOJ->AFR[0] &= ~GPIO_AFRL_AFRL6_0;
	GPIOJ->AFR[0] |= GPIO_AFRL_AFRL6_1 | GPIO_AFRL_AFRL6_2 | GPIO_AFRL_AFRL6_3;

	//G0 PJ7
	GPIOJ->MODER   &= ~GPIO_MODER_MODER7;
	GPIOJ->MODER   |= GPIO_MODER_MODER7_1;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7_1;
	GPIOJ->AFR[0] &= ~GPIO_AFRL_AFRL7_0;
	GPIOJ->AFR[0] |= GPIO_AFRL_AFRL7_1 | GPIO_AFRL_AFRL7_2 | GPIO_AFRL_AFRL7_3;

	//G1 PJ8
	GPIOJ->MODER   &= ~GPIO_MODER_MODER8;
	GPIOJ->MODER   |= GPIO_MODER_MODER8_1;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8_1;
	GPIOJ->AFR[1] &= ~GPIO_AFRL_AFRL0_0;
	GPIOJ->AFR[1] |= GPIO_AFRL_AFRL0_1 | GPIO_AFRL_AFRL0_2 | GPIO_AFRL_AFRL0_3;

	//G2 PJ9
	GPIOJ->MODER   &= ~GPIO_MODER_MODER9;
	GPIOJ->MODER   |= GPIO_MODER_MODER9_1;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_1;
	GPIOJ->AFR[1] &= ~GPIO_AFRL_AFRL1_0;
	GPIOJ->AFR[1] |= GPIO_AFRL_AFRL1_1 | GPIO_AFRL_AFRL1_2 | GPIO_AFRL_AFRL1_3;

	//G3 PJ10
	GPIOJ->MODER   &= ~GPIO_MODER_MODER10;
	GPIOJ->MODER   |= GPIO_MODER_MODER10_1;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10_1;
	GPIOJ->AFR[1] &= ~GPIO_AFRL_AFRL2_0;
	GPIOJ->AFR[1] |= GPIO_AFRL_AFRL2_1 | GPIO_AFRL_AFRL2_2 | GPIO_AFRL_AFRL2_3;

	//G4 PJ11
	GPIOJ->MODER   &= ~GPIO_MODER_MODER11;
	GPIOJ->MODER   |= GPIO_MODER_MODER11_1;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR11_1;
	GPIOJ->AFR[1] &= ~GPIO_AFRL_AFRL3_0;
	GPIOJ->AFR[1] |= GPIO_AFRL_AFRL3_1 | GPIO_AFRL_AFRL3_2 | GPIO_AFRL_AFRL3_3;

	//G5 PK0
	GPIOK->MODER   &= ~GPIO_MODER_MODER0;
	GPIOK->MODER   |= GPIO_MODER_MODER0_1;
	GPIOK->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0_1;
	GPIOK->AFR[0] &= ~GPIO_AFRL_AFRL0_0;
	GPIOK->AFR[0] |= GPIO_AFRL_AFRL0_1 | GPIO_AFRL_AFRL0_2 | GPIO_AFRL_AFRL0_3;

	//G6 PK1
	GPIOK->MODER   &= ~GPIO_MODER_MODER1;
	GPIOK->MODER   |= GPIO_MODER_MODER1_1;
	GPIOK->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1_1;
	GPIOK->AFR[0] &= ~GPIO_AFRL_AFRL1_0;
	GPIOK->AFR[0] |= GPIO_AFRL_AFRL1_1 | GPIO_AFRL_AFRL1_2 | GPIO_AFRL_AFRL1_3;

	//G7 PK2
	GPIOK->MODER   &= ~GPIO_MODER_MODER2;
	GPIOK->MODER   |= GPIO_MODER_MODER2_1;
	GPIOK->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2_1;
	GPIOK->AFR[0] &= ~GPIO_AFRL_AFRL2_0;
	GPIOK->AFR[0] |= GPIO_AFRL_AFRL2_1 | GPIO_AFRL_AFRL2_2 | GPIO_AFRL_AFRL2_3;

	//VSYNC
	GPIOI->MODER   &= ~GPIO_MODER_MODER9;
	GPIOI->MODER   |= GPIO_MODER_MODER9_1;
	GPIOI->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_1;
	GPIOI->AFR[1] &= ~GPIO_AFRL_AFRL1_0;
	GPIOI->AFR[1] |= GPIO_AFRL_AFRL1_1 | GPIO_AFRL_AFRL1_2 | GPIO_AFRL_AFRL1_3;

	//HSYNC
	GPIOI->MODER   &= ~GPIO_MODER_MODER10;
	GPIOI->MODER   |= GPIO_MODER_MODER10_1;
	GPIOI->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10_1;
	GPIOI->AFR[1] &= ~GPIO_AFRL_AFRL2_0;
	GPIOI->AFR[1] |= GPIO_AFRL_AFRL2_1 | GPIO_AFRL_AFRL2_2 | GPIO_AFRL_AFRL2_3;

	//CLK
	GPIOI->MODER   &= ~GPIO_MODER_MODER14;
	GPIOI->MODER   |= GPIO_MODER_MODER14_1;
	GPIOI->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR14_1;
	GPIOI->AFR[1] &= ~GPIO_AFRL_AFRL6_0;
	GPIOI->AFR[1] |= GPIO_AFRL_AFRL6_1 | GPIO_AFRL_AFRL6_2 | GPIO_AFRL_AFRL6_3;

	//DE
	GPIOK->MODER   &= ~GPIO_MODER_MODER7;
	GPIOK->MODER   |= GPIO_MODER_MODER7_1;
	GPIOK->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7_1;
	GPIOK->AFR[0] &= ~GPIO_AFRL_AFRL7_0;
	GPIOK->AFR[0] |= GPIO_AFRL_AFRL7_1 | GPIO_AFRL_AFRL7_2 | GPIO_AFRL_AFRL7_3;

	//LED
	GPIOK->MODER &= ~GPIO_MODER_MODER3;
	GPIOK->MODER |= GPIO_MODER_MODER3_0;
	GPIOK->BSRR |= GPIO_BSRR_BS_3;

	//ON
	GPIOI->MODER &= ~GPIO_MODER_MODER12;
	GPIOI->MODER |= GPIO_MODER_MODER12_0;
	GPIOI->BSRR |= GPIO_BSRR_BS_12;

	GPIOC->MODER &= ~GPIO_MODER_MODER7;
	GPIOC->MODER |= GPIO_MODER_MODER7_0;
	GPIOC->BSRR |= GPIO_BSRR_BS_7;

	LTDC->SSCR |= ((DISPLAY_HSYNC - 1) << 16 | (DISPLAY_VSYNC - 1));
	LTDC->BPCR |= ((DISPLAY_HSYNC+DISPLAY_HBP-1) << 16 | (DISPLAY_VSYNC+DISPLAY_VBP-1));
	LTDC->AWCR |= ((DISPLAY_WIDTH + DISPLAY_HSYNC + DISPLAY_HBP - 1) << 16 | (DISPLAY_HEIGHT + DISPLAY_VSYNC + DISPLAY_VBP - 1));
	LTDC->TWCR |= ((DISPLAY_WIDTH + DISPLAY_HSYNC + DISPLAY_HBP + DISPLAY_HFP -1)<< 16 |(DISPLAY_HEIGHT + DISPLAY_VSYNC + DISPLAY_VBP + DISPLAY_VFP - 1));
	LTDC_Layer2->WHPCR |= (((DISPLAY_WIDTH + DISPLAY_HBP + DISPLAY_HSYNC - 1) << 16) | (DISPLAY_HBP + DISPLAY_HSYNC));
	LTDC_Layer2->WVPCR |= (((DISPLAY_HEIGHT + DISPLAY_VSYNC + DISPLAY_VBP - 1) << 16) |(DISPLAY_VSYNC + DISPLAY_VBP));
	LTDC_Layer2->PFCR = 2;
	LTDC_Layer2->BFCR |= ((4 << 8) | 5);
	LTDC_Layer2->CACR = 0xff;
	LTDC_Layer2->CFBLR |= (((PIXEL_SIZE * DISPLAY_WIDTH) << 16) | (PIXEL_SIZE * DISPLAY_WIDTH + 3));
	LTDC_Layer2->CFBLNR |= DISPLAY_HEIGHT;
	LTDC_Layer2->CR |= LTDC_LxCR_LEN;
	LTDC->SRCR |= LTDC_SRCR_VBR;
	LTDC->GCR |= LTDC_GCR_LTDCEN;

	for(int i = 0; i <= 130559; ++i)
		screen[i] = main_picture[i];

	GPIOK->BSRR |= GPIO_BSRR_BS_3;
}

void change_digit_1(int poz, int number)
{
	int x = 0;
	int k = 0;

	if(poz==1)
		x = 0;
	if(poz==2)
		x = 38;
	if(poz==3)
		x = 86;
	if(poz==4)
		x = 124;

	if(number==0)
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[x+5113+i*480+j] = zero_picture_1[k++];
	if(number==1)
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[x+5113+i*480+j] = one_picture_1[k++];
	if(number==2)
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[x+5113+i*480+j] = two_picture_1[k++];
	if(number==3)
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[x+5113+i*480+j] = three_picture_1[k++];
	if(number==4)
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[x+5113+i*480+j] = four_picture_1[k++];
	if(number==5)
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[x+5113+i*480+j] = five_picture_1[k++];
	if(number==6)
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[x+5113+i*480+j] = six_picture_1[k++];
	if(number==7)
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[x+5113+i*480+j] = seven_picture_1[k++];
	if(number==8)
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[x+5113+i*480+j] = eigth_picture_1[k++];
	if(number==9)
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[x+5113+i*480+j] = nine_picture_1[k++];
	LTDC_Layer2->CFBAR = (uint32_t)screen;
	LTDC->SRCR |= LTDC_SRCR_VBR;
}

void change_digit_2(int poz, int number)
{
	int x = 0;
	int k = 0;

	if(poz==1)
		x = 0;
	if(poz==2)
		x = 110;
	if(poz==3)
		x = 246;
	if(poz==4)
		x = 356;

	if(number==0)
		for(int i = 0; i <= 173; ++i)
			for(int j = 0; j <= 98; ++j)
				screen[x+42253+i*480+j] = zero_picture_2[k++];
	if(number==1)
		for(int i = 0; i <= 173; ++i)
			for(int j = 0; j <= 98; ++j)
				screen[x+42253+i*480+j] = one_picture_2[k++];
	if(number==2)
		for(int i = 0; i <= 173; ++i)
			for(int j = 0; j <= 98; ++j)
				screen[x+42253+i*480+j] = two_picture_2[k++];
	if(number==3)
		for(int i = 0; i <= 173; ++i)
			for(int j = 0; j <= 98; ++j)
				screen[x+42253+i*480+j] = three_picture_2[k++];
	if(number==4)
		for(int i = 0; i <= 173; ++i)
			for(int j = 0; j <= 98; ++j)
				screen[x+42253+i*480+j] = four_picture_2[k++];
	if(number==5)
		for(int i = 0; i <= 173; ++i)
			for(int j = 0; j <= 98; ++j)
				screen[x+42253+i*480+j] = five_picture_2[k++];
	if(number==6)
		for(int i = 0; i <= 173; ++i)
			for(int j = 0; j <= 98; ++j)
				screen[x+42253+i*480+j] = six_picture_2[k++];
	if(number==7)
		for(int i = 0; i <= 173; ++i)
			for(int j = 0; j <= 98; ++j)
				screen[x+42253+i*480+j] = seven_picture_2[k++];
	if(number==8)
		for(int i = 0; i <= 173; ++i)
			for(int j = 0; j <= 98; ++j)
				screen[x+42253+i*480+j] = eigth_picture_2[k++];
	if(number==9)
		for(int i = 0; i <= 173; ++i)
			for(int j = 0; j <= 98; ++j)
				screen[x+42253+i*480+j] = nine_picture_2[k++];
	LTDC_Layer2->CFBAR = (uint32_t)screen;
	LTDC->SRCR |= LTDC_SRCR_VBR;
}

void change_digit_3(int number)
{
	int k = 0;

	if(number==0)
	{
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[76+4861+i*480+j] = zero_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[38+4861+i*480+j] = none_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[4861+i*480+j] = none_picture_3[k++];
	}

	if(number==10)
	{
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[76+4861+i*480+j] = zero_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[38+4861+i*480+j] = one_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[4861+i*480+j] = none_picture_3[k++];
	}

	if(number==20)
	{
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[76+4861+i*480+j] = zero_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[38+4861+i*480+j] = two_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[4861+i*480+j] = none_picture_3[k++];
	}

	if(number==30)
	{
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[76+4861+i*480+j] = zero_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[38+4861+i*480+j] = three_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[4861+i*480+j] = none_picture_3[k++];
	}

	if(number==40)
	{
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[76+4861+i*480+j] = zero_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[38+4861+i*480+j] = four_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[4861+i*480+j] = none_picture_3[k++];
	}

	if(number==50)
	{
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[76+4861+i*480+j] = zero_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[38+4861+i*480+j] = five_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[4861+i*480+j] = none_picture_3[k++];
	}

	if(number==60)
	{
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[76+4861+i*480+j] = zero_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[38+4861+i*480+j] = six_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[4861+i*480+j] = none_picture_3[k++];
	}

	if(number==70)
	{
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[76+4861+i*480+j] = zero_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[38+4861+i*480+j] = seven_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[4861+i*480+j] = none_picture_3[k++];
	}

	if(number==80)
	{
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[76+4861+i*480+j] = zero_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[38+4861+i*480+j] = eigth_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[4861+i*480+j] = none_picture_3[k++];
	}

	if(number==90)
	{
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[76+4861+i*480+j] = zero_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[38+4861+i*480+j] = nine_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[4861+i*480+j] = none_picture_3[k++];
	}

	if(number==100)
	{
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[76+4861+i*480+j] = zero_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[38+4861+i*480+j] = zero_picture_3[k++];
		k = 0;
		for(int i = 0; i <= 57; ++i)
			for(int j = 0; j <= 32; ++j)
				screen[4861+i*480+j] = one_picture_3[k++];
	}

	LTDC_Layer2->CFBAR = (uint32_t)screen;
	LTDC->SRCR |= LTDC_SRCR_VBR;
}

void SysTick_Handler(void)
{
	++cnt;
	// 600000 - 1.5%
	// 599000 - 1.3%
	// 592500 - 0.38%
	// 590000 - %
	if(cnt == 590000)
	{
		cnt = 136;
		++minute;
		if(minute == 10)
		{
			cnt += 278;
			minute = 0;
			++minute_2;
			change_digit_2(3,minute_2);
			if(minute_2 == 6)
			{
				cnt += 269;
				minute_2 = 0;
				++hour;
				change_digit_2(2,hour);
				if(hour == 10)
				{
					cnt += 136;
					hour = 0;
					++hour_2;
					change_digit_2(1,hour_2);
					change_digit_2(2,0);
				}
				change_digit_2(3,0);
			}
			change_digit_2(4,0);
		}
		change_digit_2(4,minute);
	}
}

int main(void)
{
	initialization();

	// Initialization picture
	LTDC_Layer2->CFBAR = (uint32_t)init_picture;
	LTDC->SRCR |= LTDC_SRCR_VBR;
	for(int i = 0; i <= 5000000; ++i);

	// Main picture
	LTDC_Layer2->CFBAR = (uint32_t)main_picture;
	LTDC->SRCR |= LTDC_SRCR_VBR;

	// Time
	change_digit_1(1,9);
	change_digit_1(2,9);
	change_digit_1(3,9);
	change_digit_1(4,9);

	// Power
	change_digit_3(100);

	SysTick_Config(180);
}