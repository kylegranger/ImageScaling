
#ifndef __LINEAR16_H
#define __LINEAR16_H

#include "acidtypes.h"
#include "simple.h"


class CLinear16 {

public:
	int  mWidth;
	int  mHeight;
	int  mDataSize;
	int mChannel;
	color_t *mData;

	CLinear16();
	CLinear16(int w, int h);
	~CLinear16();
	void Invert();
	void ChannelSwap(int swap);
	bool WriteSimple16(char *filename, ESimpleFormat format);
	bool ReadSimple16(char *filename);
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
	bool WriteBmp(char *filename);
	bool ReadBmp(char *filename);
	bool ReadBmpCropped( char *filename, int offsetX, int offsetY );
	void ConvertToMonochrome();
	void CompositePremultiplied(CLinear16 *overlay);
	void CompositeStraight(CLinear16 *overlay);
	void WriteLumaToAlpha(bool invertLuma);
	void BlitImage(CLinear16 *src, int dstX, int dstY);
	void DrawMonochromeAnaglyph(CLinear16 *left, CLinear16 *right);
	bool Write( char *filename );
	//void Mix( CLinear16 *bitmap_a, CLinear16 *bitmap_b,
	//	int milli_a, int milli_b );
	bool Init( int width, int height );
	void GetPixel( int x, int y, color_t &color);
	//void GetScalePixel( int x, int y, color_t &color);
	//void SetPixel( int x, int y, color_t &color);
	void Flip( bool flipX, bool flipY );
	void Rotate( int angle );
private:
	void CLinear16::WriteSimpleScanline( color_t *src, uint16_t *dst, 
		ESimpleFormat format );
	void ReadSimpleScanline( uint16_t *src, color_t *dst, 
		ESimpleFormat format );
	void Rotate90();

};



#endif 
