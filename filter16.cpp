// File: linear16.cpp
// Date: August 24, 2014
// Create by: Kyle Granger
// License: Public Domain
// Checked into Githib: October 17, 2015



#include "acidtypes.h"


void DownfilterX(color_t *src, color_t *dst)
{
	// we mix four source pixels into one destination pixel
	// All on same scanline.
	dst->r = ((src[0].r + 3 * (src[1].r + src[2].r) + src[3].r + 4) >> 3);
	dst->g = ((src[0].g + 3 * (src[1].g + src[2].g) + src[3].g + 4) >> 3);
	dst->b = ((src[0].b + 3 * (src[1].b + src[2].b) + src[3].b + 4) >> 3);
	dst->a = ((src[0].a + 3 * (src[1].a + src[2].a) + src[3].a + 4) >> 3);
}

void DownfilterXLeft(color_t *src, color_t *dst)
{
	// we mix four source pixels into one destination pixel
	// All on same scanline.
	dst->r = ((3 * (src[1].r + src[2].r) + src[3].r + 3) / 7);
	dst->g = ((3 * (src[1].g + src[2].g) + src[3].g + 3) / 7);
	dst->b = ((3 * (src[1].b + src[2].b) + src[3].b + 3) / 7);
	dst->a = ((3 * (src[1].a + src[2].a) + src[3].a + 3) / 7);
}

void DownfilterXRight(color_t *src, color_t *dst)
{
	// we mix four source pixels into one destination pixel
	// All on same scanline.
	dst->r = ((src[0].r + 3 * (src[1].r + src[2].r) + 3) / 7);
	dst->g = ((src[0].g + 3 * (src[1].g + src[2].g) + 3) / 7);
	dst->b = ((src[0].b + 3 * (src[1].b + src[2].b) + 3) / 7);
	dst->a = ((src[0].a + 3 * (src[1].a + src[2].a) + 3) / 7);
}

void DownfilterY(color_t *src1, color_t *src2, color_t *src3, color_t *src4, color_t *dst)
{
	// we mix four source pixels into one destination pixel
	// All within same column.
	dst->r = ((src1->r + 3 * (src2->r + src3->r) + src4->r + 4) >> 3);
	dst->g = ((src1->g + 3 * (src2->g + src3->g) + src4->g + 4) >> 3);
	dst->b = ((src1->b + 3 * (src2->b + src3->b) + src4->b + 4) >> 3);
	dst->a = ((src1->a + 3 * (src2->a + src3->a) + src4->a + 4) >> 3);
}

void DownfilterY(color_t *src2, color_t *src3, color_t *src4, color_t *dst)
{
	// we mix four source pixels into one destination pixel
	// All within same column.
	dst->r = ((3 * (src2->r + src3->r) + src4->r + 3) / 7);
	dst->g = ((3 * (src2->g + src3->g) + src4->g + 3) / 7);
	dst->b = ((3 * (src2->b + src3->b) + src4->b + 3) / 7);
	dst->a = ((3 * (src2->a + src3->a) + src4->a + 3) / 7);
}

void Downfilter(color_t *src1, color_t *src2, color_t *src3, color_t *src4, color_t *dst)
{
	// we mix 16 source pixels into one destination pixel
	int r = (src1[0].r + src1[3].r)     + 3 * (src1[1].r + src1[2].r);
	r    += (src2[0].r + src2[3].r) * 3 + 9 * (src2[1].r + src2[2].r);
	r    += (src3[0].r + src3[3].r) * 3 + 9 * (src3[1].r + src3[2].r);
	r    += (src4[0].r + src4[3].r)     + 3 * (src4[1].r + src4[2].r);
	dst->r = ((r+32)>>6);
	int g = (src1[0].g + src1[3].g)     + 3 * (src1[1].g + src1[2].g);
	g    += (src2[0].g + src2[3].g) * 3 + 9 * (src2[1].g + src2[2].g);
	g    += (src3[0].g + src3[3].g) * 3 + 9 * (src3[1].g + src3[2].g);
	g    += (src4[0].g + src4[3].g)     + 3 * (src4[1].g + src4[2].g);
	dst->g = ((g+32)>>6);
	int b = (src1[0].b + src1[3].b)     + 3 * (src1[1].b + src1[2].b);
	b    += (src2[0].b + src2[3].b) * 3 + 9 * (src2[1].b + src2[2].b);
	b    += (src3[0].b + src3[3].b) * 3 + 9 * (src3[1].b + src3[2].b);
	b    += (src4[0].b + src4[3].b)     + 3 * (src4[1].b + src4[2].b);
	dst->b = ((b+32)>>6);
	int a = (src1[0].a + src1[3].a)     + 3 * (src1[1].a + src1[2].a);
	a    += (src2[0].a + src2[3].a) * 3 + 9 * (src2[1].a + src2[2].a);
	a    += (src3[0].a + src3[3].a) * 3 + 9 * (src3[1].a + src3[2].a);
	a    += (src4[0].a + src4[3].a)     + 3 * (src4[1].a + src4[2].a);
	dst->a = ((a+32)>>6);
}

