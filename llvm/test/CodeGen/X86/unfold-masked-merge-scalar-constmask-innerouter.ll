; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc -mtriple=x86_64-unknown-linux-gnu -mattr=-bmi < %s | FileCheck %s --check-prefix=CHECK-NOBMI
; RUN: llc -mtriple=x86_64-unknown-linux-gnu -mattr=+bmi < %s | FileCheck %s --check-prefix=CHECK-BMI

; https://bugs.llvm.org/show_bug.cgi?id=37104

; X: [byte3]              [byte0]
; Y:        [byte2][byte1]

define i8 @out8_constmask(i8 %x, i8 %y) {
; CHECK-NOBMI-LABEL: out8_constmask:
; CHECK-NOBMI:       # %bb.0:
; CHECK-NOBMI-NEXT:    # kill: def $esi killed $esi def $rsi
; CHECK-NOBMI-NEXT:    # kill: def $edi killed $edi def $rdi
; CHECK-NOBMI-NEXT:    andb $60, %dil
; CHECK-NOBMI-NEXT:    andb $-61, %sil
; CHECK-NOBMI-NEXT:    leal (%rsi,%rdi), %eax
; CHECK-NOBMI-NEXT:    # kill: def $al killed $al killed $eax
; CHECK-NOBMI-NEXT:    retq
;
; CHECK-BMI-LABEL: out8_constmask:
; CHECK-BMI:       # %bb.0:
; CHECK-BMI-NEXT:    # kill: def $esi killed $esi def $rsi
; CHECK-BMI-NEXT:    # kill: def $edi killed $edi def $rdi
; CHECK-BMI-NEXT:    andb $60, %dil
; CHECK-BMI-NEXT:    andb $-61, %sil
; CHECK-BMI-NEXT:    leal (%rsi,%rdi), %eax
; CHECK-BMI-NEXT:    # kill: def $al killed $al killed $eax
; CHECK-BMI-NEXT:    retq
  %mx = and i8 %x, 60
  %my = and i8 %y, -61
  %r = or i8 %mx, %my
  ret i8 %r
}

define i16 @out16_constmask(i16 %x, i16 %y) {
; CHECK-NOBMI-LABEL: out16_constmask:
; CHECK-NOBMI:       # %bb.0:
; CHECK-NOBMI-NEXT:    # kill: def $esi killed $esi def $rsi
; CHECK-NOBMI-NEXT:    # kill: def $edi killed $edi def $rdi
; CHECK-NOBMI-NEXT:    andl $4080, %edi # imm = 0xFF0
; CHECK-NOBMI-NEXT:    andl $-4081, %esi # imm = 0xF00F
; CHECK-NOBMI-NEXT:    leal (%rsi,%rdi), %eax
; CHECK-NOBMI-NEXT:    # kill: def $ax killed $ax killed $eax
; CHECK-NOBMI-NEXT:    retq
;
; CHECK-BMI-LABEL: out16_constmask:
; CHECK-BMI:       # %bb.0:
; CHECK-BMI-NEXT:    # kill: def $esi killed $esi def $rsi
; CHECK-BMI-NEXT:    # kill: def $edi killed $edi def $rdi
; CHECK-BMI-NEXT:    andl $4080, %edi # imm = 0xFF0
; CHECK-BMI-NEXT:    andl $-4081, %esi # imm = 0xF00F
; CHECK-BMI-NEXT:    leal (%rsi,%rdi), %eax
; CHECK-BMI-NEXT:    # kill: def $ax killed $ax killed $eax
; CHECK-BMI-NEXT:    retq
  %mx = and i16 %x, 4080
  %my = and i16 %y, -4081
  %r = or i16 %mx, %my
  ret i16 %r
}

