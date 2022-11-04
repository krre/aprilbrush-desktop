#include "MainWindow.h"
#include "CanvasTabWidget.h"
#include "NewImage.h"
#include "Preferences.h"
#include "Canvas.h"
#include "InputDevice.h"
#include "ColorPicker.h"
#include "BrushSettings.h"
#include "core/Context.h"
#include "core/SignalHub.h"
#include "core/Constants.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setAutoFillBackground(true);

    new SignalHub(this);
    new Context(this);

    m_undoGroup = new QUndoGroup(this);

    canvasTabWidget = new CanvasTabWidget(this);
    setCentralWidget(canvasTabWidget);

    createActions();
    createUi();
    readSettings();
    canvasTabWidget->addCanvas();
}

QUndoGroup* MainWindow::undoGroup() const {
    return m_undoGroup;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::onNew() {
    NewImage newImage(canvasTabWidget->nextName());

    if (newImage.exec() == QDialog::Accepted) {
        canvasTabWidget->addCanvas(newImage.name(), newImage.size());
    }
}

void MainWindow::onOpen() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Image"), QString(), tr("Images (*.ora)"));

    if (!filePath.isEmpty()) {
        canvasTabWidget->addCanvas(QString(), QSize());
        currentCanvas()->open(filePath);
        canvasTabWidget->setTabText(canvasTabWidget->currentIndex(), currentCanvas()->name());
    }
}

void MainWindow::onSave() {
    Canvas* canvas =  currentCanvas();

    if (!canvas->filePath().isEmpty()) {
        canvas->save();
    } else {
        onSaveAs();
    }
}

void MainWindow::onSaveAs() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Image As"),  currentCanvas()->name() + ".ora", tr("OpenRaster (*.ora)"));

    if (!filePath.isEmpty()) {
        QString oraPath = filePath.last(4) != ".ora" ? filePath + ".ora" : filePath;
        currentCanvas()->setFilePath(oraPath);
        currentCanvas()->save();
        canvasTabWidget->setTabText(canvasTabWidget->currentIndex(), currentCanvas()->name());
    }
}

void MainWindow::onExport() {
    QString fileName = currentCanvas()->name() + ".png";
    QString filePath = QFileDialog::getSaveFileName(this, tr("Export Image"), fileName, tr("Images (*.png)"));

    if (!filePath.isEmpty()) {
        currentCanvas()->exportPng(filePath);
    }
}

void MainWindow::onClose() {
    canvasTabWidget->closeCanvas(canvasTabWidget->currentIndex());
}

void MainWindow::onCloseAll() {
    int count = canvasTabWidget->count();

    for (int i = 0; i < count; ++i) {
        canvasTabWidget->closeCanvas(0);
    }
}

void MainWindow::onCloseOthers() {
    int count = canvasTabWidget->count() - 1;
    QWidget* activeTab = canvasTabWidget->currentWidget();

    for (int i = 0; i < count; i++) {
        if (canvasTabWidget->widget(0) != activeTab) {
            canvasTabWidget->closeCanvas(0);
        } else {
            canvasTabWidget->closeCanvas(1);
        }
    }
}

void MainWindow::onClear() {
    currentCanvas()->clear();
}

void MainWindow::onAbout() {
    using namespace Const::App;

    QMessageBox::about(this, tr("About %1").arg(Name),
        tr("<h3>%1 %2</h3>"
           "Painting application<br><br>"
           "Based on Qt %3<br>"
           "Build on %4 %5<br><br>"
           "<a href=%6>%6</a><br><br>"
           "Copyright © 2012-%7, Vladimir Zarypov")
           .arg(Name, Version, QT_VERSION_STR, BuildDate, BuildTime, URL, CopyrightLastYear));
}

void MainWindow::onPreferences() {
    Preferences preferences;

    if (preferences.exec() == QDialog::Accepted) {
        applyHotSettings();
    }
}

void MainWindow::onInputDevice() {
    auto inputDevice = new InputDevice(this);
    inputDevice->show();
}

