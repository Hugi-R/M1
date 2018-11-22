L0:
	seti r0, #0
L1:
	seti r1, #1
L2:
	seti r6, #0
L3:
	goto L4
L4:
	seti r5, #0
L5:
	set r7, r6
L6:
	seti r8, #0
L7:
	seti r9, #8
L8:
	goto_eq L15, r8, r9
L9:
	add r8, r8, r1
L10:
	invoke 1, 0, 0
L11:
	invoke 11, 10, 0
L12:
	goto_eq L14, r10, r0
L13:
	add r6, r6, r1
L14:
	goto L8
L15:
	sub r11, r6, r7
L16:
	set r5, r11
L17:
	invoke 2, 0, 0
L18:
	invoke 2, 0, 0
L19:
	set r12, r6
L20:
	seti r13, #0
L21:
	goto_eq L28, r13, r5
L22:
	add r13, r13, r1
L23:
	invoke 1, 0, 0
L24:
	invoke 11, 14, 0
L25:
	goto_eq L27, r14, r0
L26:
	add r6, r6, r1
L27:
	goto L21
L28:
	sub r15, r6, r12
L29:
	set r4, r15
L30:
	invoke 2, 0, 0
L31:
	invoke 2, 0, 0
L32:
	invoke 2, 0, 0
L33:
	invoke 5, 1, 16
L34:
	goto_eq L48, r16, r0
L35:
	seti r17, #0
L36:
	seti r18, #2
L37:
	goto_eq L48, r17, r18
L38:
	add r17, r17, r1
L39:
	seti r19, #0
L40:
	goto_eq L47, r19, r4
L41:
	add r19, r19, r1
L42:
	invoke 1, 0, 0
L43:
	invoke 11, 20, 0
L44:
	goto_eq L46, r20, r0
L45:
	add r6, r6, r1
L46:
	goto L40
L47:
	goto L37
L48:
	invoke 1, 0, 0
L49:
	invoke 11, 21, 0
L50:
	goto_eq L52, r21, r0
L51:
	add r6, r6, r1
L52:
	invoke 2, 0, 0
L53:
	invoke 1, 0, 0
L54:
	invoke 11, 22, 0
L55:
	goto_eq L57, r22, r0
L56:
	add r6, r6, r1
L57:
	stop
L58:
	stop
