#include <iostream>
#include "Chat.h"

const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string PURPLE = "\033[35m";
const std::string CYAN = "\033[36m";

void Chat::startChat()
{
	std::cout << PURPLE << "\n********** ���������� ��� v0.0.1 **********\n\n" << RESET;
	work_ = true;
}

std::shared_ptr <User> Chat::getUserLogin(const std::string& login) const
{
	for (auto& user : userArr_)
	{
		if (login == user.getLogin())
		{
			return std::make_shared<User>(user);
		}
	}
	return nullptr;
}

std::shared_ptr <User> Chat::getUserName(const std::string& name) const
{
	for (auto& user : userArr_)
	{
		if (name == user.getName())
		{
			return std::make_shared<User>(user);
		}
	}
	return nullptr;
}

void Chat::showLoginMenu()
{
	std::cout << CYAN << "\n--- ������� ���� ---\n" << RESET;
	currentUser_ = nullptr;
	char op;
	do
	{
		std::cout << " 1 - ����, 2 - �����������, 0 - �����\n" << GREEN << ">> " << RESET;
		std::cin >> op;

		switch (op)
		{
		case '1':
			userLogin();
			break;
		case '2':
			try
			{
				userRegistration();
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
			break;
		case '0':
			work_ = false;
			break;

		default:
			std::cout << "������� ���������� ������: 1, 2 ��� 0\n";
		}
	} while (!currentUser_ && work_);
}

void Chat::userLogin()
{
	std::string login, password;
	char op;

	do
	{
		std::cout << CYAN << "\n--- ���� � ��� ---\n" << RESET;
		std::cout << "�����: ";
		std::cin >> login;
		std::cout << "������: ";
		std::cin >> password;

		//��������� �� �������� ������������ (nullptr, ���� ����� ������ �����������)
		currentUser_ = getUserLogin(login);

		//�������� ������������ ��������� ������ � ������
		if (currentUser_ == nullptr || password != currentUser_->getPassword())
		{
			currentUser_ = nullptr;
			std::cout << "������� ������ ����� ��� ������. ������� ����� ������ ��� ���������� ��� \"0\" ��� �������� � ��������� ����\n" << GREEN << ">> " << RESET;
			std::cin >> op;

			if (op == '0') { break;	}
		}

	} while (!currentUser_);
}

void Chat::userRegistration()
{
	std::cout << CYAN << "\n--- ����������� ---\n" << RESET;

	std::string login, password, name;

	std::cout << "�����: ";
	std::cin >> login;

	//�������� ������������� ���������� ������
	if (getUserLogin(login) || login == "all")
	{
		throw UserLoginExp();
	}

	std::cout << "������: ";
	std::cin >> password;
	std::cout << "���: ";
	std::cin >> name;

	//�������� ������������� ���������� �����
	if (getUserName(name))
	{
		throw UserNameExp();
	}

	User user = User(login, password, name);
	userArr_.push_back(user);
	currentUser_ = std::make_shared <User>(user);
}

void Chat::showUserMenu()
{
	char op;
	std::cout << "������, " << currentUser_->getLogin();
	while (currentUser_)
	{
		std::cout << "\n1 - �������� ���, 2 - �������� ���������, 3 - �������� ���� �������������, 0 - �����\n" << GREEN << ">> "<< RESET;
		std::cin >> op;

		switch (op)
		{
		case '1':
			showChat();
			break;
		case '2':
			addMessage();
			break;
		case '3':
			showAllUsers();
			break;
		case '0':
			currentUser_ = nullptr;
			break;

		default:
			std::cout << "������� ���������� ������: 1, 2 ��� 3\n";
		}
	}
}

void Chat::addMessage()
{
	std::string to, text;
	std::cout << CYAN << "\n--- �������� ��������� ---\n" << RESET;
	std::cout << "������� ��� ���������� ��� ������� \"all\" ��� �������� ��������� ���� �������������: ";
	std::cin >> to;
	//�������� ������� ���������� �� �����
	if (!((to == "all") || getUserName(to)))
	{
		std::cout << "������! ������ ������� ��� ����������\n";
		return;
	}

	std::cout << "������� ���������: ";
	std::cin.ignore();
	getline(std::cin, text);
	
	if (to == "all")
	{
		messageArr_.push_back(Message{ currentUser_->getLogin(), "all", text });
	}

	else
	{
		messageArr_.push_back(Message{ currentUser_->getLogin(), getUserName(to)->getLogin(), text });
	}
}

void Chat::showChat() const
{
	std::string from, to;
	std::cout << CYAN << "\n--- ������� ��������� ---\n" << RESET;

	for (auto& message : messageArr_)
	{
		//�������� �� ���������� ������� �������� ������������ � ������������/����������� � ���������� ���������� � �������� ������ "all"
		if (currentUser_->getLogin() == message.getFrom() || currentUser_->getLogin() == message.getTo() || message.getTo() != "all")
		{
			from = (currentUser_->getLogin() == message.getFrom()) ? "me" : getUserLogin(message.getFrom())->getName();
		}

		if (message.getTo() == "all")
		{
			to = "(all)";
		}

		else
		{
			to = (currentUser_->getLogin() == message.getTo()) ? "me" : getUserLogin(message.getTo())->getName();
		}

		std::cout << "��: " << from << ", ���: " << to << std::endl;
		std::cout << " ���������: " << message.getText() << std::endl;
	}
	std::cout << CYAN << "\n--- --- ---\n" << RESET;
}

void Chat::showAllUsers() const
{
	std::cout << CYAN << "\n--- ������ ������������� ---\n" << RESET;

	for (auto& user : userArr_)
	{
		std::cout << user.getName();
		if (currentUser_->getLogin() == user.getLogin())
		{
			std::cout << " (me)";
		}
		std::cout << "" << std::endl;
	}
	std::cout << CYAN << "\n--- --- ---\n" << RESET;
}