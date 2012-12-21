/*
 * Raging MIDI (https://github.com/waddlesplash/ragingmidi).
 *
 * Copyright (c) 2012 WaddleSplash & contributors (see AUTHORS.txt).
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef ALLEVENTS_H
#define ALLEVENTS_H

#include <QDialog>
#include <QTreeWidget>
#include <QtMidiFile.h>

namespace Ui {
class AllEvents;
}

class GuiMidiEvent : public QTreeWidgetItem
{
public:
    inline explicit GuiMidiEvent(QTreeWidget *p = 0)
        : QTreeWidgetItem(p) {}
    inline ~GuiMidiEvent() {}

    void init(QtMidiEvent *e);
};

class AllEvents : public QDialog
{
    Q_OBJECT
public:
    explicit AllEvents(QWidget *parent = 0, QtMidiFile *f = 0);
    ~AllEvents();
    
private:
    Ui::AllEvents *ui;
};

#endif // ALLEVENTS_H