/*

    Copyright (C) 2010 Oeyvind Brandtsegg and Partikkelaudio.com

    This file is part of the Hadron Particle Synthesizer.

    The Hadron Particle Synthesizer is free software; you can redistribute it
    and/or modify it under the terms of the GNU Lesser General Public
    License, version 3.0, as published by the Free Software Foundation.

    Hadron Particle Synthesizer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with Hadron Particle Synthesizer; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA
*/

;******************************************************
; parameter automation, morph from one ftable to another
; (from excisting table to new one specified by p-fields)
;******************************************************
	instr 10
	; (p6 to p70 sets new table values)
	StableName	strget p4		; ftable name to write to
	;puts StableName, 1
	iOriginal	chnget StableName	; find table number
	iCurve		= p5			; transeg curve for morphing transition
	;print p1, p2, p3

;generate morph control signal
	kMorph		transeg 	0, p3-(2/kr), iCurve, 1
	p3 		= p3 + 2/kr				; modify p3 so the ending value can be reached fully

; generate new ftable, and a copy of the original
	iTempNew	ftgentmp	0, 0, giMaskSize, -2, p6,p7,p8,p9,\
					p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,\
					p20,p21,p22,p23,p24,p25,p26,p27,p28,p29,\
					p30,p31,p32,p33,p34,p35,p36,p37,p38,p39,\
					p40,p41,p42,p43,p44,p45,p46,p47,p48,p49,\
					p50,p51,p52,p53,p54,p55,p56,p57,p58,p59,\
					p60,p61,p62,p63,p64,p65,p66,p67,p68,p69,p70

	iTempOld	ftgentmp	0, 0, giMaskSize, -2, 0
			tableicopy	iTempOld, iOriginal
; morph indexing
	iMorphTab	ftgentmp	0, 0, 2, -2, iTempOld, iTempNew

; execute morphing (write new values to original table)
			ftmorf		kMorph, iMorphTab, iOriginal
	endin

;******************************************************
; parameter automation, LFO controls morphing between two ftables 
; (one is the current table, the other one specified by p-fields)
;******************************************************
	instr 11

	; (p9 to p73 sets new table values)
	StableName	strget p4		; ftable name to write to
	;puts StableName, 1
	iOriginal	chnget StableName	; find table number
	iLfoAmount	= p5			; LFO amount (amp)
	iLfoFreq	= p6                    ; LFO frequency   
	iFadeIn		= (p7 <= 0 ? 2/kr : p7)	; fade must not be zero, or linseg will not work correctly
	iFadeOut	= (p8 <= 0 ? 2/kr : p8)	; fade must not be zero, or linseg will not work correctly
	;print p1, p2, iLfoAmount

	kEnvelope	linseg	0, iFadeIn, 1, p3-(2/kr)-iFadeIn-iFadeOut, 1, iFadeOut, 0, 1, 0	; optional fade in and out of modulator signal
	kMorph		oscil	iLfoAmount*0.5, iLfoFreq, giTri	; LFO
	kMorph		= (kMorph+0.5) * kEnvelope

; generate new ftable, and a copy of the original
	iTempNew	ftgentmp	0, 0, giMaskSize, -2, p9,\
					p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,\
					p20,p21,p22,p23,p24,p25,p26,p27,p28,p29,\
					p30,p31,p32,p33,p34,p35,p36,p37,p38,p39,\
					p40,p41,p42,p43,p44,p45,p46,p47,p48,p49,\
					p50,p51,p52,p53,p54,p55,p56,p57,p58,p59,\
					p60,p61,p62,p63,p64,p65,p66,p67,p68,p69,\
					p70,p71,p72,p73

	iTempOld	ftgentmp	0, 0, giMaskSize, -2, 0
			tableicopy	iTempOld, iOriginal
; morph indexing
	iMorphTab	ftgentmp	0, 0, 2, -2, iTempOld, iTempNew

; execute morphing (write new values to original table)
			ftmorf		kMorph, iMorphTab, iOriginal
	endin

