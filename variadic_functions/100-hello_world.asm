section .data
    hello db "Hello, World", 0xA ; '0xA' represents a newline character
    hello_len equ $ - hello

section .text
    global asm_main

asm_main:
    ;; File descriptor for standard output (stdout) is 1
    mov rdi, 1          ; File descriptor: stdout
    mov rsi, hello      ; Message to be printed
    mov rdx, hello_len  ; Length of the message
    mov rax, 1          ; Syscall number for sys_write
    syscall             ; Call kernel

    ;; Exit the program
    mov rax, 60         ; Syscall number for sys_exit
    xor rdi, rdi        ; Exit code 0
    syscall             ; Call kernel
