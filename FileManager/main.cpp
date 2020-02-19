#include "memu.h"
#include "FileManager.h"

int main() {
	while (1) {
		menu m;
		char c = m.init();
		m.press(c);
		char ch = m.deletOptions();
		m.deletPress(ch);
		system("cls");
	}

	return 0;
}