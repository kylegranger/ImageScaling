#include "windows.h"
#include "math.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "linear16.h"
#include "filter16.h"
#include "simple.h"
#include "pool.h"

CLinear16::CLinear16()
{
	mWidth = 0;
	mHeight = 0;
	mDataSize = 0;
	mData = NULL;
	mChannel = -1;
}


CLinear16::CLinear16(int width, int height)
{
	mWidth = width;
	mHeight = height;
	mDataSize = mWidth * mHeight * sizeof(color_t);
	mData = new color_t[ mWidth * mHeight ];
	memset(mData,128,mDataSize);
	assert(mData);
	mChannel = -1;
}




CLinear16::~CLinear16()
{
	if ( mData ) 
	{
		delete [] mData;
		mData = NULL;
	}
}

bool CLinear16::ReadBmp( char *filename )
{
	size_t res;

	FILE *f = fopen(filename,"rb");
	if ( !f ) 
	{
		assert(0);
		return false;
	}

	BITMAPFILEHEADER bfh;
	res = fread(&bfh,1,sizeof(bfh),f);

	BITMAPINFOHEADER bmh;
	res = fread(&bmh,1,sizeof(bmh),f);

	bool isFlipped = (bmh.biHeight > 0);
	mWidth = bmh.biWidth;
	mHeight = isFlipped ? bmh.biHeight : -bmh.biHeight ;
	
	int num_pixels = mWidth * mHeight;
	int size = num_pixels * sizeof(color_t);
	if ( size > mDataSize )
	{
		if ( mData ) delete [] mData;
		mData = new color_t[num_pixels];
		assert(mData);
		mDataSize = size;
	}

	uint8_t *buffer = new uint8_t[ mWidth * mHeight * 3 ];
	res = fread(buffer,1, mWidth * mHeight * 3,f);

	color_t *c = mData;
	uint8_t *cptr = buffer;
	for ( int y = 0; y < mHeight; y++ )
	{
		color_t *c = isFlipped ? mData + (mHeight - y - 1) * mWidth : mData + y * mWidth;
		for ( int x = 0; x < mWidth; x++ )
		{
			c->b = cptr[0] * 65535 / 255;
			c->g = cptr[1] * 65535 / 255;
			c->r = cptr[2] * 65535 / 255;
			cptr += 3;
			c++;
		}
	}

	delete [] buffer;
	fclose(f);
	return true;
}


bool CLinear16::ReadBmpCropped( char *filename, int offsetX, int offsetY )
{
	unsigned char buffer[48*1024];
	size_t res;

	FILE *f = fopen(filename,"rb");
	if ( !f ) 
	{
		assert(0);
		return false;
	}

	BITMAPFILEHEADER bfh;
	res = fread(&bfh,1,sizeof(bfh),f);

	BITMAPINFOHEADER bmh;
	res = fread(&bmh,1,sizeof(bmh),f);

	bool isFlipped = (bmh.biHeight > 0);
	int fileWidth = bmh.biWidth;
	int fileHeight = isFlipped ? bmh.biHeight : -bmh.biHeight ;
	
	for ( int y = 0; y < offsetY; y++ )
		res = fread(buffer,1, fileWidth * 3,f);

	color_t *c = mData;
	for ( int y = 0; y < mHeight; y++ )
	{
		res = fread(buffer,1, fileWidth * 3,f);
		uint8_t *cptr = buffer + offsetX*3;
		color_t *c = isFlipped ? mData + (mHeight - y - 1) * mWidth : mData + y * mWidth;
		for ( int x = 0; x < mWidth; x++ )
		{
			c->b = cptr[0] * 65535 / 255;
			c->g = cptr[1] * 65535 / 255;
			c->r = cptr[2] * 65535 / 255;
			cptr += 3;
			c++;
		}
	}

	fclose(f);
	return true;
}


