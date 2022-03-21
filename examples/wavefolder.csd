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

instr 1 

kenv = linseg(0, p3/2, 0.8, p3/2, 0)

ifreq = 100

igain = p4
ifb = p5
iff = p6 
imode = p7

aSig poscil kenv, ifreq, 1

aOut wavefolder aSig, igain, ifb, iff, 0.5, imode

outs	aOut, aOut

endin

</CsInstruments>
<CsScore>

;inst start dur gain fb    ff    mode
i 1    0    10  1    0.5   0.5   0
i .    +    .   2    0.6   0.25  .    
i .    +    .   4    0.3   0.8   .
i .    +    .   2    0.8   0.4   1
i .    +    .   1    0.3   0.7   .    
i .    +    .   4    0.7   0.5   .

</CsScore>

</CsoundSynthesizer>
