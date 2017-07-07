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

#include "audioDevice.h"

audioDevice::audioDevice(QGraphicsScene* scene, QObject *parent) :
	QIODevice(parent),
	scene(scene)
{
}

qint64 audioDevice::readData(char * data, qint64 maxSize)
{
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return -1;
}

//Método que es llamado cada vez que el audio recorder recibe un paquete de 8 bytes, se ejecuta automáticamente
qint64 audioDevice::writeData(const char * data, qint64 maxSize)
{
	int value = 0; // variable para guardar la intensidad actual
	for(int counter = 0; counter < maxSize; ++counter){
		value = abs((quint8)data[counter] - 128); //Calcular la intensidad de 0 a 128
		std::cout << value << std::endl;
	}
}
