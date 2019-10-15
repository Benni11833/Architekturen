;
; SimpleAssemblerProgramm.asm
;
; Created: 10.10.2018 10:55:20
; Author : ie4938e
;

.def outerLoop = r18;
.def mid_1_Loop = r19;
.def mid_2_Loop = r20;
.def innerLoop = r21;

.include "m8def.inc"	; Prozessordefinitionen laden


.org 0x000		; Reset Vector
	rjmp start
;Rest der Tabelle bleibt ungenutzt

start:
	ldi r16, LOW( RAMEND )
	out SPL, r16	;StackPointer-Low (8 Bits) - warum nicht ldi SPL, LOW( RAMEND )?
	ldi r16, HIGH( RAMEND )
	out SPH, r16	;StackPointer-High (8 Bits)

	;PB0 PB1 als Output
	ldi r16,0b00000011	;letzen beiden Leds als Output(1) -> wo im datasheet steht PB0/1 als LEDs
	out DDRB, r16	;inhalt von r16 in DDRB schreiben -> eigentliche Daten werden auf Input-Bus gelegt Data-Direction-Register(um ausgelesen zu werden von Befehlen)
				
				;R16 = Arbeitsregister(allzweck)

main:
	in r16, PORTB	;PORTB lesen ?
	ldi r17,1		;r17 laden - 0-Bit gesetzt zu 1
	eor r16, r17	;Bit0 in r16 negieren - exclusive or -> negiert 0-Bit (00000011 mit 00000001 zu 00000010)
	out PORTB, r16	;PORTB schreiben - Register zu I/O-Location
	rcall delay_start		;kleine Pause (unterprogramm) - relative call to subroutine

	rjmp main		;Ruecksprung


;muss lt Praktikum 1/5 Sekunden = 200ms sein -> ATmega8 mit 17Hz, 1 Takt = 1Nop, 1Takt dauert 1/10^6 sekunden = 1ns -> 200 Millionen NOPs/Zyklen
delay_start:			;insgesamt
	ldi outerLoop, 5	;1 Zyklus outerLoop midLoop innerLoop

delay_outerLoop:		;bei x aufrufen: (outerLoop-1)*(3+131.325) + 1*(1+1+2+1+4)
	dec outerLoop		;1 Zyklus
	ldi mid_1_Loop, 255	;1 Zyklus
	brne delay_midLoop1	;1->false 2->true
	clz					;1 Zyklus
	ret					;4 Zyklen

delay_midLoop1:			;bei 255 aufrufen: 254*(3+131.325) + 1*(1+1+2+1+2) = 33.357.319
	dec mid_1_Loop		;1 Zyklus
	ldi mid_2_Loop, 255	;1 Zyklus
	brne delay_midLoop2	;1->false 2->true
	clz					;1 Zyklus
	rjmp delay_outerLoop;2 Zyklen

delay_midLoop2:			;bei 255 aufrufen: 254*(3+514) + 1*(1+1+2+1+2) = 131.325
	dec mid_2_Loop		;1 Zyklus
	ldi innerLoop, 255	;1 Zyklus
	brne delay_innerLoop;1->false 2->true
	clz;				;1 Zyklus
	rjmp delay_midLoop1	;2 Zyklen

delay_innerLoop:		;bei 255 aufrufen insgesamt 254*2 + 1*(1+2+1+2) = 514 Zyklen
	dec innerLoop		;1 Zyklus
	brne delay_innerLoop;1->false 2->true
	clz					;1 Zyklus -> Zero-Flag clearen, damit in delay_midLoop bzw delay_start brne nicht immer true ist
	rjmp delay_midLoop2	;2 Zyklen

	;rcall = 3 Zyklen, ldi = 1, dec = 1, brne = 1->cond false 2->cond true, ret 4 Zyklen

	;muss lt Praktikum 1/5 Sekunden = 200ms sein -> ATmega8 macht 16 MIPS(Million Instructions Per Second), also 3,2 MIP/200ms -> 3,2 Millionen (NOPs , CMP & BRNE)
	;muss lt Praktikum 1/5 Sekunden = 200ms sein -> ATmega8 mit 17Hz, 1 Takt = 1Nop, 1Takt dauert 1/10^6 sekunden = 1ns -> 200 Millionen NOPs/Zyklen