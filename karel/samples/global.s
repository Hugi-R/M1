L0:
	invoke 12, 0, 0
L1:
	seti r1, #0
L2:
	goto_eq L14, r0, r1
L3:
	invoke 5, 3, 2
L4:
	seti r3, #0
L5:
	goto_eq L7, r2, r3
L6:
	invoke 2, 0, 0
L7:
	invoke 6, 1, 4
L8:
	seti r5, #0
L9:
	goto_eq L12, r4, r5
L10:
	invoke 2, 0, 0
L11:
	goto L7
L12:
	invoke 1, 0, 0
L13:
	goto L0
L14:
	stop