void Downfilter(color_t *src1, color_t *src2, color_t *src3, color_t *dst)
{
	// we mix 16 source pixels into one destination pixel
	int r = (src1[0].r + src1[3].r)     + 3 * (src1[1].r + src1[2].r);
	r    += (src2[0].r + src2[3].r) * 3 + 9 * (src2[1].r + src2[2].r);
	r    += (src3[0].r + src3[3].r) * 3 + 9 * (src3[1].r + src3[2].r);
	dst->r = ((r+28)/56);
	int g = (src1[0].g + src1[3].g)     + 3 * (src1[1].g + src1[2].g);
	g    += (src2[0].g + src2[3].g) * 3 + 9 * (src2[1].g + src2[2].g);
	g    += (src3[0].g + src3[3].g) * 3 + 9 * (src3[1].g + src3[2].g);
	dst->g = ((g+28)/56);
	int b = (src1[0].b + src1[3].b)     + 3 * (src1[1].b + src1[2].b);
	b    += (src2[0].b + src2[3].b) * 3 + 9 * (src2[1].b + src2[2].b);
	b    += (src3[0].b + src3[3].b) * 3 + 9 * (src3[1].b + src3[2].b);
	dst->b = ((b+28)/56);
	int a = (src1[0].a + src1[3].a)     + 3 * (src1[1].a + src1[2].a);
	a    += (src2[0].a + src2[3].a) * 3 + 9 * (src2[1].a + src2[2].a);
	a    += (src3[0].a + src3[3].a) * 3 + 9 * (src3[1].a + src3[2].a);
	dst->a = ((a+28)/56);
}

void DownfilterLeft(color_t *src1, color_t *src2, color_t *src3, color_t *src4, color_t *dst)
{
	// we mix 16 source pixels into one destination pixel
	int r = (src1[3].r)     + 3 * (src1[1].r + src1[2].r);
	r    += (src2[3].r) * 3 + 9 * (src2[1].r + src2[2].r);
	r    += (src3[3].r) * 3 + 9 * (src3[1].r + src3[2].r);
	r    += (src4[3].r)     + 3 * (src4[1].r + src4[2].r);
	dst->r = ((r+28)/56);
	int g = (src1[3].g)     + 3 * (src1[1].g + src1[2].g);
	g    += (src2[3].g) * 3 + 9 * (src2[1].g + src2[2].g);
	g    += (src3[3].g) * 3 + 9 * (src3[1].g + src3[2].g);
	g    += (src4[3].g)     + 3 * (src4[1].g + src4[2].g);
	dst->g = ((g+28)/56);
	int b = (src1[3].b)     + 3 * (src1[1].b + src1[2].b);
	b    += (src2[3].b) * 3 + 9 * (src2[1].b + src2[2].b);
	b    += (src3[3].b) * 3 + 9 * (src3[1].b + src3[2].b);
	b    += (src4[3].b)     + 3 * (src4[1].b + src4[2].b);
	dst->b = ((b+28)/56);
	int a = (src1[3].a)     + 3 * (src1[1].a + src1[2].a);
	a    += (src2[3].a) * 3 + 9 * (src2[1].a + src2[2].a);
	a    += (src3[3].a) * 3 + 9 * (src3[1].a + src3[2].a);
	a    += (src4[3].a)     + 3 * (src4[1].a + src4[2].a);
	dst->a = ((a+28)/56);
}

