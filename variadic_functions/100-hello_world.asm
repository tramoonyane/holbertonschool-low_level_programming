section .data
    message db 'Hello, World', 10  ; 10 is the ASCII code for newline character '\n'
    msg_len equ $ - message         ; Calculate the length of the message

section .text
    global main                    ; Change the entry point label to 'main'

main:                              ; Rename _start to main
    ; Write the message to stdout
    mov rax, 1                     ; System call number for sys_write
    mov rdi, 1                     ; File descriptor 1 (stdout)
    mov rsi, message               ; Pointer to the message
    mov rdx, msg_len               ; Length of the message
    syscall                        ; Perform the system call to write

    ; Exit the program
    mov rax, 60                    ; System call number for sys_exit
    xor rdi, rdi                   ; Return 0 status
    syscall                        ; Perform the system call to exit
