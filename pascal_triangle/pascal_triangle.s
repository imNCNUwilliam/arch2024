.data
    # initilize the data section with the specied row number of Pascal's Triangle
    # the row number `i` starts from 0, and there are `i + 1` elements in row `i`
    row_id:		.word 5
    counters:		.word 0, 0, 0, 0, 0, 0
    zero:		.word 0

.text
    # Begin the main code in the text section
    lw t4, row_id		# load the given row id into register t4
    la a0, counters		# load the counters array address to register a0
    # calculate the upper limits for enumeration
    addi t5, x0, 1		# keep the upper limits for enumeration with register t5
    sll t5, t5, t4
    addi t6, x0, -1		# enumerate from 0 to `(1 << row_id) - 1` with register t6
    lw s3, zero			# hold the constant value `0` with register s3

loop:
    addi t6, t6, 1
    beq t6, t5, end		# determine whether to end the enumeration
    addi s0, t6, 0		# local variable stored with register s0 for pop_count
    addi s1, x0, 0		# local variable stored with register s1 for one-time counter

pop_count:
    beq s0, x0, out		# determine whether to finish the pop_count
    andi s4, s0, 1
    beq s4, s3, skip_add	# determine whether to increase the one-time counter
    addi s1, s1, 1		# increase counter by 1

skip_add:
    srli s0, s0, 1		# right shift one position for pop_count checking the next bit
    j pop_count
    
out:
    slli s1, s1, 2		# a word occupies 4 bytes in riscv32
    add a1, a0, s1		# load counter `i` address into register a1
    lw s2, 0(a1)		# load content of counter `i` to register s2
    addi s2, s2, 1		# increase counter `i` by 1
    sw s2, 0(a1)		# store register s2 to counter `i`
    j loop

end:
    nop				# No operation, acts as a placeholder

