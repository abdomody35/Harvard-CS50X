#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover file.raw\n");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Failed to open file\n");
        return 2;
    }
    int name = 0;
    uint8_t buffer[512];
    char file_name[8];
    FILE *image = NULL;

    while (fread(buffer, sizeof(buffer), 1, f) != 0)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {
            snprintf(file_name, sizeof(file_name), "%03d.jpg", name++);
            if (image)
            {
                fclose(image);
            }
            image = fopen(file_name, "w");
            if (!image)
            {
                printf("Failed to create a new file\n");
                fclose(f);
                return 3;
            }
        }
        if (image && fwrite(buffer, sizeof(buffer), 1, image) == 0)
        {
            printf("Failed to write to new file\n");
            fclose(f);
            fclose(image);
            return 4;
        }
    }
    fclose(image);
    fclose(f);
}
