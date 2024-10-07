.data
    # initialize the data section with the number to be converted
    # default convertion from float to bfloat16 (direction == 0)
    num:	.word 0x40800000
    direction:	.word 0
    mask1:	.word 0x7fffffff
    mask2:	.word 0x7f800001
    large_num:	.word 0x7fff

.text
    # Begin the main code in the text section
    lw t1, num		# load the given number into register t1
    lw t2, direction	# load the given direction into register t2

    # determine the conversion type
    bne t2, x0, bf16_to_fp32

fp32_to_bf16:
    addi t2, t1, 0	# t2 = t1
    lw t3, mask1	# load mask1 into register t3
    lw t4, mask2	# load mask2 into register t4
    and t5, t2, t3	# t5 = t2 & t3
    srli t6, t2, 0x10	# extract the first 16 bits
    bge t5, t4, quiet	# jump to quiet for special case NaN

    # Rounding related
    andi t6, t6, 1	# examine whether the 16th bit is odd
    lw t5 large_num
    add t6, t6, t5
    add t6, t6, t2

    # convert to 2-byte
    srli t6 t6 0x10
    j out

quiet:
    ori t6, t6, 64
    j out

bf16_to_fp32:

out:
    # result hold in register t6
    nop		# No operation, acts as a placeholder

