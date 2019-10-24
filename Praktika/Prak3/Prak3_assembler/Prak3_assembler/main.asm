;
; Prak3_assembler.asm
;
; Created: 24.10.2019 17:24:24
; Author : bh8332s
;

.org 0x000
	jmp start

start:
    inc r16
    rjmp start
