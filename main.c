#include <stdio.h>
#include <yalibwav.h>
#include <stdlib.h>
#include <string.h>
#include "wavUtils.h"
#include "outputStrings.h"

int main(int argc, char **argv) {
    if (argc < 2 || argc > 7) {
        printf("%s", HELP);
        return 0;
    }
    WAV wav;
    FILE *file;
    if (!strcmp(argv[1], "compress")) {
        if (argc != 6) {
            printf("%s", HELP_COMPRESS);
            return 0;
        }
        file = fopen(argv[2], "r");
        if (file == NULL) {
            fprintf(stderr, ERR_INPUT);
            return -1;
        }
        checkStatus(wavFileRead(file, &wav));
        fclose(file);
        unsigned short threshold = strtol(argv[4], NULL, 10);
        double ratio = strtod(argv[5], NULL);
        if(compression(&wav, threshold, ratio)) {
            printf("%s", WARN_OVERFLOW);
        }
        file = fopen(argv[3], "w");
        if (file == NULL) {
            fprintf(stderr, ERR_OUTPUT);
            return -2;
        }
        wavFileWrite(file, wav);
        return 0;
    }
    if (!strcmp(argv[1], "amplify")) {
        if (argc != 6) {
            printf("%s", HELP_AMPLIFY);
            return 0;
        }
        file = fopen(argv[2], "r");
        if (file == NULL) {
            fprintf(stderr, ERR_INPUT);
            return -1;
        }
        checkStatus(wavFileRead(file, &wav));
        fclose(file);
        unsigned short threshold = strtol(argv[4], NULL, 10);
        double ratio = strtod(argv[5], NULL);
        if(amplification(&wav, threshold, ratio)) {
            printf(WARN_OVERFLOW);
        }
        file = fopen(argv[3], "w");
        if (file == NULL) {
            fprintf(stderr, ERR_INPUT);
            return -2;
        }
        wavFileWrite(file, wav);
        return 0;
    }
    if (!strcmp(argv[1], "echo")) {
        if (argc != 7) {
            printf("%s", HELP_ECHO);
            return 0;
        }
        file = fopen(argv[2], "r");
        if (file == NULL) {
            fprintf(stderr, ERR_INPUT);
            return -1;
        }
        checkStatus(wavFileRead(file, &wav));
        fclose(file);
        double delay = strtod(argv[4], NULL);
        double decay = strtod(argv[5], NULL);
        if(echo(&wav, delay, decay)) {
            printf(WARN_OVERFLOW);
        }
        file = fopen(argv[3], "w");
        if (file == NULL) {
            fprintf(stderr, ERR_OUTPUT);
            return -2;
        }
        wavFileWrite(file, wav);
        return 0;
    }
    if (!strcmp(argv[1], "reverb")) {
        if (argc != 7) {
            printf("%s", HELP_REVERB);
            return 0;
        }
        file = fopen(argv[2], "r");
        if (file == NULL) {
            fprintf(stderr, ERR_INPUT);
            return -1;
        }
        checkStatus(wavFileRead(file, &wav));
        fclose(file);
        double delay = strtod(argv[4], NULL);
        double dry_gain = strtod(argv[5], NULL);
        double wet_gain = strtod(argv[6], NULL);
        if(reverb(&wav, delay, dry_gain, wet_gain)) {
            printf(WARN_OVERFLOW);
        }
        file = fopen(argv[3], "w");
        if (file == NULL) {
            fprintf(stderr, ERR_OUTPUT);
            return -2;
        }
        wavFileWrite(file, wav);
        return 0;
    }
    printf("%s", HELP);
    return 0;
}