void CLinear16::ChannelSwap(int swap)
{
	color_t *c = mData;
	int numpixels = mWidth * mHeight;
	if (swap == 132)
	{
		for (int i = 0; i < numpixels; i++)
		{
			color_t temp = *c;
			c->g = temp.b;
			c->b = temp.g;
			c++;
		}
	}
	else if (swap == 213)
	{
		for (int i = 0; i < numpixels; i++)
		{
			color_t temp = *c;
			c->r = temp.g;
			c->g = temp.r;
			c++;
		}
	}
	else if (swap == 231)
	{
		for (int i = 0; i < numpixels; i++)
		{
			color_t temp = *c;
			c->r = temp.g;
			c->g = temp.b;
			c->b = temp.r;
			c++;
		}
	}
	else if (swap == 312)
	{
		for (int i = 0; i < numpixels; i++)
		{
			color_t temp = *c;
			c->r = temp.b;
			c->g = temp.r;
			c->b = temp.g;
			c++;
		}
	}
	else if (swap == 321)
	{
		for (int i = 0; i < numpixels; i++)
		{
			color_t temp = *c;
			c->r = temp.b;
			c->b = temp.r;
			c++;
		}
	}
}


void CLinear16::Invert()
{
	color_t *c = mData;
	int numpixels = mWidth * mHeight;
	for ( int i = 0; i < numpixels; i++ )
	{
		c->r = 65535 - c->r;
		c->g = 65535 - c->g;
		c->b = 65535 - c->b;
		c++;
	}
}


bool CLinear16::Init( int width, int height )
{
	mWidth = width;
	mHeight = height;
	mDataSize = mWidth * mHeight * sizeof(color_t);
	mData = new color_t[ mWidth * mHeight ];
	if ( !mData ) return false;
	return true;
}

void CLinear16::GetPixel( int x, int y, color_t &color)
{
	if ( x < 0 )        x = 0;
	if ( x >= mWidth )  x = mWidth - 1;
	if ( y < 0 )        y = 0;
	if ( y >= mHeight ) y = mHeight - 1;

	color_t *c = mData + y * mWidth + x;
	color = *c;
}

/*void CLinear16::SetPixel( int x, int y, color_t &color)
{
	if ( x < 0 )        x = 0;
	if ( x >= mWidth )  x = mWidth - 1;
	if ( y < 0 )        y = 0;
	if ( y >= mHeight ) y = mHeight - 1;

	color_t *c = mData + (mHeight - y - 1) * mWidth * 3 + x * 3;
	*c = color;
}


void CLinear16::Mix( CLinear16 *bitmap_a, CLinear16 *bitmap_b,
		int milli_a, int milli_b )
{
	if ( mWidth == 0 )
	{
		Init(bitmap_a->mWidth,bitmap_a->mHeight);
	}
	color_t *src1 = bitmap_a->mData;
	color_t *src2 = bitmap_b->mData;
	color_t *dst  = mData;

	int i;
	for ( i = 0; i < mWidth * mHeight; i++ )
	{
		dst->r = ( src1->r * milli_a + src2->r * milli_b ) / 1000;
		dst->g = ( src1->g * milli_a + src2->g * milli_b ) / 1000;
		dst->b = ( src1->b * milli_a + src2->b * milli_b ) / 1000;
		src1++; src2++; dst++;
	}
}
*/


/*bool CLinear16::WritePng16(char *filename)
{
	return true;
}
bool CLinear16::ReadPng16(char *filename)
{
	return true;
}*/

