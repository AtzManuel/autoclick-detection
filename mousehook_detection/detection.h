#pragma once
#include "singleton.h"
#include <Windows.h>
#include <iostream>

class detect : public singleton<detect> {
public:
	HHOOK mouse_hook;
	void run_check( );

};