void DownfilterLeft(color_t *src1, color_t *src2, color_t *src3, color_t *dst)
{
	// we mix 16 source pixels into one destination pixel
	int r = (src1[3].r)     + 3 * (src1[1].r + src1[2].r);
	r    += (src2[3].r) * 3 + 9 * (src2[1].r + src2[2].r);
	r    += (src3[3].r) * 3 + 9 * (src3[1].r + src3[2].r);
	dst->r = ((r+24)/49);
	int g = (src1[3].g)     + 3 * (src1[1].g + src1[2].g);
	g    += (src2[3].g) * 3 + 9 * (src2[1].g + src2[2].g);
	g    += (src3[3].g) * 3 + 9 * (src3[1].g + src3[2].g);
	dst->g = ((g+24)/49);
	int b = (src1[3].b)     + 3 * (src1[1].b + src1[2].b);
	b    += (src2[3].b) * 3 + 9 * (src2[1].b + src2[2].b);
	b    += (src3[3].b) * 3 + 9 * (src3[1].b + src3[2].b);
	dst->b = ((b+24)/49);
	int a = (src1[3].a)     + 3 * (src1[1].a + src1[2].a);
	a    += (src2[3].a) * 3 + 9 * (src2[1].a + src2[2].a);
	a    += (src3[3].a) * 3 + 9 * (src3[1].a + src3[2].a);
	dst->a = ((a+24)/49);
}

void DownfilterRight(color_t *src1, color_t *src2, color_t *src3, color_t *src4, color_t *dst)
{
	// we mix 16 source pixels into one destination pixel
	int r = (src1[0].r)     + 3 * (src1[1].r + src1[2].r);
	r    += (src2[0].r) * 3 + 9 * (src2[1].r + src2[2].r);
	r    += (src3[0].r) * 3 + 9 * (src3[1].r + src3[2].r);
	r    += (src4[0].r)     + 3 * (src4[1].r + src4[2].r);
	dst->r = ((r+28)/56);
	int g = (src1[0].g)     + 3 * (src1[1].g + src1[2].g);
	g    += (src2[0].g) * 3 + 9 * (src2[1].g + src2[2].g);
	g    += (src3[0].g) * 3 + 9 * (src3[1].g + src3[2].g);
	g    += (src4[0].g)     + 3 * (src4[1].g + src4[2].g);
	dst->g = ((g+28)/56);
	int b = (src1[0].b)     + 3 * (src1[1].b + src1[2].b);
	b    += (src2[0].b) * 3 + 9 * (src2[1].b + src2[2].b);
	b    += (src3[0].b) * 3 + 9 * (src3[1].b + src3[2].b);
	b    += (src4[0].b)     + 3 * (src4[1].b + src4[2].b);
	dst->b = ((b+28)/56);
	int a = (src1[0].a)     + 3 * (src1[1].a + src1[2].a);
	a    += (src2[0].a) * 3 + 9 * (src2[1].a + src2[2].a);
	a    += (src3[0].a) * 3 + 9 * (src3[1].a + src3[2].a);
	a    += (src4[0].a)     + 3 * (src4[1].a + src4[2].a);
	dst->a = ((a+28)/56);
}

void DownfilterRight(color_t *src1, color_t *src2, color_t *src3, color_t *dst)
{
	// we mix 16 source pixels into one destination pixel
	int r = (src1[0].r)     + 3 * (src1[1].r + src1[2].r);
	r    += (src2[0].r) * 3 + 9 * (src2[1].r + src2[2].r);
	r    += (src3[0].r) * 3 + 9 * (src3[1].r + src3[2].r);
	dst->r = ((r+24)/49);
	int g = (src1[0].g)     + 3 * (src1[1].g + src1[2].g);
	g    += (src2[0].g) * 3 + 9 * (src2[1].g + src2[2].g);
	g    += (src3[0].g) * 3 + 9 * (src3[1].g + src3[2].g);
	dst->g = ((g+24)/49);
	int b = (src1[0].b)     + 3 * (src1[1].b + src1[2].b);
	b    += (src2[0].b) * 3 + 9 * (src2[1].b + src2[2].b);
	b    += (src3[0].b) * 3 + 9 * (src3[1].b + src3[2].b);
	dst->b = ((b+24)/49);
	int a = (src1[0].a)     + 3 * (src1[1].a + src1[2].a);
	a    += (src2[0].a) * 3 + 9 * (src2[1].a + src2[2].a);
	a    += (src3[0].a) * 3 + 9 * (src3[1].a + src3[2].a);
	dst->a = ((a+24)/49);
}

