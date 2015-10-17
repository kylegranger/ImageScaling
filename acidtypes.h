
// File: acidtypes.h
// Date: August 24, 2014
// Create by: Kyle Granger
// License: Public Domain
// Checked into Githib: October 17, 2015

#ifndef ACIDTYPES_H
#define ACIDTYPES_H

typedef signed char        int8_t;
typedef unsigned char     uint8_t;
typedef short             int16_t;
typedef unsigned short   uint16_t;
typedef int               int32_t;
typedef unsigned         uint32_t;
typedef __int64           int64_t;
typedef unsigned __int64 uint64_t;

typedef struct color_t {
	uint16_t b;
	uint16_t g;
	uint16_t r;
	uint16_t a;
} color_t;

typedef struct vector3_t {
	float x;
	float y;
	float z;
} vector3_t;

typedef enum ECameraView {
	CAMERA_LEFT = 1,
	CAMERA_MIDDLE,
	CAMERA_RIGHT
} ECameraView;

typedef enum ERenderType {
	RENDER_TYPE_NONE = 0,
	RENDER_TYPE_BOX,
	RENDER_TYPE_IMAGE,
	RENDER_TYPE_SMOKE,
} ERenderType;

typedef struct keyframe_t {
	int startframe;
	float a;
	int endframe;
	float b;
	float *dst;
} keyframe_t;



#endif

