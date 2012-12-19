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

#ifndef VIRTUALPIANO_H
#define VIRTUALPIANO_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPaintEvent>
#include <QList>
#include <QMap>
#include <QColor>
#include <QReadWriteLock>

#include <QtMidi.h>

namespace Ui {
class VirtualPiano;
}

class VirtualPianoKey : public QObject, QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit VirtualPianoKey(QObject *parent = 0, int midiKey = 0, QString noteName = "", bool isBlackKey = false);
    inline ~VirtualPianoKey() {}

    inline void setSize(int x, int y, int w, int h)
    { this->setRect(0,0,w,h); this->setPos(x,y); }

    QList<QColor> trackColors();
    void setTrackColors(QList<QColor> newColors);
    void addTrackColor(int track);
    void removeTrackColor(int track);

private:
    bool isBlack;
    bool isHovering;
    bool isClicking;
    int myMidiKey;
    QString myNoteName;

    QList<QColor> myColors;
    QReadWriteLock lock;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);

    inline void hoverEnterEvent(QGraphicsSceneHoverEvent *)
    { isHovering = true; this->scene()->update(x(),y(),rect().x(),rect().y()); }
    inline void hoverLeaveEvent(QGraphicsSceneHoverEvent *)
    { isHovering = false; this->scene()->update(x(),y(),rect().x(),rect().y()); }

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

class VirtualPiano : public QGraphicsView
{
    Q_OBJECT
    
public:
    explicit VirtualPiano(QWidget *parent = 0);
    ~VirtualPiano();

    inline VirtualPianoKey* key(int num) { return keys.value(num); }

    void clearTrackColors();
    void clearTrackColors(int track);

    static int voiceToUse;
    
private:
    Ui::VirtualPiano *ui;
    QMap<int,VirtualPianoKey*> keys;

    int k;
    int curKey;

    void addWhiteKey(QGraphicsScene* scene, QString noteName);
    void addBlackKey(QGraphicsScene* scene, QString noteName);
};

#endif // VIRTUALPIANO_H