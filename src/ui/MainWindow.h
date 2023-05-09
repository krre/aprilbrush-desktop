#pragma once
#include <QMainWindow>

class CanvasTabWidget;
class Canvas;
class ColorPicker;
class BrushEngine;
class EventFilter;
class QUndoGroup;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void onNew();
    void onOpen();
    void onSave();
    void onSaveAs();
    void onExport();
    void onClose();
    void onCloseAll();
    void onCloseOthers();

    void onClear();

    void onAbout();
    void onPreferences();
    void onInputDevice();

private:
    void readSettings();
    void writeSettings();

    void createActions();
    void createUi();
    void createDockWindows();
    void applyHotSettings();

    Canvas* currentCanvas() const;

    EventFilter* m_eventFilter = nullptr;
    CanvasTabWidget* m_canvasTabWidget;
    ColorPicker* m_colorPicker = nullptr;
    BrushEngine* m_brushEngine = nullptr;
    QMenu* m_viewMenu = nullptr;
    QUndoGroup* m_undoGroup = nullptr;
};
