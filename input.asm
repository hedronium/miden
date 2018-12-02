main:
	li $s0, 0
	li $a0, 18
	li $a1, 6
	jal multiplyNumbers
	addi $s0, $v0, 0
	j done

multiplyNumbers:
	li $t0, 0
	li $v0, 0
	j multiplyNumbersLoop

multiplyNumbersLoop:
	beq $t0, $a1, multiplyNumbersReturn

	add $v0, $v0, $a0
	addi $t0, $t0, 1

	j multiplyNumbersLoop

multiplyNumbersReturn:
	jr $ra
done:
	