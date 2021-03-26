.name "Yasbaltrine"
.comment "La duchesse d'aquitaine"

start:
	sti r1, %:live, %1
live:
	live %1
	fork %:start	
	ld  %512, r3
	ld 	%-805304831, r4
	sti r3, %:start, %0
	sti	r4, %:start, %3
	st r1, 6
	live %42
