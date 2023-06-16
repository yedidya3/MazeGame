#include "Dragon.h"
#include "Line.h"
namespace experis
{



bool IsLife(Dragon& a_dargon)
{
	return a_dargon.GetNumPointsLife() > 0;
}




void Draw(const Dragon& a_dragon, Group& a_group)
{
	a_group.Add<Line>(0,0,0).SetBrush('0').SetFg(ascii::ColoredCanvas::RED);
	a_group.Add<Line>(-1,-1,0).SetBrush('o').SetFg(ascii::ColoredCanvas::YELLOW);
	a_group.Add<Line>(1,-1,0).SetBrush('o').SetFg(ascii::ColoredCanvas::YELLOW);
	a_group.Add<Line>(1,0,0).SetBrush('\\').SetFg(ascii::ColoredCanvas::YELLOW);
	//a_group.Add<Line>(0,2,0).SetBrush('=').SetFg(ascii::ColoredCanvas::YELLOW);
	a_group.Add<Line>(-1,0,0).SetBrush('/').SetFg(ascii::ColoredCanvas::YELLOW);
	//a_group.Add<Line>(1,1,0).SetBrush('&').SetFg(ascii::ColoredCanvas::YELLOW);
}


}