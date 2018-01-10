#pragma once

class TaskObserver {
public:
	virtual void taskFinished(int result) = 0;
};