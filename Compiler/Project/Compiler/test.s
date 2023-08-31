	.text
	.file	"main"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	$250, 12(%rsp)
	movl	$50, 16(%rsp)
	cmpl	$0, 16(%rsp)
	je	.LBB0_3
	.p2align	4, 0x90
.LBB0_2:                                # %WhileLoop
                                        # =>This Inner Loop Header: Depth=1
	movl	16(%rsp), %ecx
	movl	%ecx, 20(%rsp)
	movl	12(%rsp), %eax
	cltd
	idivl	%ecx
	movl	%edx, 16(%rsp)
	movl	%ecx, 12(%rsp)
	cmpl	$0, 16(%rsp)
	jne	.LBB0_2
.LBB0_3:                                # %WhileEnd
	movl	12(%rsp), %esi
	movl	$.L__unnamed_1, %edi
	xorl	%eax, %eax
	callq	printf@PLT
	xorl	%eax, %eax
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L__unnamed_1,@object           # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_1:
	.asciz	"\"%d\""
	.size	.L__unnamed_1, 5

	.section	".note.GNU-stack","",@progbits
