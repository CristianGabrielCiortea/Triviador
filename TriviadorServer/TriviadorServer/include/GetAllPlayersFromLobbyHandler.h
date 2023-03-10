#pragma once
#include <crow.h>
#include "utils.h"
#include "Lobby.h"
#include <nlohmann/json.hpp>

class GetAllPlayersFromLobbyHandler
{
public:
	GetAllPlayersFromLobbyHandler(Lobby& lobby);
	crow::response operator()(const crow::request& req) const;

private:
	Lobby& m_lobby;
};