bool CLinear16::WriteBmp(char *filename)
{
	FILE *f = NULL;
	int size, res;
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bmh;

	fopen_s( &f, filename,"wb");
	if ( !f ) return false;
	size = mWidth*mHeight*3;

	memcpy(&bfh.bfType,"BM",2);
	bfh.bfSize = size + 56;
	bfh.bfOffBits = 54;
	res = (int)fwrite(&bfh,1,sizeof(bfh),f);

	memset(&bmh,0,sizeof(bmh));
	bmh.biSize = sizeof(bmh);
	bmh.biWidth = mWidth;
	bmh.biHeight = -mHeight;
	bmh.biPlanes = 1;
	bmh.biBitCount = 24;
	bmh.biXPelsPerMeter = 2834;
	bmh.biYPelsPerMeter = 2834;
	res = (int)fwrite(&bmh,1,sizeof(bmh),f);
	int npixels = mWidth*mHeight;
	color_t *cptr = mData;
	uint8_t color[4];
	int pad = 0;
	int rowbytes = mWidth * 3;
	int modu = rowbytes & 3;
	if ( modu )
		pad = 4 - modu;

	for ( int y = 0; y < mHeight; y++ )
	{
		for ( int x = 0; x < mWidth; x++ )
		{
			color[0] = cptr->b * 255 / 65535;
			color[1] = cptr->g * 255 / 65535;
			color[2] = cptr->r * 255 / 65535;
			res = (int)fwrite(color,1,3,f);
			cptr++;
		}
		if ( pad )
			res = (int)fwrite(color,1,pad,f);
	}
	res = (int)fwrite(color,1,2,f);
	fclose(f);
	return true;
}

CLinear16 *CLinear16::Upsample()
{
	CLinear16 *bmp = new CLinear16(mWidth*2, mHeight*2);
	Upsample(bmp);
	return bmp;
}


void CLinear16::Upsample(CLinear16 *bmp)
{
	color_t *src1 = mData - 1 - mWidth;
	color_t *src2 = mData - 1;
	color_t *src3 = mData - 1 + mWidth;
	color_t *dst1 = bmp->mData;
	color_t *dst2 = bmp->mData + bmp->mWidth;
	for ( int y = 0; y < mHeight; y++ )
	{
		if ( y == 0 )
		{
			UpfilterLeft(src2, src2, src3, dst1, dst2);
			src1++; src2++; src3++;
			dst1 += 2;
			dst2 += 2;
			for ( int x = 1; x < mWidth-1; x++ )
			{
				Upfilter(src2, src2, src3, dst1, dst2);
				dst1 += 2;
				dst2 += 2;
				src1++; src2++; src3++;
			}
			UpfilterRight(src1, src2, src2, dst1, dst2);
			src1++; src2++; src3++;
			dst1 += 2;
			dst2 += 2;
		}
		else if ( y == mHeight - 1 )
		{
			UpfilterLeft(src1, src2, src2, dst1, dst2);
			src1++; src2++; src3++;
			dst1 += 2;
			dst2 += 2;
			for ( int x = 1; x < mWidth-1; x++ )
			{
				Upfilter(src1, src2, src2, dst1, dst2);
				src1++; src2++; src3++;
				dst1 += 2;
				dst2 += 2;
			}
			UpfilterRight(src1, src2, src2, dst1, dst2);
			src1++; src2++; src3++;
			dst1 += 2;
			dst2 += 2;
		}
		else
		{
			UpfilterLeft(src1++, src2++, src3++, dst1, dst2);
			dst1 += 2;
			dst2 += 2;
			for ( int x = 1; x < mWidth-1; x++ )
			{
				Upfilter(src1++, src2++, src3++, dst1, dst2);
				dst1 += 2;
				dst2 += 2;
			}
			UpfilterRight(src1++, src2++, src3++, dst1, dst2);
			dst1 += 2;
			dst2 += 2;
		}
		dst1 += bmp->mWidth;
		dst2 += bmp->mWidth;
	}
}


CLinear16 *CLinear16::UpsampleX()
{
	CLinear16 *bmp = new CLinear16(mWidth*2, mHeight);
	UpsampleX(bmp);
	return bmp;
}

void CLinear16::UpsampleX(CLinear16 *bmp)
{
	color_t *src = mData - 1;
	color_t *dst = bmp->mData;
	for ( int y = 0; y < mHeight; y++ )
	{
		UpfilterXLeft(src++, dst);
		dst += 2;
		for ( int x = 1; x < mWidth-1; x++ )
		{
			UpfilterX(src++, dst);
			dst += 2;
		}
		UpfilterXRight(src++, dst);
		dst += 2;
	}
}


