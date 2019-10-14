;
; SimpleAssemblerProgramm.asm
;
; Created: 10.10.2018 10:55:20
; Author : ie4938e
;
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
	rcall delay		;kleine Pause (unterprogramm) - relative call to subroutine - warum nicht rjmp oder gar jump?

	rjmp main		;Ruecksprung

delay:
	nop
	ret
