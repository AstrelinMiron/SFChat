#pragma once
#include <vector>
#include <exception>
#include<memory>
#include "Message.h"


struct UserLoginExp : public std::exception
{
	const char* what() const noexcept override 	{ return "����� ��� �����������, ������� ������ �������"; }
};

struct UserNameExp : public std::exception
{
	const char* what() const noexcept override { return "��� ��� ������������, ������� ������ �������"; }
};

class Chat
{
private:
	//������ �������������
	std::vector <User> userArr_;
	//������ ���������
	std::vector <Message> messageArr_;
	//����� ��������� �� �������� ������������
	std::shared_ptr <User> currentUser_ = nullptr;
	bool work_ = false;

	//���� � ��� �� ������ � ������
	void userLogin();
	//����������� � ����
	void userRegistration();
	//���������� ������� ���������
	void showChat() const;
	//���������� ������ �������������
	void showAllUsers() const;
	//�������� ���������
	void addMessage();

	//���������� ����� ��������� �� ���������� ������������ �� ������, ���� �� ���� � ���� ������������� ��� nullptr ���� ���
	std::shared_ptr <User> getUserLogin(const std::string& login) const;
	//���������� ����� ��������� �� ���������� ������������ �� �����, ���� �� ���� � ���� ������������� ��� nullptr ���� ���
	std::shared_ptr <User> getUserName(const std::string& name) const;

public:
	//������ ����
	void startChat();
	//������� ���� ����
	void showLoginMenu();
	//���� ����
	void showUserMenu();
	//����� ��� ��������� ���� � �������� ��������� 
	bool work() const { return work_; }
	//���������� ����� ��������� �� �������� ������������
	std::shared_ptr <User> getCurrentUser() const { return currentUser_; }
};