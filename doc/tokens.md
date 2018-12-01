// label declaration
LBL name

// keyword
KWD name

// register name
REG name

// integer
INT value

// single line comment
COM comment

// target
TAR name

LBL = main
KWD = li
REG = s0
INT = 0
KWD = li
REG = a0
INT = 2
KWD = li
REG = a1
INT = 3
KWD = jal
KWD = multiplyNumbers
LBL = multiplyNumbers
KWD = li
REG = t0
INT = 0
KWD = li
REG = v0
INT = 0
LBL = multiplyNumbersLoop
KWD = beq
REG = t0
REG = a1
TAR = multiplyNumbersReturn
KWD = add
REG = v0
REG = v0
REG = a0
KWD = addi
REG = t0
REG = t0
INT = 1
KWD = j
KWD = multiplyNumbersLoop
LBL = multiplyNumbersReturn
KWD = jr
REG = ra