CLinear16 *CLinear16::UpsampleY()
{
	CLinear16 *bmp = new CLinear16(mWidth, mHeight*2);
	UpsampleY(bmp);
	return bmp;
}

void CLinear16::UpsampleY(CLinear16 *bmp)
{
	color_t *src1 = mData - mWidth;
	color_t *src2 = mData;
	color_t *src3 = mData + mWidth;
	color_t *dst1 = bmp->mData;
	color_t *dst2 = bmp->mData + bmp->mWidth;
	for ( int y = 0; y < mHeight; y++ )
	{
		if ( y == 0 )
		{
			for ( int x = 0; x < mWidth; x++ )
			{
				UpfilterY(src2, src2, src3, dst1++, dst2++);
				src1++; src2++; src3++;
			}
		}
		else if ( y == mHeight - 1 )
		{
			for ( int x = 0; x < mWidth; x++ )
			{
				UpfilterY(src1, src2, src2, dst1++, dst2++);
				src1++; src2++; src3++;
			}
		}
		else
		{
			for ( int x = 0; x < mWidth; x++ )
			{
				Upfilter(src1++, src2++, src3++, dst1++, dst2++);
			}
		}
		dst1 += bmp->mWidth;
		dst2 += bmp->mWidth;
	}
}


CLinear16 *CLinear16::Downsample()
{
	CLinear16 *bmp = new CLinear16(mWidth/2, mHeight/2);
	Downsample(bmp);
	return bmp;
}

void CLinear16::Downsample(CLinear16 *bmp)
{
	assert((mWidth  & 0xfffe) == bmp->mWidth*2);
	assert((mHeight & 0xfffe) == bmp->mHeight*2);
	color_t *src1 = mData - 1 - mWidth;
	color_t *src2 = mData - 1;
	color_t *src3 = mData - 1 + mWidth;
	color_t *src4 = mData - 1 + mWidth * 2;
	color_t *dst = bmp->mData;
	int padw = mWidth & 1;
	for ( int y = 0; y < bmp->mHeight; y++)
	{
		if ( y == 0 )
		{
			DownfilterLeft(src4, src2, src3, dst++);
			src1 += 2;
			src2 += 2;
			src3 += 2;
			src4 += 2;
			for ( int x = 1; x < bmp->mWidth-1; x++ )
			{
				Downfilter(src4, src2, src3, dst++);
				src1 += 2;
				src2 += 2;
				src3 += 2;
				src4 += 2;
			}
			DownfilterRight(src4, src2, src3, dst++);
			src1 += 2 + padw;
			src2 += 2 + padw;
			src3 += 2 + padw;
			src4 += 2 + padw;
		}
		else if ( y == bmp->mHeight - 1 )
		{
			DownfilterLeft(src1, src2, src3, dst++);
			src1 += 2;
			src2 += 2;
			src3 += 2;
			src4 += 2;
			for ( int x = 1; x < bmp->mWidth-1; x++ )
			{
				Downfilter(src1, src2, src3, dst++);
				src1 += 2;
				src2 += 2;
				src3 += 2;
				src4 += 2;
			}
			DownfilterRight(src1, src2, src3, dst++);
			src1 += 2 + padw;
			src2 += 2 + padw;
			src3 += 2 + padw;
			src4 += 2 + padw;
		}
		else
		{
			DownfilterLeft(src1, src2, src3, src4, dst++);
			src1 += 2;
			src2 += 2;
			src3 += 2;
			src4 += 2;
			for ( int x = 1; x < bmp->mWidth-1; x++ )
			{
				Downfilter(src1, src2, src3, src4, dst++);
				src1 += 2;
				src2 += 2;
				src3 += 2;
				src4 += 2;
			}
			DownfilterRight(src1, src2, src3, src4, dst++);
			src1 += 2 + padw;
			src2 += 2 + padw;
			src3 += 2 + padw;
			src4 += 2 + padw;
		}
		src1 += mWidth;
		src2 += mWidth;
		src3 += mWidth;
		src4 += mWidth;
	}
}