define i32 @out32_constmask(i32 %x, i32 %y) {
; CHECK-NOBMI-LABEL: out32_constmask:
; CHECK-NOBMI:       # %bb.0:
; CHECK-NOBMI-NEXT:    # kill: def $esi killed $esi def $rsi
; CHECK-NOBMI-NEXT:    # kill: def $edi killed $edi def $rdi
; CHECK-NOBMI-NEXT:    andl $16776960, %edi # imm = 0xFFFF00
; CHECK-NOBMI-NEXT:    andl $-16776961, %esi # imm = 0xFF0000FF
; CHECK-NOBMI-NEXT:    leal (%rsi,%rdi), %eax
; CHECK-NOBMI-NEXT:    retq
;
; CHECK-BMI-LABEL: out32_constmask:
; CHECK-BMI:       # %bb.0:
; CHECK-BMI-NEXT:    # kill: def $esi killed $esi def $rsi
; CHECK-BMI-NEXT:    # kill: def $edi killed $edi def $rdi
; CHECK-BMI-NEXT:    andl $16776960, %edi # imm = 0xFFFF00
; CHECK-BMI-NEXT:    andl $-16776961, %esi # imm = 0xFF0000FF
; CHECK-BMI-NEXT:    leal (%rsi,%rdi), %eax
; CHECK-BMI-NEXT:    retq
  %mx = and i32 %x, 16776960
  %my = and i32 %y, -16776961
  %r = or i32 %mx, %my
  ret i32 %r
}

define i64 @out64_constmask(i64 %x, i64 %y) {
; CHECK-NOBMI-LABEL: out64_constmask:
; CHECK-NOBMI:       # %bb.0:
; CHECK-NOBMI-NEXT:    movabsq $281474976645120, %rcx # imm = 0xFFFFFFFF0000
; CHECK-NOBMI-NEXT:    andq %rdi, %rcx
; CHECK-NOBMI-NEXT:    movabsq $-281474976645121, %rax # imm = 0xFFFF00000000FFFF
; CHECK-NOBMI-NEXT:    andq %rsi, %rax
; CHECK-NOBMI-NEXT:    orq %rcx, %rax
; CHECK-NOBMI-NEXT:    retq
;
; CHECK-BMI-LABEL: out64_constmask:
; CHECK-BMI:       # %bb.0:
; CHECK-BMI-NEXT:    movabsq $281474976645120, %rcx # imm = 0xFFFFFFFF0000
; CHECK-BMI-NEXT:    andq %rdi, %rcx
; CHECK-BMI-NEXT:    movabsq $-281474976645121, %rax # imm = 0xFFFF00000000FFFF
; CHECK-BMI-NEXT:    andq %rsi, %rax
; CHECK-BMI-NEXT:    orq %rcx, %rax
; CHECK-BMI-NEXT:    retq
  %mx = and i64 %x, 281474976645120
  %my = and i64 %y, -281474976645121
  %r = or i64 %mx, %my
  ret i64 %r
}

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Should be the same as the previous one.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define i8 @in8_constmask(i8 %x, i8 %y) {
; CHECK-NOBMI-LABEL: in8_constmask:
; CHECK-NOBMI:       # %bb.0:
; CHECK-NOBMI-NEXT:    movl %esi, %eax
; CHECK-NOBMI-NEXT:    xorl %esi, %edi
; CHECK-NOBMI-NEXT:    andb $60, %dil
; CHECK-NOBMI-NEXT:    xorb %dil, %al
; CHECK-NOBMI-NEXT:    # kill: def $al killed $al killed $eax
; CHECK-NOBMI-NEXT:    retq
;
; CHECK-BMI-LABEL: in8_constmask:
; CHECK-BMI:       # %bb.0:
; CHECK-BMI-NEXT:    movl %esi, %eax
; CHECK-BMI-NEXT:    xorl %esi, %edi
; CHECK-BMI-NEXT:    andb $60, %dil
; CHECK-BMI-NEXT:    xorb %dil, %al
; CHECK-BMI-NEXT:    # kill: def $al killed $al killed $eax
; CHECK-BMI-NEXT:    retq
  %n0 = xor i8 %x, %y
  %n1 = and i8 %n0, 60
  %r = xor i8 %n1, %y
  ret i8 %r
}

define i16 @in16_constmask(i16 %x, i16 %y) {
; CHECK-NOBMI-LABEL: in16_constmask:
; CHECK-NOBMI:       # %bb.0:
; CHECK-NOBMI-NEXT:    movl %edi, %eax
; CHECK-NOBMI-NEXT:    xorl %esi, %eax
; CHECK-NOBMI-NEXT:    andl $4080, %eax # imm = 0xFF0
; CHECK-NOBMI-NEXT:    xorl %esi, %eax
; CHECK-NOBMI-NEXT:    # kill: def $ax killed $ax killed $eax
; CHECK-NOBMI-NEXT:    retq
;
; CHECK-BMI-LABEL: in16_constmask:
; CHECK-BMI:       # %bb.0:
; CHECK-BMI-NEXT:    movl %edi, %eax
; CHECK-BMI-NEXT:    xorl %esi, %eax
; CHECK-BMI-NEXT:    andl $4080, %eax # imm = 0xFF0
; CHECK-BMI-NEXT:    xorl %esi, %eax
; CHECK-BMI-NEXT:    # kill: def $ax killed $ax killed $eax
; CHECK-BMI-NEXT:    retq
  %n0 = xor i16 %x, %y
  %n1 = and i16 %n0, 4080
  %r = xor i16 %n1, %y
  ret i16 %r
}

