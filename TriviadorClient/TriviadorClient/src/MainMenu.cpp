#include "MainMenu.h"

MainMenu::MainMenu(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_user.SetUsername("No name");
	m_user.SetId(-1);
}

MainMenu::MainMenu(const User& user, QWidget* parent) :
	QWidget(parent),
	m_user(user)
{
	ui.setupUi(this);
}

MainMenu::~MainMenu()
{
	// empty
}

void MainMenu::hiMessage(const std::string& playerName)
{
	QString message = "Salut, ";
	message += playerName.c_str();
	ui.hiMessage->setText(message);
}

bool MainMenu::CheckGameCanStart()
{
	auto res = cpr::Put
	(
		cpr::Url{ "http://localhost:18080/newgame" }
	);
	return res.status_code == 200;
}

void MainMenu::StartGame(std::vector<Player>& players)
{
	m_game = new Game(players, this);
	m_game->show();
	hide();
	connect(m_game, SIGNAL(finished()), this, SLOT(on_gameFinished()));
}

void MainMenu::StartLobby(std::string lobbyID)
{
	m_lobby = new Lobby(lobbyID, m_user.GetUsername());
	m_lobby->show();
	hide();
	connect(m_lobby, SIGNAL(finished()), this, SLOT(on_lobbyFinished()));
}

void MainMenu::Show()
{
	showMaximized();
}

void MainMenu::on_myProfileButton_clicked() const
{
	this->ui.stackedWidget->setCurrentWidget(ui.myProfile);
}

void MainMenu::on_creditsButton_clicked() const
{
	this->ui.stackedWidget->setCurrentWidget(ui.credits);
}

void MainMenu::on_playButton_clicked() const
{
	this->ui.stackedWidget->setCurrentWidget(ui.play);
}

void MainMenu::on_joinGameButton_clicked() const
{
	this->ui.stackedWidget->setCurrentWidget(ui.joinGame);
}

void MainMenu::on_joinLobbyButton_clicked()
{
	std::string lobbyId = this->ui.lineEdit->text().toUtf8().constData();
	auto res = cpr::Put
	(
		cpr::Url{ "http://localhost:18080/addplayertolobby" },
		cpr::Body{ "id=" + lobbyId + "&" + "username=" + m_user.GetUsername() }
	);

	if (res.status_code == 200)
	{
		StartLobby(lobbyId);
	}
	else if (res.status_code == 401)
	{
		QMessageBox msgBox;
		msgBox.setText("Lobby is full");
		msgBox.exec();
	}
	else if (res.status_code == 400)
	{
		QMessageBox msgBox;
		msgBox.setText("Lobby not found");
		msgBox.exec();
	}
}

void MainMenu::on_createGameButton_clicked() const
{
	this->ui.stackedWidget->setCurrentWidget(ui.createGame);
}

void MainMenu::on_createButton_clicked() 
{
	auto res = cpr::Get
	(
		cpr::Url{ "http://localhost:18080/newlobby" },
		cpr::Body{ "username=" + m_user.GetUsername() }
	);

	try
	{
		auto id = crow::json::load(res.text);
		int lobbyId = id["lobby_id"].i();

		StartLobby(std::to_string(lobbyId));
	}
	catch(std::exception ex)
	{
		qDebug() << "Can't create new lobby";
	}
}

void MainMenu::on_backButton_clicked()
{
	this->ui.stackedWidget->setCurrentWidget(ui.play);
}

void MainMenu::on_logOutButton_clicked()
{
	close();
	Registration* registration = new Registration;
	registration->show();

	qDebug() << "Log Out button clicked";
}

void MainMenu::on_twoPlayersButton_clicked()
{
	Player a("cristian", Player::Color::Blue);
	Player b("tibi", Player::Color::Red);
	std::vector<Player> players = { a, b };

	if (CheckGameCanStart())
	{
		StartGame(players);
	}
}

void MainMenu::on_threePlayersButton_clicked()
{
	Player a("cristian", Player::Color::Blue);
	Player b("tibi", Player::Color::Red);
	Player c("adi", Player::Color::Yellow);
	std::vector<Player> players = { a, b, c };

	if (CheckGameCanStart())
	{
		StartGame(players);
	}

}

void MainMenu::on_fourPlayersButton_clicked()
{
	Player a("cristian", Player::Color::Blue);
	Player b("tibi", Player::Color::Red);
	Player c("adi", Player::Color::Yellow);
	Player d("andrei", Player::Color::Green);
	std::vector<Player> players = { a, b, c, d };

	if (CheckGameCanStart())
	{
		StartGame(players);
	}
}

void MainMenu::on_lobbyFinished()
{
	Show();
	m_lobby->close();
	delete m_lobby;
}

void MainMenu::on_gameFinished()
{
	Show();
	m_game->close();
	delete m_game;
}