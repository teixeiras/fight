#include "headers/screen.h"

#include <ncurses.h>
#include <panel.h>
#include <signal.h>
#include <string.h>

std::shared_ptr<WINDOW> Screen::logs;
std::shared_ptr<WINDOW> Screen::board;
std::vector<std::shared_ptr<PANEL>> Screen::panels;
PANEL* Screen::top;

typedef std::tuple<int, int> Point;
typedef std::tuple<int, int> Size;
template<typename type> std::shared_ptr<type> reference(type* object) {
    std::shared_ptr<type> ref(object);
    return ref;
}

void handle_winch(int sig) {
    signal(SIGWINCH, SIG_IGN);
    Screen::UpdateScreenSize();
    signal(SIGWINCH, handle_winch);
}

void Screen::Initialize() {
    initscr();
    signal(SIGWINCH, handle_winch);

    Size dim = {COLS, LINES};

    logs  = reference<WINDOW>(newwin(COLS / 2, LINES, COLS / 2, 0));
    board = reference<WINDOW>(newwin(COLS / 2, LINES, 0, 0));

    box(logs.get(), 1, 1);
    box(board.get(), 1, 1);
    keypad(stdscr, TRUE);

    /* Attach a panel to each window */                         /* Order is bottom up */
    panels.push_back(reference<PANEL>(new_panel(logs.get())));  /* Push 0, order: stdscr-0 */
    panels.push_back(reference<PANEL>(new_panel(board.get()))); /* Push 0, order: stdscr-0 */

    /* Set up the user pointers to the next panel */
    set_panel_userptr(panels[0].get(), panels[1].get());
    set_panel_userptr(panels[1].get(), panels[0].get());
}
void Screen::UpdateScreenSize() {
    wresize(logs.get(), COLS / 2, LINES);
    wmove(logs.get(), COLS / 2, 0);

    wresize(board.get(), COLS / 2, LINES);
    refresh();
}

void Screen::WaitForInput() {
    char ch;
    while ((ch = getch()) != KEY_F(1)) {
        switch (ch) {
            case 9:
                top = (PANEL*)panel_userptr(top);
                top_panel(top);
                break;
        }
        update_panels();
        doupdate();
    }
    endwin();
}