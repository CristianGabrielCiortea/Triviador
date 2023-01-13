#include "Player.h"

std::string Player::ToString(Color color)
{
	switch (color)
	{
	case Color::Blue:
		return "Blue";
		break;
	case Color::Green:
		return "Green";
		break;
	case Color::Red:
		return "Red";
		break;
	case Color::Yellow:
		return "Yellow";
		break;
	default:
		return "None";
	}
}

Player::Color Player::ToColor(std::string color)
{
	if (color == "Red")
	{
		return Color::Red;
	}
	else if (color == "Green")
	{
		return Color::Green;
	}
	else if (color == "Blue")
	{
		return Color::Blue;
	}
	else if (color == "Yellow")
	{
		return Color::Yellow;
	}
	return Color::None;
}

Player::Player(const std::string& playerName, const Color& color) :
	m_playerName(playerName), m_color(color), m_score(0)
{
	// empty
}

Player::Player(const Player& other)
{
	*this = other;
}

Player::Player(Player&& other) noexcept
{
	*this = std::move(other);
}

const std::string& Player::GetName() const
{
	return m_playerName;
}

Player::Color Player::GetColor() const
{
	return m_color;
}

uint16_t Player::GetScore() const
{
	return m_score;
}

uint16_t Player::GetRank() const
{
	return m_rank;
}
//
//std::vector<std::reference_wrapper<Territory>> Player::GetOwnedTerritories() const
//{
//	return m_ownedTerritories;
//}
//
//std::vector<std::reference_wrapper<Territory>>& Player::GetOwnedTerritories()
//{
//	return m_ownedTerritories;
//}

void Player::SetName(const std::string& name)
{
	this->m_playerName = name;
}

void Player::SetColor(const Player::Color& color)
{
	this->m_color = color;
}

void Player::SetScore(const uint16_t& score)
{
	this->m_score = score;
}

void Player::SetRank(const uint16_t& rank)
{
	m_rank = rank;
}

void Player::AddScore(uint16_t score)
{
	this->m_score += score;
}

//void Player::AddTerritory(Territory& territory)
//{
//	m_ownedTerritories.push_back(territory);
//}
//
//void Player::RemoveTerritory(Territory& territory)
//{
//	const auto it = std::find(m_ownedTerritories.begin(), m_ownedTerritories.end(), territory);
//	if (it != m_ownedTerritories.end())
//	{
//		m_ownedTerritories.erase(it);
//	}
//}

Player& Player::operator=(const Player& other)
{
	if (this != &other)
	{
		this->m_score = other.m_score;
		this->m_color = other.m_color;
		this->m_playerName = other.m_playerName;
	}
	return *this;
}

Player& Player::operator=(Player&& other) noexcept
{
	if (this != &other)
	{
		m_playerName = std::exchange(other.m_playerName, std::string());
		m_color = std::exchange(other.m_color, Player::Color::None);
		m_score = std::exchange(other.m_score, 0);
	}
	return *this;
}

bool Player::operator<(const Player& other)
{
	return this->m_score < other.m_score;
}
