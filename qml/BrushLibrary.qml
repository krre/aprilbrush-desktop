import QtQuick 2.0
import "components"

Window {
    id: root
    title: "Brush Library"

    Item {
        anchors.fill: parent

        GridView {
            id: libraryView
            model: libraryModel
            delegate: brushDelegate

            width: parent.width
            height: root.height - 65
            cellWidth: 56
            cellHeight: 56
            highlight: brushSelected
            highlightMoveDuration: 1
            clip: true
        }

        Component {
            id: brushDelegate
            ListItem {
                text: nameLib
                width: 50
                height: 50
                closable: false
                color: GridView.isCurrentItem ? "transparent" : "lightgray"
                onClicked: {
                    libraryView.currentIndex = index
                    brushSettings.brushSettingsModel.setProperty(0, "initParam", sizeLib)
                    brushSettings.brushSettingsModel.setProperty(1, "initParam", opacityLib)
                    brushSettings.brushSettingsModel.setProperty(2, "initParam", spacingLib)
                    brushSettings.brushSettingsModel.setProperty(3, "initParam", hardnessLib)
                    brushSettings.brushSettingsModel.setProperty(4, "initParam", roundnessLib)
                    brushSettings.brushSettingsModel.setProperty(5, "initParam", angleLib)
                    //console.log(JSON.stringify(brushSettings.brushSettingsModel, null, 4))
                }
            }
        }

        Component {
            id: brushSelected
            ListItemComponent {
                width: 50
                height: 50
            }
        }

        ListModel {
            id: libraryModel
            ListElement {nameLib: "Active"; sizeLib: 10; opacityLib: 50; spacingLib: 25; hardnessLib: 34; roundnessLib: 2; angleLib: 90 }
            ListElement {nameLib: "Default"; sizeLib: 30; opacityLib: 50; spacingLib: 30; hardnessLib: 85; roundnessLib: 1; angleLib: 90 }
            ListElement {nameLib: "Big"}
            ListElement {nameLib: "Little"}
            ListElement {nameLib: "Ellipse"}
            ListElement {nameLib: "Eraser"}
        }
    }
}
