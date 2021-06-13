#include "eventTests.h"

TEST(EventTests, ResizeConstructor)
{
	Engine::WindowResizeEvent event(800, 600);

	int32_t width_1 = event.getWidth();
	int32_t height_1 = event.getHeight();

	auto windowSize = event.getWindowSize();
	int32_t width_2 = windowSize.x;
	int32_t height_2 = windowSize.y;

	int32_t category = event.getCategoryFlag();
	Engine::EventType type = event.getEventType();
	Engine::EventType staticType = event.getStaticType();
	

	EXPECT_EQ(width_1, 800);
	EXPECT_EQ(width_2, 800);
	EXPECT_EQ(height_1, 600);
	EXPECT_EQ(height_2, 600);

	EXPECT_EQ(category, Engine::EventCategory::EventCategoryWindow);
	EXPECT_TRUE(event.isEventInCategory(Engine::EventCategory::EventCategoryWindow));

	EXPECT_EQ(type, staticType);
	EXPECT_EQ(type, Engine::EventType::WindowResize);
}
