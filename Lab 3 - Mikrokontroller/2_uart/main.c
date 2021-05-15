#include "uart.h"

ssize_t _write(int fd, const void *buf, size_t count){
char * letter = (char *)(buf);
for(int i = 0; i < count; i++){
uart_send(*letter);
letter++;
}
return count;
};


int main(){
    uart_init();
    int sleep = 0;

    // Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

    int state = 0;
    GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;

    while(1){
        //iprintf("The average grade in TTK%d was in %d and %d: %c\n\r",4235,2019,2018,'C');
        
        if (!(GPIO->IN & (1 << 17))){
            uart_send('A');
        }

        if (!(GPIO->IN & (1 << 26))){
            uart_send('B');
        }

        if (uart_read() != '\0'){
            state = !state;
            if (state == 0){
                for(int i = 4; i < 13; i++){
				GPIO->OUTSET = (1 << i);
			    }
                for(int i = 13; i < 16; i++){
                    GPIO->OUTCLR = (1 << i);
                }
		    }
            else{
                for(int i = 13; i < 16; i++){
				GPIO->OUTSET = (1 << i);
                }
                for(int i = 4; i < 13; i++){
                    GPIO->OUTCLR = (1 << i);
                }
            } 
        }

        sleep = 10000;
		while(--sleep);
    }
    

    return 0;

}