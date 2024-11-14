#include "hnm.h"

/**
 * swap16 - Swaps the bytes of a 16-bit unsigned integer
 *
 * @val: value to be swapped
 *
 * Return: Byte-swapped value
 */
uint16_t swap16(uint16_t val)
{
	return ((val << 8) | (val >> 8));
}

/**
 * swap32 - Swaps the bytes of a 32-bit unsigned integer
 *
 * @val: value to be swapped
 *
 * Return: Byte-swapped value
 */
uint32_t swap32(uint32_t val)
{
	return (((val << 24) & 0xFF000000) |
		   ((val << 8) & 0x00FF0000) |
		   ((val >> 8) & 0x0000FF00) |
		   ((val >> 24) & 0x000000FF));
}

/**
 * swap64 - Swaps the bytes of a 64-bit unsigned integer
 *
 * @val: value to be swapped
 *
 * Return: Byte-swapped value
 */
uint64_t swap64(uint64_t val)
{
	return (((val << 56) & 0xFF00000000000000ULL) |
		   ((val << 40) & 0x00FF000000000000ULL) |
		   ((val << 24) & 0x0000FF0000000000ULL) |
		   ((val << 8) & 0x000000FF00000000ULL) |
		   ((val >> 8) & 0x00000000FF000000ULL) |
		   ((val >> 24) & 0x0000000000FF0000ULL) |
		   ((val >> 40) & 0x000000000000FF00ULL) |
		   ((val >> 56) & 0x00000000000000FFULL));
}
