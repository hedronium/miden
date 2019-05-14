# Instructions
There are 7 instructions.

|Opcode |Name   |
|-------|-------|
|000    |   add |
|001    |   addi|
|010    |   beq |
|011    |   li  |
|100    |   j   |
|101    |   jal |
|110    |   jr  |

# Registers
There are 8 registers:

|Binary |Name   |
|-------|-------|
|000    |    $0 |
|001    |    $s0|
|010    |    $t0|
|011    |    $v0|
|100    |    $a0|
|101    |    $a1|
|110    |    $ra|
|111    |    $sp|

# Instruction formats

## RRR
Example: add $s0, $t0, $a0 will be 000 001 010 0000 100.

|opcode|reg_d |reg_s | 0    |reg_t |
|------|------|------|------|------|
|3 bits|3 bits|3 bits|4 bits|3 bits|

## RRI

Example: addi $s0, $s0, 1 will be 001 001 001 0000001

|opcode|reg_d |reg_s |immediate |
|------|------|------|----------|
|3 bits|3 bits|3 bits|7 bits    |

## RRJ

Example: beq $s0, $t0, loop

|opcode|reg_a |reg_b |target|
|------|------|------|------|
|3 bits|3 bits|3 bits|7 bits|

## RI

Example: li $s0, 1 will be 001 001 0000000001

|opcode|reg_d |immediate |
|------|------|----------|
|3 bits|3 bits|10 bits   |

## R

Example: jr $ra

|opcode| 0     |reg   |
|------|-------|------|
|3 bits|10 bits|3 bits|

## J

Example: j done

|opcode|target |
|------|-------|
|3 bits|13 bits|