define i32 @in32_constmask(i32 %x, i32 %y) {
; CHECK-NOBMI-LABEL: in32_constmask:
; CHECK-NOBMI:       # %bb.0:
; CHECK-NOBMI-NEXT:    movl %edi, %eax
; CHECK-NOBMI-NEXT:    xorl %esi, %eax
; CHECK-NOBMI-NEXT:    andl $16776960, %eax # imm = 0xFFFF00
; CHECK-NOBMI-NEXT:    xorl %esi, %eax
; CHECK-NOBMI-NEXT:    retq
;
; CHECK-BMI-LABEL: in32_constmask:
; CHECK-BMI:       # %bb.0:
; CHECK-BMI-NEXT:    movl %edi, %eax
; CHECK-BMI-NEXT:    xorl %esi, %eax
; CHECK-BMI-NEXT:    andl $16776960, %eax # imm = 0xFFFF00
; CHECK-BMI-NEXT:    xorl %esi, %eax
; CHECK-BMI-NEXT:    retq
  %n0 = xor i32 %x, %y
  %n1 = and i32 %n0, 16776960
  %r = xor i32 %n1, %y
  ret i32 %r
}

define i64 @in64_constmask(i64 %x, i64 %y) {
; CHECK-NOBMI-LABEL: in64_constmask:
; CHECK-NOBMI:       # %bb.0:
; CHECK-NOBMI-NEXT:    xorq %rsi, %rdi
; CHECK-NOBMI-NEXT:    movabsq $281474976645120, %rax # imm = 0xFFFFFFFF0000
; CHECK-NOBMI-NEXT:    andq %rdi, %rax
; CHECK-NOBMI-NEXT:    xorq %rsi, %rax
; CHECK-NOBMI-NEXT:    retq
;
; CHECK-BMI-LABEL: in64_constmask:
; CHECK-BMI:       # %bb.0:
; CHECK-BMI-NEXT:    xorq %rsi, %rdi
; CHECK-BMI-NEXT:    movabsq $281474976645120, %rax # imm = 0xFFFFFFFF0000
; CHECK-BMI-NEXT:    andq %rdi, %rax
; CHECK-BMI-NEXT:    xorq %rsi, %rax
; CHECK-BMI-NEXT:    retq
  %n0 = xor i64 %x, %y
  %n1 = and i64 %n0, 281474976645120
  %r = xor i64 %n1, %y
  ret i64 %r
}

; ============================================================================ ;
; Constant Commutativity tests.
; ============================================================================ ;

define i32 @in_constmask_commutativity_0_1(i32 %x, i32 %y) {
; CHECK-NOBMI-LABEL: in_constmask_commutativity_0_1:
; CHECK-NOBMI:       # %bb.0:
; CHECK-NOBMI-NEXT:    movl %edi, %eax
; CHECK-NOBMI-NEXT:    xorl %esi, %eax
; CHECK-NOBMI-NEXT:    andl $16776960, %eax # imm = 0xFFFF00
; CHECK-NOBMI-NEXT:    xorl %esi, %eax
; CHECK-NOBMI-NEXT:    retq
;
; CHECK-BMI-LABEL: in_constmask_commutativity_0_1:
; CHECK-BMI:       # %bb.0:
; CHECK-BMI-NEXT:    movl %edi, %eax
; CHECK-BMI-NEXT:    xorl %esi, %eax
; CHECK-BMI-NEXT:    andl $16776960, %eax # imm = 0xFFFF00
; CHECK-BMI-NEXT:    xorl %esi, %eax
; CHECK-BMI-NEXT:    retq
  %n0 = xor i32 %x, %y
  %n1 = and i32 %n0, 16776960
  %r = xor i32 %y, %n1 ; swapped
  ret i32 %r
}