;******************************************************
; parameter automation, random morphing between two ftables 
; (one is the current table, the other one specified by p-fields)
;******************************************************
	instr 12
	; (p11 to p75 sets new table values)
	StableName	strget p4			; ftable name to write to
	;puts StableName, 1
	iOriginal	chnget StableName		; find table number
	irangeMin	= p5				; noise minimum value                         
	irangeMax	= p6                            ; noise maximum value                         
	icpsMin		= p7                            ; minimum frequency for noise (rate of change)
	icpsMax		= p8                            ; maximum frequency for noise (rate of change)
	iFadeIn		= (p9 <= 0 ? 2/kr : p9)		; fade must not be zero, or linseg will not work correctly
	iFadeOut	= (p10 <= 0 ? 2/kr : p10)	; fade must not be zero, or linseg will not work correctly	
	;print p1, p2, irangeMax

	kEnvelope	linseg	0, iFadeIn, 1, p3-(2/kr)-iFadeIn-iFadeOut, 1, iFadeOut, 0, 1, 0	; optional fade in and out of modulator signal

	kMorph 		rspline irangeMin, irangeMax, icpsMin, icpsMax	; generate noise
	kMorph		= kMorph * kEnvelope

; generate new ftable, and a copy of the original
	iTempNew	ftgentmp	0, 0, giMaskSize, -2, \
					p11,p12,p13,p14,p15,p16,p17,p18,p19,\
					p20,p21,p22,p23,p24,p25,p26,p27,p28,p29,\
					p30,p31,p32,p33,p34,p35,p36,p37,p38,p39,\
					p40,p41,p42,p43,p44,p45,p46,p47,p48,p49,\
					p50,p51,p52,p53,p54,p55,p56,p57,p58,p59,\
					p60,p61,p62,p63,p64,p65,p66,p67,p68,p69,\
					p70,p71,p72,p73,p74,p75

	iTempOld	ftgentmp	0, 0, giMaskSize, -2, 0
			tableicopy	iTempOld, iOriginal
; morph indexing
	iMorphTab	ftgentmp	0, 0, 2, -2, iTempOld, iTempNew

; execute morphing (write new values to original table)
			ftmorf		kMorph, iMorphTab, iOriginal
	endin

;******************************************************
; parameter automation, set tables (source waveforms)
;******************************************************
	instr 20

	iVoice		= p4			; partikkel instance
	iWaveSlot	= p5			; wave slot (1,2,3 or 4)
	SwaveSlot	sprintf	"Partikkel%iSourceWave%i", iVoice, iWaveSlot
	SwaveName	strget p6

; set flag for single cycle waveform mode
	iSingleCycle	 = -1
	iTestSine	strcmp	SwaveName, "Sine"
	iSingleCycle	= (iTestSine == 0 ?  0 : iSingleCycle)
	iTest		strcmp	SwaveName, "Triangle"
	iSingleCycle	= (iTest == 0 ?  0 : iSingleCycle)
	iTest		strcmp	SwaveName, "Square"
	iSingleCycle	= (iTest == 0 ?  0 : iSingleCycle)
	iTest		strcmp	SwaveName, "Saw"
	iSingleCycle	= (iTest == 0 ?  0 : iSingleCycle)
	iTest		strcmp	SwaveName, "Pulse"
	iSingleCycle	= (iTest == 0 ?  0 : iSingleCycle)
; then set it for the waveslot being processed
	if iWaveSlot != 1 goto setSingleCycleFlag2
	gkSingleCycle1	= iSingleCycle
setSingleCycleFlag2:
	if iWaveSlot != 2 goto setSingleCycleFlag3
	gkSingleCycle2	= iSingleCycle
setSingleCycleFlag3:
	if iWaveSlot != 3 goto setSingleCycleFlag4
	gkSingleCycle3	= iSingleCycle
setSingleCycleFlag4:
	if iWaveSlot != 4 goto noSetSingleCycleFlag
	gkSingleCycle4	= iSingleCycle
noSetSingleCycleFlag:

; reassign waveform name for bandlimited waveforms
	iSmoothName	= (iSingleCycle == 0 && iTestSine != 0 ? 1 : 0)
	if iSmoothName == 0 goto noSmoothName
	SwaveName	strcat	SwaveName, "Smooth"
noSmoothName:

