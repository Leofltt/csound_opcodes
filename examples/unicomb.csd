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

kblend = 0.8
kfb = 0.8
kff = -0.7
idelfb = 10
idelff = 12

al unicomb aL,kblend, kfb, kff, idelfb, idelff
ar unicomb aR,kblend, kfb, kff, idelfb, idelff


outs	al, ar

endin

</CsInstruments>
<CsScore>

;inst start dur
i 1    0    10

</CsScore>
</CsoundSynthesizer>

