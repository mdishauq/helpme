#include<stdint.h>
#include<stdio.h>

//registers used
volatile uint32_t *RCC_APB2ENR =(volatile uint32_t *)0x40021018;
volatile uint32_t *GPIOx_CRH =(volatile uint32_t *)0x40011004;
volatile uint32_t *GPIOx_ODR =(volatile uint32_t *)0x4001100C;
volatile uint32_t *ADC_SQR3 =(volatile uint32_t *)0x40012434;
volatile uint32_t *ADC_SMPR1 =(volatile uint32_t *)0x4001240C;
volatile uint32_t *ADC_CR2 =(volatile uint32_t *)0x40012408;
volatile uint32_t *ADC_SR =(volatile uint32_t *)0x40012400;
volatile uint32_t *ADC_DR =(volatile uint32_t *)0x4001244C;



void internal_tempsensorInit(){
	*RCC_APB2ENR |= (1<<4);//PORTC clock enabled
	*RCC_APB2ENR |= (1<<9);//ADC1 clock enabled


	//port c pin 13 configuration
	*GPIOx_CRH &= ~(0xF << 20);       // Clear bits
	*GPIOx_CRH |=  (0x2 << 20);       // 0b0010 = Output, 2MHz, push-pull

	*ADC_SQR3 &=~(0x1F<<0);//clear SQ1
	*ADC_SQR3 |=(16<<0);//select channel 16

	*ADC_SMPR1 &=~(0x7<<18);//clear sample time for channel 16
	*ADC_SMPR1 |=(0x7<<18);//set sample time (239.5cycles)

	*ADC_CR2 |=(1<<23);//set temperature sensor
	for (volatile uint32_t i = 0; i < 10000; i++); // ~short delay
	*ADC_CR2 |=(1<<0);//set ADON ADC ON

	//CALIBRATION
	*ADC_CR2 |=(1<<3);//RESET calibration
	while(*ADC_CR2&(1<<3)){//wait until its cleared

	}
	*ADC_CR2 |=(1<<2);//SET calibration
	while(*ADC_CR2&(1<<2)){//wait until its cleared

	}

	//continuous conversion
	*ADC_CR2 |=(1<<1);
}

uint16_t adcread(){


	*ADC_CR2 |=(1<<22);//start of conversion

	while(!(*ADC_SR&(1<<1))){
			}
	return (uint16_t) *ADC_DR;
}

static inline void delay_ms(uint32_t ms) {
    // crude ~ms delay assuming ~72MHz, adjust if too fast/slow
    for (uint32_t m=0; m<ms; m++) {
        for (volatile uint32_t i=0; i<72000; i++) {
            __asm__("nop");
        }
    }
}



int main(){

	internal_tempsensorInit();
	(void)adcread(); // throw away first reading
	while (1) {
    	    uint16_t analog_value = adcread();

    	    float Vsense = (analog_value * 3.3f) / 4095.0f;
    	    float temperature = ((1.43f - Vsense) / 0.0043f) + 25.0f;

    	    uint32_t ms = (uint32_t)(temperature * 50.0f); // ~1.5s around 30°C
    	    if (ms < 100)  ms = 100;   // clamp for visibility
    	    if (ms > 2000) ms = 2000;

    	    *GPIOx_ODR &=~ (1<<13);// LED ON (active-low)

    	    delay_ms(1000);
    	    *GPIOx_ODR |=  (1<<13); // LED OFF

    	    delay_ms(1000);
    	}


}

