#ifndef __JOGGLER_HPP__
#define __JOGGLER_HPP__

#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include "task.hpp"

class jogglerTask : public task {
	public:
		jogglerTask(config *cfg);
		~jogglerTask();

		void run();

		void backlightOn();
		void backlightOff();
		void reset();

	private:
		int m_i2c;
        	union i2c_smbus_data smbus_data;
        	struct i2c_smbus_ioctl_data smbus_ioctl_data;
		int m_timer;
		const int m_timeout;
};

#endif//__JOGGLER_HPP__
