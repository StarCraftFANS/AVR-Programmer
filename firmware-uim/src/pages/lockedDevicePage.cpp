#include "lockedDevicePage.h"

LockedDevicePage::LockedDevicePage(PageManager* manager, byte s1, byte s2, byte s3)
	: Page(manager)
{
	this->b1 = s1;
	this->b2 = s2;
	this->b3 = s3;
}

void LockedDevicePage::confirm()
{
	this->pageManager->changePage(new MainPage(this->pageManager));
}

void LockedDevicePage::initRender(SSD1306Ascii* display)
{
	display->println(F("Device locked."));

	// Display HEX signature
	display->print(F("HEX: "));
	DisplayUtils::printHex(display, this->b1);
	display->print(F(", "));
	DisplayUtils::printHex(display, this->b2);
	display->print(F(", "));
	DisplayUtils::printHex(display, this->b3);
	display->println();

	// Display back button in bottom right
	const char* back = "> Back";
	display->setCursor(DISPLAY_COLUMNS - display->strWidth(back), DISPLAY_ROWS - 1);
	display->print(back);
}
