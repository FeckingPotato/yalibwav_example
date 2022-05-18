#ifndef KURS_WAV_WAVUTILS_H
#define KURS_WAV_WAVUTILS_H

void checkStatus(unsigned short statusCode);
int compression(WAV *input, unsigned short threshold, double ratio);
int amplification(WAV *input, unsigned short threshold, double ratio);
int echo(WAV *input, double delayms, double decay);
int reverb(WAV *input, double delayms, double dry_gain, double wet_gain);

#endif
