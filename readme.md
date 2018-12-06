<p align="center">
    <img height="50%" width="50%" src="https://raw.githubusercontent.com/nahiyan/miden/master/miden-logo.png">
    <p align="center">An assembler for 16-bit RISC processors.</p>
</p>

# Introduction
Miden is an assembler that assembles MIPS assembly to machine code. It generates machine code for 16-bit RISC processors, and as a result, it only supports a subset of the MIPS assembly.

# Example

Here's a C program which multiplies two numbers:

```cpp
int main() {
    int y;
    y = multiplyNumbers(2, 3); /*Returns product of 2 and 3*/
}

int multiplyNumbers(int a, int b) {
    int i;
    int product = 0;
    for (i = 0; i != b; i = i + 1) {
        product = product + a;
    }
    return product;
}
```

It's equivalent to the following piece of assembly code:

```nasm
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
	
```

This assembly program to fed into Miden. Miden generates machine code out of it.

Here's the machine code generated out of the assembly code above:

```binary
0110010000000000
0111000000010010
0111010000000110
1010000000001100
0010010010000000
1000000000011100
0110100000000000
0110110000000000
1000000000010010
0100101010011010
0000110110000100
0010100100000001
1000000000010010
1100000000000110
```

# Instruction Set Architecture
Miden supports 7 instructions and 8 registers. You can find more information [here](https://github.com/nahiyan/miden/blob/master/doc/isa.md).