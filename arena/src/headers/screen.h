#pragma once
#include <ncurses.h>
#include <panel.h>

#include <iostream>
#include <memory>
#include <vector>
class Screen {
    static std::shared_ptr<WINDOW> logs;
    static std::shared_ptr<WINDOW> board;
    static std::vector<std::shared_ptr<PANEL>> panels;
    static PANEL* top;

   public:
    Screen() = delete;

    static void Initialize();
    static void UpdateScreenSize();
    static void WaitForInput();
};