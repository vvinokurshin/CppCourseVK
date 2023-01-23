#include "gui_manager.h"

GuiManager::GuiManager(QObject* parent): QObject(parent) {
    _authWindow.show();

    // connections
    // from main window
    connect(&_mainWindow, &MainWindow::addObjectSignal, this, &GuiManager::addObjectSignal);
    connect(&_mainWindow, &MainWindow::delObjectSignal, this, &GuiManager::delObjectSignal);
    connect(&_mainWindow, &MainWindow::onCardClickedSignal, this, &GuiManager::openCardSlot);
    connect(&_mainWindow, &MainWindow::showBoardSignal, this, &GuiManager::showBoardSignal);

    // from auth window
    connect(&_authWindow, &AuthWindow::authSignal, this, &GuiManager::authSignal);
    connect(&_authWindow, &AuthWindow::openRegSignal, this, &GuiManager::openRegSlot);

    // from reg window
    connect(&_regWindow, &RegWindow::regSignal, this, &GuiManager::regSignal);
    connect(&_regWindow, &RegWindow::openAuthSignal, this, &GuiManager::openAuthSlot);
}

GuiManager::~GuiManager() {
    _mainWindow.close();
    _authWindow.close();
    _regWindow.close();
}

void GuiManager::showBoards(const std::vector<Board>& boards) {
    _mainWindow.showBoards(boards);
}

void GuiManager::showBoard(const Board& board) {
    _mainWindow.showBoard(board);
}

void GuiManager::deleteLoad() {
    _mainWindow.deleteLoad();
}

void GuiManager::showLoadAllData() {
    _authWindow.close();
    _regWindow.close();
    _mainWindow.showMaximized();
    _mainWindow.showLoadAllData();
}

// public slots
void GuiManager::openRegSlot() {
    _authWindow.close();
    _regWindow.show();
}

void GuiManager::openAuthSlot() {
    _regWindow.close();
    _authWindow.show();
}

void GuiManager::openCardSlot(CardWidget* cw) {
    _regWindow.close();
    _authWindow.close();
    _cardWindow = new CardWindow(cw);
    _cardWindow->show();

    connect(_cardWindow, &CardWindow::delObjectSignal, this, &GuiManager::delObjectSignal);
    connect(_cardWindow, &CardWindow::updateObjectSignal, this, &GuiManager::updateObjectSignal);
}
