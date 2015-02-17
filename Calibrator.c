//
//  Calibrator.c
//  TaskScheduler
//
//  Created by Richy Kapadia on 2/16/15.
//  Copyright (c) 2015 Richy Kapadia. All rights reserved.
//

#include "Calibrator.h"


int calibrator(){
    
    
    pthread_t timerThread;
    pthread_t burnThread;
    burnCount = 0;
    calibrated = 0;
    
    pthread_mutex_lock(&lock);
    
    if(pthread_create(&timerThread, NULL, startTimer, NULL) == -1){
        printf("Failed to create timerThread\n");
    }
    
    //block until timer is ready
    pthread_mutex_lock(&lock);
    
    //counts until timer ticks again
    while(calibrated != 0){
        burnCount++;
    }
    
    return burnCount;
}


void startTimer( void* dummy)
{
    struct sigevent         event;
    struct itimerspec       itime;
    timer_t                 timer_id;
    int                     chid;
    int                     rcvid;
    my_message_t            msg;
    
    chid = ChannelCreate(0);
    
    event.sigev_notify = SIGEV_PULSE;
    event.sigev_coid = ConnectAttach(ND_LOCAL_NODE, 0,
                                     chid,
                                     _NTO_SIDE_CHANNEL, 0);
    event.sigev_priority = getprio(0);
    event.sigev_code = MY_PULSE_CODE;
    timer_create(CLOCK_REALTIME, &event, &timer_id);
    
    itime.it_value.tv_sec = 1;
    itime.it_value.tv_nsec = 0;
    itime.it_interval.tv_sec = 1;
    itime.it_interval.tv_nsec = 0;
    timer_settime(timer_id, 0, &itime, NULL);
    
    /*
     * As of the timer_settime(), we will receive our pulse
     * in 1.5 seconds (the itime.it_value) and every 1.5
     * seconds thereafter (the itime.it_interval)
     */
    
    for (;;) {
        rcvid = MsgReceive(chid, &msg, sizeof(msg), NULL);
        if (rcvid == 0) { /* we got a pulse */
            if (msg.pulse.code == MY_PULSE_CODE) {
                if(burnCount == 0){
                    //have the other thread start counting at this point
                    pthread_mutex_unlock(&lock);
                }else{
                    calibrated = 1;
                }
            } /* else other pulses ... */
        } /* else other messages ... */
    }
}
