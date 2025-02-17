

#ifndef GAMEINFO_HPP
#define GAMEINFO_HPP

#include "functionsFullProject.h"

// Конструктор по умолчанию.
GameInfo::GameInfo() {
  _numberOfRounds = 1;
  _numberOfBots = 0;
  _mapSize = "medium";
  _somethingIsPressed = false;
  _isSolo = true;
  _currentRound = 1;

  // Задается название открытого сейчас окна.
  _currentWindowName = "MainMenu";

  // Создаются объекты для хранения настроек игроков.
  _firstPlayerInfo = CreateFirstPlayer();
  _secondPlayerInfo = CreateSecondPlayer();

  // Для изменяемого поля устанавливается пустое значение т.к. никакой из полей
  // не изменяется.
  _fieldInUse = "";
}

// Функция устанавливает значение на игру для двоих.
void GameInfo::SetDuo() { _isSolo = false; }

// Функция устанавливает значение на игру для одного.
void GameInfo::SetSolo() { _isSolo = true; }

// Функция возвращает: сколько человек играет.
bool GameInfo::GetIsSolo() { return _isSolo; }

// Функция возвращает количество раундов в игре.
int GameInfo::GetNumberOfRounds() { return _numberOfRounds; }

// Функция увеличивает количество раундов в игре.
void GameInfo::IncreaseNumberOfRounds() {
  if (_numberOfRounds < 9) {
    ++_numberOfRounds;
  }
}

// Функция уменьшает количство раундов в игре.
void GameInfo::DecreaseNumberOfRounds() {
  if (_numberOfRounds > 1) {
    --_numberOfRounds;
  }
}

void GameInfo::LoadFromFile(const std::string &filename) {
  std::ifstream inFile(filename);
  if (!inFile) {
    throw std::runtime_error("Не удалось открыть файл для чтения: " + filename);
  }

  std::string line;
  while (std::getline(inFile, line)) {
    std::string key;
    size_t pos = line.find(' ');
    if (pos != std::string::npos) {
      key = line.substr(0, pos);
    } else {
      key = line; // Если пробелов нет, вся строка - это ключ
    }

    if (key == "NumberOfRounds") {
      _numberOfRounds = std::stoi(line.substr(pos + 1));
    } else if (key == "NumberOfBots") {
      _numberOfBots = std::stoi(line.substr(pos + 1));
    } else if (key == "MapSize") {
      _mapSize = line.substr(pos + 1);
    } else if (key == "IsSolo") {
      _isSolo = (line.substr(pos + 1) == "true");
    } else if (key == "SomethingIsPressed") {
      _somethingIsPressed = (line.substr(pos + 1) == "true");
    } else if (key == "CurrentWindowName") {
      _currentWindowName = line.substr(pos + 1);
    } else if (key == "FirstPlayerInfo") {
      _firstPlayerInfo.LoadFromFile(inFile);
    } else if (key == "SecondPlayerInfo") {
      _secondPlayerInfo.LoadFromFile(inFile);
    } else if (key == "FieldInUse") {
      _fieldInUse = line.substr(pos + 1);
    }
  }

  inFile.close();
}

// Сохранение состояния в файл
void GameInfo::SaveToFile(const std::string &filename) const {
  std::ofstream outFile(filename);
  if (!outFile) {
    throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
  }

  outFile << _numberOfRounds << std::endl;
  outFile << _numberOfBots << std::endl;
  outFile << _mapSize << std::endl;
  outFile << _isSolo << std::endl;
  outFile << _somethingIsPressed << std::endl;
  outFile << _currentWindowName << std::endl;
  _firstPlayerInfo.SaveToFile(outFile);
  _secondPlayerInfo.SaveToFile(outFile);
  outFile << _fieldInUse << std::endl;

  outFile.close();
}

// Функция возвращает количество ботов в игре.
int GameInfo::GetNumberOfBots() { return _numberOfBots; }

// Функция увеличивает количество ботов в игре.
void GameInfo::IncreaseNumberOfBots() {
  if (_numberOfBots < 3 &&
      this->GetIsSolo()) { // Если ботов меньше трех и выбран режим для одного
                           // игрока, то количество ботов увеличивается.
    ++_numberOfBots;
  }
}

// Функция уменьшает количетсов ботов в игре.
void GameInfo::DecreaseNumberOfBots() {
  if (_numberOfBots > 0) {
    --_numberOfBots;
  }
}

// Функция возвращает размер игрового поля.
std::string GameInfo::GetMapSize() { return _mapSize; }

// Функция для того, чтобы сменить карту игры на большую.
void GameInfo::IncreaseMapSize() {
  if (_mapSize == "medium") {
    _mapSize = "large";
  }
  if (_mapSize == "small") {
    _mapSize = "medium";
  }
}

// Функция для того, чтобы сменить карту игры на меньшую.
void GameInfo::DecreaseMapSize() {
  if (_mapSize == "medium") {
    _mapSize = "small";
  }
  if (_mapSize == "large") {
    _mapSize = "medium";
  }
}

bool GameInfo::GetPressedButton() { return _somethingIsPressed; }

void GameInfo::SetPressedButton() { _somethingIsPressed = true; }

void GameInfo::UnsetPressedButton() { _somethingIsPressed = false; }

std::string GameInfo::GetCurrentWindowName() { return _currentWindowName; }

// Функция устанавливает название текущего экрана.
void GameInfo::SetCurrentWindowName(std::string newWindowName) {
  _currentWindowName = newWindowName;
}

// Функция возвращает информацию о первом игроке.
PlayerInfo GameInfo::GetFirstPlayerInfo() { return _firstPlayerInfo; }

// Функция устанавливает информацию о первом игроке.
void GameInfo::SetFirstPlayerInfo(PlayerInfo newInfo) {
  _firstPlayerInfo = newInfo;
}

// Функция возвращает информацию о втором игроке.
PlayerInfo GameInfo::GetSecondPlayerInfo() { return _secondPlayerInfo; }

// Функция устанавливает информацию о втором игроке.
void GameInfo::SetSecondPlayerInfo(PlayerInfo newInfo) {
  _secondPlayerInfo = newInfo;
}

// Функция возвращает название изменяемого поля.
std::string GameInfo::GetFieldInUse() { return _fieldInUse; }

// Функция устанавливает название изменяемого поля.
void GameInfo::SetFieldInUse(std::string fieldName) { _fieldInUse = fieldName; }

// Функция вернёт текущий раунд
int GameInfo::GetCurrentRound() { return _currentRound; }

int GameInfo::SetCurrentRound(int currentRound) {
  _currentRound = currentRound;
}

#endif // GAMEINFO_HPP
