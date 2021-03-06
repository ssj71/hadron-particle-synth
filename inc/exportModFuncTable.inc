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
; export func table values text file (Csound table file format)
;******************************************************

	iModfuncNo	= p4			; select modulator function number (1,2,3,4)
	Sfilename	strget p5		; file name to write to
	Sfilename_p	sprintf		"func_files/%s", Sfilename

	SfuncTable	sprintf	"giModTransFunc%i", iModfuncNo
	ifuncTableNum	chnget SfuncTable

			ftsave		Sfilename_p, 1, ifuncTableNum

