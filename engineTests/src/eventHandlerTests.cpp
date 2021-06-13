#include "eventHandlerTests.h"

TEST(EventHandler, onWindowClose)
{
	Engine::WindowCloseEvent event;
	MockApplication mockApp;

	bool handledBefore = event.isEventHandled();

	auto& onWindowCloseFuncDefault = mockApp.m_handler.getOnWindowCloseCallback();
	onWindowCloseFuncDefault(event);

	bool handledDefault = event.isEventHandled();

	mockApp.setCallback();
	auto& onWindowCloseFunc = mockApp.m_handler.getOnWindowCloseCallback();
	onWindowCloseFunc(event);

	bool handledAfter = event.isEventHandled();

	EXPECT_EQ(handledDefault, false);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledBefore, false);
	EXPECT_EQ(handledAfter, true);
}
