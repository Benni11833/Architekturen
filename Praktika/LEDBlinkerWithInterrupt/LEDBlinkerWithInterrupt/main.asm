;
; LEDBlinkerWithInterrupt.asm
;
; Created: 18.10.2018 13:54:48
; Author : ie4938e
;
; This file contains the assembler opcodes for ATMega8 in comments
; The current version is written for ATMega328p
;.include "m8def.inc"
.include "m328pdef.inc"

; register aliases
.def temp = r16
.def ledstatus = r17
.def counter = r18

; constant definitions
.equ numwaits = 0x4					; Die Warteschleife numwaits mal durchlaufen,
									; bevor der LED Zustand sich �ndert

.org 0x0000
	rjmp    main                  	; Reset Handler
.org OVF0addr						; Adresse f�r den Interruptvektor
    rjmp    timer0_overflow       	; Adresse f�r den Timer Overflow Handler

main:
	; Stackpointer initialisieren
    ldi		temp, HIGH(RAMEND)
    out     SPH, temp
    ldi     temp, LOW(RAMEND)     
    out     SPL, temp
	
	rcall	initialize_application
	rcall	initialize_timer		; Initialisierungsroutine (Takt, Modus, Interrupts)

main_loop:
   	rjmp    main_loop				; Hauptschleife, hier passiert nichts mehr


initialize_application:
    ldi     temp, 0xFF			
    out     DDRB, temp				; Alle Pins von PortB als Ausgang schalten

	ldi     ledstatus, 0xFF			; Initialisierung: Pins von Port B auf High Pegel				
	ldi     counter, 0				; Z�hlregister
	ret


initialize_timer:
	cli								; Interrupts sperren
	in		temp, TCCR0B			; in		temp, TCCR0
	cbr     temp, 0b00000111		; L�sche Bits 0-2 (Timer stopped)
	sbr     temp, 0b00000101		; CS00 und CS02 setzen: Teiler 1024
    out     TCCR0B, temp			;out     TCCR0, temp

	ldi		temp, 0x00				; == clr temp ?
	out		TCNT0, temp				; Z�hlregister initialisieren   
   	ldi     temp, (1<<TOIE0)      	; TOIE0: Interrupt bei Timer Overflow  -> schaltet Interrupt bei Timer Overflow ein
    STS     TIMSK0, temp			; out     TIMSK, temp				; Interrupt maskieren w -- Warum STS und nicht out
									; Achtung: Hier anderer Befehl bei ATMega328p und ATMega8
	sei								; Interrupts freischalten
	ret


timer0_overflow:                    ; Timer 0 Overflow Handler, ( CLI ist implizit)
       	inc     counter
		cpi     counter, numwaits	; Oft genug gewartet
		brlo    endSub				; Nein? Dann weiterz�hlen 
									; ohne den LED Status zu �ndern
		out     PORTB, ledstatus	; LED Status ausgeben 
        com     ledstatus			; LED Status �ndern	-	 Ones Complement
		ldi     counter, 0			; Z�hler zur�cksetzen
endSub: 
		reti						; Beende die ISR (SEI ist implizit)