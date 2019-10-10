# Questions

## What's `stdint.h`?

Library that let's us control the size of our own defined integers.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

These let us control how much bits are allocated to the data types that we are defining.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

In order -> 1, 4, 4, 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

Hexidecimal: 424d -> Decimal: 16973

## What's the difference between `bfSize` and `biSize`?

bfSize refers to the size in bytes of the BM file. biSize refers to the size of the structure.

## What does it mean if `biHeight` is negative?

If negative, the pixels are drawn starting from the top-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

If the file doesn't exist, fopen will return NULL.  An application could be using
the file as well which would prevent the file from being modified.

## Why is the third argument to `fread` always `1` in our code?

Only 1 element of each data structure is read. ie: BITMAPFILEHEADER, BITMAPINFOHEADER

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

It moves the file cursor to a different location. First input is the pointer file, second input is the offset and the last
input is the location from where the offset takes place.

## What is `SEEK_CUR`?

SEEK_CUR is the current file cursor position. It's used as a reference point for the offset in fseek

## Whodunit?

It was Professor Plum with the candlestick in the library
