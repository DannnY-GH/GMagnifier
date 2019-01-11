#include "Windows.h"
#include "magnification.h"
#include <iostream>
#include <string>
using namespace std;

BOOL SetZoom(float magnificationFactor) {
	if (magnificationFactor < 1.0)
		return FALSE;
	int xDlg = (int)((float)GetSystemMetrics(SM_CXSCREEN) * (1.0 - (1.0 / magnificationFactor)) / 2.0);
	int yDlg = (int)((float)GetSystemMetrics(SM_CYSCREEN) * (1.0 - (1.0 / magnificationFactor)) / 2.0);
	return MagSetFullscreenTransform(magnificationFactor, xDlg, yDlg);
}

int main() {
	MagInitialize();
	char userKey;
	float magnificationFactor = 1.5;
	bool mode = false, toggle = false;
	cout << "GMagnifier\n";
	cout << "Enter a Latin Capital Key to bind as Zoom Activate Mode: \n";
	cout << "(M1 or M2 for mouse extra key)\n";
	string s;
	cin >> s;
	if (s == "M1")
		userKey = VK_XBUTTON1;
	else if (s == "M2")
		userKey = VK_XBUTTON2;
	else
		userKey = s[0];
	cout << "Now in ZAM you can adjust magnification factor by +/- and this factor will be saved after ZAM triggering... \nGood Luck ;)\n";
	while (true) {
		if ((GetAsyncKeyState(userKey) < 0) && !toggle) {
			SetZoom((!mode) ? magnificationFactor : 1);
			mode = !mode;
			cout << ((mode) ? "Activated\n" : "Dectivated\n");
			toggle = true;
		}
		if ((GetAsyncKeyState(VK_OEM_PLUS) < 0)) {
			if (mode) {
				magnificationFactor += 0.5;
				if (magnificationFactor > 15)
					magnificationFactor = 15;
				SetZoom(magnificationFactor);
			}
		}
		if ((GetAsyncKeyState(VK_OEM_MINUS) < 0)) {
			if (mode) {
				magnificationFactor -= 0.5;
				if (magnificationFactor < 1)
					magnificationFactor = 1;
				SetZoom(magnificationFactor);
			}
		}
		if (!(GetKeyState(userKey) < 0)) {
			toggle = false;
		}
		Sleep(50);
	}
	return 0;
}