CLinear16 *CLinear16::DownsampleX()
{
	CLinear16 *bmp = new CLinear16(mWidth/2, mHeight);
	DownsampleX(bmp);
	return bmp;
}

void CLinear16::DownsampleX(CLinear16 *bmp)
{
	assert((mWidth  & 0xfffe) == bmp->mWidth*2);
	assert(mHeight == bmp->mHeight);
	color_t *src = mData - 1;
	color_t *dst = bmp->mData;
	for ( int y = 0; y < bmp->mHeight; y++)
	{
		DownfilterXLeft(src, dst++);
		src += 2;
		for ( int x = 1; x < bmp->mWidth-1; x++ )
		{
			DownfilterX(src, dst++);
			src += 2;
		}
		DownfilterXRight(src, dst++);
		src += 2 + (mWidth&1);
	}
}


CLinear16 *CLinear16::DownsampleY()
{
	CLinear16 *bmp = new CLinear16(mWidth, mHeight/2);
	DownsampleY(bmp);
	return bmp;
}

void CLinear16::DownsampleY(CLinear16 *bmp)
{
	assert(mWidth == bmp->mWidth);
	assert(mHeight == bmp->mHeight*2);
	color_t *src1 = mData - mWidth;
	color_t *src2 = mData;
	color_t *src3 = mData + mWidth;
	color_t *src4 = mData + mWidth * 2;
	color_t *dst = bmp->mData;
	for ( int y = 0; y < bmp->mHeight; y++)
	{
		if ( y == 0 )
		{
			for ( int x = 0; x < bmp->mWidth; x++ )
			{
				DownfilterY(src2++, src3++, src4++, dst++);
				src1++;
			}
		}
		else if ( y == bmp->mHeight - 1 )
		{
			for ( int x = 0; x < bmp->mWidth; x++ )
			{
				DownfilterY(src2++, src3++, src1++, dst++);
				src4++;
			}
		}
		else
		{
			for ( int x = 0; x < bmp->mWidth; x++ )
			{
				DownfilterY(src1++, src2++, src3++, src4++, dst++);
			}
		}
		src1 += mWidth;
		src2 += mWidth;
		src3 += mWidth;
		src4 += mWidth;
	}
}

