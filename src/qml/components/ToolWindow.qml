/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2014 Vladimir Zarypov <krre31@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

import QtQuick 2.2

Item {
    id: root
    property alias title: title.text
    default property alias content: stack.children
    property int indent: 10
    property int headerHeight: 30
    property bool collapse: false
    property real currentHeight: implicitHeight

    implicitWidth: 200
    implicitHeight: 200
    height: collapse ? headerHeight: currentHeight

    Rectangle {
        anchors.fill: parent
        opacity: 0.8
        border.color: "black"
        radius: 5
        antialiasing: true
        gradient: Gradient {
            GradientStop { position: 0.0; color: "gray" }
            GradientStop { position: headerHeight / height; color: "black" }
            GradientStop { position: 1.0; color: "black" }
        }
    }

    MouseArea {
        anchors.fill: parent
        drag.target: root
    }

    Row {
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.top: parent.top
        anchors.topMargin: 8
        spacing: 2

        Image {
            y: -2
            source: "../../images/triangle.png"
            scale: 0.6
            rotation: collapse ? 0 : 90
            MouseArea {
                anchors.fill: parent
                onClicked: collapse = !collapse
            }
        }

        Text {
            id: title
            text: qsTr("Untitled")
            color: "white"
        }
    }

    CloseButton {
        id: closeButton
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 5
        onClicked: colorPicker.visible = false
    }

    // Content stack
    Item {
        id: stack
        width: parent.width - indent * 2
        height: parent.height - headerHeight - indent
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: indent
        visible: !collapse
    }

    // Resize handler
    Item {
        id: resizeHandler
        width: 20
        height: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 3
        anchors.right: parent.right
        anchors.rightMargin: 3
        visible: !collapse

        Text {
            text: "="
            anchors.centerIn: parent
            font.pointSize: 15
            color: resizeMouseArea.containsMouse ? "white" : "gray"
            opacity: resizeMouseArea.pressed ? 0.5 : 1
        }

        MouseArea {
            id: resizeMouseArea
            property bool resizeMode: false
            anchors.fill: parent
            hoverEnabled: true
            onPressed: resizeMode = true
            onReleased: { resizeMode = false }
            onPositionChanged: {
                if (resizeMode) {
                    var newWidth = root.width + mouseX - indent
                    root.width = newWidth < root.implicitWidth ? root.implicitWidth : newWidth
                    var newHeight = root.height + mouseY - indent
                    currentHeight = newHeight < root.implicitWidth ? root.implicitWidth : newHeight
                }
            }
        }
    }
}

