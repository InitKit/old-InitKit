#define Uses_TApplication
#define Uses_TDeskTop
#define Uses_TMenuBar
#define Uses_TKeys
#define Uses_TSubMenu
#define Uses_TMenuItem
#define Uses_TStatusLine
#define Uses_TStatusItem
#define Uses_TStatusDef
#define Uses_TWindow

#include <tvision/tv.h>

class TSystemStatus;

class TInitAdm : public TApplication {
	TSystemStatus *winSysStat;

    public:
	TInitAdm();

	virtual void handleEvent(TEvent &event);
	static TMenuBar *initMenuBar(TRect);
	static TStatusLine *initStatusLine(TRect);
};

class TSystemStatus : public TWindow {
    public:
	TSystemStatus(TRect bounds);
};

TInitAdm::TInitAdm()
	: TProgInit(&TInitAdm::initStatusLine, &TInitAdm::initMenuBar,
		    &TInitAdm::initDeskTop)
{
	deskTop->insert(winSysStat = new TSystemStatus(
				{ 2, 1, deskTop->getBounds().b.x - 3,
				  deskTop->getBounds().b.y - 3 }));
}

void
TInitAdm::handleEvent(TEvent &event)
{
	TApplication::handleEvent(event);
	if (event.what == evCommand) {
		switch (event.message.command) {
		default:
			break;
		}
	}
}

TMenuBar *
TInitAdm::initMenuBar(TRect r)
{
	r.b.y = r.a.y + 1;

	return new TMenuBar(r, *new TSubMenu("~H~ello", kbAltH) + newLine() +
				       *new TMenuItem("E~x~it", cmQuit, cmQuit,
						      hcNoContext, "Alt-X"));
}

TStatusLine *
TInitAdm::initStatusLine(TRect r)
{
	r.a.y = r.b.y - 1;
	return new TStatusLine(r, *new TStatusDef(0, 0xFFFF) +
					  *new TStatusItem("~Alt-X~ Exit",
							   kbAltX, cmQuit) +
					  *new TStatusItem(0, kbF10, cmMenu));
}

TSystemStatus::TSystemStatus(TRect bounds)
	: TWindow(bounds, "System Status", 0), TWindowInit(initFrame)
{
}

int
main(int argc, char *argv[])
{
	TInitAdm initadm;
	initadm.run();
}