void CLinear16::WriteSimpleScanline( color_t *src, uint16_t *dst, 
	ESimpleFormat format )
{

	switch ( format )
	{
	case ESimpleFormatRgba:
		for ( int i = 0; i < mWidth; i++ )
		{
			*dst++ = src->r;
			*dst++ = src->g;
			*dst++ = src->b;
			*dst++ = src->a;
			src++;
		}
		break;
	case ESimpleFormatBgra:
		for ( int i = 0; i < mWidth; i++ )
		{
			*dst++ = src->b;
			*dst++ = src->g;
			*dst++ = src->r;
			*dst++ = src->a;
			src++;
		}
		break;
	case ESimpleFormatRgb:
		for ( int i = 0; i < mWidth; i++ )
		{
			*dst++ = src->r;
			*dst++ = src->g;
			*dst++ = src->b;
			src++;
		}
		break;
	case ESimpleFormatBgr:
		for ( int i = 0; i < mWidth; i++ )
		{
			*dst++ = src->b;
			*dst++ = src->g;
			*dst++ = src->r;
			src++;
		}
		break;
	case ESimpleFormatL:
		for ( int i = 0; i < mWidth; i++ )
		{
			*dst++ = ( src->r * 299 + src->g * 587 + src->b * 114 ) / 1000;
			src++;
		}
		break;
	case ESimpleFormatLa:
		for ( int i = 0; i < mWidth; i++ )
		{
			*dst++ = ( src->r * 299 + src->g * 587 + src->b * 114 ) / 1000;
			*dst++ = src->a;
			src++;
		}
		break;
	}
}
void CLinear16::ReadSimpleScanline( uint16_t *src, color_t *dst, 
	ESimpleFormat format )
{
	switch ( format )
	{
	case ESimpleFormatRgba:
		for ( int i = 0; i < mWidth; i++ )
		{
			dst->r = *src++;
			dst->g = *src++;
			dst->b = *src++;
			dst->a = *src++;
			dst++;
		}
		break;
	case ESimpleFormatBgra:
		for ( int i = 0; i < mWidth; i++ )
		{
			dst->b = *src++;
			dst->g = *src++;
			dst->r = *src++;
			dst->a = *src++;
			dst++;
		}
		break;
	case ESimpleFormatRgb:
		for ( int i = 0; i < mWidth; i++ )
		{
			dst->r = *src++;
			dst->g = *src++;
			dst->b = *src++;
			dst->a = 0xffff;
			dst++;
		}
		break;
	case ESimpleFormatBgr:
		for ( int i = 0; i < mWidth; i++ )
		{
			dst->b = *src++;
			dst->g = *src++;
			dst->r = *src++;
			dst->a = 0xffff;
			dst++;
		}
		break;
	case ESimpleFormatL:
		for ( int i = 0; i < mWidth; i++ )
		{
			dst->b = *src;
			dst->g = *src;
			dst->r = *src++;
			dst->a = 0xffff;
			dst++;
		}
		break;
	case ESimpleFormatLa:
		for ( int i = 0; i < mWidth; i++ )
		{
			dst->b = *src;
			dst->g = *src;
			dst->r = *src++;
			dst->a = *src++;
			dst++;
		}
		break;
	}
}

bool CLinear16::WriteSimple16(char *filename, ESimpleFormat format)
{
	int bytesPerPixel;
	TSimpleHeader header;
	int bytesPerLine;
	FILE *file;

	fopen_s(&file, filename, "wb");
	if ( file == NULL ) 
		return false;
	switch ( format )
	{
	case ESimpleFormatRgba:
	case ESimpleFormatBgra:
		bytesPerPixel = 8;
		break;
	case ESimpleFormatRgb:
	case ESimpleFormatBgr:
		bytesPerPixel = 6;
		break;
	case ESimpleFormatL:
		bytesPerPixel = 2;
		break;
	case ESimpleFormatLa:
		bytesPerPixel = 4;
		break;
	default:
		assert(0);
	return false;
	}

	header.cookie = 'PMIS' + ((uint64_t)'ECIL' << 32L);
	header.datasize = bytesPerPixel * mWidth * mHeight;
	header.width = mWidth;
	header.height = mHeight;
	header.bits = 16;
	header.format = format;
	fwrite(&header,1,sizeof(TSimpleHeader),file);
	bytesPerLine = mWidth * bytesPerPixel;
	uint16_t *dst = (uint16_t *) malloc(bytesPerLine);
	color_t *src = mData;
	for ( int i = 0; i < mHeight; i++ )
	{
		WriteSimpleScanline( src, dst, format );
		fwrite(dst,1,bytesPerLine,file);
		src += mWidth;
	}
	fclose(file);
	free(dst);
	return true;
}

