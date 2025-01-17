/* See UNLICENSE file for copyright and license details. */

#include <stdint.h>

static inline void
outb(uint16_t port, uint8_t val)
{
    asm volatile ("outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
    /*
     * there's an outb %al, $imm8 encoding, for compile-time constant port numbers that fit in 8b. (N constraint).
     * wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * the  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type
     */
}

static inline void
outw(uint16_t port, uint16_t val)
{
    asm volatile ("outw %w0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

static inline uint8_t
inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ("inb %w1, %b0" : "=a"(ret) : "Nd"(port) : "memory");
    return ret;
}
