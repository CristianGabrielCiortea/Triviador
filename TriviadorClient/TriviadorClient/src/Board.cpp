#include "Board.h"

Board::Board()
	: m_width(0)
	, m_height(0)
	, m_size(0)
	//, m_board(m_size, Territory())
{
	// empty
}

Board::Board(const std::size_t& height, const std::size_t& width, QWidget* parent)
	: m_height(height)
	, m_width(width)
	, m_size(m_width * m_height)
	, m_board(m_size, Territory(parent))
{
	// empty
}

Board::Board(const Board& other)
{
	*this = other;
}

Board::Board(Board&& other) noexcept
{
	*this = std::move(other);
}

Board::~Board() {
	// empty
}

Territory Board::operator[](int pos) const
{
	if (pos < 0 || pos >= m_board.size())
	{
		throw std::out_of_range("Position is out of range!");
	}
	return m_board[pos];
}

Territory& Board::operator[](int pos)
{
	if (pos < 0 || pos >= m_board.size())
	{
		throw std::out_of_range("Position is out of range!");
	}
	return m_board[pos];
}

Board& Board::operator=(const Board& other)
{
	this->m_board = other.m_board;
	this->m_height = other.m_height;
	this->m_width = other.m_width;
	return *this;
}

Board& Board::operator=(Board&& other) noexcept
{
	this->m_board = std::move(other.m_board);
	this->m_height = std::move(other.m_height);
	this->m_width = std::move(other.m_width);
	new(&other) Board;
	return *this;
}

void Board::Set2PGame()
{
	SetGeometry2PGame();
	SetMasks(2);
}

void Board::Set3PGame()
{
	SetGeometry3PGame();
	SetMasks(3);
}

void Board::Set4PGame()
{
	SetGeometry4PGame();
	SetMasks(4);
}

int Board::Size()
{
	return m_board.size();
}

void Board::SetMasks(int playersNumber)
{
	QString imageLocation = "../TriviadorClient/resource/map";
	switch (playersNumber)
	{
	case 2:
		imageLocation += QString::number(2);
		break; 
	case 3:
		imageLocation += QString::number(3);
		break;
	case 4:
		imageLocation += QString::number(4);
		break;
	default:
		break;
	}
	imageLocation += "players/";
	for (size_t line = 0; line < m_height; line++)
	{
		for (size_t column = 0; column < m_width; column++)
		{
			QString auxLocation = imageLocation;
			auxLocation += QString::number(line) + QString::number(column) + ".png";
			m_board[line * m_width + column].SetMask(QPixmap(auxLocation));
		}
	}
}

void Board::SetGeometry2PGame()
{
	m_board[0].SetGeometry(357, 155, 341, 232);
	m_board[1].SetGeometry(610, 172, 218, 220);
	m_board[2].SetGeometry(802, 133, 245, 255);
	m_board[3].SetGeometry(228, 332, 377, 214);
	m_board[4].SetGeometry(576, 364, 254, 193);
	m_board[5].SetGeometry(794, 352, 253, 203);
	m_board[6].SetGeometry(283, 502, 450, 276);
	m_board[7].SetGeometry(586, 522, 300, 264);
	m_board[8].SetGeometry(805, 518, 396, 254);
}

void Board::SetGeometry3PGame()
{
	m_board[0].SetGeometry(357, 155, 341, 232);
	m_board[1].SetGeometry(610, 172, 218, 220);
	m_board[2].SetGeometry(802, 133, 245, 255);
	m_board[3].SetGeometry(316, 333, 290, 128);
	m_board[4].SetGeometry(598, 362, 236, 107);
	m_board[5].SetGeometry(800, 352, 251, 95);
	m_board[6].SetGeometry(228, 422, 371, 123);
	m_board[7].SetGeometry(577, 433, 243, 119);
	m_board[8].SetGeometry(791, 425, 251, 124);
	m_board[9].SetGeometry(285, 504, 407, 164);
	m_board[10].SetGeometry(586, 523, 280, 121);
	m_board[11].SetGeometry(808, 518, 393, 116);
	m_board[12].SetGeometry(463, 635, 270, 143);
	m_board[13].SetGeometry(700, 633, 187, 152);
	m_board[14].SetGeometry(874, 593, 325, 179);
}

void Board::SetGeometry4PGame()
{
	m_board[0].SetGeometry(406, 153, 188, 120);
	m_board[1].SetGeometry(586, 172, 113, 137);
	m_board[2].SetGeometry(689, 170, 144, 112);
	m_board[3].SetGeometry(818, 131, 187, 161);
	m_board[4].SetGeometry(356, 266, 215, 86);
	m_board[5].SetGeometry(458, 275, 219, 112);
	m_board[6].SetGeometry(610, 273, 203, 115);
	m_board[7].SetGeometry(802, 270, 250, 119);
	m_board[8].SetGeometry(316, 334, 130, 98);
	m_board[9].SetGeometry(417, 333, 191, 127);
	m_board[10].SetGeometry(598, 362, 236, 107);
	m_board[11].SetGeometry(800, 352, 251, 95);
	m_board[12].SetGeometry(226, 421, 219, 86);
	m_board[13].SetGeometry(421, 439, 174, 111);
	m_board[14].SetGeometry(577, 433, 243, 119);
	m_board[15].SetGeometry(791, 425, 251, 124);
	m_board[16].SetGeometry(285, 504, 256, 164);
	m_board[17].SetGeometry(439, 521, 253, 121);
	m_board[18].SetGeometry(586, 523, 280, 121);
	m_board[19].SetGeometry(808, 518, 393, 116);
	m_board[20].SetGeometry(463, 635, 122, 129);
	m_board[21].SetGeometry(549, 633, 185, 147);
	m_board[22].SetGeometry(700, 633, 187, 152);
	m_board[23].SetGeometry(874, 593, 325, 179);
}