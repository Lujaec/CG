AUX_RGBImageRec* LoadBMPFile(char* filename)
{
    FILE* hFile = NULL;
    if (!filename) return NULL;

    hFile = fopen(filename, "r");
    if (hFile) {
        fclose(hFile);
        return auxDIBImageLoad(filename);
    }

    return NULL;
}