define i32 @in_constmask_commutativity_1_0(i32 %x, i32 %y) {
; CHECK-NOBMI-LABEL: in_constmask_commutativity_1_0:
; CHECK-NOBMI:       # %bb.0:
; CHECK-NOBMI-NEXT:    movl %esi, %eax
; CHECK-NOBMI-NEXT:    xorl %edi, %eax
; CHECK-NOBMI-NEXT:    andl $16776960, %eax # imm = 0xFFFF00
; CHECK-NOBMI-NEXT:    xorl %edi, %eax
; CHECK-NOBMI-NEXT:    retq
;
; CHECK-BMI-LABEL: in_constmask_commutativity_1_0:
; CHECK-BMI:       # %bb.0:
; CHECK-BMI-NEXT:    movl %esi, %eax
; CHECK-BMI-NEXT:    xorl %edi, %eax
; CHECK-BMI-NEXT:    andl $16776960, %eax # imm = 0xFFFF00
; CHECK-BMI-NEXT:    xorl %edi, %eax
; CHECK-BMI-NEXT:    retq
  %n0 = xor i32 %x, %y
  %n1 = and i32 %n0, 16776960
  %r = xor i32 %n1, %x ; %x instead of %y
  ret i32 %r
}

define i32 @in_constmask_commutativity_1_1(i32 %x, i32 %y) {
; CHECK-NOBMI-LABEL: in_constmask_commutativity_1_1:
; CHECK-NOBMI:       # %bb.0:
; CHECK-NOBMI-NEXT:    movl %esi, %eax
; CHECK-NOBMI-NEXT:    xorl %edi, %eax
; CHECK-NOBMI-NEXT:    andl $16776960, %eax # imm = 0xFFFF00
; CHECK-NOBMI-NEXT:    xorl %edi, %eax
; CHECK-NOBMI-NEXT:    retq
;
; CHECK-BMI-LABEL: in_constmask_commutativity_1_1:
; CHECK-BMI:       # %bb.0:
; CHECK-BMI-NEXT:    movl %esi, %eax
; CHECK-BMI-NEXT:    xorl %edi, %eax
; CHECK-BMI-NEXT:    andl $16776960, %eax # imm = 0xFFFF00
; CHECK-BMI-NEXT:    xorl %edi, %eax
; CHECK-BMI-NEXT:    retq
  %n0 = xor i32 %x, %y
  %n1 = and i32 %n0, 16776960
  %r = xor i32 %x, %n1 ; swapped, %x instead of %y
  ret i32 %r
}

; ============================================================================ ;
; Y is an 'and' too.
; ============================================================================ ;

define i32 @in_complex_y0_constmask(i32 %x, i32 %y_hi, i32 %y_low) {
; CHECK-NOBMI-LABEL: in_complex_y0_constmask:
; CHECK-NOBMI:       # %bb.0:
; CHECK-NOBMI-NEXT:    movl %edi, %eax
; CHECK-NOBMI-NEXT:    andl %edx, %esi
; CHECK-NOBMI-NEXT:    xorl %esi, %eax
; CHECK-NOBMI-NEXT:    andl $16776960, %eax # imm = 0xFFFF00
; CHECK-NOBMI-NEXT:    xorl %esi, %eax
; CHECK-NOBMI-NEXT:    retq
;
; CHECK-BMI-LABEL: in_complex_y0_constmask:
; CHECK-BMI:       # %bb.0:
; CHECK-BMI-NEXT:    movl %edi, %eax
; CHECK-BMI-NEXT:    andl %edx, %esi
; CHECK-BMI-NEXT:    xorl %esi, %eax
; CHECK-BMI-NEXT:    andl $16776960, %eax # imm = 0xFFFF00
; CHECK-BMI-NEXT:    xorl %esi, %eax
; CHECK-BMI-NEXT:    retq
  %y = and i32 %y_hi, %y_low
  %n0 = xor i32 %x, %y
  %n1 = and i32 %n0, 16776960
  %r = xor i32 %n1, %y
  ret i32 %r
}

