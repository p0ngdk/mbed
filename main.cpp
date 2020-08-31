/* 
THIS IS THE MAIN CONTROLLER AND IS ONLY USED TO START THE OTHER THREADS;
 */

#include "mbed.h"
#include "headerFiles/display.h"
#include "headerFiles/temprature.h"
#include "headerFiles/sound.h"
#include "DHT.h"

DHT sensor(D8, DHT22);

//defining threads
Thread thread;
Thread soundT;
Thread dThread;

//starting threads functyion

void startThreads(){
    dThread.start(displayThread);
    thread.start(tempThread);
    soundT.start(soundThread);
}

//main loop
int main()
{   
    //starts threads
    startThreads();

}

