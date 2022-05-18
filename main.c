#include <stdio.h>
#include <yalibwav.h>
#include <stdlib.h>
#include <string.h>
#include "wavUtils.h"

char help[] = "Commands: \n"
              "compress - dynamic range compression\n"
              "amplify - amplification\n"
              "echo - echo effect\n"
              "reverb - reverb effect\n"
              "For more detailed description use a command without arguments\n";

int main(int argc, char **argv) {
    if (argc < 2 || argc > 7) {
        printf("%s", help);
        return 0;
    }
    WAV wav;
    FILE *file;
    if (!strcmp(argv[1], "compress")) {
        if (argc != 6) {
            printf("compress <input file> <output file> <threshold (0-32767)> <ratio (х:1)>\n");
            return 0;
        }
        file = fopen(argv[2], "r");
        if (file == NULL) {
            fprintf(stderr, "Unable to open the input file\n");
            return -1;
        }
        checkStatus(wavFileRead(file, &wav));
        fclose(file);
        unsigned short threshold = strtol(argv[4], NULL, 10);
        double ratio = strtod(argv[5], NULL);
        if(compression(&wav, threshold, ratio)) {
            printf("WARNING: Current parameters caused an integer overflow, the sound may be distorted\n");
        }
        file = fopen(argv[3], "w");
        if (file == NULL) {
            fprintf(stderr, "Unable to open the output file\n");
            return -2;
        }
        wavFileWrite(file, wav);
        return 0;
    }
    if (!strcmp(argv[1], "amplify")) {
        if (argc != 6) {
            printf("amplify <input file> <output file> <threshold (0-32767)> <ratio (х:1)>\n");
            return 0;
        }
        file = fopen(argv[2], "r");
        if (file == NULL) {
            fprintf(stderr, "Unable to open the input file\n");
            return -1;
        }
        checkStatus(wavFileRead(file, &wav));
        fclose(file);
        unsigned short threshold = strtol(argv[4], NULL, 10);
        double ratio = strtod(argv[5], NULL);
        if(amplification(&wav, threshold, ratio)) {
            printf("WARNING: Current parameters caused an integer overflow, the sound may be distorted\n");
        }
        file = fopen(argv[3], "w");
        if (file == NULL) {
            fprintf(stderr, "Unable to open the output file\n");
            return -2;
        }
        wavFileWrite(file, wav);
        return 0;
    }
    if (!strcmp(argv[1], "echo")) {
        if (argc != 6) {
            printf("echo <input file> <output file> <delay (ms)> <input gain> <decay>\n");
            return 0;
        }
        file = fopen(argv[2], "r");
        if (file == NULL) {
            fprintf(stderr, "Unable to open the input file\n");
            return -1;
        }
        checkStatus(wavFileRead(file, &wav));
        fclose(file);
        double delay = strtod(argv[4], NULL);
        double decay = strtod(argv[5], NULL);
        if(echo(&wav, delay, decay)) {
            printf("WARNING: Current parameters caused an integer overflow, the sound may be distorted\n");
        }
        file = fopen(argv[3], "w");
        if (file == NULL) {
            fprintf(stderr, "Unable to open the output file\n");
            return -2;
        }
        wavFileWrite(file, wav);
        return 0;
    }
    if (!strcmp(argv[1], "reverb")) {
        if (argc != 7) {
            printf("reverb <input file> <output file> <delay (ms)> <dry gain> <wet gain>\n");
            return 0;
        }
        file = fopen(argv[2], "r");
        if (file == NULL) {
            fprintf(stderr, "Unable to open the input file\n");
            return -1;
        }
        checkStatus(wavFileRead(file, &wav));
        fclose(file);
        double delay = strtod(argv[4], NULL);
        double dry_gain = strtod(argv[5], NULL);
        double wet_gain = strtod(argv[6], NULL);
        if(reverb(&wav, delay, dry_gain, wet_gain)) {
            printf("WARNING: Current parameters caused an integer overflow, the sound may be distorted\n");
        }
        file = fopen(argv[3], "w");
        if (file == NULL) {
            fprintf(stderr, "Unable to open the output file\n");
            return -2;
        }
        wavFileWrite(file, wav);
        return 0;
    }
    printf("%s", help);
    return 0;
}