define i32 @in_complex_y1_constmask(i32 %x, i32 %y_hi, i32 %y_low) {
; CHECK-NOBMI-LABEL: in_complex_y1_constmask:
; CHECK-NOBMI:       # %bb.0:
; CHECK-NOBMI-NEXT:    movl %edi, %eax
; CHECK-NOBMI-NEXT:    andl %edx, %esi
; CHECK-NOBMI-NEXT:    xorl %esi, %eax
; CHECK-NOBMI-NEXT:    andl $16776960, %eax # imm = 0xFFFF00
; CHECK-NOBMI-NEXT:    xorl %esi, %eax
; CHECK-NOBMI-NEXT:    retq
;
; CHECK-BMI-LABEL: in_complex_y1_constmask:
; CHECK-BMI:       # %bb.0:
; CHECK-BMI-NEXT:    movl %edi, %eax
; CHECK-BMI-NEXT:    andl %edx, %esi
; CHECK-BMI-NEXT:    xorl %esi, %eax
; CHECK-BMI-NEXT:    andl $16776960, %eax # imm = 0xFFFF00
; CHECK-BMI-NEXT:    xorl %esi, %eax
; CHECK-BMI-NEXT:    retq
  %y = and i32 %y_hi, %y_low
  %n0 = xor i32 %x, %y
  %n1 = and i32 %n0, 16776960
  %r = xor i32 %y, %n1
  ret i32 %r
}

; ============================================================================ ;
; Negative tests. Should not be folded.
; ============================================================================ ;

; Multi-use tests.

declare void @use32(i32) nounwind

define i32 @in_multiuse_A_constmask(i32 %x, i32 %y, i32 %z) nounwind {
; CHECK-NOBMI-LABEL: in_multiuse_A_constmask:
; CHECK-NOBMI:       # %bb.0:
; CHECK-NOBMI-NEXT:    pushq %rbp
; CHECK-NOBMI-NEXT:    pushq %rbx
; CHECK-NOBMI-NEXT:    pushq %rax
; CHECK-NOBMI-NEXT:    movl %esi, %ebx
; CHECK-NOBMI-NEXT:    movl %edi, %ebp
; CHECK-NOBMI-NEXT:    xorl %esi, %ebp
; CHECK-NOBMI-NEXT:    andl $16776960, %ebp # imm = 0xFFFF00
; CHECK-NOBMI-NEXT:    movl %ebp, %edi
; CHECK-NOBMI-NEXT:    callq use32
; CHECK-NOBMI-NEXT:    xorl %ebx, %ebp
; CHECK-NOBMI-NEXT:    movl %ebp, %eax
; CHECK-NOBMI-NEXT:    addq $8, %rsp
; CHECK-NOBMI-NEXT:    popq %rbx
; CHECK-NOBMI-NEXT:    popq %rbp
; CHECK-NOBMI-NEXT:    retq
;
; CHECK-BMI-LABEL: in_multiuse_A_constmask:
; CHECK-BMI:       # %bb.0:
; CHECK-BMI-NEXT:    pushq %rbp
; CHECK-BMI-NEXT:    pushq %rbx
; CHECK-BMI-NEXT:    pushq %rax
; CHECK-BMI-NEXT:    movl %esi, %ebx
; CHECK-BMI-NEXT:    movl %edi, %ebp
; CHECK-BMI-NEXT:    xorl %esi, %ebp
; CHECK-BMI-NEXT:    andl $16776960, %ebp # imm = 0xFFFF00
; CHECK-BMI-NEXT:    movl %ebp, %edi
; CHECK-BMI-NEXT:    callq use32
; CHECK-BMI-NEXT:    xorl %ebx, %ebp
; CHECK-BMI-NEXT:    movl %ebp, %eax
; CHECK-BMI-NEXT:    addq $8, %rsp
; CHECK-BMI-NEXT:    popq %rbx
; CHECK-BMI-NEXT:    popq %rbp
; CHECK-BMI-NEXT:    retq
  %n0 = xor i32 %x, %y
  %n1 = and i32 %n0, 16776960
  call void @use32(i32 %n1)
  %r = xor i32 %n1, %y
  ret i32 %r
}

