/* Linked first into every module: start marker of the constructor list. */
	.section .ctors, "aw", @progbits
	.balign 4
	.globl ko_ctors_start
ko_ctors_start:
