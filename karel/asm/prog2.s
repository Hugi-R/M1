_start:
    invoke 2, 0, 0
    invoke 2, 0, 0
    seti r0, #5
    seti r1, #1
    seti r2, #0
loop:
    invoke 1, 0, 0
    add r2, r2, r1 
    goto_lt loop, r2, r0
end:
    stop