define i32 @in_multiuse_B_constmask(i32 %x, i32 %y, i32 %z) nounwind {
; CHECK-NOBMI-LABEL: in_multiuse_B_constmask:
; CHECK-NOBMI:       # %bb.0:
; CHECK-NOBMI-NEXT:    pushq %rbp
; CHECK-NOBMI-NEXT:    pushq %rbx
; CHECK-NOBMI-NEXT:    pushq %rax
; CHECK-NOBMI-NEXT:    movl %esi, %ebx
; CHECK-NOBMI-NEXT:    xorl %esi, %edi
; CHECK-NOBMI-NEXT:    movl %edi, %ebp
; CHECK-NOBMI-NEXT:    andl $16776960, %ebp # imm = 0xFFFF00
; CHECK-NOBMI-NEXT:    callq use32
; CHECK-NOBMI-NEXT:    xorl %ebx, %ebp
; CHECK-NOBMI-NEXT:    movl %ebp, %eax
; CHECK-NOBMI-NEXT:    addq $8, %rsp
; CHECK-NOBMI-NEXT:    popq %rbx
; CHECK-NOBMI-NEXT:    popq %rbp
; CHECK-NOBMI-NEXT:    retq
;
; CHECK-BMI-LABEL: in_multiuse_B_constmask:
; CHECK-BMI:       # %bb.0:
; CHECK-BMI-NEXT:    pushq %rbp
; CHECK-BMI-NEXT:    pushq %rbx
; CHECK-BMI-NEXT:    pushq %rax
; CHECK-BMI-NEXT:    movl %esi, %ebx
; CHECK-BMI-NEXT:    xorl %esi, %edi
; CHECK-BMI-NEXT:    movl %edi, %ebp
; CHECK-BMI-NEXT:    andl $16776960, %ebp # imm = 0xFFFF00
; CHECK-BMI-NEXT:    callq use32
; CHECK-BMI-NEXT:    xorl %ebx, %ebp
; CHECK-BMI-NEXT:    movl %ebp, %eax
; CHECK-BMI-NEXT:    addq $8, %rsp
; CHECK-BMI-NEXT:    popq %rbx
; CHECK-BMI-NEXT:    popq %rbp
; CHECK-BMI-NEXT:    retq
  %n0 = xor i32 %x, %y
  %n1 = and i32 %n0, 16776960
  call void @use32(i32 %n0)
  %r = xor i32 %n1, %y
  ret i32 %r
}

; Various bad variants

define i32 @n0_badconstmask(i32 %x, i32 %y) {
; CHECK-NOBMI-LABEL: n0_badconstmask:
; CHECK-NOBMI:       # %bb.0:
; CHECK-NOBMI-NEXT:    movl %esi, %eax
; CHECK-NOBMI-NEXT:    andl $16776960, %edi # imm = 0xFFFF00
; CHECK-NOBMI-NEXT:    andl $-16776960, %eax # imm = 0xFF000100
; CHECK-NOBMI-NEXT:    orl %edi, %eax
; CHECK-NOBMI-NEXT:    retq
;
; CHECK-BMI-LABEL: n0_badconstmask:
; CHECK-BMI:       # %bb.0:
; CHECK-BMI-NEXT:    movl %esi, %eax
; CHECK-BMI-NEXT:    andl $16776960, %edi # imm = 0xFFFF00
; CHECK-BMI-NEXT:    andl $-16776960, %eax # imm = 0xFF000100
; CHECK-BMI-NEXT:    orl %edi, %eax
; CHECK-BMI-NEXT:    retq
  %mx = and i32 %x, 16776960
  %my = and i32 %y, -16776960 ; instead of -16776961
  %r = or i32 %mx, %my
  ret i32 %r
}

define i32 @n1_thirdvar_constmask(i32 %x, i32 %y, i32 %z) {
; CHECK-NOBMI-LABEL: n1_thirdvar_constmask:
; CHECK-NOBMI:       # %bb.0:
; CHECK-NOBMI-NEXT:    movl %edi, %eax
; CHECK-NOBMI-NEXT:    xorl %esi, %eax
; CHECK-NOBMI-NEXT:    andl $16776960, %eax # imm = 0xFFFF00
; CHECK-NOBMI-NEXT:    xorl %edx, %eax
; CHECK-NOBMI-NEXT:    retq
;
; CHECK-BMI-LABEL: n1_thirdvar_constmask:
; CHECK-BMI:       # %bb.0:
; CHECK-BMI-NEXT:    movl %edi, %eax
; CHECK-BMI-NEXT:    xorl %esi, %eax
; CHECK-BMI-NEXT:    andl $16776960, %eax # imm = 0xFFFF00
; CHECK-BMI-NEXT:    xorl %edx, %eax
; CHECK-BMI-NEXT:    retq
  %n0 = xor i32 %x, %y
  %n1 = and i32 %n0, 16776960
  %r = xor i32 %n1, %z ; instead of %y
  ret i32 %r
}
