// Created by: Kyle Granger
// License: MIT


#include "linear16.h"
#include <stdio.h>
#include <string>


void doDownsample() {
    std::string filename = "images/large.bmp";
    auto image = new CLinear16();
    if (!image->ReadBmp(filename)) {
        printf("could not read downsample image\n");
        return;
    }
    printf("loaded image, width %d height %d\n", image->mWidth, image->mHeight);

    auto x2 = image->Downsample();
    x2->WriteBmp("images/large_down_x2.bmp");
    delete image;

    auto x4 = x2->Downsample();
    x4->WriteBmp("images/large_down_x4.bmp");
    delete x2;

    auto x8 = x4->Downsample();
    x8->WriteBmp("images/large_down_x8.bmp");
    delete x4;

    auto x16 = x8->Downsample();
    x16->WriteBmp("images/large_down_x16.bmp");
    delete x8;

    auto x32 = x16->Downsample();
    x32->WriteBmp("images/large_down_32.bmp");
    delete x16;
    delete x32;

}

void doUpsample() {
    std::string filename = "images/small.bmp";
    auto image = new CLinear16();
    if (!image->ReadBmp(filename)) {
        printf("could not read upsample image\n");
        return;
    }
    printf("loaded image, width %d height %d\n", image->mWidth, image->mHeight);

    auto x2 = image->Upsample();
    x2->WriteBmp("images/small_up_x2.bmp");
    delete image;

    auto x4 = x2->Upsample();
    x4->WriteBmp("images/small_up_x4.bmp");
    delete x2;

    auto x8 = x4->Upsample();
    x8->WriteBmp("images/small_up_x8.bmp");
    delete x4;

    auto x16 = x8->Upsample();
    x16->WriteBmp("images/small_up_x16.bmp");
    delete x8;

    auto x32 = x16->Upsample();
    x32->WriteBmp("images/small_up_32.bmp");
    delete x16;
    delete x32;
}


int main(int /*argc*/, char * /*argv*/ []) {
    doDownsample();
    doUpsample();
    return 0;
}