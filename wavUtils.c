#include <stdlib.h>
#include <string.h>
#include <limits.h>
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
}

int compression(WAV *input, unsigned short threshold, double ratio) {
    int overflow = 0;
    for (unsigned int i = 0; i < input->audioSize/2; i++) {
        int result;
        if (input->audio[i] > threshold) {
            result = input->audio[i] - (input->audio[i] - threshold) / ratio;
            input->audio[i] = (short)result;
            if (result > SHRT_MAX || result < SHRT_MIN) {
                overflow = 1;
            }
        }
        else if (input->audio[i] < -threshold) {
            result = input->audio[i] - (input->audio[i] + threshold) / ratio;
            input->audio[i] = (short)result;
            if (result > SHRT_MAX || result < SHRT_MIN) {
                overflow = 1;
            }
        }
    }
    return overflow;
}

int amplification(WAV *input, unsigned short threshold, double ratio) {
    int overflow = 0;
    for (unsigned int i = 0; i < input->audioSize/2; i++) {
        if (abs(input->audio[i]) < threshold) {
            int result = input->audio[i] * ratio;
            input->audio[i] = (short)result;
            if (result > SHRT_MAX || result < SHRT_MIN) {
                overflow = 1;
            }
        }
    }
    return overflow;
}

int echo(WAV *input, double delayms, double input_gain, double decay) {
    int overflow = 0;
    unsigned int delaySamples = (unsigned int) ((double) input->fmt.sampleRate/1000 * delayms);
    short *resultAudio = (short *) malloc(input->audioSize);
    unsigned int i,j,k;
    for (i = 0; i < input->fmt.channels; i++) {
        for (j = i; j < delaySamples; j += input->fmt.channels) {
            resultAudio[j] = input->audio[j];
        }
        for (k = i; j < input->audioSize; j += input->fmt.channels, k += input->fmt.channels) {
            int result = input->audio[j]*input_gain + input->audio[k] * decay;
            resultAudio[j] = (short)result;
            if (result > SHRT_MAX || result < SHRT_MIN) {
                overflow = 1;
            }
        }
        for (; k < input->audioSize; j += input->fmt.channels, k += input->fmt.channels) {
            resultAudio[k] = input->audio[k];
        }
    }
    memcpy(input->audio, resultAudio, input->audioSize/2);
    free(resultAudio);
    return overflow;
}

int reverb(WAV *input, double delayms, double dry_gain, double wet_gain) {
    int overflow = 0;
    unsigned int delaySamples = (unsigned int)(((double)input->fmt.sampleRate)/1000 * delayms);
    unsigned int i,j;
    for (i = 0; i < input->fmt.channels; i++) {
        for (j = i; j < input->audioSize - delaySamples; j += input->fmt.channels) {
            int result = input->audio[j + delaySamples]*dry_gain + ((input->audio[j]))*wet_gain;
            input->audio[j + delaySamples] = (short)result;
            if (result > SHRT_MAX || result < SHRT_MIN) {
                overflow = 1;
            }
        }
    }
    return overflow;
}
