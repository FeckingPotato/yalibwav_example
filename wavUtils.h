#ifndef KURS_WAV_WAVUTILS_H
#define KURS_WAV_WAVUTILS_H
void checkStatus(unsigned short statusCode);
WAV compression(WAV input, unsigned short threshold, double ratio);
WAV amplification(WAV input, unsigned short threshold, double ratio);
WAV echo(WAV input, double delayms, double decay);
WAV reverb(WAV input, double delayms, double decay);

#endif
