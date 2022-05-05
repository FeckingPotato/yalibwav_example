#include <stdlib.h>
#include <string.h>
#include <yalibwav.h>

void checkStatus(unsigned short statusCode) {
    switch(statusCode) {
        default:
            return;
        case 1:
            fprintf(stderr, "Input file is not a RIFF file\n");
            break;
        case 2:
            fprintf(stderr, "Input file size mismatch\n");
            break;
        case 3:
            fprintf(stderr, "Input file is not a WAVE file\n");
            break;
        case 4:
            fprintf(stderr, "Input file has no format chunk\n");
            break;
        case 5:
            fprintf(stderr, "Input file has no data chunk\n");
            break;
    }
    exit(statusCode);
};

WAV compression(WAV input, unsigned short threshold, double ratio) {
    for (unsigned int i = 0; i < input.audioSize/2; i++) {
        if (input.audio[i] > threshold) {
            input.audio[i] -= (input.audio[i] - threshold) / ratio;
        }
        else if (input.audio[i] < -threshold) {
            input.audio[i] -= (input.audio[i] + threshold) / ratio;
        }
    }
    return input;
}

WAV amplification(WAV input, unsigned short threshold, double ratio) {
    for (unsigned int i = 0; i < input.audioSize/2; i++) {
        if (abs(input.audio[i]) < threshold) {
            input.audio[i] *= ratio;
        }
    }
    return input;
}

WAV echo(WAV input, double delayms, double decay) {
    unsigned int delaySamples = (unsigned int) ((double) input.fmt.sampleRate/1000 * delayms);
    short *resultAudio = (short *) malloc(input.audioSize);
    unsigned int i,j,k;
    for (i = 0; i < input.fmt.channels; i++) {
        for (j = i; j < delaySamples; j += input.fmt.channels) {
            resultAudio[j] = input.audio[j];
        }
        for (k = i; j < input.audioSize; j += input.fmt.channels, k += input.fmt.channels) {
            resultAudio[j] = input.audio[j]*(1-decay/2) + input.audio[k] * decay; //idk how to prevent overflow, so here's a not so great solution
        }
        for (; k < input.audioSize; j += input.fmt.channels, k += input.fmt.channels) {
            resultAudio[k] = input.audio[k];
        }
    }
    memcpy(input.audio, resultAudio, input.audioSize/2);
    free(resultAudio);
    return input;
}

WAV reverb(WAV input, double delayms, double decay) {
    unsigned int delaySamples = (unsigned int)(((double)input.fmt.sampleRate)/1000 * delayms);
    unsigned int i,j;
    for (i = 0; i < input.fmt.channels; i++) {
        for (j = i; j < input.audioSize - delaySamples; j += input.fmt.channels) {
            input.audio[j + delaySamples] = input.audio[j + delaySamples]*(1-decay/2) + input.audio[j]*decay; //idk how to prevent overflow, so here's a not so great solution again
        }
    }
    return input;
}
