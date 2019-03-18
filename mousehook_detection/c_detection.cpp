#include "detection.h"

LRESULT CALLBACK mouse_callback( int code, WPARAM param, LPARAM l_param ) {
	PMSLLHOOKSTRUCT p_mouse = reinterpret_cast<PMSLLHOOKSTRUCT>( l_param );
	static int found_count;
	if ( code == HC_ACTION && p_mouse != nullptr && p_mouse->flags == LLMHF_INJECTED ) {
		switch ( param ) {
		case WM_LBUTTONDOWN:
			++found_count;
			printf( "Autoclicking with left button found. LVL: %i\n", found_count);
			return -1;
			break;
		case WM_RBUTTONDOWN:
			++found_count;
			printf("Autoclicking with right button found. LVL: %i\n", found_count);
			return -1;
			break;
		}
	}
	return CallNextHookEx( detect::get( ).mouse_hook, code, param, l_param );
}

auto hooking( ) {
	detect::get( ).mouse_hook = SetWindowsHookEx( WH_MOUSE_LL, &mouse_callback, NULL, NULL );
	MSG msg;
	while ( GetMessage( &msg, NULL, 0, 0 ) ) {
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
	UnhookWindowsHookEx( detect::get( ).mouse_hook );
}

void detect::run_check( ) {
	CreateThread( NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>( &hooking ), NULL, 0, 0 );
}