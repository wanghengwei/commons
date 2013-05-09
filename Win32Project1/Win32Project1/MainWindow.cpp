#include "stdafx.h"
#include "MainWindow.h"

using namespace std;

MainWindow::MainWindow(HINSTANCE app_inst) : Window(app_inst, L"MainWindow", L"sample_main_window"), Widget(""), mPointer(new MousePointer(this))
{
	//���һ�������Widget�����ָ��
	add(mPointer);

	//���ó�ʼ״̬
	mState.Background = Color::Blue;

	Height(Window::GetHeight());
	Width(Window::GetWidth());
}
