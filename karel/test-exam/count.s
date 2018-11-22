L0:
	seti r0, #0
L1:
	seti r1, #1
L2:
	seti r6, #0
L3:
	goto L4
L4:
	set r7, r6
L5:
	seti r4, #0
L6:
	sub r8, r6, r7
L7:
	set r5, r8
L8:
	set r9, r6
L9:
	invoke 5, 1, 10
L10:
	goto_eq L16, r10, r0
L11:
	invoke 1, 0, 0
L12:
	invoke 11, 11, 0
L13:
	goto_eq L15, r11, r0
L14:
	add r6, r6, r1
L15:
	goto L9
L16:
	sub r12, r6, r9
L17:
	set r4, r12
L18:
	invoke 5, 1, 13
L19:
	goto_eq L24, r13, r0
L20:
	set r14, r6
L21:
	invoke 2, 0, 0
L22:
	sub r15, r6, r14
L23:
	set r4, r15
L24:
	invoke 5, 1, 16
L25:
	goto_eq L31, r16, r0
L26:
	set r17, r6
L27:
	invoke 2, 0, 0
L28:
	sub r18, r6, r17
L29:
	set r4, r18
L30:
	goto L35
L31:
	invoke 1, 0, 0
L32:
	invoke 11, 19, 0
L33:
	goto_eq L35, r19, r0
L34:
	add r6, r6, r1
L35:
	stop
L36:
	stop
