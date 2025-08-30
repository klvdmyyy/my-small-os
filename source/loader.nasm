;; -*- mode: nasm; -*-

global __start					; Это определение точки входа
global _lgdt
extern kernel_main				; Вызываем C функцию
	
	;; Некоторые константы, объяснение которых здесь должно появиться
	;; позже.
	MBALIGN			  equ 1<<0
	MEMINFO			  equ 1<<1
	MAGIC_NUMBER	  equ 0x1BADB002
	MBFLAGS			  equ 0 | MBALIGN | MEMINFO
	CHECKSUM		  equ -(MAGIC_NUMBER + MBFLAGS)
	KERNEL_STACK_SIZE equ 4096

bits 32

section .multiboot
align 4
	dd MAGIC_NUMBER
	dd MBFLAGS
	dd CHECKSUM

	
;; Секция .bss нужна для создания неинициализированных данных. (Пустых или zeroed data)
;;
;; Самое то чтобы сделать пока что пустой стэк для ядра.
section .bss
align 16
kernel_stack:
	resb KERNEL_STACK_SIZE


;; Как я смог понять, секция .text нужна для определения исполняемого кода программы.
;; Т.е именно отсюда будет запускаться ядро и всякая прочая шелупонь
section .text
__start:
	mov esp, kernel_stack + KERNEL_STACK_SIZE

	call kernel_main
	cli
	hlt
	jmp 1b

_lgdt:
	mov eax, [esp + 4]
	lgdt [eax]
	ret
