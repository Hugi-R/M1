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
	seti r16, #0
L34:
	seti r17, #1
L35:
	goto_eq L45, r16, r17
L36:
	add r16, r16, r1
L37:
	set r18, r4
L38:
	goto_eq L40, r18, r5
L39:
	add r18, r18, r1
L40:
	invoke 1, 0, 0
L41:
	invoke 11, 19, 0
L42:
	goto_eq L44, r19, r0
L43:
	add r6, r6, r1
L44:
	goto L35
L45:
	invoke 2, 0, 0
L46:
	set r20, r4
L47:
	goto_eq L49, r20, r5
L48:
	add r20, r20, r1
L49:
	invoke 5, 1, 21
L50:
	goto_eq L56, r21, r0
L51:
	invoke 1, 0, 0
L52:
	invoke 11, 22, 0
L53:
	goto_eq L55, r22, r0
L54:
	add r6, r6, r1
L55:
	goto L59
L56:
	invoke 2, 0, 0
L57:
	invoke 2, 0, 0
L58:
	invoke 2, 0, 0
L59:
	invoke 1, 0, 0
L60:
	invoke 11, 23, 0
L61:
	goto_eq L63, r23, r0
L62:
	add r6, r6, r1
L63:
	stop
L64:
	stop
