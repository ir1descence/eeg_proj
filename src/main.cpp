#include "test.h"
#include "ui/mainWindow.h"
#include <AUI/Platform/Entry.h>
#include <AUI/i18n/AI18n.h>
#include <AUI/ASS/AStylesheet.h>

AUI_ENTRY
{
    auto w = _new<MainWindow>();
    w->show();
    return 0;
}