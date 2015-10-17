# ImageScaling
This code included a C++ port of John Costella's 'Magic Kernel', which he wrote in C#.  It is a 1:2:2:1 convolution filter in one dimension.

This is implemented as part of a simple bitmap class and simple file format.  The bitmap class handles 16-bit linear data primarily, in 4 channels.  I am using this for stereoscopic computer graphics for digital cinema.

The file format is defined in simple.h.

The bitmap in linear16.h.  

Power-of-two upsampling and downscaling is straight forward through the respective methods declared in linear16.h (Downscale/Upscale).  Although these are 2D scalers, it is possible to scale in only one dimension: e.g., UpscaleX() and UpscaleY().There are also some other image processing goodies there, which can safely be ignored.  The main scaling work in done in C functions in filter16.cpp

I am sure there are several optimizations that could be done to the core filter code.  But it works.

Lastly, the linear16 bitmap class has can read and write 24-bit BMP files, converting back and forth between 8- and 16-bit primaries, but ignoring sRGB-to-lin conversion, and vice versa (I'm lazy).


