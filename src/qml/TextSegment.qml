import QtQuick 2.0

Rectangle {
    id: textSegmentItem
    property QtObject textSegment
    property string text
    property color foregroundColor
    property color backgroundColor
    property font font

    y: 0
    width: textItem.paintedWidth
    height: textItem.paintedHeight

    color: backgroundColor

    Text {
        id: textItem
        text: textSegmentItem.text
        color: textSegmentItem.foregroundColor
        height: paintedHeight
        width: paintedWidth
        font: textSegmentItem.font
        textFormat: Text.PlainText
    }

    Connections {
        target: textSegment

        onTextChanged: {
            textSegmentItem.text = textSegment.text
        }

        onStyleChanged: {
            textSegmentItem.backgroundColor = textSegment.backgroundColor;
            textSegmentItem.foregroundColor = textSegment.foregroundColor;
        }

        onIndexChanged: {
            textSegmentItem.x = textSegment.index *  textSegment.screen.charWidth;
        }

        onVisibleChanged: {
            textSegmentItem.visible = textSegment.visible;
        }
    }
}
