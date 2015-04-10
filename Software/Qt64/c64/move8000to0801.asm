
	!source "common.asm"

	*=cartcopier

	lda #$37
	sta $01

	lda #$01
	sta $fd
	lda #$08
	sta $fe

	; Wait for kickstart

waitforsignal:
	lda $9fff
	cmp #$32
	bne notrun
	jmp run
notrun: cmp #$64
	bne waitforsignal


	; Copy data

	ldx #16-1
cloop:	ldy #0
copyA:
	;lda #$37
	;sta $01
	lda $8000,y
	;pha
	;lda #$36
	;sta $01
	;pla

	sta ($fd),y
	sta $d020
	iny
	bne copyA


	inc copyA+2
	inc $fe
	dex
	bpl cloop

	; Signal still high? Wait some more.

waitrelease:
	lda $9fff
	cmp #$64
	beq waitrelease

	; Restore read pointer

	lda #$00
	sta copyA+1
	lda #$80
	sta copyA+2

	; Loop indefinitely

	jmp waitforsignal

	; Run as if it's a BASIC program
	
run:	jsr $e453		; init vectors
	jsr $e3bf		; init BASIC
	jsr $a86e		; sty $3a + RTS
	jsr $a533		; relink

	ldx $22
	ldy $23
	stx $2d
	sty $2e

	lda #$37
	sta $01

	jsr $a659
	jmp $a7ae

