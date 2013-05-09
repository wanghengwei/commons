#include "stdafx.h"
#include "MainWindow.h"

using namespace std;

MainWindow::MainWindow(HINSTANCE app_inst) : Window(app_inst, L"MainWindow", L"sample_main_window"), Widget(""), mPointer(new MousePointer(this))
{
	//添加一个特殊的Widget：鼠标指针
	add(mPointer);

	//设置初始状态
	mState.Background = Color::Blue;

	Height(Window::GetHeight());
	Width(Window::GetWidth());
}
