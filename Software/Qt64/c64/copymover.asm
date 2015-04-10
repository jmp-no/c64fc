
	*=$8000
	!word start
	!word start
	!byte $c3,$c2,$cd,$38,$30

	!source "common.asm"

start:	
	ldx #$ff
	sei
	txs
	cld
	stx $d016
	jsr $ff84
	jsr $ff87
	jsr $ff8a
	jsr $ff81
	cli
	jsr $e453
	jsr $e3bf
	jsr $e422
	

;	ldx #$00
;	lda #$a0
;	jsr $fd8c	; init memory ptrs

;	jsr $ff8a
;	jsr $ff81
;	cli
;	jsr $e453
;	jsr $e3bf
;	jsr $e422
;	ldx #$fb
;	txs
;	rts


;	jsr $fda3	; Enable CIA
;	jsr $fd50	; memtest
;	jsr $fd15	; restor
;	jsr $ff5b	; init vic


;	jsr $e453	; init vectors
;	jsr $e3bf	; init BASIC
;	jsr $e422
;	ldx #$fb
;	txs

;	rts

	lda #6
	ldx #0
clrscr:	sta $d800,x
	sta $d900,x
	sta $da00,x
	sta $db00,x
	inx
	bne clrscr

skip_clr:

	ldx #textlen-1
s:	lda text,x
	sta $400+(40*12)+20-(textlen>>1),x
	lda #$11
	sta $d800+(40*12)+20-(textlen>>1),x
	dex
	bpl s

;	copy copier to destination

	ldx #0
copy:	lda data,x
	sta cartcopier,x
	inx
	cpx #datasize
	bne copy

;	go to copier which waits for signal

	jmp cartcopier


text:	!scr "loading prg, please wait."
textlen=*-text

data:	!bin "move8000to0801.bin"
datasize=*-data

