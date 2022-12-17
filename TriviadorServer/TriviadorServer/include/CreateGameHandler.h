#include <unordered_map>
#include "Game.h"
#include <crow.h>
#include "utils.h"
struct CreateGameHandler
{
public:
	CreateGameHandler() = delete;
	CreateGameHandler(std::unordered_map<int32_t, Game> gamesOngoing);
	crow::response operator()(const crow::request& req) const;
private:
	std::unordered_map<int32_t, Game>& m_gamesOngoing;
};