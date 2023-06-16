#include "ProducesRoomsGroup.h"
#include <colored_canvas.hpp>
#include <unordered_map>
namespace experis
{

namespace roomDimension
{
    static short startPointX = 3; 
    static short startPointY = 1; 
    static short lengthWidth = 17; 
    static short lengthHigh = 7; 
}

std::unordered_map<Directions, char> directionsToChar{
    {Directions::NORTH, '^'}
    ,{Directions::EAST, '>'}
    ,{Directions::SOUTH, 'v'}
    ,{Directions::WEST, '<'}
};


enum class DirectionDraw
{
    Vertical
    ,Horizontal
};

void GateVertical(bool a_isOpen, Group& a_group)
{
    ascii::ColoredCanvas::Color color = a_isOpen ? ascii::ColoredCanvas::GREEN : ascii::ColoredCanvas::RED;
    static short lengthGate = 2;
    int spaciousLeft = 1;
    int spaciousRight = 0;
    int xStart = 0;
    int ystart = 0;

    if (a_isOpen)
    {
        ++spaciousLeft;
        ++spaciousRight;
        a_group.Add<Line>(xStart , ystart, lengthGate).SetBrush(' ').SetDegrees(90);
        a_group.Add<Line>(xStart + 1, ystart, lengthGate).SetBrush(' ').SetDegrees(90);
    }
    

    a_group.Add<Line>(xStart + spaciousLeft, ystart, lengthGate).SetBrush('<').SetFg(color).SetDegrees(90);
    a_group.Add<Line>(xStart + spaciousLeft + 1, ystart, lengthGate).SetBrush(')').SetFg(color).SetDegrees(90);
    a_group.Add<Line>(xStart - spaciousRight, ystart, lengthGate).SetBrush('>').SetFg(color).SetDegrees(90);
    a_group.Add<Line>(xStart - spaciousRight - 1, ystart, lengthGate).SetBrush('(').SetFg(color).SetDegrees(90);
}


void GateHorizontal(bool a_isOpen, Group& a_group)
{
    ascii::ColoredCanvas::Color color = a_isOpen ? ascii::ColoredCanvas::GREEN : ascii::ColoredCanvas::RED;
    static short lengthGate = 2;
    int spaciousUp = 1;
    int spaciousDown = 0;
    int xStart = 0;
    int ystart = 0;

    if (a_isOpen)
    {
        ++spaciousUp;
        ++spaciousDown;
        a_group.Add<Line>(xStart , ystart + 1, lengthGate).SetBrush(' ');//.SetDegrees(90);
        a_group.Add<Line>(xStart , ystart, lengthGate).SetBrush(' ');//.SetDegrees(90);
    }

    a_group.Add<Line>(xStart , ystart + spaciousUp, lengthGate).SetBrush('X').SetFg(color);//.SetDegrees(90);
    a_group.Add<Line>(xStart , ystart - spaciousDown, lengthGate).SetBrush('X').SetFg(color);//.SetDegrees(90);

}

void Gate(bool a_isOpen, Group& a_group, const DirectionDraw& a_direction)
{
    if (a_direction == DirectionDraw::Horizontal)
    {
        GateHorizontal(a_isOpen, a_group);
    }
    else
    {
        GateVertical(a_isOpen, a_group);
    }
}






void DrawSquareRoom(Group& a_group)
{
    using namespace roomDimension;
    ascii::ColoredCanvas::Color color = ascii::ColoredCanvas::CYAN;
    //std::unique_ptr<Group> g{std::make_unique<Group>(Group{0,0})};
    a_group.Add<Line>(0, 0, lengthWidth).SetBrush('-').SetFg(color);
    a_group.Add<Line>(0, 1,lengthHigh).SetBrush('|').SetFg(color).SetDegrees(90);
    a_group.Add<Line>(0,lengthHigh + 2,lengthWidth).SetBrush('-').SetFg(color);
    a_group.Add<Line>(lengthWidth,lengthHigh + 1,lengthHigh).SetBrush('|').SetFg(color).SetDegrees(270);
}



std::unique_ptr<Group> ProducesRoomStructureGroup(const StructureRoom& a_room, const Directions a_directory)
{
    using namespace roomDimension;
    std::unique_ptr<Group> g{std::make_unique<Group>(Group{startPointX,startPointY})};
    DrawSquareRoom(g->Add<Group>(startPointX, startPointY));
    Gate(a_room.GetIdxRoomNext(Directions::NORTH).has_value(), g->Add<Group>(lengthWidth / 2 + 3, startPointY - 2 ), DirectionDraw::Vertical);
    Gate(a_room.GetIdxRoomNext(Directions::SOUTH).has_value(), g->Add<Group>(lengthWidth / 2 + 3, startPointY + lengthHigh + 2), DirectionDraw::Vertical);
    Gate(a_room.GetIdxRoomNext(Directions::WEST).has_value(), g->Add<Group>(startPointX - 2, (startPointY + lengthHigh) / 2 + 1), DirectionDraw::Horizontal);
    Gate(a_room.GetIdxRoomNext(Directions::EAST).has_value(), g->Add<Group>(startPointX + lengthWidth, (startPointY + lengthHigh) / 2 + 1), DirectionDraw::Horizontal);

    Line& direction = g->Add<Line>(lengthWidth / 2 + 2 , lengthHigh - 2, 0);
    direction.SetBrush(directionsToChar.at(a_directory)).SetFg(ascii::ColoredCanvas::YELLOW);
    return std::move(g);
}


} //experis
