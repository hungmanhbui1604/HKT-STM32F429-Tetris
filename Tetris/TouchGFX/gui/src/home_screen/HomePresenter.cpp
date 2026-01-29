#include <gui/home_screen/HomeView.hpp>
#include <gui/home_screen/HomePresenter.hpp>

HomePresenter::HomePresenter(HomeView& v)
    : view(v)
{

}

void HomePresenter::activate()
{

}

void HomePresenter::deactivate()
{

}

void HomePresenter::gotoGame()
{
    static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen1ScreenNoTransition();
}
