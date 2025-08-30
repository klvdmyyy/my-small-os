;; -*- mode: nasm; -*-

global lgdt

lgdt:
	mov eax, [esp + 4]
	lgdt [eax]
	ret
