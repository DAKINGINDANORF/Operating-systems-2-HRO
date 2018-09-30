/*
 * Tommie Terhoeve 0926280 TI3B Eindopdracht
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "string.h"
#include "uart.h"

// Maximum number of memory frames
#define MEMORYSIZE	64

// Memory frame , containing starting address, size of frame, if the frame is in used
struct frame {
	void	*addr;
	size_t	size;
	bool	used;
};

// Frame array with 64 frame places 
static struct frame table[MEMORYSIZE];

// A pointer that defines the end of the kernel
#if 0
extern void *__end;
static void *_end = &__end;
#else
static void *_end = (void *) 0x400000;
#endif

// Sorts the frames in the right address order
static void frames_sort(void)
{
	struct frame temp;
	size_t i, j;

	// For every i, check if its greater than every j in the array
	for (i = 0; i < MEMORYSIZE; i++) {
		for (j = i + 1; j < MEMORYSIZE; j++) {
			// Swap frames if i adddress is greater than j address
			if (table[j].addr && table[i].addr > table[j].addr) {
				temp = table[i];
				table[i] = table[j];
				table[j] = temp;
			}
		}
	}
}

static struct frame *frame_alloc(void)
{
	// Goes through array, returns pointer if the address is null.
	for (size_t i = 0; i < MEMORYSIZE; i++)
		if (!table[i].addr)
			return &table[i];

	return NULL;
}

// Allocates N bytes , returns "generic" pointer to starting address
void *malloc(size_t n)
{
	struct frame *f;
	void *addr;
	size_t i;

	if (!n)
		return NULL;

	frames_sort();

	// Search for a big enough gap
	for (size_t j = 0; j < MEMORYSIZE; j++) {
		// If the space in the array can't be used for this frame (In use or frame too small)
		if (table[j].used || table[j].size < n)
			continue;

		// If there is enough space and the frame isnt allocated
		if (table[j].size - n > 0 && (f = frame_alloc())) {
			// Initialise frame;
			f->addr = table[j].addr + n;
			f->size = table[j].size - n;
			f->used = false;

			table[j].size = n;
		}

		table[j].used = true;
		return table[j].addr;
	}

	// Go through every frame till the table[i].addr is null
	for (i = 0; i < MEMORYSIZE && table[i].addr; i++);
	// Set the address to the last frame address + the size of that frame
	i--;
	addr = table[i].addr + table[i].size;

	// If there is no free array entry, return null
	if (!(f = frame_alloc()))
		return NULL;

	// If the address space isnt initialised yet, place it at the end of the kernel space
	if (!addr)
		addr = _end;

	// Allocate the frame
	f->addr = addr;
	f->size = n;
	f->used = true;

	// Returns the pointer
	return addr;
}

// Sets matching entry.used to false in array
void free(void *ptr)
{
	size_t i;

	// If the pointer doesnt exist, return
	if (!ptr)
		return;

	// Goes through array, sets matching array entry to used = false
	for (i = 0; i < MEMORYSIZE; i++) {
		if (table[i].addr == ptr) {
			table[i].used = false;
			return;
		}
	}
}

// Reallocates memory space, alters the size to N
void *realloc(void *ptr, size_t n)
{
	void *newptr;
	size_t i;

	// Tries to allocate N amount of bytes, if malloc fails frees frame returns null
	if (!(newptr = malloc(n))) {
		free(ptr);
		return NULL;
	}

	// If parameter is null, returns the new pointer
	if (!ptr)
		return newptr;

	// Go through array
	for (i = 0; i < MEMORYSIZE; i++) {
		// If the table entry addr matches ptr
		if (table[i].addr == ptr) {
			// Copies content of ptr to newptr
			memmove(newptr, ptr, table[i].size);
			// Free the old ptr space
			free(ptr);

			return newptr;
		}
	}

	return NULL;
}


void *calloc(size_t n, size_t m)
{
	void *ptr;

	// If malloc can't t find a memory space the size of n*m, return null
	if (!(ptr = malloc(n * m)))
		return NULL;


	for (size_t i = 0; i < n + m; i++)
		// Sets memory to 0
		((unsigned char *) ptr)[i] = 0;

	return ptr;
}

// Execute testing
void main()
{
	uart_init();
	uart_puts(" Tommie Terhoeve 0926280 Kernel\n");
	char * str;
	if (!(str = malloc(69)))
		uart_puts(" out of memory\n");
	uart_puts("Malloc works \n ");
	if (!(str = realloc(str, 69))) {
		uart_puts("out of memory\n");
		return;
	}
	uart_puts("Realloc works\n");
	strcpy(str, " The quick brown fox jumps over the lazy dog");
	uart_puts(str);
	free(str);
}
