#pragma once
#include <vector>
#include <exception>
#include<memory>
#include "Message.h"


struct UserLoginExp : public std::exception
{
	const char* what() const noexcept override 	{ return "Логин уже использован, введите другой вариант"; }
};

struct UserNameExp : public std::exception
{
	const char* what() const noexcept override { return "Имя уже использовано, введите другой вариант"; }
};

class Chat
{
private:
	//Массив пользователей
	std::vector <User> userArr_;
	//Массив сообщений
	std::vector <Message> messageArr_;
	//Умный указатель на текущего пользователя
	std::shared_ptr <User> currentUser_ = nullptr;
	bool work_ = false;

	//Вход в чат по логину и паролю
	void userLogin();
	//Регистрация в чате
	void userRegistration();
	//Возвращает историю сообщений
	void showChat() const;
	//Возвращает список пользователей
	void showAllUsers() const;
	//Отправка сообщения
	void addMessage();

	//Возвращает умный указатель на требуемого пользователя по логину, если он есть в базе пользователей или nullptr если нет
	std::shared_ptr <User> getUserLogin(const std::string& login) const;
	//Возвращает умный указатель на требуемого пользователя по имени, если он есть в базе пользователей или nullptr если нет
	std::shared_ptr <User> getUserName(const std::string& name) const;

public:
	//Запуск чата
	void startChat();
	//Главное меню чата
	void showLoginMenu();
	//Меню чата
	void showUserMenu();
	//Метод для удержания чата в открытом состоянии 
	bool work() const { return work_; }
	//Возвращает умный указатель на текущего пользователя
	std::shared_ptr <User> getCurrentUser() const { return currentUser_; }
};