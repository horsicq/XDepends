/* Copyright (c) 2022 hors<horsicq@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef GUIMAINWINDOW_H
#define GUIMAINWINDOW_H

#include "../global.h"
#include <QDragEnterEvent>
#include <QFileDialog>
#include <QMainWindow>
#include <QMimeData>
#include "dialogattachprocess.h"
#include "dialogoptions.h"
#include "dialogpe.h"
#include "dialogshortcuts.h"
#include "xformats.h"
#include "xoptions.h"

namespace Ui {
class GuiMainWindow;
}

class GuiMainWindow : public QMainWindow
{
    Q_OBJECT

    enum MODE
    {
        MODE_UNKNOWN=0,
        MODE_FILE,
        MODE_PROCESS
    };

public:
    GuiMainWindow(QWidget *pParent=nullptr);
    ~GuiMainWindow();

private slots:
    void adjustWindow();
    void processFile(QString sFileName);
    void closeCurrent();
    void setMode(MODE mode);
    void on_pushButtonFile_clicked();
    void on_pushButtonProcess_clicked();
    void on_pushButtonViewer_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonReload_clicked();
    void on_pushButtonOptions_clicked();
    void on_pushButtonShortcuts_clicked();
    void on_pushButtonAbout_clicked();
    void on_pushButtonExit_clicked();
    void on_checkBoxRecursive_toggled(bool bChecked);

protected:
    void dragEnterEvent(QDragEnterEvent *pEvent) override;
    void dragMoveEvent(QDragMoveEvent *pEvent) override;
    void dropEvent(QDropEvent *pEvent) override;

private:
    Ui::GuiMainWindow *ui;
    XOptions g_xOptions;
    XShortcuts g_xShortcuts;
    MODE g_mode;
};
#endif // GUIMAINWINDOW_H
