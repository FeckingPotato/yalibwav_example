# Simple wav CLI editor
An example (not really well written) program which uses [this](https://github.com/FeckingPotato/yalibwav) library
## Usage
`./libwav_example <command> <input file> <output file> <command argument 1> <command argument 2> <command argument 3>`
## Commands and arguments
- `compress <threshold (0-32767)> <ratio (х:1)>` - dynamic range compression
- `amplify <threshold (0-32767)> <ratio (х:1)>` - amplification
- `echo <delay (ms)> <decay (<1) >` - echo effect
- `echo <delay (ms)> <decay (<1) >` - reverb effect

There is no overflow check, so use last three effects carefully