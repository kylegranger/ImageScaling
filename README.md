# ImageScaling
This is a C++ port of John Costella's 'Magic Kernel', which he wrote in C#.  It is a 1:2:2:1 kernel (in one dimension).

This is implemented as part of a simple bitmaps class and simple file format.  The bitmaps class handled 16-bit linear data primarily, in 4 channels.  I am using this for stereoscopic computer graphics for digital cinema.

The file format is defined in simple.h.

The bitmap in linear16.h.  

Power-of-two upsampling and downscaling is straight forward through the respective methods declared in liner16.h.  There are also some other image processing goodies there, which can safely be ignored.  The main scaling work in done in C functions in filter16.cpp


