	!cpu 6502

temp	= $55
*	= $800

	sei

	; select lowercase charset

	lda #$16
	sta $d018

	; clear screen

	ldx #0
clr:	lda #' '
	sta $400,x
	sta $500,x
	sta $600,x
	sta $700,x
	lda #$1
	sta $d800,x
	inx
	bne clr

	; print welcome text

	ldx #0
print:	lda welcome,x
	beq loop
	sta $400+$28+1,x
	inx
	bne print

	; main loop

	lda #$37	; Enable cartridge
	sta $01

loop:	ldx #$ff
	cpx $d012
	bne *-3

	inc $d020
	jsr check_new_song
play:	jsr ret
	dec $d020

	jmp loop

ret:	rts



check_new_song:
	lda #$ff
	cmp $9eff
	bne ret
	lda #$ff
wait_ready:
	inc $d020
	cmp $9eff
	beq wait_ready

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
	lda #$37	; Enable cart
	sta $01

	lda ($40),y	; READs will read from cart
	sta temp

	lda #$35	; Disable cart
	sta $01

	lda temp
	sta ($50),y	; WRITEs will be written to internal memory

	iny
	bne copybytes
	inc $41
	inc $51
	dex
	bne copyblocks

	lda #$37	; Enable cart
	sta $01

	ldx #$20-1
copytitle:
	lda $8000+$16,x
	bne sp1
	lda #$20
sp1:	jsr convert
	sta $400+($28*1)+1,x
	dex
	bpl copytitle

	ldx #$20-1
copyauthor:
	lda $8000+$36,x
	bne sp2
	lda #$20
sp2:	jsr convert
	sta $400+($28*3)+1,x
	dex
	bpl copyauthor
skip:

	lda $8000+$b	; $00
	sta init+1
	lda $8000+$a	; $10
	sta init+2

	lda $8000+$d
	sta play+1
	lda $8000+$c
	sta play+2

	lda #$35	; Disable cart
	sta $01

	lda #0		; subtune?
	ldx #0
	ldy #0
init:	jsr $1000
	rts


convert:
	sta temp
	lda #%00100000
	bit temp
	bvc nobit
	beq nobit
	lda temp
	and #%10011111
	rts
nobit:	lda temp
	rts

welcome:!scr "Waiting for data.."
	!byte 0

