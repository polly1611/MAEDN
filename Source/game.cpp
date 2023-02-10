#include "game.h"

Game *Game::m_instance = nullptr;

Game *Game::getInstance()
{
  if (m_instance == nullptr)
  {
      m_instance = new Game;
  }
  return m_instance;
}
Game::Game(QObject *parent)
    : QObject{parent}
{

}
