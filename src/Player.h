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

#ifndef PLAYER_H
#define PLAYER_H

#include <QThread>

#include <QtMidiFile.h>
#include "Gui/Widgets/VirtualPiano.h"

class Player : public QThread
{
    Q_OBJECT
public:
    inline Player(QtMidiFile* fil, VirtualPiano* p, qint32 tick = 0)
        : QThread(0)
    {
        f = fil;
        piano = p;
        doStop = false;
        sTick = tick;
    }
    inline ~Player() {}

    inline void stop() { doStop = true; }

protected:
    void run();

signals:
    void tickChanged(qint32 tick);

private:
    QtMidiEvent* e;
    QtMidiFile* f;
    VirtualPiano* piano;

    bool doStop;

    qint32 sTick;

private slots:
    void handleEvent();
};

#endif // PLAYER_H