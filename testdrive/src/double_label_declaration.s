.name    "Survivor"
.comment "Invincible"

run:	xor	r0, r0, r0
	live	greg

run:	xor	r0, r0, r0

	xor	r0, r0, r0
	fork	%:f1
	zjmp	%:j1
f1:	ld	%5, r2
	zjmp	%:run
j1:	
l1:	st	r2, 1
	live	%1
	zjmp	%:l1
