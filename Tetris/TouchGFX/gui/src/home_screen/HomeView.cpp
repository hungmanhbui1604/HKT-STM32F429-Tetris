#include <gui/home_screen/HomeView.hpp>
#include <cmsis_os2.h>

extern "C" {
    extern osMessageQueueId_t myQueue01Handle;
}

extern uint16_t highestScore;

HomeView::HomeView()
{
	Unicode::snprintf(highScoreTextBuffer, HIGHSCORETEXT_SIZE, "%u", highestScore);
}

void HomeView::setupScreen()
{
    HomeViewBase::setupScreen();
}

void HomeView::tearDownScreen()
{
    HomeViewBase::tearDownScreen();
}

void HomeView::handleTickEvent()
{
    if (osMessageQueueGetCount(myQueue01Handle) > 0)
    {
        uint8_t res;
        osMessageQueueGet(myQueue01Handle, &res, NULL, 0);

        if (res == 'M')
        {
            presenter->gotoGame();
        }
    }
}
