/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "widget.h"
#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioInput>

#include "audioDevice.h"

Widget::Widget(QWidget *parent):
      m_device(0),
      m_audioInput(0)
{
	Q_UNUSED(parent);
	// create the scene
	scene = new QGraphicsScene();
	scene->setSceneRect(0,0,1920,1080); // make the scene 800x600 instead of infinity by infinity (default)

	// make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
	// it can be used to visualize scenes)
	setScene(scene);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(1920,1080);
	scene->setBackgroundBrush(QBrush(QColor(QRgb(0000))));


    QAudioFormat formatAudio;
    formatAudio.setSampleRate(8000);
    formatAudio.setChannelCount(1);
	formatAudio.setSampleSize(8);
    formatAudio.setCodec("audio/pcm");
    formatAudio.setByteOrder(QAudioFormat::LittleEndian);
    formatAudio.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo inputDevices = QAudioDeviceInfo::defaultInputDevice();
    m_audioInput = new QAudioInput(inputDevices,formatAudio, this);

	m_device = new audioDevice(scene, this);
    m_device->open(QIODevice::WriteOnly);

    m_audioInput->start(m_device);
}

Widget::~Widget()
{
    m_audioInput->stop();
    m_device->close();
	delete scene;
}
