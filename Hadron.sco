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

;***************************************************
#define SCORELEN # 86400 #				; set length of score
#define cpsMidi(N) # [440*(1.0594631^($N-69))] #	; get cps value from (midi style) note number
#define semiTone(N) # [1.0594631^$N] #			; transposition by semitones
;***************************************************
;***************************************************
;; INSTR START TIME IS HIGHLY IMPORTANT FOR CORRECT INITIALIZATION
;***************************************************
;***************************************************

i2	0	1			; global ftables

i50	1	$SCORELEN		; check record pointer reset
i52	1	$SCORELEN		; live follow input enable

i 70 	1.1 	1 "_unassigned.spst"	; read default preset as single preset 

i 75 	1.1 	1			; and copy values to default preset table

i 73	1.3	1 "default.mpst" 1	; read default master preset

i 72 	1.4 	1 "_unassigned.spst" 0	; read default preset as preset 0 in master
i 72 	1.4 	1 "_unassigned.spst" 1	; read default preset as preset 0 in master
i 72 	1.4 	1 "_unassigned.spst" 2	; read default preset as preset 0 in master
i 72 	1.4 	1 "_unassigned.spst" 3	; read default preset as preset 0 in master

i 74 	1.42 	-1			; and start preset interpolation for master presets

i 89 	1	.01  	60 60		; midi note init

i 240	2	$SCORELEN		; external audio (sidechain) sync input
i 251 	2	$SCORELEN		; partikkel instr
i 260	2.1 1				; message to host (csound ready)

;********************************
; mask morphing functions

i81 	1.5 	$SCORELEN	"gainmasks1"
i81 	1.5 	$SCORELEN	"channelmasks1"
i81 	1.5 	$SCORELEN	"wavemasks1"
i81 	1.5 	$SCORELEN	"fmampmasks1"
i81 	1.5 	$SCORELEN	"freqstartmasks1"
i81 	1.5 	$SCORELEN	"freqendmasks1"

;i 100 	2	1			; clear modmatrix (test)
;i 101 	2	1			; clear mask tables (test)

;********************************
; modulator matrix
i90	1.6	$SCORELEN		; modulators 

i91	1	$SCORELEN		; mod matrix, and merge modulation with parameter values 
;********************************
;********************************

; enable always on instruments 
i293	1.45	$SCORELEN		; bandpass1
i294	1.45	$SCORELEN		; bandpass2
i295	1.45	$SCORELEN		; lowpass
i296	1.45	$SCORELEN		; bandpass3
i297	1.45	$SCORELEN		; delay
i400	1	$SCORELEN		; master audio out


;***************************************************

