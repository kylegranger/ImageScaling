// File: simple.h
// Created by: Kyle Granger
// License: MIT

#ifndef SIMPLE_H
#define SIMPLE_H

#include "stdint.h"

typedef enum ESimpleFormat {
	ESimpleFormatRgba = 3131,  // 4 channels
	ESimpleFormatBgra = 3132,  // 4 channels
	ESimpleFormatRgb  = 3133,  // 3 channels
	ESimpleFormatBgr  = 3134,  // 4 channels
	ESimpleFormatL    = 3135,  // 1 channel, luma
	ESimpleFormatLa   = 3136,  // 2 channels
} ESimpleFormat;


typedef struct TSimpleHeader {
	// 'SIMPLICE' = 0x4543494c504d4953L
	uint32_t cookieA;
	uint32_t cookieB;
	// datasize does not include 32-byte header
	int64_t datasize;
	int32_t width;
	int32_t height;
	// 8, 16, or 32; if 32, then float
	int32_t bits;
	// ESimpleFormat
	int32_t format;
} TSimpleHeader;


#endif

