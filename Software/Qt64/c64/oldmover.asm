
	!source "common.asm"

	*=cartcopier

waitforsignal:
	lda $8000
	cmp #$01
	bne waitforsignal

	ldy #50
wait1second:
	ldx #$50
	cpx $d012
	bne *-3
	ldx #$a0
	cpx $d012
	bne *-3
	dey
	bpl wait1second

DEST=$0801-2

	ldx #0
copy:
	lda $8000+$0000,x
	sta DEST+$0000,x
	lda $8000+$0100,x
	sta DEST+$0100,x
	lda $8000+$0200,x
	sta DEST+$0200,x
	lda $8000+$0300,x
	sta DEST+$0300,x
	lda $8000+$0400,x
	sta DEST+$0400,x
	lda $8000+$0500,x
	sta DEST+$0500,x
	lda $8000+$0600,x
	sta DEST+$0600,x
	lda $8000+$0700,x
	sta DEST+$0700,x
	lda $8000+$0800,x
	sta DEST+$0800,x
	lda $8000+$0900,x
	sta DEST+$0900,x
	lda $8000+$0a00,x
	sta DEST+$0a00,x
	lda $8000+$0b00,x
	sta DEST+$0b00,x
	lda $8000+$0c00,x
	sta DEST+$0c00,x
	lda $8000+$0d00,x
	sta DEST+$0d00,x
	lda $8000+$0e00,x
	sta DEST+$0e00,x
	lda $8000+$0f00,x
	sta DEST+$0f00,x

	lda $8000+$1000,x
	sta DEST+$1000,x
	lda $8000+$1100,x
	sta DEST+$1100,x
	lda $8000+$1200,x
	sta DEST+$1200,x
	lda $8000+$1300,x
	sta DEST+$1300,x
	lda $8000+$1400,x
	sta DEST+$1400,x
	lda $8000+$1500,x
	sta DEST+$1500,x
	lda $8000+$1600,x
	sta DEST+$1600,x
	lda $8000+$1700,x
	sta DEST+$1700,x
	lda $8000+$1800,x
	sta DEST+$1800,x
	lda $8000+$1900,x
	sta DEST+$1900,x
	lda $8000+$1a00,x
	sta DEST+$1a00,x
	lda $8000+$1b00,x
	sta DEST+$1b00,x
	lda $8000+$1c00,x
	sta DEST+$1c00,x
	lda $8000+$1d00,x
	sta DEST+$1d00,x
	lda $8000+$1e00,x
	sta DEST+$1e00,x
	lda $8000+$1f00,x
	sta DEST+$1f00,x

	inx
	;cpx #0
	beq done
	jmp copy

done:
	jsr $e453		; init vectors
	jsr $e3bf		; init BASIC

	jsr $a86e		; sty $3a + RTS
	jsr $a533		; relink

	ldx $22
	ldy $23
	stx $2d
	sty $2e

	jsr $a659		; run

	jmp $a7ae

