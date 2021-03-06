#include "flashSelectPage.h"

FlashSelectPage::FlashSelectPage(PageManager* manager, char* fileName)
	: TabPage( manager, 3 )
{
    this->fileName = fileName;
    if (fileName[0] == 0x00) // String ends instantly
        this->fileFound = false;
    else
        this->fileFound = true;
}

FlashSelectPage::~FlashSelectPage()
{
    delete this->fileName;
}

void FlashSelectPage::confirm()
{
    switch (this->getTabIndex())
    {
    case 0:
        this->pageManager->changePage(new FlashSelectInitPage(this->pageManager));
        break;
    case 1:
    {
        if (!this->fileFound)
            return;

        // Copy fileName to new memory location so it wont get deleted on deconstruction
        // Will be deleted by flash init.
        char* fileName = new char[SFN_LENGTH];
        memcpy(fileName, this->fileName, SFN_LENGTH);
        this->pageManager->changePage(new FlashInitPage(this->pageManager, fileName));
        break; 
    }
    case 2:
        this->pageManager->changePage(new MainPage(this->pageManager));
        break;
    default:
        break;
    }
}

void FlashSelectPage::initRender(SSD1306Ascii* display)
{
    display->println(F("Select file to Flash"));
    display->println();
    if (this->fileFound)
    {
        display->print(F("/"));
        display->println(this->fileName);
    }
    else
        display->println(F("No more files."));

    display->println();
    display->println(F("  Next file"));
    display->println(F("  Flash file"));

    // Display back button in bottom right
    display->setCursor(DISPLAY_COLUMNS - display->strWidth(back), DISPLAY_ROWS - 1);
    display->print(back);
}

void FlashSelectPage::render(SSD1306Ascii* display)
{
    display->setCursor(0, 4);
    if (this->getTabIndex() == 0)
        display->print(F(">"));
    else
        display->print(F(" "));

    display->setCursor(0, 5);
    if (this->getTabIndex() == 1)
        display->print(F(">"));
    else
        display->print(F(" ")); 
    
    display->setCursor(DISPLAY_COLUMNS - display->strWidth(back), DISPLAY_ROWS - 1);
    if (this->getTabIndex() == 2)
        display->print(F(">"));
    else
        display->print(F(" "));
}
