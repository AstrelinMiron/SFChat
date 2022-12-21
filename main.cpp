#include <iostream>
#include "Chat.h"
#include <Windows.h>

int main()
{
	//Кодировка для вывода кирилицы на экран
	SetConsoleCP(1251);
	setlocale(LC_ALL, "");

	Chat chat;
	chat.startChat();

	while (chat.work())
	{
		chat.showLoginMenu();
		while (chat.getCurrentUser())
		{
			chat.showUserMenu();
		}
	}
	return 0;
}
