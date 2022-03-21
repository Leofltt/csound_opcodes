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

gisine ftgen 1,  0, 4096, 11, 1 ; cosine table
giphsine ftgen 2,  0, 4096, 7, 0, 4096, 1 ; generate a sinewave
giphsaw ftgen 3,  0, 4096, 7, 0, 10, 0.5, 4086, 1 ; generate a sawwave
giphsqr ftgen 4,  0, 4096, 7, 0, 2038, 0, 10, 0.5, 2038, 0.5, 10, 1 ; generate a squarewave

instr 1 

kenv = linseg(0, p3/2, 0.8, p3/2, 0)

ifreq = p4

iphase = p5

al pdosc kenv, ifreq, gisine, iphase
ar pdosc kenv, ifreq, gisine, iphase  

outs	al, ar

endin

</CsInstruments>
<CsScore>

;inst start dur freq phasetable
i 1    0     5   220  2
i .    +     .   .    3
i .    +     .   .    4

</CsScore>
</CsoundSynthesizer>