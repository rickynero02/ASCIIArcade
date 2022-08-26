#include "menu.hpp"

void Menu::printBanner() {
	printw("      ___           ___           ___                             ");
	mvprintw(1, 0, "     /\\  \\         /\\__\\         /\\__\\                            ");
	mvprintw(2, 0, "    /::\\  \\       /:/ _/_       /:/  /        ___         ___     ");
	mvprintw(3, 0, "   /:/\\:\\  \\     /:/ /\\  \\     /:/  /        /\\__\\       /\\__\\    ");
	mvprintw(4, 0, "  /:/ /::\\  \\   /:/ /::\\  \\   /:/  /  ___   /:/__/      /:/__/    ");
	mvprintw(5, 0, " /:/_/:/\\:\\__\\ /:/_/:/\\:\\__\\ /:/__/  /\\__\\ /::\\  \\     /::\\  \\    ");
	mvprintw(6, 0, " \\:\\/:/  \\/__/ \\:\\/:/ /:/  / \\:\\  \\ /:/  / \\/\\:\\  \\__  \\/\\:\\  \\__ ");
	mvprintw(7, 0, "  \\::/__/       \\::/ /:/  /   \\:\\  /:/  /   ~~\\:\\/\\__\\  ~~\\:\\/\\__\\");
	mvprintw(8, 0, "   \\:\\  \\        \\/_/:/  /     \\:\\/:/  /       \\::/  /     \\::/  /");
	mvprintw(9, 0, "    \\:\\__\\         /:/  /       \\::/  /        /:/  /      /:/  / ");
	mvprintw(10, 0, "     \\/__/         \\/__/         \\/__/         \\/__/       \\/__/  ");
	
	mvprintw(11, 0, "     ___          ___         ___          ___                      ___     ");
	mvprintw(12, 0, "    /\\  \\        /\\  \\       /\\__\\        /\\  \\        _____       /\\__\\    ");
	mvprintw(13, 0, "   /::\\  \\      /::\\  \\     /:/  /       /::\\  \\      /::\\  \\     /:/ _/_   ");
	mvprintw(14, 0, "  /:/\\:\\  \\    /:/\\:\\__\\   /:/  /       /:/\\:\\  \\    /:/\\:\\  \\   /:/ /\\__\\  ");
	mvprintw(15, 0, " /:/ /::\\  \\  /:/ /:/  /  /:/  /  ___  /:/ /::\\  \\  /:/  \\:\\__\\ /:/ /:/ _/_ ");
	mvprintw(16, 0, "/:/_/:/\\:\\__\\/:/_/:/__/__/:/__/  /\\__\\/:/_/:/\\:\\__\\/:/__/ \\:|__/:/_/:/ /\\__\\");
	mvprintw(17, 0, "\\:\\/:/  \\/__/\\:\\/:::::/  |:\\  \\ /:/  /\\:\\/:/  \\/__/\\:\\  \\ /:/  |:\\/:/ /:/  /");
	mvprintw(18, 0, " \\::/__/      \\::/~~/~~~~ \\:\\  /:/  /  \\::/__/      \\:\\  /:/  / \\::/_/:/  / ");
	mvprintw(19, 0, "  \\:\\  \\       \\:\\~~\\      \\:\\/:/  /    \\:\\  \\       \\:\\/:/  /   \\:\\/:/  /  ");
	mvprintw(20, 0, "   \\:\\__\\       \\:\\__\\      \\::/  /      \\:\\__\\       \\::/  /     \\::/  /   ");
	mvprintw(21, 0, "    \\/__/        \\/__/       \\/__/        \\/__/        \\/__/       \\/__/    ");
	refresh();
}

Menu::Menu() {
	getmaxyx(stdscr, maxY, maxX);
	menuwin = newwin(6, maxX - 12, maxY - 8, 5);
	keypad(menuwin, true);
	highlight = 0;
}

int Menu::show() {
	printBanner();
	box(menuwin, 0, 0);
	refresh();
	wrefresh(menuwin);

	int choice = 0;

	while (1) {
		printMenu();
		choice = wgetch(menuwin);

		switch (choice) {
			case KEY_UP:
				highlight--;
				break;
			case KEY_DOWN:
				highlight++;
				break;
			case 10:
				return highlight;
		}

		if (highlight < 0) {
			highlight = 0;
		}

		if (highlight > 2) {
			highlight = 2;
		}
	}
}

void Menu::printMenu() {
	for (int i = 0; i < 3; i++) {
		if (i == highlight) {
			wattron(menuwin, A_REVERSE);
		}
		mvwprintw(menuwin, i+1, 1, "%s", choices[i]);
		wattroff(menuwin, A_REVERSE);
	}
	wrefresh(menuwin);
}

Menu::~Menu() {
	delwin(menuwin);
}