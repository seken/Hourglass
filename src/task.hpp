#ifndef __TASK_HPP__
#define __TASK_HPP__

#include "config.hpp"

class task {
	public:
		task(config *cfg);
		~task();

		virtual void run()=0;
};

#endif//__TASK_HPP__
