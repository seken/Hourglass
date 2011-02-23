#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "joggler.hpp"

jogglerTask::jogglerTask(config *cfg) : task(cfg),
        	m_i2c(open("/dev/i2c-0", O_RDWR)),
		m_timer(0),
		m_timeout(300) {

        if (m_i2c < 0) {
                perror("Open i2c bus\n");
                exit(1);
        }
       
        // set slave device to 8051 microprocessor
        if (ioctl(m_i2c, I2C_SLAVE, 0x34)) {
                perror("Set slave i2c address\n");
                exit(1);
        }
       
        // send the initial request
        smbus_data.block[0] = 2; // count of bytes
        smbus_data.block[1] = 0;
        smbus_data.block[2] = 0;
        smbus_ioctl_data.read_write = 0;
        smbus_ioctl_data.command = 0x27;
        smbus_ioctl_data.size = I2C_SMBUS_BLOCK_DATA;
        smbus_ioctl_data.data = &smbus_data;
        if (ioctl(m_i2c, I2C_SMBUS, &smbus_ioctl_data)) {
                perror("Send initial request\n");
                exit(1);
        }
       
        smbus_data.block[0] = 4;
        smbus_ioctl_data.read_write = 1;
}

jogglerTask::~jogglerTask() {
        close(m_i2c);
}

void jogglerTask::run() {

	if ((m_timer++ % m_timeout) != 0) return;

        while(1) {
                if (ioctl(m_i2c, I2C_SMBUS, &smbus_ioctl_data)) {
                        perror("Read result\n");
                        exit(1);
                }
                if (smbus_data.block[1] == 0x87)
                        break;
                usleep(1000);
        }

        if (smbus_data.block[1] != 0x87) {
                fprintf(stderr, "Failed to get response\n");
                exit(1);
        }

        int result =  (smbus_data.block[3] << 8) | smbus_data.block[2];
	
	if (result < 3) {
		backlightOff();
	} else {
		backlightOn();
	}
}

void jogglerTask::backlightOn() {
	system("xset s reset");
	system("xset dpms force on");
}

void jogglerTask::backlightOff() {
	system("xset dpms force off");
}

void jogglerTask::reset() {
	m_timer = 0;
}

