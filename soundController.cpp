
#include "mbed.h"
#include "headerFiles/sound.h"


AnalogIn soundSensor(A1);
float max = 49;

//sound thread to get sound noise 
void soundThread(){
    while(true){
        int sound = int(soundSensor.read() * 100);

        int sum = 0;
        for(int i = 0; i< 32; i++){
            sum += sound;
        }
       // printf("in: %i \n", sum);
        //wait_us(500);
    }
}


/*         float sound = soundSensor.read();
                wait_us(1000);

        printf("%i \n", int(sound * 100)); */
