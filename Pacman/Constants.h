#pragma once

using namespace std;

//Constants for the graphic part.
#define defaultWidth 300

#define defaultHeight defaultWidth
#define pacmanRadius (defaultWidth/40)

#define ghostRadius (pacmanRadius*2/3)
#define circleRadius (pacmanRadius/7)

#define lineThickness defaultWidth/200
#define borderWidth (2.5*pacmanRadius + 3*lineThickness)
#define borderWidthInside 1.5*borderWidth
#define xAmount 25
#define xStep  defaultWidth/xAmount
#define yAmount 25
#define yStep (defaultHeight/yAmount)
#define firstRectanglesHeight 1
#define secondRectanglesHeight 1.5
#define thirdRectangleHeight 2
#define firstRectangleWidth2 1
#define secondRectangleWidth2 1.5
#define thirdRectangleWidth2 1
#define RowAmount 3
#define ColumnAmount 3

#define rectangleBaseHeight (defaultWidth-(RowAmount+1)*borderWidth)/(firstRectanglesHeight+secondRectanglesHeight+thirdRectangleHeight)
#define rectangleBaseWidth (defaultWidth - (ColumnAmount +1)*borderWidth)/(firstRectangleWidth2+secondRectangleWidth2+thirdRectangleWidth2)

#define secondRowStartY (firstRectanglesHeight*rectangleBaseHeight + 2*borderWidth)
#define thirdRowStartY (secondRowStartY + secondRectanglesHeight*rectangleBaseHeight+ + borderWidth)

#define secondRowStartX (2*borderWidth + firstRectangleWidth2*rectangleBaseWidth)
#define thirdRowStartX (secondRowStartX + borderWidth + secondRectangleWidth2*rectangleBaseWidth)

#define defaultR 0
#define defaultG 0
#define defaultB 0


#define defaultFPS 60.0
#define ghostPace (defaultWidth/80)
#define pacmanPace (defaultWidth/120)

typedef struct {
	unsigned int x;
	unsigned int y;
} Position;
