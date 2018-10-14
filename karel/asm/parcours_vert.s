_start:
    seti r0, #0
    seti r3, #0
loop:
    invoke 11, 1, 0
    goto_ne end, r1, r0
    invoke 6, 1, 1
    goto_ne turn, r1, r0
    invoke 1, 0, 0
    goto loop
    
turn:
    invoke 2, 0, 0
    goto_eq turn_1, r3, r0
    invoke 2, 0, 0
    invoke 2, 0, 0
turn_1:
    invoke 11, 1, 0
    goto_ne end, r1, r0
    invoke 6, 1, 1
    goto_ne end, r1, r0
    invoke 1, 0, 0
    invoke 2, 0, 0
    goto_eq turn_2, r3, r0
    invoke 2, 0, 0
    invoke 2, 0, 0
    seti r3, #0
    goto loop
turn_2:
    seti r3, #1
    goto loop
end:
    stop