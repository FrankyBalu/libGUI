#include "../include/rect.h"
#include "../include/point.h"
#include <iostream>

int main ()
{
	std::cout << "Teste LIBGUI::RECT" << std::endl;
	LIBGUI::Rect rectA;
	LIBGUI::Rect rectB ( 3,3, 10, 20 );
	LIBGUI::Point pointA(20,20);
	
	std::cout << "Rect A:" << std::endl;
	std::cout << "\tX: " << rectA.getX() << std::endl;
	std::cout << "\tY: " << rectA.getY() << std::endl;
	std::cout << "\tW: " << rectA.getW() << std::endl;
	std::cout << "\tH: " << rectA.getH() << std::endl;
	std::cout << "Rect B:" << std::endl;
	std::cout << "\tX: " << rectB.getX() << std::endl;
	std::cout << "\tY: " << rectB.getY() << std::endl;
	std::cout << "\tW: " << rectB.getW() << std::endl;
	std::cout << "\tH: " << rectB.getH() << std::endl;
	std::cout << "Point A:" << std::endl;
	std::cout << "\tX: " << pointA.getX() << std::endl;
	std::cout << "\tY: " << pointA.getY() << std::endl;
	std::cout << std::endl << std::endl;
	
	std::cout << "Rect B wird gleich Rect A" << std::endl;
	std::cout << "Rect A wird Point A zugewiesen" << std::endl << std::endl;
	rectB = rectA;
	rectA = pointA;
	std::cout << "Rect A:" << std::endl;
	std::cout << "\tX: " << rectA.getX() << std::endl;
	std::cout << "\tY: " << rectA.getY() << std::endl;
	std::cout << "\tW: " << rectA.getW() << std::endl;
	std::cout << "\tH: " << rectA.getH() << std::endl;
	std::cout << "Rect B:" << std::endl;
	std::cout << "\tX: " << rectB.getX() << std::endl;
	std::cout << "\tY: " << rectB.getY() << std::endl;
	std::cout << "\tW: " << rectB.getW() << std::endl;
	std::cout << "\tH: " << rectB.getH() << std::endl;
	
}