void MainWindow::readSettings() {
    QSettings settings;
    QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();

    if (geometry.isEmpty()) {
        QSize screenSize = QGuiApplication::screens().first()->size();
        resize(screenSize.width() * 2 / 3, screenSize.height() * 2 / 3);
        move((screenSize.width() - width()) / 2, (screenSize.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}

void MainWindow::writeSettings() {
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
}

void MainWindow::createActions() {
    // File
    QMenu* fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New..."), this, &MainWindow::onNew, Qt::CTRL | Qt::Key_N);
    fileMenu->addAction(tr("Open..."), this, &MainWindow::onOpen, Qt::CTRL | Qt::Key_O);

    QAction* saveAction = fileMenu->addAction(tr("Save"), this, &MainWindow::onSave, Qt::CTRL | Qt::Key_S);
    QAction* saveAsAction = fileMenu->addAction(tr("Save As..."), this, &MainWindow::onSaveAs, Qt::CTRL | Qt::SHIFT | Qt::Key_S);
    QAction* exportAction = fileMenu->addAction(tr("Export..."), this, &MainWindow::onExport, Qt::CTRL | Qt::Key_E);
    fileMenu->addSeparator();

    QAction* closeAction = fileMenu->addAction(tr("Close"), this, &MainWindow::onClose, Qt::CTRL | Qt::Key_W);
    QAction* closeAllAction =fileMenu->addAction(tr("Close All"), this, &MainWindow::onCloseAll, Qt::CTRL | Qt::SHIFT | Qt::Key_W);
    QAction* closeOthersAction = fileMenu->addAction(tr("Close Others"), this, &MainWindow::onCloseOthers, Qt::CTRL | Qt::ALT | Qt::Key_W);

    fileMenu->addSeparator();
    fileMenu->addAction(tr("Preferences..."), this, &MainWindow::onPreferences);
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), this, &QMainWindow::close, Qt::CTRL | Qt::Key_Q);

    // Edit
    QMenu* editMenu = menuBar()->addMenu(tr("Edit"));

    auto undoAction = m_undoGroup->createUndoAction(this, tr("Undo"));
    undoAction->setShortcuts(QKeySequence::Undo);
    editMenu->addAction(undoAction);

    auto redoAction = m_undoGroup->createRedoAction(this, tr("Redo"));
    redoAction->setShortcuts(QKeySequence::Redo);
    editMenu->addAction(redoAction);

    QAction* clearAction = editMenu->addAction(tr("Clear"), this, &MainWindow::onClear, Qt::Key_Delete);

    // View
    viewMenu = menuBar()->addMenu(tr("View"));

    // Window
    QMenu* windowMenu = menuBar()->addMenu(tr("Window"));
    windowMenu->addAction(tr("Input Device..."), this, &MainWindow::onInputDevice);

    // Help
    QMenu* helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Const::App::Name), this, &MainWindow::onAbout);

    connect(canvasTabWidget, &CanvasTabWidget::countChanged, [=] (int count) {
        saveAction->setEnabled(count);
        saveAsAction->setEnabled(count);
        exportAction->setEnabled(count);
        closeAction->setEnabled(count);
        closeAllAction->setEnabled(count);
        closeOthersAction->setEnabled(count >= 2);
        undoAction->setEnabled(count);
        redoAction->setEnabled(count);
        clearAction->setEnabled(count);
    });
}

void MainWindow::createUi() {
    createDockWindows();
}

void MainWindow::createDockWindows() {
    auto colorPicker = new ColorPicker;
    Context::setColorPicker(colorPicker);
    auto dock = new QDockWidget(colorPicker->windowTitle(), this);
    dock->setWidget(colorPicker);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    auto brushSettings = new BrushSettings(Context::brushEngine());
    dock = new QDockWidget(brushSettings->windowTitle(), this);
    dock->setWidget(brushSettings);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    auto undoView = new QUndoView(m_undoGroup);
    dock = new QDockWidget(tr("Commands"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWidget(undoView);
    addDockWidget(Qt::RightDockWidgetArea, dock);
}

void MainWindow::applyHotSettings() {

}

Canvas* MainWindow::currentCanvas() const {
    return static_cast<Canvas*>(canvasTabWidget->currentWidget());
}
