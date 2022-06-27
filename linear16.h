// File: linear16.h
// Created by: Kyle Granger
// License: MIT

#ifndef __LINEAR16_H
#define __LINEAR16_H

#include "simple.h"
#include "filter16.h"
#include <string>


class CLinear16 {

public:
	int  mWidth;
	int  mHeight;
	size_t  mDataSize;
	int mChannel;
	color_t *mData;

	CLinear16();
	CLinear16(int w, int h);
	~CLinear16();
	void Invert();
	void ChannelSwap(int swap);
	bool WriteSimple16(std::string filename, ESimpleFormat format);
	bool ReadSimple16(std::string filename);
	CLinear16 *Upsample();
	CLinear16 *UpsampleX();
	CLinear16 *UpsampleY();
	CLinear16 *Downsample();
	CLinear16 *DownsampleX();
	CLinear16 *DownsampleY();
	void Upsample(CLinear16 *bmp);
	void UpsampleX(CLinear16 *bmp);
	void UpsampleY(CLinear16 *bmp);
	void Downsample(CLinear16 *bmp);
	void DownsampleX(CLinear16 *bmp);
	void DownsampleY(CLinear16 *bmp);
	bool WriteBmp(std::string filename);
	bool ReadBmp(std::string filename);
	void ConvertToMonochrome();
	void CompositePremultiplied(CLinear16 *overlay);
	void CompositeStraight(CLinear16 *overlay);
	void WriteLumaToAlpha(bool invertLuma);
	void BlitImage(CLinear16 *src, int dstX, int dstY);
	void DrawMonochromeAnaglyph(CLinear16 *left, CLinear16 *right);
	bool Write(std::string filename);
	//void Mix( CLinear16 *bitmap_a, CLinear16 *bitmap_b,
	//	int milli_a, int milli_b );
	bool Init(int width, int height);
	void GetPixel(int x, int y, color_t &color);
	//void GetScalePixel( int x, int y, color_t &color);
	//void SetPixel( int x, int y, color_t &color);
	void Flip( bool flipX, bool flipY );
	void Rotate( int angle );
private:
	void WriteSimpleScanline( color_t *src, uint16_t *dst, ESimpleFormat format );
	void ReadSimpleScanline( uint16_t *src, color_t *dst, ESimpleFormat format );
	void Rotate90();

};


// BMP structs


struct __attribute__ ((packed)) BitmapFileHeader
{
      int16_t  bfType;
      uint32_t bfSize;
      int16_t  bfReserved1;
      int16_t  bfReserved2;
      uint32_t bfOffBits;
};

struct __attribute__ ((packed)) BitmapInfoHeader
{
      uint32_t biSize;
      int32_t  biWidth;
      int32_t  biHeight;
      int16_t  biPlanes;
      int16_t  biBitCount;
      uint32_t biCompression;
      uint32_t biSizeImage;
      int32_t  biXPelsPerMeter;
      int32_t  biYPelsPerMeter;
      uint32_t biClrUsed;
      uint32_t biClrImportant;
};



#endif 