; special processing for live sampled segments
	; test if "segment" is found in the start of the wave name
	ipos strindex 	SwaveName, "segment"
	if ipos != 0 goto liveFollowMode
	SsegmentNum	strsub SwaveName, 8
	iSegmentNum	strtol SsegmentNum	; this refers to a live sampled segment number
	iSegmentNum	= iSegmentNum + 10000	; 10000 is added to the live sampled segment number, to keep it in a separate range from the table numbers for sound files
	goto setWaveformNumber

liveFollowMode:
	; test if "audioInput" is found in the start of the wave name
	ipos strindex 	SwaveName, "audioInput"
	if ipos != 0 goto noLiveSampledSegment
	iSegmentNum	= giLiveFeed		; this refers to a table number, containing a circular buffer for live audio recording
	goto setWaveformNumber

noLiveSampledSegment:
	iSegmentNum	chnget SwaveName	; this refers to a table number, containing a loaded soundfile or a single cycle waveform
	if iSegmentNum != 0 goto doneLoadingFile
	Sscoreline	sprintf	{{i 60 0 .1 "%s"
				  i 61 0 .1 "%s"}}, SwaveName, SwaveName
	scoreline_i	Sscoreline
checkSoundLoaded:
	iSegmentNum	chnget SwaveName	; this refers to a table number, containing a loaded soundfile
	if iSegmentNum == 0 goto holdWhileLoadingSound
doneLoadingFile:
	SwaveName_orig	strcat SwaveName, "_orig"
	i_origkey	chnget SwaveName_orig	; read original key (in cps) for this sample
	SwaveSlot_orig	strcat SwaveSlot, "_orig"
			chnset i_origkey, SwaveSlot_orig	; write original key to waveslot channel

setWaveformNumber:
	SloadStr	sprintf "Set source wave:%s, segmentOrTableNum:%i, voice:%i, slot:%i", SwaveName, iSegmentNum, iVoice, iWaveSlot
	puts SloadStr, 1
			chnset	iSegmentNum, SwaveSlot
; output the assigned wave name to host
			SwaveSlotName strcat SwaveSlot, "Name"
			;outvalue SwaveSlotName, SwaveName

; set flags for liveFollow or live sampling mode
	iFollowMode	strindex SwaveName, "audioInput"
	iLiveSamplMode 	strindex SwaveName, "segment"

; find the analysis ftables corresponding to the assigned source wave, using SwaveName to format the table names and chn to lookup the numbers
	iStrLen		strlen	SwaveName
	SwnameRoot	strsub	SwaveName, 0, iStrLen-4		; chop off the file type extension (e.g. .wav)
	SampTable	strcat SwnameRoot, "AmpAnalysis"
	iAmpFtno	chnget SampTable
	; special case for live follow mode, for live sampling segments, and for classic wavetable sources
	iAmpFtno	= (iFollowMode == 0 ? giLiveFeedAmp : iAmpFtno)
	iAmpFtno	= (iLiveSamplMode == 0 ? giLiveSamplingAmp : iAmpFtno)
	iAmpFtno	= (iSingleCycle == 0 ? giAmpFnDefault : iAmpFtno)
	SAmpAnalysFtab	sprintf "AmpAnalysis%i", iWaveSlot
			chnset iAmpFtno, SAmpAnalysFtab
	ScpsTable	strcat SwnameRoot, "CpsAnalysis"
	iCpsFtno	chnget ScpsTable
	; special case for live follow mode, for live sampling segments, and for classic wavetable sources
	iCpsFtno	= (iFollowMode == 0 ? giLiveFeedCps : iCpsFtno)
	iCpsFtno	= (iLiveSamplMode == 0 ? giLiveSamplingCps : iCpsFtno)
	iCpsFtno	= (iSingleCycle == 0 ? giCpsFnDefault : iCpsFtno)
	SCpsAnalysFtab	sprintf "CpsAnalysis%i", iWaveSlot
			chnset iCpsFtno, SCpsAnalysFtab
	StransTable	strcat SwnameRoot, "TransientAnalysis"
	iTransFtno	chnget StransTable
	; special case for live follow mode, for live sampling segments, and for classic wavetable sources
	iTransFtno	= (iFollowMode == 0 ? giLiveFeedTrans : iTransFtno)
	iTransFtno	= (iLiveSamplMode == 0 ? giLiveSamplingTrans : iTransFtno)
	iTransFtno	= (iSingleCycle == 0 ? giTransFnDefault : iTransFtno)
	STransAnalysFtab sprintf "TransientAnalysis%i", iWaveSlot
			chnset iTransFtno, STransAnalysFtab

