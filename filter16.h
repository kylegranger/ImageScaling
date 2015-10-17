// File: filter16.h
// Date: August 24, 2014
// Create by: Kyle Granger
// License: Public Domain
// Checked into Github: October 17, 2015


#ifndef __FILTER16_H
#define __FILTER16_H

#include "acidtypes.h"

// 2D down
extern void Downfilter      (color_t *src1, color_t *src2, color_t *src3, color_t *src4, color_t *dst);
extern void DownfilterLeft  (color_t *src1, color_t *src2, color_t *src3, color_t *src4, color_t *dst);
extern void DownfilterRight (color_t *src1, color_t *src2, color_t *src3, color_t *src4, color_t *dst);
extern void Downfilter      (color_t *src1, color_t *src2, color_t *src3, color_t *dst);
extern void DownfilterLeft  (color_t *src1, color_t *src2, color_t *src3, color_t *dst);
extern void DownfilterRight (color_t *src1, color_t *src2, color_t *src3, color_t *dst);

// 2D down
extern void Upfilter     (color_t *src1, color_t *src2, color_t *src3, color_t *dst1, color_t *dst2);
extern void UpfilterLeft (color_t *src1, color_t *src2, color_t *src3, color_t *dst1, color_t *dst2);
extern void UpfilterRight(color_t *src1, color_t *src2, color_t *src3, color_t *dst1, color_t *dst2);

// X down
extern void DownfilterX(color_t *src1, color_t *dst);
extern void DownfilterXLeft(color_t *src1, color_t *dst);
extern void DownfilterXRight(color_t *src1, color_t *dst);

// X up
extern void UpfilterX(color_t *src1, color_t *dst);
extern void UpfilterXLeft(color_t *src1, color_t *dst);
extern void UpfilterXRight(color_t *src1, color_t *dst);


// Y filtering
extern void DownfilterY(color_t *src1, color_t *src2, color_t *src3, color_t *src4, color_t *dst);
extern void DownfilterY(color_t *src1, color_t *src2, color_t *src3, color_t *dst);
extern void UpfilterY(color_t *src1, color_t *src2, color_t *src3, color_t *dst1, color_t *dst2);



#endif 
