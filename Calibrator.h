//
//  Calibrator.h
//  TaskScheduler
//
//  Created by Richy Kapadia on 2/16/15.
//  Copyright (c) 2015 Richy Kapadia. All rights reserved.
//

#ifndef __TaskScheduler__Calibrator__
#define __TaskScheduler__Calibrator__

#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <sys/netmgr.h>
#include <sys/neutrino.h>


#define MY_PULSE_CODE   _PULSE_CODE_MINAVAIL

typedef union {
    struct _pulse   pulse;
    /* your other message structures would go
     here too */
} my_message_t;

pthread_mutex_t lock;
int burnCount;
int calibrated;

int calibrate(void* dummy);
void startTimer(void* dummy);
void burnCPU(void* dummy);

#endif /* defined(__TaskScheduler__Calibrator__) */