void UpfilterX(color_t *src, color_t *dst)
{
	// we mix three source pixels (A,B.C) into two destination pixels (1,2)
	// AB -> 1;  BC -> 2
	// All on same scanline.
	dst[0].r = ((src[0].r + 3 * src[1].r + 2) >> 2);
	dst[1].r = ((src[1].r * 3 + src[2].r + 2) >> 2);
	dst[0].g = ((src[0].g + 3 * src[1].g + 2) >> 2);
	dst[1].g = ((src[1].g * 3 + src[2].g + 2) >> 2);
	dst[0].b = ((src[0].b + 3 * src[1].b + 2) >> 2);
	dst[1].b = ((src[1].b * 3 + src[2].b + 2) >> 2);
	dst[0].a = ((src[0].a + 3 * src[1].a + 2) >> 2);
	dst[1].a = ((src[1].a * 3 + src[2].a + 2) >> 2);
}

void UpfilterXLeft(color_t *src, color_t *dst)
{
	dst[0].r = src[1].r;
	dst[1].r = ((src[1].r * 3 + src[2].r + 2) >> 2);
	dst[0].g = src[1].g;
	dst[1].g = ((src[1].g * 3 + src[2].g + 2) >> 2);
	dst[0].b = src[1].b;
	dst[1].b = ((src[1].b * 3 + src[2].b + 2) >> 2);
}

void UpfilterXRight(color_t *src, color_t *dst)
{
	dst[0].r = ((src[0].r + 3 * src[1].r + 2) >> 2);
	dst[1].r = src[1].r;
	dst[0].g = ((src[0].g + 3 * src[1].g + 2) >> 2);
	dst[1].g = src[1].g;
	dst[0].b = ((src[0].b + 3 * src[1].b + 2) >> 2);
	dst[1].b = src[1].b;
	dst[0].a = ((src[0].a + 3 * src[1].a + 2) >> 2);
	dst[1].a = src[1].a;
}

void UpfilterY(color_t *src1, color_t *src2, color_t *src3, color_t *dst1, color_t *dst2)
{
	dst1->r = ((src1->r + 3 * src2->r + 2) >> 2);
	dst2->r = ((src2->r * 3 + src3->r + 2) >> 2);
	dst1->g = ((src1->g + 3 * src2->g + 2) >> 2);
	dst2->g = ((src2->g * 3 + src3->g + 2) >> 2);
	dst1->b = ((src1->b + 3 * src2->b + 2) >> 2);
	dst2->b = ((src2->b * 3 + src3->b + 2) >> 2);
	dst1->a = ((src1->a + 3 * src2->a + 2) >> 2);
	dst2->a = ((src2->a * 3 + src3->a + 2) >> 2);
}

void Upfilter(color_t *src1, color_t *src2, color_t *src3, color_t *dst1, color_t *dst2)
{
	dst1[0].r = ((src1[0].r + 3 * (src1[1].r + src2[0].r) + src2[1].r * 9 + 8) >> 4);
	dst1[1].r = ((src1[2].r + 3 * (src1[1].r + src2[2].r) + src2[1].r * 9 + 8) >> 4);
	dst2[0].r = ((src3[0].r + 3 * (src3[1].r + src2[0].r) + src2[1].r * 9 + 8) >> 4);
	dst2[1].r = ((src3[2].r + 3 * (src3[1].r + src2[2].r) + src2[1].r * 9 + 8) >> 4);

	dst1[0].g = ((src1[0].g + 3 * (src1[1].g + src2[0].g) + src2[1].g * 9 + 8) >> 4);
	dst1[1].g = ((src1[2].g + 3 * (src1[1].g + src2[2].g) + src2[1].g * 9 + 8) >> 4);
	dst2[0].g = ((src3[0].g + 3 * (src3[1].g + src2[0].g) + src2[1].g * 9 + 8) >> 4);
	dst2[1].g = ((src3[2].g + 3 * (src3[1].g + src2[2].g) + src2[1].g * 9 + 8) >> 4);

	dst1[0].b = ((src1[0].b + 3 * (src1[1].b + src2[0].b) + src2[1].b * 9 + 8) >> 4);
	dst1[1].b = ((src1[2].b + 3 * (src1[1].b + src2[2].b) + src2[1].b * 9 + 8) >> 4);
	dst2[0].b = ((src3[0].b + 3 * (src3[1].b + src2[0].b) + src2[1].b * 9 + 8) >> 4);
	dst2[1].b = ((src3[2].b + 3 * (src3[1].b + src2[2].b) + src2[1].b * 9 + 8) >> 4);

	dst1[0].a = ((src1[0].a + 3 * (src1[1].a + src2[0].a) + src2[1].a * 9 + 8) >> 4);
	dst1[1].a = ((src1[2].a + 3 * (src1[1].a + src2[2].a) + src2[1].a * 9 + 8) >> 4);
	dst2[0].a = ((src3[0].a + 3 * (src3[1].a + src2[0].a) + src2[1].a * 9 + 8) >> 4);
	dst2[1].a = ((src3[2].a + 3 * (src3[1].a + src2[2].a) + src2[1].a * 9 + 8) >> 4);
}


