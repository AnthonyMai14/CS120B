#include </Users/munoz/Desktop/header files/SHIFT.c>

unsigned char temps[8] = {0, 0, 0, 0, 0, 0, 0, 0};
const unsigned char one = 0x01;
unsigned char i = 0;
unsigned char row = 0x00;
unsigned char column = 0x00;

void turnOnLED(unsigned char x, unsigned char y){
	if(x < 0){
		return;
	}
	if(x > 7){
		return;
	}
	if(y < 0){
		return;
	}
	if(y > 7){
		return;
	}
	temps[y] |= (one << (7 - x));
	return;
}

int isOn(unsigned char x, unsigned char y){
	if((temps[y] & (one << (7 - x))) >> (7 - x)){
		return 1;
	}
	else return 0;
}

void turnOffLED(unsigned char x, unsigned char y){
	if(x < 0){
		return;
	}
	if(x > 7){
		return;
	}
	if(y < 0){
		return;
	}
	if(y > 7){
		return;
	}
	temps[y] &= ~(one << (7 - x));
	return;
}

void clearLED()
{
    for(row = 0; row < 8; ++row)
    {
        for(column = 0; column < 8; ++ column)
        {
            turnOffLED(row, column);
        }
    }
    return;
}

enum displayMatrixstates {Init1, displayScreen} displayState;
void displayMatrix(){
	unsigned char multiplex[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
	switch(displayState){
		case Init1:
		displayState = displayScreen;
		break;
		
		case displayScreen:
		displayState = displayScreen;
		break;
		
		default:
		displayState = Init1;
		break;
	}
	
	switch(displayState){
		case Init1:
		break;
		
		case displayScreen:
		transmit_data1(multiplex[i]);
		transmit_data3(~(temps[i]));
		if(i > 6){
			i = 0;
		}
		else{
			i++;
		}
		break;
		
		default:
		break;
	}
	return;
}

