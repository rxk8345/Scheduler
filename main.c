//
//  main.c
//  TaskScheduler
//
//  Created by Richy Kapadia on 2/16/15.
//  Copyright (c) 2015 Richy Kapadia. All rights reserved.
//

#include <stdio.h>
#include "Calibrator.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    
    int burnCount = calibrator();
    
    printf("%d", burnCount);
    
    return 0;
}
