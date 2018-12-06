# About Token
Miden reads the assembly code and turns it into a series of identical pieces called **tokens**.

For example, here's a line of assembly code:

```asm
li $s0, 1
```

The code above can be represented by the following series of tokens:

```
KWD	li
REG	s0
INT	1
```

As you can see, each token has:

- a name
- a value

As an example, the first token has a name of "KWD" and a value of "li."

Token names are 3 characters long for simplicity.

# Types of tokens
Miden utilizes 5 types of tokens:

|Name/Identifier|Description|
|----|-----------|
|LBL | Label|
|KWD| Keyword|
|REG|Register|
|INT|Integer|
|TAR|Target|

# Labels
Label declarations in assembly are represented by **LBL** tokens.

For example, here's an assembly code with a declaration of a label named "main":

```asm
main:
```

This will be represented by the token:

```
LBL	main
```

# Keywords
In assembly code, keyword is just a word that can either be the name of an instruction or a label.

Here's an assembly code representing a keyword "li" along with registers "s0" and integer "1":

```asm
li $s0, 1
```

The "li" keyword will be represented by the token:

```
KWD	li
```

# Registers
Registers in assembly code are units of storage within a processor. In MIPS assembly, registers are represented by a dollar sign '$' and a name.

In this following assembly code, we got a register named "s0":

```asm
li $s0, 1
```

This register will be represented by the token:

```
REG	s0
```

# Integers
In assembly code, integers or any values, which do not have to be retrieved from anywhere else, are usually called immediate values.

> Miden only supports integer immediate values.

# Target
A target is a label pointing to an instruction or an address of an instruction.

For example, we got two labels "setTwo" and "setThree" here:

```asm
j setTwo

setTwo:
	li $s0, 2
setThree:
	li $s0, 3	
```

In the code, we got a **j** instruction which jumps to the label "setTwo." Here, "setTwo" inside the **j** instruction is a **target**.