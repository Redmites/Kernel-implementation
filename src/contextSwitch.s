# 1 "src/contextSwitch.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/riscv64-linux-gnu/include/stdc-predef.h" 1 3
# 32 "<command-line>" 2
# 1 "src/contextSwitch.S"
.global _ZN17KernelClassThread13contextSwitchEPNS_7ContextES1_
.type _ZN17KernelClassThread13contextSwitchEPNS_7ContextES1_, @function
_ZN17KernelClassThread13contextSwitchEPNS_7ContextES1_:
    sd ra, 0 * 8(a0)
    sd sp, 1 * 8(a0)

    ld ra, 0 * 8(a1)
    ld sp, 1 * 8(a1)

    ret
