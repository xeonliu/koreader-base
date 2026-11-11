/* Linked last into every module: end marker of the constructor list (".ctors.~" sorts after every ".ctors.NNNNN")
 * and the zero terminator of the unwind tables. */
	.section ".ctors.~end", "aw", @progbits
	.balign 4
	.globl ko_ctors_end
ko_ctors_end:
	.section .eh_frame, "a", @progbits
	.balign 4
	.long 0
