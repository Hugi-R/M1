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
	invoke 1, 0, 0
L10:
	call L1
L11:
	invoke 1, 0, 0
L12:
	call L1
L13:
	invoke 1, 0, 0
L14:
	call L1
L15:
	invoke 1, 0, 0
L16:
	call L1
L17:
	stop
