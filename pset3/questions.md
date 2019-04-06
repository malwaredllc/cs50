# Solution to PSET3 Questions

## What's `stdint.h`?

`stdint.h` defines new integer types with specific width in bits.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

Using integer types with specific bit widths ensures portability of your program across different systems/environments with varying native integer sizes.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

`BYTE`  = 1 byte
`WORD`  = 2 bytes
`DWORD` = 4 bytes
`LONG`  = 8 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

`0x42`
`0x4D`

## What's the difference between `bfSize` and `biSize`?

`biSize` is the size of the BITMAPINFOHEADER, it is 40 bytes.
`bfSize` is the size of both headers and the bitmap itself (BITMAPFILEHEADER + BITMAPINFOHEADER + bitmap).

## What does it mean if `biHeight` is negative?

If `biHeight` is negative, the bitmap is top-down and the origin is the bottom-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

`biBitCount` field of `BITMAPINFOHEADER` specifies the BMP's color depth (bits per pixel).

## Why might `fopen` return `NULL` in `copy.c`?

`fopen` will return `NULL` in read-mode if the target file does not exist, and it will return `NULL` in write-mode if it cannot create the output file (for example if the user does not have write-permission).

## Why is the third argument to `fread` always `1` in our code?

The third argument to `fread` specifies how many elements to read at a time, and we specify 1 because we always want to read 1 RGB struct at a time.

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

The forumula for padding is `int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4`, because we want to pad scanlines to a multiple of 4 (because each RGBTRIPLE struct is 3 pixels * 3 bytes per pixel = 12 bytes) so if `bi.biWidth` is equal to 3, then:
`int padding = (4 - (3 * 3) % 4) % 4`
`int padding = (4 - 9 % 4) % 4`
`int padding = (4 - 1) % 4`
`int padding = 3`

Therfore `padding` would be assigned a value of 3.

## What does `fseek` do?

`fseek` is used to move the file position to a specific location within the file.

## What is `SEEK_CUR`?

`SEEK_CUR` is the current file position.


