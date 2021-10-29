# Csound Opcodes

A few opcodes for Csound

* Waveloss : based on waveloss ugen from SC

* Pan3 : 3 stereo panning algorithms (constant power sin, constant power sqrt, mid/side)

* PDOsc : Phase Distortion oscillator


To build and install (requires Csound and cmake)

```
git clone https://github.com/Leofltt/csound_opcodes.git
cd csound_opcodes
mkdir build && cd build
make
make install
```