void UpfilterLeft(color_t *src1, color_t *src2, color_t *src3, color_t *dst1, color_t *dst2)
{
	// we mix 9 source pixels to four destination pixels
	dst1[0].r = (3 * src1[1].r + src2[1].r * 9 + 6) / 12;
	dst1[1].r = ((src1[2].r + 3 * (src1[1].r + src2[2].r) + src2[1].r * 9 + 8) >> 4);
	dst2[0].r = (3 * src3[1].r + src2[1].r * 9 + 6) / 12;
	dst2[1].r = ((src3[2].r + 3 * (src3[1].r + src2[2].r) + src2[1].r * 9 + 8) >> 4);

	dst1[0].g = (3 * src1[1].g + src2[1].g * 9 + 6) / 12;
	dst1[1].g = ((src1[2].g + 3 * (src1[1].g + src2[2].g) + src2[1].g * 9 + 8) >> 4);
	dst2[0].g = (3 * src3[1].g + src2[1].g * 9 + 6) / 12;
	dst2[1].g = ((src3[2].g + 3 * (src3[1].g + src2[2].g) + src2[1].g * 9 + 8) >> 4);

	dst1[0].b = (3 * src1[1].b + src2[1].b * 9 + 6) / 12;
	dst1[1].b = ((src1[2].b + 3 * (src1[1].b + src2[2].b) + src2[1].b * 9 + 8) >> 4);
	dst2[0].b = (3 * src3[1].b + src2[1].b * 9 + 6) / 12;
	dst2[1].b = ((src3[2].b + 3 * (src3[1].b + src2[2].b) + src2[1].b * 9 + 8) >> 4);

	dst1[0].a = (3 * src1[1].a + src2[1].a * 9 + 6) / 12;
	dst1[1].a = ((src1[2].a + 3 * (src1[1].a + src2[2].a) + src2[1].a * 9 + 8) >> 4);
	dst2[0].a = (3 * src3[1].a + src2[1].a * 9 + 6) / 12;
	dst2[1].a = ((src3[2].a + 3 * (src3[1].a + src2[2].a) + src2[1].a * 9 + 8) >> 4);
}

void UpfilterRight(color_t *src1, color_t *src2, color_t *src3, color_t *dst1, color_t *dst2)
{
	dst1[0].r = ((src1[0].r + 3 * (src1[1].r + src2[0].r) + src2[1].r * 9 + 8) >> 4);
	dst1[1].r = (3 * src1[1].r + src2[1].r * 9 + 6) / 12;
	dst2[0].r = ((src3[0].r + 3 * (src3[1].r + src2[0].r) + src2[1].r * 9 + 8) >> 4);
	dst2[1].r = (3 * src3[1].r + src2[1].r * 9 + 6) / 12;

	dst1[0].g = ((src1[0].g + 3 * (src1[1].g + src2[0].g) + src2[1].g * 9 + 8) >> 4);
	dst1[1].g = (3 * src1[1].g + src2[1].g * 9 + 6) / 12;
	dst2[0].g = ((src3[0].g + 3 * (src3[1].g + src2[0].g) + src2[1].g * 9 + 8) >> 4);
	dst2[1].g = (3 * src3[1].g + src2[1].g * 9 + 6) / 12;

	dst1[0].b = ((src1[0].b + 3 * (src1[1].b + src2[0].b) + src2[1].b * 9 + 8) >> 4);
	dst1[1].b = (3 * src1[1].b + src2[1].b * 9 + 6) / 12;
	dst2[0].b = ((src3[0].b + 3 * (src3[1].b + src2[0].b) + src2[1].b * 9 + 8) >> 4);
	dst2[1].b = (3 * src3[1].b + src2[1].b * 9 + 6) / 12;

	dst1[0].a = ((src1[0].a + 3 * (src1[1].a + src2[0].a) + src2[1].a * 9 + 8) >> 4);
	dst1[1].a = (3 * src1[1].a + src2[1].a * 9 + 6) / 12;
	dst2[0].a = ((src3[0].a + 3 * (src3[1].a + src2[0].a) + src2[1].a * 9 + 8) >> 4);
	dst2[1].a = (3 * src3[1].a + src2[1].a * 9 + 6) / 12;
}

