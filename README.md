# Csound Opcodes

A few opcodes for Csound

* Waveloss : based on waveloss ugen from SC

* Pan3 : stereo panning algorithms (constant power sin, constant power sqrt, mid/side)

* PDOsc : Phase Distortion oscillator

* Wavefolder : wavefolder based on https://ccrma.stanford.edu/~jatin/ComplexNonlinearities/Wavefolder.html by Jatin Chowdhury


To build and install (requires Csound and cmake)

```
git clone https://github.com/Leofltt/csound_opcodes.git
cd csound_opcodes
mkdir build && cd build
make
make install
```