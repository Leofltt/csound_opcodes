<CsoundSynthesizer>
<CsOptions>
-odac0 ;realtime audio out
--opcode-lib=~/Users/$USER/Library/csound/6.0/plugins64 ;update this path with your opcode folder
</CsOptions>
<CsInstruments>

sr = 44100
ksmps = 128
nchnls = 2
0dbfs = 1

instr 1 

aL,aR diskin2 "./dperc.wav",1, 0, 1 

kcontrol = linseg(0, p3, 1)

imode = p4

al, ar pan3 aL, aR, kcontrol, imode

outs	al, ar

endin

</CsInstruments>
<CsScore>

;inst start dur mode
i 1    0     8     0
i .    +     .     1
i .    +     .     2

</CsScore>
</CsoundSynthesizer>