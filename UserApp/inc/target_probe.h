#ifndef _TARGET_PROBE_H_
#define _TARGET_PROBE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

//Conditional defines
#include "config.h"

//https://www.youtube.com/watch?v=wj427hpP81s
//https://github.com/controllerstech/stm32-uart-ring-buffer
#include "UartRingbuffer.h"

#include "buscycles.h"
#include "target_bits.h"
#include "main.h"
#include "retarget.h"
#include "UserApp.h"
#include "binedit.h"
#include "memops.h"
#include "menus.h"
#include "utils.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#endif /* _TARGET_PROBE_H_ */
