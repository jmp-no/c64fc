	!cpu 6502

        *=$8000

        !word start
        !word start
        !byte $c3,$c2,$cd,$38,$30

start:	sei
        stx $d016

        jsr $ff5b               ; init video

	lda #0
	sta $d020
	sta $d021

	ldx #0

copy:	lda playerstart,x
	sta $800,x
	inx
	cpx #playerlen
	bne copy
	jmp $800

playerstart:
	!bin "player.bin"
playerlen=*-playerstart


