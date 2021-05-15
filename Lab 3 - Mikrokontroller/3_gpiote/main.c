#include <stdint.h>
#include "gpio.h"
#include "ppi.h"
#include "gpiote.h"

int main(){
    // Configure LED Matrix
	// Configure LED Matrix
	for(int i = 4; i <= 12; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// A-button
	GPIOTE->CONFIG[0] = (1 | (17 << 8) | (2 << 16));

	// Task-channels
	for (int i = 1; i < 4; i++){
		GPIOTE->CONFIG[i] = (3 | ((12 + i) << 8) | (3 << 16) | (0 << 20));
	}
	
	// enable interrupt
	GPIOTE->INTEN = 1; 

	for (int i = 0; i<3; i++){
		PPI->CHENSET = (1 << i);
		PPI->PPI_CH[i].EEP = (uint32_t)&(GPIOTE->IN[0]);
		PPI->PPI_CH[i].TEP = (uint32_t)&(GPIOTE->OUT[i+1]);
	}
	

    return 0;
}