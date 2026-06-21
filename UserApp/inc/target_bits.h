#ifndef _TARGET_BITS_H_
#define _TARGET_BITS_H_

#define BIT_RESET	9
#define BIT_IORDY	0
#define BIT_IOCHK	1
#define BIT_TC		5

#define BIT_MEMW	8
#define BIT_MEMR	9
#define BIT_IOW		10
#define BIT_IOR	 	11
#define BIT_ALE		12
#define BIT_AEN		13

#define MASK_RESET	(1<<BIT_RESET)
#define MASK_IODRY	(1<<BIT_IORDY)
#define MASK_IOCHK	(1<<BIT_IOCHK)
#define MASK_TC		(1<<BIT_TC)

#define MASK_MEMW	(1<<BIT_MEMW)
#define MASK_MEMR	(1<<BIT_MEMR)
#define MASK_IOW	(1<<BIT_IOW)
#define MASK_IOR	(1<<BIT_IOR)
#define MASK_ALE	(1<<BIT_ALE)
#define MASK_AEN	(1<<BIT_AEN)

#endif /* _TARGET_BITS_H_ */
