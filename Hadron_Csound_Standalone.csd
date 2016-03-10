<CsoundSynthesizer>
<CsOptions>
-odac -Ma -+rtmidi=alsa -b2048 -B4096 -f
</CsOptions>
<CsInstruments>

#include "inc/hadron_FLTK.inc"
#include "Hadron.orc"	

instr 3

kCtrl1Changed	changed	gkCTRf1
if kCtrl1Changed == 0 goto skipCtrl1Write	; write to variable only if gui controller value has changed
		chnset	gkCTRf1, "ctrl1"	; overwrite value in chn channel on gui widget change
skipCtrl1Write:

kCtrl2Changed	changed	gkCTRf2
if kCtrl2Changed == 0 goto skipCtrl2Write	; write to variable only if gui controller value has changed
		chnset	gkCTRf2, "ctrl2"	; overwrite value in chn channel on gui widget change
skipCtrl2Write:

kCtrl3Changed	changed	gkCTRf3
if kCtrl3Changed == 0 goto skipCtrl3Write	; write to variable only if gui controller value has changed
		chnset	gkCTRf3, "ctrl3"	; overwrite value in chn channel on gui widget change
skipCtrl3Write:

kCtrl4Changed	changed	gkCTRf4
if kCtrl4Changed == 0 goto skipCtrl4Write	; write to variable only if gui controller value has changed
		chnset	gkCTRf4, "ctrl4"	; overwrite value in chn channel on gui widget change
skipCtrl4Write:

kCtrlXChanged	changed	gkJoyX
if kCtrlXChanged == 0 goto skipCtrlXWrite	; write to variable only if gui controller value has changed
		chnset	gkJoyX, "presetX"	; overwrite value in chn channel on gui widget change
skipCtrlXWrite:

kCtrlYChanged	changed	gkJoyY
if kCtrlYChanged == 0 goto skipCtrlYWrite	; write to variable only if gui controller value has changed
		chnset	gkJoyY, "presetY"	; overwrite value in chn channel on gui widget change
skipCtrlYWrite:

endin

</CsInstruments>

<CsScore>

#include "Hadron.sco"

i3	3	86400		; enable FLTK control

#include "hadron_cs_standalone_sco.inc"

e
</CsScore>
</CsoundSynthesizer>
