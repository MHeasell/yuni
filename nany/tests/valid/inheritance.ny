
class Shape
{
public
	//! Surface area
	method surface;
}

class Rectangle : Shape
{
public
	method create
	{
		width  := 50u;
		height := 50u;
	}

	method create(w, h)
	{
		width  := w;
		height := h;
	}

	method surface
	{
		width * height
	}

	method := (copy)
	{
		width  := copy.width;
		height := copy.height;
	}

	//! Width of the rectangle
	property width;
	//! Height of the rectangle
	property height;
}


class Circle : Shape
{
public
	method create
	{
		radius := 1.0;
	}

	method create(r)
	{
		radius := r;
	}

	method surface
	{
		Math.pi * radius^2
	}

	//! Circle radius
	property radius;
}




function main
{
	l := [
		new Rectangle(10, 200),
		new class
		{
			method surface { "some strange text here" }
		},
		new Circle ];

	for i in l do
		system.writeln << i.classname << ": " << i.surface;
}
