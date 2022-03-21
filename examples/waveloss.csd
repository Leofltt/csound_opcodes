<CsoundSynthesizer>
<CsOptions>
-odac ;realtime audio out
--opcode-lib=~/Users/$USER/Library/csound/6.0/plugins64 ;update this path with your opcode folder
</CsOptions>
<CsInstruments>

sr = 44100
ksmps = 128
nchnls = 2
0dbfs = 1

instr 1 

aL,aR diskin2 "./dperc.wav",1, 0, 1 

imode = p4

imax = p5

kdrop = linseg(0, p3/2, imax, p3/2, 0)


al waveloss aL, kdrop, imax, imode
ar waveloss aR, kdrop, imax, imode

outs	al, ar

endin

</CsInstruments>
<CsScore>

;inst start dur mode maxdrops
i 1    0    10  0    50
i .    +    .   1    50

</CsScore>
</CsoundSynthesizer>

