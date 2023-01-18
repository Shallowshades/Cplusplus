	.file	"clause2.cpp"
	.text
	.section	.rodata
	.type	_ZStL19piecewise_construct, @object
	.size	_ZStL19piecewise_construct, 1
_ZStL19piecewise_construct:
	.zero	1
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.align 8
	.type	_ZL11AspectRatio, @object
	.size	_ZL11AspectRatio, 8
_ZL11AspectRatio:
	.long	549755814
	.long	1073377968
.LC0:
	.string	"Scott Meyers"
	.section	.data.rel.ro.local,"aw",@progbits
	.align 8
	.type	_ZL11authorName1, @object
	.size	_ZL11authorName1, 8
_ZL11authorName1:
	.quad	.LC0
	.local	_ZL11authorName2
	.comm	_ZL11authorName2,32,32
	.globl	_ZN11GamePlayer18NumTurnsE
	.section	.rodata
	.align 4
	.type	_ZN11GamePlayer18NumTurnsE, @object
	.size	_ZN11GamePlayer18NumTurnsE, 4
_ZN11GamePlayer18NumTurnsE:
	.long	5
	.text
	.globl	_Z1fi
	.type	_Z1fi, @function
_Z1fi:
.LFB1493:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZNSolsEi@PLT
	movq	%rax, %rdx
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPFRSoS_E@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1493:
	.size	_Z1fi, .-_Z1fi
	.globl	main
	.type	main, @function
main:
.LFB1495:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$5, -20(%rbp)
	movl	$0, -16(%rbp)
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %edx
	movl	-16(%rbp), %eax
	cmpl	%eax, %edx
	jle	.L3
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	jmp	.L4
.L3:
	movl	-16(%rbp), %eax
.L4:
	movl	%eax, %edi
	call	_Z1fi
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	movl	-16(%rbp), %edx
	addl	$10, %edx
	cmpl	%edx, %eax
	jle	.L5
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	jmp	.L6
.L5:
	movl	-16(%rbp), %eax
	addl	$10, %eax
.L6:
	movl	%eax, %edi
	call	_Z1fi
	movl	$5, -20(%rbp)
	movl	$0, -16(%rbp)
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	leaq	-16(%rbp), %rdx
	leaq	-20(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_Z11callWithMaxIiEvRKT_S2_
	movl	-16(%rbp), %eax
	addl	$10, %eax
	movl	%eax, -12(%rbp)
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	leaq	-12(%rbp), %rdx
	leaq	-20(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_Z11callWithMaxIiEvRKT_S2_
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L8
	call	__stack_chk_fail@PLT
.L8:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1495:
	.size	main, .-main
	.section	.text._Z11callWithMaxIiEvRKT_S2_,"axG",@progbits,_Z11callWithMaxIiEvRKT_S2_,comdat
	.weak	_Z11callWithMaxIiEvRKT_S2_
	.type	_Z11callWithMaxIiEvRKT_S2_, @function
_Z11callWithMaxIiEvRKT_S2_:
.LFB1737:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %edx
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jle	.L10
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	jmp	.L11
.L10:
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
.L11:
	movl	%eax, %edi
	call	_Z1fi
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1737:
	.size	_Z11callWithMaxIiEvRKT_S2_, .-_Z11callWithMaxIiEvRKT_S2_
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB1985:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA1985
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movl	%edi, -36(%rbp)
	movl	%esi, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	cmpl	$1, -36(%rbp)
	jne	.L12
	cmpl	$65535, -40(%rbp)
	jne	.L12
	leaq	_ZStL8__ioinit(%rip), %rdi
.LEHB0:
	call	_ZNSt8ios_base4InitC1Ev@PLT
.LEHE0:
	leaq	__dso_handle(%rip), %rdx
	leaq	_ZStL8__ioinit(%rip), %rsi
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	__cxa_atexit@PLT
	leaq	-25(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-25(%rbp), %rax
	movq	%rax, %rdx
	leaq	.LC0(%rip), %rsi
	leaq	_ZL11authorName2(%rip), %rdi
.LEHB1:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE1:
	leaq	-25(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	__dso_handle(%rip), %rdx
	leaq	_ZL11authorName2(%rip), %rsi
	movq	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	__cxa_atexit@PLT
	jmp	.L12
.L16:
	movq	%rax, %rbx
	leaq	-25(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB2:
	call	_Unwind_Resume@PLT
.LEHE2:
.L12:
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L15
	call	__stack_chk_fail@PLT
.L15:
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1985:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA1985:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1985-.LLSDACSB1985
.LLSDACSB1985:
	.uleb128 .LEHB0-.LFB1985
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB1985
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L16-.LFB1985
	.uleb128 0
	.uleb128 .LEHB2-.LFB1985
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSE1985:
	.text
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I__ZN11GamePlayer18NumTurnsE, @function
_GLOBAL__sub_I__ZN11GamePlayer18NumTurnsE:
.LFB1986:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1986:
	.size	_GLOBAL__sub_I__ZN11GamePlayer18NumTurnsE, .-_GLOBAL__sub_I__ZN11GamePlayer18NumTurnsE
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__ZN11GamePlayer18NumTurnsE
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
