	!cpu 6502

        *=$800

	ldx #0
	lda #' '
clr:	sta $400,x
	sta $500,x
	sta $600,x
	sta $700,x
	inx
	bne clr

	lda #$37
	sta $01

	ldx #0
s:
	lda #$1
	sta $d800,x
	sta $d900,x
	lda #' '
	sta $0400,x
	sta $0500,x
	inx
	bne s

loop:
	ldx #$ff
	cpx $d012
	bne *-3

	inc $d020
	jsr check_new_song
play:	jsr not_new_song
	dec $d020

	jmp loop


not_new_song:
	rts

check_new_song:
	lda #$ff
	cmp $9eff
	bne not_new_song
	lda #$ff
wait_ready:
	inc $d020
	cmp $9eff
	beq wait_ready


;	lda #$02
;	sta $40
;	lda #$04
;	sta $41
;	ldx $807d
;	jsr printhex

;	lda #$00
;	sta $40
;	lda #$04
;	sta $41
;	ldx $807e
;	jsr printhex

	; SOURCE:

	lda #$7e
	sta $40
	lda #$80
	sta $41

	; DESTINATION:

	lda $8000+$7c	; $00
	sta $50
	lda $8000+$7d	; $10
	sta $51


bequerel:
	ldx #32-1
copyblocks:
	ldy #0
copybytes:
	lda ($40),y
	sta ($50),y
	iny
	bne copybytes
	inc $41
	inc $51
	dex
	bne copyblocks


	lda $8000+$b	; $00
	sta init+1
	lda $8000+$a	; $10
	sta init+2

	lda #0
	ldx #0
	ldy #0
init:	jsr $1000

	lda $8000+$d
	sta play+1
	lda $8000+$c
	sta play+2
	rts


;	lda #$4c
;	sta $1800


;printhex:
;	clc
;	txa
;	lsr
;	lsr
;	lsr
;	lsr
;	and #$f
;	tay
;	lda hex,y
;	ldy #0
;	sta ($40),y
;	txa
;	and #$f
;	tay
;	lda hex,y
;	ldy #1
;	sta ($40),y
;	rts
;
;hex:	!scr "0123456789abcdef"
;
