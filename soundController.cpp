
#include "mbed.h"
#include "headerFiles/sound.h"


AnalogIn soundSensor(A1);

void soundThread(){
    while(true){
        float sound = soundSensor.read();
                wait_us(1000);

        printf(" volume %i \n", int(sound * 100));
    }
}
