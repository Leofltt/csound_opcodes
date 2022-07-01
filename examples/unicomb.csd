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

kblend = 0.4
kfb = linseg(0.71, p3/2, 0.9, p3/2, 0.71)
kff = linseg(0.8, p3/2, 0.2, p3/2, 0.8)
kdelfb = linseg(11,p3,23)
kdelff = linseg(22,p3,10)

al unicomb aL,kblend, kfb, kff, kdelfb, kdelff
ar unicomb aR,kblend, kfb, kff, kdelfb, kdelff


outs	al, ar

endin

</CsInstruments>
<CsScore>

;inst start dur
i 1    0    10
i .    +    .

</CsScore>
</CsoundSynthesizer>



<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>100</x>
 <y>100</y>
 <width>320</width>
 <height>240</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="background">
  <r>240</r>
  <g>240</g>
  <b>240</b>
 </bgcolor>
</bsbPanel>
<bsbPresets>
</bsbPresets>
