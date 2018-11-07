L0:
	goto L9
L1:
	seti r0, #0
L2:
	seti r1, #1
L3:
	seti r2, #3
L4:
	goto_eq L8, r0, r2
L5:
	add r0, r0, r1
L6:
	invoke 2, 0, 0
L7:
	goto L4
L8:
	return
L9:
	invoke 12, 3, 0
L10:
	seti r4, #0
L11:
	goto_eq L24, r3, r4
L12:
	invoke 5, 3, 5
L13:
	seti r6, #0
L14:
	goto_eq L17, r5, r6
L15:
	call L1
L16:
	goto L22
L17:
	invoke 6, 1, 7
L18:
	seti r8, #0
L19:
	goto_eq L22, r7, r8
L20:
	invoke 2, 0, 0
L21:
	goto L17
L22:
	invoke 1, 0, 0
L23:
	goto L9
L24:
	stop
