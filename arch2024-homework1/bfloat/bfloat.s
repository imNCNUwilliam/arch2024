.data
    # initialize the data section with the number to be converted
    # default convertion from float to bfloat16 (direction == 0)
    nums:	.word 0x3f800000, 0x3fa00000, 0x40800000
    numsSize:	.word 3
    direction:	.word 0
    mask1:	.word 0x7fffffff
    mask2:	.word 0x7f800001
    large_num:	.word 0x7fff

.text
    # Begin the main code in the text section
    la a0, nums		# load the nums array address to register a0
    lw a1, numsSize	# load the nums array size to register a1
    addi a2, x0, 0	# keep the element index in register a2
    lw s0, direction	# load the given direction into register s0

loop:
    lw t1, 0(a0)	# load the nums[i] into register t1
    # determine the conversion type
    bne s0, x0, bf16_to_fp32

fp32_to_bf16:
    lw t2, mask1	# load mask1 into register t2
    lw t3, mask2	# load mask2 into register t3
    and t4, t1, t2	# t4 = t1 & t2
    srli t5, t1, 0x10	# extract the first 16 bits
    bge t4, t3, quiet	# jump to quiet for special case NaN

    # Rounding related
    andi t5, t5, 1	# examine whether the 16th bit is odd
    lw t4 large_num
    add t5, t5, t4
    add t5, t5, t1

    # convert to 2-byte
    srli t5 t5 0x10
    j out

quiet:
    ori t5, t5, 64
    j out

bf16_to_fp32:

out:
    # result hold in register t6
    addi a2, a2, 1	# increase the loop index
    addi a0, a0, 4	# get the next nums[i] address
    blt a2, a1, loop	# continue the next conversion
    nop			# No operation, acts as a placeholder