bool CLinear16::ReadSimple16(char *filename)
{
	int bytesPerPixel;
	TSimpleHeader header;
	int bytesPerLine;
	FILE *file;
	fopen_s(&file, filename, "rb");

	if ( filename == NULL ) 
		return false;
	size_t res = fread(&header,1,sizeof(TSimpleHeader),file);

	switch ( header.format )
	{
	case ESimpleFormatRgba:
	case ESimpleFormatBgra:
		bytesPerPixel = 4 * header.bits / 8;
		break;
	case ESimpleFormatRgb:
	case ESimpleFormatBgr:
		bytesPerPixel = 3 * header.bits / 8;
		break;
	case ESimpleFormatL:
		bytesPerPixel = 1 * header.bits / 8;
		break;
	case ESimpleFormatLa:
		bytesPerPixel = 2 * header.bits / 8;
		break;
	default:
		assert(0);
		return false;
	}


	assert(header.cookie == 0x4543494c504d4953L);
	//header.width = mWidth;
	//header.height = mHeight;
	//header.bits = 16;
	//header.format = format;
	//fwrite(&header,1,sizeof(TSimpleHeader),file);
	bytesPerLine = mWidth * bytesPerPixel;
	uint16_t *src = (uint16_t *) malloc(bytesPerLine);
	color_t *dst = mData;
	for ( int i = 0; i < mHeight; i++ )
	{
		fread(src,1,bytesPerLine,file);
		ReadSimpleScanline( src, dst, (ESimpleFormat) header.format );
		dst += mWidth;
	}
	fclose(file);
	free(src);
	return true;
}


// Linear RGB to grayscale
// Y = .2126 * R^gamma + .7152 * G^gamma + .0722 * B^gamma
void CLinear16::ConvertToMonochrome()
{
	color_t *c = mData;
	for ( int y = 0; y < mHeight; y++ )
	{
		for ( int x = 0; x < mWidth; x++ )
		{
			// scale by 10000
			int luma = c->r * 2126 + c->g * 7152 + c->b * 722 + 5000;
			luma /= 10000;
			c->r = luma;
			c->g = luma;
			c->b = luma;
			c++;
		}
	}

}


void CLinear16::CompositePremultiplied(CLinear16 *overlay)
{
	color_t *src = overlay->mData;
	color_t *dst = mData;
	for ( int y = 0; y < mHeight; y++ )
	{
		for ( int x = 0; x < mWidth; x++ )
		{
			if ( src->a == 0xffff )
			{
				// destination gets 100% of source
				*dst = *src;
			}
			else if ( src->a > 0 )
			{
				// destination gets 100% of source
				int b = 0xffff - src->a;
				dst->b = dst->b * b / 65535 + src->b;
				dst->g = dst->g * b / 65535 + src->g;
				dst->r = dst->r * b / 65535 + src->r;
			}
			src++;
			dst++;
		}
	}
}

void CLinear16::CompositeStraight(CLinear16 *overlay)
{
	color_t *src = overlay->mData;
	color_t *dst = mData;
	for ( int y = 0; y < mHeight; y++ )
	{
		for ( int x = 0; x < mWidth; x++ )
		{
			if ( src->a == 0xffff )
			{
				// destination gets 100% of source
				*dst = *src;
			}
			else if ( src->a > 0 )
			{
				// destination gets 100% of source
				int b = 0xffff - src->a;
				dst->b = ( dst->b * b + src->b * src->a ) / 65535;
				dst->g = ( dst->g * b + src->g * src->a ) / 65535;
				dst->r = ( dst->r * b + src->r * src->a ) / 65535;
			}
			src++;
			dst++;
		}
	}
}


void CLinear16::WriteLumaToAlpha(bool invertLuma)
{
	color_t *c = mData;
	for ( int y = 0; y < mHeight; y++ )
	{
		for ( int x = 0; x < mWidth; x++ )
		{
			int luma = c->r * 2126 + c->g * 7152 +c->b * 722 + 5000;
			luma /= 10000;
			c->a = invertLuma ? 65535 - luma : luma;
			c++;
		}
	}
}

void CLinear16::BlitImage(CLinear16 *image, int dstX, int dstY)
{
	if (dstX + image->mWidth > mWidth)
	{
		assert(0);
		return;
	}
	if (dstY + image->mHeight > mHeight)
	{
		assert(0);
		return;
	}
	color_t *src = image->mData;
	color_t *dst = mData + dstY*mWidth + dstX;
	for (int y = 0; y < image->mHeight; y++)
	{
		for (int x = 0; x < image->mWidth; x++)
		{
			*dst++ = *src++;
		}
		dst += mWidth - image->mWidth;
	}
}