; get the analysis length
	kLengthAnalys	table	0, iAmpFtno
	; special case for live follow mode and for live sampling segments
	kLengthAnalys	= (iFollowMode == 0 ? giLiveFeedAnalyzeLen : kLengthAnalys)
	kLengthAnalys	= (iLiveSamplMode == 0 ? giLiveSamplingAnalyzeLen : kLengthAnalys)
	SAnalysisLength	sprintf	"AnalysisLength%i", iWaveSlot
			chnset kLengthAnalys, SAnalysisLength


; write soundfile name as ascii to table, to enable saving soundfile name as part of preset
#define WriteSoundfileName(Voice'Slot)#

; first, remove "Smooth" from the single cycle waveforms that use it in their name
	iTestS1		strcmp	SwaveName, "TriangleSmooth"
	iTestS2		strcmp	SwaveName, "SquareSmooth"
	iTestS3		strcmp	SwaveName, "SawSmooth"
	iTestS4		strcmp	SwaveName, "PulseSmooth"
	iTestS		= (iTestS1 == 0 ? 1 : 0)
	iTestS		= (iTestS2 == 0 ? 1 : iTestS)
	iTestS		= (iTestS3 == 0 ? 1 : iTestS)
	iTestS		= (iTestS4 == 0 ? 1 : iTestS)
	if iTestS == 0 goto noSmooth\$Voice$Slot
	ilen		strlen SwaveName
	SwaveName	strsub	SwaveName, 0, ilen-6
	puts SwaveName, 1
noSmooth\$Voice\$Slot:

; then do the conversion from chanracters to ascii
	ipos		= -1
	iStrLen		strlen SwaveName
WriteAsciiLoop_\$Voice_\$Slot:
	ipos		= ipos + 1
	iAscii		strchar	SwaveName, ipos
	;print iAscii
; write ascii to table 
	tableiw		iAscii, ipos, giPartikkel\$VoiceSourceWave\$SlotName	
	if ipos < iStrLen goto WriteAsciiLoop_\$Voice_$Slot
	SoutvalName	sprintf	"p%iwav%iname", $Voice, $Slot
			;outvalue SoutvalName, SwaveName
#

; kludgy hack to allow dynamic wavetable name
if iVoice == 1 goto voice1
if iVoice == 2 goto voice2
Swarning  = "instr 20, voice number > 2 not implemented"

voice1:
if iWaveSlot == 1 goto v1Slot1
if iWaveSlot == 2 goto v1Slot2
if iWaveSlot == 3 goto v1Slot3
if iWaveSlot == 4 goto v1Slot4
v1Slot1:
$WriteSoundfileName(1'1)
goto end
v1Slot2:
$WriteSoundfileName(1'2)
goto end
v1Slot3:
$WriteSoundfileName(1'3)
goto end
v1Slot4:
$WriteSoundfileName(1'4)
goto end

voice2:
if iWaveSlot == 1 goto v2Slot1
if iWaveSlot == 2 goto v2Slot2
if iWaveSlot == 3 goto v2Slot3
if iWaveSlot == 4 goto v2Slot4
v2Slot1:
$WriteSoundfileName(2'1)
goto end
v2Slot2:
$WriteSoundfileName(2'2)
goto end
v2Slot3:
$WriteSoundfileName(2'3)
goto end
v2Slot4:
$WriteSoundfileName(2'4)
goto end


holdWhileLoadingSound:
	kSegmentNum	init 0
	kSegmentLoaded	init 0
	kSegmentLoaded	= (kSegmentNum > 0 ? 1 : 0)
	kSegmentNum	chnget SwaveName		; this refers to a table number, containing a loaded soundfile
	if kSegmentNum == 0 goto end			; don't do anything while waiting for sound to load
	if kSegmentLoaded == 1 goto doneLoadingFile	; do the reinit (on next line) only once
reinit checkSoundLoaded					; reinit and assign sound to source waveform when loaded

end:

	endin
;******************************************************
