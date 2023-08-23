
#include "asf.h"

#define LED1_PIO           PIOA
#define LED1_PIO_ID        ID_PIOA
#define LED1_PIO_INDX       0
#define LED1_PIO_INDX_MASK  (1 << LED1_PIO_INDX)

#define BUT1_PIO           PIOD
#define BUT1_PIO_ID        ID_PIOD
#define BUT1_PIO_INDX       28
#define BUT1_PIO_INDX_MASK (1u << BUT1_PIO_INDX)

#define LED2_PIO           PIOC
#define LED2_PIO_ID        ID_PIOC
#define LED2_PIO_INDX       30
#define LED2_PIO_INDX_MASK  (1 << LED2_PIO_INDX)

#define BUT2_PIO           PIOC
#define BUT2_PIO_ID        ID_PIOC
#define BUT2_PIO_INDX       31
#define BUT2_PIO_INDX_MASK (1u << BUT2_PIO_INDX)

#define LED3_PIO           PIOB
#define LED3_PIO_ID        ID_PIOB
#define LED3_PIO_INDX       2
#define LED3_PIO_INDX_MASK  (1 << LED3_PIO_INDX)

#define BUT3_PIO           PIOA
#define BUT3_PIO_ID        ID_PIOA
#define BUT3_PIO_INDX       19
#define BUT3_PIO_INDX_MASK (1u << BUT3_PIO_INDX)


void init(void);


void init(void){
	sysclk_init();

	WDT->WDT_MR = WDT_MR_WDDIS;
	
	pmc_enable_periph_clk(LED1_PIO_ID);
	pmc_enable_periph_clk(LED2_PIO_ID);
	pmc_enable_periph_clk(LED3_PIO_ID);
	
	pio_set_output(LED1_PIO, LED1_PIO_INDX_MASK, 0, 0, 0);
	pio_set_output(LED2_PIO, LED2_PIO_INDX_MASK, 0, 0, 0);
	pio_set_output(LED3_PIO, LED3_PIO_INDX_MASK, 0, 0, 0);
	
	pmc_enable_periph_clk(BUT1_PIO_ID);
	pmc_enable_periph_clk(BUT2_PIO_ID);
	pmc_enable_periph_clk(BUT3_PIO_ID);

	pio_set_input(BUT1_PIO, BUT1_PIO_INDX_MASK, PIO_DEFAULT);
	pio_set_input(BUT2_PIO, BUT2_PIO_INDX_MASK, PIO_DEFAULT);
	pio_set_input(BUT3_PIO, BUT3_PIO_INDX_MASK, PIO_DEFAULT);
	
	pio_pull_up(BUT1_PIO, BUT1_PIO_INDX_MASK, 1);
	pio_pull_up(BUT2_PIO, BUT2_PIO_INDX_MASK, 1);
	pio_pull_up(BUT3_PIO, BUT3_PIO_INDX_MASK, 1);
}


int main(void)
{
	init();
	
	while (1)
	{
		if (!pio_get(BUT1_PIO, PIO_INPUT, BUT1_PIO_INDX_MASK)) {
			for (int i = 0; i < 5; i++) {
				pio_clear(LED1_PIO, LED1_PIO_INDX_MASK); 
				delay_ms(100);
				pio_set(LED1_PIO, LED1_PIO_INDX_MASK);
				delay_ms(100);
		  	}
	  	} 
		if (pio_get(BUT1_PIO, PIO_INPUT, BUT1_PIO_INDX_MASK)) {
			pio_set(LED1_PIO, LED1_PIO_INDX_MASK);
	  	}

		if (!pio_get(BUT2_PIO, PIO_INPUT, BUT2_PIO_INDX_MASK)) {
			for (int i = 0; i < 5; i++) {
				pio_clear(LED2_PIO, LED2_PIO_INDX_MASK); 
				delay_ms(100);
				pio_set(LED2_PIO, LED2_PIO_INDX_MASK);
				delay_ms(100);
			}
	  	}
	  	if (pio_get(BUT2_PIO, PIO_INPUT, BUT2_PIO_INDX_MASK)) {
			pio_set(LED2_PIO, LED2_PIO_INDX_MASK);
		}

		if (!pio_get(BUT3_PIO, PIO_INPUT, BUT3_PIO_INDX_MASK)) {
			for (int i = 0; i < 5; i++) {
				pio_clear(LED3_PIO, LED3_PIO_INDX_MASK); 
				delay_ms(100);
				pio_set(LED3_PIO, LED3_PIO_INDX_MASK); 
				delay_ms(100);
		  	}
		}
	  	if (pio_get(BUT3_PIO, PIO_INPUT, BUT3_PIO_INDX_MASK)) {
			pio_set(LED3_PIO, LED3_PIO_INDX_MASK);
		}
	}
	return 0;
}