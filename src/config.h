//
// Created by neutron17 on 2022.05.01..
//

#ifndef _NTR_CONFIG_H_
#define _NTR_CONFIG_H_ 1
#include "movement.h"
#include "args.h"

#define CONF_LEN 32

extern char *saveDir;
extern struct sermov movs[MOV_SZ];

void loadConfigs(unsigned args);

#endif //_NTR_CONFIG_H_
