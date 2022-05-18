#ifndef LIBWAV_EXAMPLE_OUTPUTSTRINGS_H
#define LIBWAV_EXAMPLE_OUTPUTSTRINGS_H

#define HELP "Commands: \ncompress - dynamic range compression\namplify - amplification\necho - echo effect\nreverb - reverb effect\nFor more detailed description use a command without arguments\n"
#define HELP_COMPRESS "compress <input file> <output file> <threshold (0-32767)> <ratio (х:1)>\n"
#define HELP_AMPLIFY "amplify <input file> <output file> <threshold (0-32767)> <ratio (х:1)>\n"
#define HELP_ECHO "echo <input file> <output file> <delay (ms)> <input gain> <decay>\n"
#define HELP_REVERB "reverb <input file> <output file> <delay (ms)> <dry gain> <wet gain>\n"
#define ERR_INPUT "Unable to open the input file\n"
#define ERR_OUTPUT "Unable to open the output file\n"
#define WARN_OVERFLOW "WARNING: Current parameters caused an integer overflow, the sound may be distorted\n"

#endif
