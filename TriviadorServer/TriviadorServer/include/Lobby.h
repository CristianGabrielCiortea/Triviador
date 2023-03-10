#pragma once
#include "Player.h"
#include <vector>
#include <array>
#include <random>
#include <chrono>

class Lobby
{
public:
	Lobby();
	Lobby(const Lobby& lobby);
	Lobby(const Player& player);
	~Lobby();

	Lobby& operator=(const Lobby& lobby);

	void AddPlayer(const Player& player);
	bool RemovePlayer(const std::string& username);
	void ClearLobby();


	//Getters
	const Player& GetPlayerAt(int index) const;
	int GetNumberOfPlayers();
	int GetLobbyID() const;
	const std::vector<Player>& GetPlayers();
	const std::chrono::system_clock::time_point& GetExpirationTime() const;
	bool IsActiveGame() const;
	bool IsInLobby(const std::string& username) const;
	bool HadExpired() const;

	//Setters
	void SetIsActiveGame(bool activeGame);
	void SetPlayers(const std::vector<Player>& players);

private:
	void SetAvailableColors();

	std::vector<Player> m_players;
	int m_lobbyId = INT_MAX;
	uint32_t GenerateRandomLobbyID();
	std::chrono::system_clock::time_point m_expirationTime;
	static const size_t kNumberOfColors = 4;
	std::vector<int> m_availableColors;
	bool m_isActiveGame = false;
};

