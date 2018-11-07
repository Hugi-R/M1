L0:
	invoke 1, 0, 0
L1:
	invoke 2, 0, 0
L2:
	stop
L3:
	seti r0, #0
L4:
	seti r1, #1
L5:
	seti r2, #10
L6:
	goto_eq L10, r0, r2
L7:
	add r0, r0, r1
L8:
	invoke 1, 0, 0
L9:
	goto L6
L10:
	invoke 11, 3, 0
L11:
	seti r4, #0
L12:
	goto_eq L15, r3, r4
L13:
	invoke 1, 0, 0
L14:
	goto L10
L15:
	invoke 11, 5, 0
L16:
	seti r6, #0
L17:
	goto_eq L19, r5, r6
L18:
	invoke 1, 0, 0
L19:
	invoke 1, 0, 0
L20:
	invoke 1, 0, 0
