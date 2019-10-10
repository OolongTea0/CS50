// Copies a BMP file

//Update for floats and shrinking later


#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // sets scale to first arg
    int scale = atoi(argv[1]);

    if (scale < 1 || scale > 100)
    {
        fprintf(stderr, "Scale is out of intended range\n");
        return 2;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // Remembers former width
    //long oWidth = bi.biWidth;
    long oHeight = bi.biHeight;

    // Old Padding
    int opad = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Change width by factor scale
    bi.biWidth *= scale;
    bi.biHeight *= scale;

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //Calculates image and file size
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding) * bi.biHeight;
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    //create array
    RGBTRIPLE *copy = malloc(sizeof(RGBTRIPLE) * bi.biWidth); //Maybe add padding

    // iterate over infile's scanlines
    for (int i = 0, biHeight = labs(oHeight); i < biHeight; i++)
    {

        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth/scale; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for (int k = 0; k < scale; k++)
            {
                copy[scale*j + k] = triple;
            }
        }

        // skip over padding, if any
        fseek(inptr, opad, SEEK_CUR);

        //Prints out the copied line according to height
        for (int j = 0; j < scale; j++)
        {
            for (int k = 0; k < bi.biWidth; k++)
            {
                fwrite(&copy[k], sizeof(RGBTRIPLE), 1, outptr);
            }

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
        }



    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
