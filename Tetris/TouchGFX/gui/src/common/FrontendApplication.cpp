#include <gui/common/FrontendApplication.hpp>
#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <gui/common/FrontendHeap.hpp>

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : FrontendApplicationBase(m, heap)
{

}

void FrontendApplication::gotoScreen1ScreenNoTransition()
{
	gotoScreen1Callback = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoScreen1ScreenNoTransitionImpl);
	pendingScreenTransitionCallback = &gotoScreen1Callback;
}

void FrontendApplication::gotoScreen1ScreenNoTransitionImpl()
{
	touchgfx::makeTransition<Screen1View, Screen1Presenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}
