#include <iostream>

struct point {
    int x = 0;
    int y = 0;
};

class Window {
    point zeroPoint = {0, 0};
    point endPoint = {9, 9};
    friend class Screen;

  public:
    void reSize() {
        point size;
        std::cout << "Input new size (width, height): ";
        std::cin >> size.x >> size.y;
        while(size.x < 0 || size.y < 0) {
            std::cout << "Wrong input. Try again: ";
            std::cin >> size.x >> size.y;
        }

        endPoint.x += size.x - 1;
        endPoint.y += size.y - 1;

        if (endPoint.x > 79) endPoint.x = 79;
        if (endPoint.y > 49) endPoint.y = 49;

        std::cout << "New window size: " << endPoint.x - zeroPoint.x + 1 << "x" << endPoint.y - zeroPoint.y + 1 << std::endl;
    }

    void move() {
        point deltaVector;
        std::cout << "Input the delta vector to move window (dX, dY): ";
        std::cin >> deltaVector.x >> deltaVector.y;

        zeroPoint.x += deltaVector.x;
        zeroPoint.y += deltaVector.y;
        endPoint.x += deltaVector.x;
        endPoint.y += deltaVector.y;

        if (zeroPoint.x < 0) {
            endPoint.x -= zeroPoint.x;
            zeroPoint.x = 0;
        }
        if (endPoint.x > 79) {
            zeroPoint.x += (79 - endPoint.x);
            endPoint.x = 79;
        }
        if (zeroPoint.y < 0) {
            endPoint.y -= zeroPoint.y;
            zeroPoint.y = 0;
        }
        if (endPoint.y > 49) {
            zeroPoint.y += (49 - endPoint.y);
            endPoint.y = 49;
        }
        std::cout << "Coordinates of left-top point: (" << zeroPoint.x << ", " << zeroPoint.y << ")" << std::endl;
    }
};

class Screen {
    int sizeX = 80;
    int sizeY = 50;

    bool insideWindow(int i, int j, Window* window) {
        int x1 = window->zeroPoint.x;
        int y1 = window->zeroPoint.y;
        int x2 = window->endPoint.x;
        int y2 = window->endPoint.y;
        if (i >= y1 && i <= y2 && j >= x1 && j <= x2) return true;
        return false;
    }

  public:
    void display(Window* window) {
        for (int i = 0; i < 50; ++i) {
            for (int j = 0; j < 80; ++j) {
                if (insideWindow(i, j, window)) std::cout << 1;
                else std::cout << 0;
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    Window* window = new Window();
    Screen* screen = new Screen();
    std::string command;
    while (command != "exit") {
        std::cout << "Input command: ";
        std::cin >> command;

        if (command == "resize") window->reSize();
        else if (command == "move") window->move();
        else if (command == "display") screen->display(window);
        else if (command != "exit") std::cout << "Wrong input. Try again." << std::endl;
    }
    delete screen;
    screen = nullptr;
    delete window;
    window = nullptr;
    return 0;
}