void CLinear16::DrawMonochromeAnaglyph(CLinear16 *left, CLinear16 *right)
{
	if ( left && right )
	{
		assert(left->mWidth == mWidth);
		assert(left->mHeight == mHeight);
		assert(right->mWidth == mWidth);
		assert(right->mHeight == mHeight);
		color_t *src1 = left->mData;
		color_t *src2 = right->mData;
		color_t *dst = mData;
		for (int y = 0; y < mHeight; y++)
		{
			for (int x = 0; x < mWidth; x++)
			{
				int luma1 = src1->r * 2126 + src1->g * 7152 + src1->b * 722 + 5000;
				int luma2 = src2->r * 2126 + src2->g * 7152 + src2->b * 722 + 5000;
				luma1 /= 10000;
				luma2 /= 10000;
				dst->r = luma1;
				dst->g = luma2 * 3 / 4;
				dst->b = luma2;
				dst->a = 0xffff;
				dst++;
			}
		}
	}
	else if ( left )
	{
		assert(left->mWidth == mWidth);
		assert(left->mHeight == mHeight);
		color_t *src = left->mData;
		color_t *dst = mData;
		for (int y = 0; y < mHeight; y++)
		{
			for (int x = 0; x < mWidth; x++)
			{
				int luma1 = src->r * 2126 + src->g * 7152 + src->b * 722 + 5000;
				luma1 /= 10000;
				dst->r = luma1;
				dst->a = 0xffff;
				dst++;
				src++;
			}
		}
	}
	else if ( right )
	{
		assert(right->mWidth == mWidth);
		assert(right->mHeight == mHeight);
		color_t *src = right->mData;
		color_t *dst = mData;
		for (int y = 0; y < mHeight; y++)
		{
			for (int x = 0; x < mWidth; x++)
			{
				int luma2 = src->r * 2126 + src->g * 7152 + src->b * 722 + 5000;
				luma2 /= 10000;
				dst->g = luma2 * 3 / 4;
				dst->b = luma2;
				dst++;
				src++;
			}
		}
	}
	else
		assert(0);

}

void CLinear16::Flip( bool flipX, bool flipY )
{
	color_t *src;
	color_t *dst;
	color_t temp;

	if ( flipY )
	{
		for ( int y = 0; y < mHeight/2; y++ )
		{
			src = mData + y * mWidth;
			dst = mData + (mHeight - 1 - y) * mWidth;
			if ( flipX )
			{
				dst += mWidth - 1;
				for ( int x = 0; x < mWidth; x++ )
				{
					temp = *src;
					*src++ = *dst;
					*dst-- = temp;
				}
			}
			else
			{
				for ( int x = 0; x < mWidth; x++ )
				{
					temp = *src;
					*src++ = *dst;
					*dst++ = temp;
				}
			}
		}
	}
	else if ( flipX )
	{
		for ( int y = 0; y < mHeight; y++ )
		{
			src = mData + y * mWidth;
			dst = src + mWidth - 1;
			for ( int x = 0; x < mWidth/2; x++ )
			{
				temp = *src;
				*src++ = *dst;
				*dst-- = temp;
			}
		}
	}
}

void CLinear16::Rotate90()
{
	CLinear16 *temp = gPool.Alloc(mWidth, mHeight);

	color_t *src = mData;

	for ( int y = 0; y < mHeight; y++ )
	{
		color_t *dst = temp->mData + mWidth - 1 - y;
		for ( int x = 0; x < mWidth; x++ )
		{
			*dst = *src++;
			dst += mWidth;
		}
	}

	BlitImage(temp, 0, 0);

	gPool.Free(temp);
}


void CLinear16::Rotate( int angle )
{
	assert(mWidth == mHeight);
	angle = angle % 360;
	switch ( angle )
	{
	case 0:
		break;
	case 90:
		Rotate90();
		break;
	case 180:
		Flip(true, true);
		break;
	case 270:
		Flip(true, true);
		Rotate90();
		break;
	default:
		assert(0);
	}
}
