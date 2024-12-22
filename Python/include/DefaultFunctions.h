#include "functionsFullProject.h"

int DefineMapSize(string size) {

    if (size == "small") {
        return 20;
    }

    if (size == "medium") {
        return 30;
    }

    if (size == "large") {
        return 40;
    }
    
    return 30;
}

vector<int> DefineParametersForField(GameInfo& gameInfo) {
    vector<int> result;
    string sizeMap = gameInfo.GetMapSize();

    int digitalMapSize = DefineMapSize(sizeMap);
    result.push_back(digitalMapSize);
    result.push_back(digitalMapSize);

    result.push_back(1);
    result.push_back(gameInfo.GetNumberOfBots());

    return result;
}

vector<int> GenerateRandomValues(int maxSize) {
    vector<int> randomValue;
    // Составим значения для разных штук
    srand(time(0));
    for (int i = 0; i < 7; ++i) {
        int cellForSnake = rand() % (maxSize - 1);
        if (find(randomValue.begin(), randomValue.end(), cellForSnake) == randomValue.end()) {
            randomValue.push_back(cellForSnake);
            continue;
        }
        --i;
    }
    return randomValue;
}