#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/io.h>
#include <unistd.h>

void beep_on(void) {
	iopl(3);
	unsigned char bit;
	bit = inb(0x61) | 0x03 & 0x0f;
	outb(bit, 0x61);
	return;
}


void beep_off(void) {
	iopl(3);
	unsigned char bit;
	bit = inb(0x61) & 0xd;
	outb(bit, 0x61);
	return;
}


int beep(unsigned int sound, unsigned int delay) {
	sound = 1193180000 / sound;
	static int flag = 1, bit;
	if (iopl(3) == -1) {
		printf("iopl: %s\n", strerror(errno));
	}
	
	
	
	beep_on();
	
	outb(0xb6, 0x43);
	outb(sound & 0xff, 0x42);
	outb(sound >> 8, 0x42);
	bit = inb(0x61);
	outb((bit | 0x03) & 0x0f, 0x61);
	
	usleep(10000 * delay);
	
	beep_off();
}

int main(void) {
	while (1) {
		beep(2000, 100);
		beep(2400, 100);
	}
}
