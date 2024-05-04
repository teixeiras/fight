#include "headers/screen.h"

#include <ncurses.h>
#include <panel.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

std::shared_ptr<WINDOW> Screen::logs;
std::shared_ptr<WINDOW> Screen::board;
std::vector<std::shared_ptr<PANEL>> Screen::panels;
PANEL* Screen::top;

typedef std::tuple<int, int> Point;
typedef struct {
    int width, height;
} Size;
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
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_GREEN);

    Size dim;
    getmaxyx(stdscr, dim.width, dim.height);

    logs  = reference<WINDOW>(newwin(dim.width, dim.height, 0, 0));
    board = reference<WINDOW>(newwin(dim.width, dim.height, 0, 0));
    wbkgd(board.get(), COLOR_PAIR(1));
    wbkgd(logs.get(), COLOR_PAIR(2));

    box(logs.get(), 0, 0);
    box(board.get(), 0, 0);
    keypad(stdscr, TRUE);

    /* Attach a panel to each window */                         /* Order is bottom up */
    panels.push_back(reference<PANEL>(new_panel(logs.get())));  /* Push 0, order: stdscr-0 */
    panels.push_back(reference<PANEL>(new_panel(board.get()))); /* Push 0, order: stdscr-0 */

    /* Set up the user pointers to the next panel */
    set_panel_userptr(panels[0].get(), panels[1].get());
    set_panel_userptr(panels[1].get(), panels[0].get());
    top = panels[0].get();
}
void Screen::drawMap(Cell array[], int row_max, int col_max) {
    Size dim;
    getmaxyx(stdscr, dim.width, dim.height);
    Size boardDim = {dim.width, dim.height};
    if (dim.width > row_max || dim.height > col_max) { float propotion = max(row_max / dim.width, dim.height / col_max); }
    for (int row = 0; row < boardDim.width; row++) {
        for (int col = 0; col < boardDim.height; col++) { mvaddch(row + 1, col + 1, array[row * dim.width + col].toChar()); }
    }
}
void Screen::UpdateScreenSize() {
    Size dim;
    getmaxyx(stdscr, dim.width, dim.height);
    wresize(logs.get(), dim.width, dim.height);

    wresize(board.get(), dim.width, dim.height);
    refresh();
    update_panels();
    doupdate();
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