#include "TPlex.h"
#include "TLine.h"
#include "TStack.h"
#include <fstream>

void TPlex::attachToLeft(TLine *left, TLine *l)
{
	if (left->getLeft()->getName() == l->getLeft()->getName())
	{
		//delete l->getLeft();
		l->setLeft(left->getLeft());
		left->setLeft(l);
	}
	else
	{
		//delete l->getLeft(); 
		l->setLeft(left->getRight());
		left->setRight(l);
	}
}

void TPlex::addLine(TLine *l)
{

	if (l == nullptr)
	{
		return;
	}
	if (start == nullptr)
	{
		start = l;
	}
	else
	{

		TLine *left = findLineWithPoint(((TPoint*)l->getLeft())->getX(), ((TPoint*)l->getLeft())->getY());
		TLine *right = findLineWithPoint(((TPoint*)l->getRight())->getX(), ((TPoint*)l->getRight())->getY());

		if (left != nullptr && right == nullptr)
		{
			attachToLeft(left, l);
		}
		else if (left == nullptr && right != nullptr)
		{
			l->reserve();
			attachToLeft(right, l);
		}
		else if (left != nullptr && right != nullptr)
		{
			attachToLeft(left, l);

			if (right->getLeft()->getName() == l->getLeft()->getName())
			{
				//delete l->getRight();
				l->setRight(right->getLeft());
				l->getRight()->updateMultiplicity(1);
			}
			else
			{
				//delete l->getRight();
				l->setRight(right->getRight());
				l->getRight()->updateMultiplicity(1);
			}
		}
	}
}

TPlex::TPlex(TLine *l)
{
	start = l;
}

TPlex::TPlex(const TPlex &src)
{
	TBase *cur;
	TStack<TBase*> points;
	TStack<TLine*> lines;
	TPoint* dup[100];
	int count = 0;
	cur = src.start;
	lines.push(nullptr);

	while (cur != nullptr)
	{
		if (cur->getType() == POINT)
		{
			TPoint *copy;

			for (int i = 0; i < count && copy == nullptr; i++)
			{
				if (dup[i]->getName() == cur->getName())
				{
					copy = dup[i];
				}
			}

			if (copy == nullptr)
			{
				copy = new TPoint(*((TPoint*)cur));
				dup[count++] = copy;
			}

			points.push(copy);
			cur = lines.pop();
			((TLine*)cur)->updateMultiplicity();
		}
		else
		{
			switch (cur->getMultiplicity())
			{
			case 1:
				lines.push((TLine*)cur);
				cur = ((TLine*)cur)->getLeft();
				break;
			case 2:
				lines.push((TLine*)cur);
				cur = ((TLine*)cur)->getRight();
				break;
			case 3:
				((TLine*)cur)->updateMultiplicity();

				TLine *copy = new TLine(*((TLine*)cur));
				copy->setRight(points.pop());
				copy->setLeft(points.peek());

				points.push(copy);
				cur = lines.pop();

				if (cur != nullptr)
				{
					((TLine*)cur)->updateMultiplicity();
				}
				break;
			}
		}
	}

	start = (TLine*)points.pop();
}

TPlex& TPlex::operator=(const TPlex &src)
{
	delete start;

	TBase *cur;
	TStack<TBase*> points;
	TStack<TLine*> lines;
	TPoint* dup[100];
	int count = 0;
	cur = src.start;
	lines.push(nullptr);

	while (cur != nullptr)
	{
		if (cur->getType() == POINT)
		{
			TPoint *copy;

			for (int i = 0; i < count && copy == nullptr; i++)
			{
				if (dup[i]->getName() == cur->getName())
				{
					copy = dup[i];
				}
			}

			if (copy == nullptr)
			{
				copy = new TPoint(*((TPoint*)cur));
				dup[count++] = copy;
			}

			points.push(copy);
			cur = lines.pop();
			((TLine*)cur)->updateMultiplicity();
		}
		else
		{
			switch (cur->getMultiplicity())
			{
			case 1:
				lines.push((TLine*)cur);
				cur = ((TLine*)cur)->getLeft();
				break;
			case 2:
				lines.push((TLine*)cur);
				cur = ((TLine*)cur)->getRight();
				break;
			case 3:
				((TLine*)cur)->updateMultiplicity();
				TLine *copy = new TLine(*((TLine*)cur));
				copy->setRight(points.pop());
				copy->setLeft(points.peek());
				points.push(copy);
				cur = lines.pop();
				if (cur != nullptr)
				{
					((TLine*)cur)->updateMultiplicity();
				}
				break;
			}
		}
	}
	start = (TLine*)points.pop();

	return *this;
}

TPlex::~TPlex()
{

}

void TPlex::deleteLine(std::string name)
{

}

TLine* TPlex::findLineWithPoint(std::string name)
{
	TBase *cur = start;
	TStack<TLine *> lines(100);
	TLine* res = nullptr;

	while (cur != nullptr)
	{
		if (cur->getType() == POINT)
		{
			if (res == nullptr)
			{
				if (((TPoint*)cur)->getName() == name)
				{
					res = lines.peek();
				}
			}

			cur = lines.pop();
			if (cur != nullptr)
			{
				((TLine *)cur)->updateMultiplicity();
			}
		}
		else
		{
			switch (cur->getMultiplicity())
			{
			case 1:
				lines.push((TLine *)cur);
				cur = ((TLine *)cur)->getLeft();
				break;
			case 2:
				lines.push((TLine *)cur);
				cur = ((TLine *)cur)->getRight();
				break;
			case 3:
				((TLine *)cur)->updateMultiplicity();

				cur = lines.pop();
				if (cur != nullptr)
				{
					((TLine *)cur)->updateMultiplicity();
				}
				break;
			}
		}
	}

	return res;
}

TLine* TPlex::findLineWithPoint(int x, int y)
{
	TLine *res = nullptr;
	TBase *cur = start;
	TStack<TLine *> lines(100);

	while (cur != nullptr)
	{
		if (cur->getType() == POINT)
		{
			if (res == nullptr)
			{
				if (((TPoint*)cur)->distance(x, y) == 1)
				{
					res = lines.peek();
				}
			}

			cur = lines.pop();
			if (cur != nullptr)
			{
				((TLine *)cur)->updateMultiplicity();
			}
			
		}
		else
		{
			switch (cur->getMultiplicity())
			{
			case 1:
				lines.push((TLine *)cur);
				cur = ((TLine *)cur)->getLeft();
				break;
			case 2:
				lines.push((TLine *)cur);
				cur = ((TLine *)cur)->getRight();
				break;
			case 3:
				((TLine *)cur)->updateMultiplicity();

				cur = lines.pop();
				if (cur != nullptr)
				{
					((TLine *)cur)->updateMultiplicity();
				}
				break;
			}
		}
	}

	return res;
}

TPoint* TPlex::findPoint(std::string name)
{
	TPoint *res = nullptr;
	TBase *cur = start;
	TStack<TLine *> lines(100);
	//lines.push(nullptr);

	while (cur != nullptr)
	{
		if (cur->getType() == POINT)
		{
			if (res == nullptr)
			{
				if (((TPoint *)cur)->getName() == name)
				{
					res = (TPoint *)cur;
				}
			}

			cur = lines.pop();
			if (cur != nullptr)
			{
				((TLine *)cur)->updateMultiplicity();
			}
		}
		else
		{
			switch (cur->getMultiplicity())
			{
			case 1:
				lines.push((TLine *)cur);
				cur = ((TLine *)cur)->getLeft();
				break;
			case 2:
				lines.push((TLine *)cur);
				cur = ((TLine *)cur)->getRight();
				break;
			case 3:
				((TLine *)cur)->updateMultiplicity();
				cur = lines.pop();

				if (cur != nullptr)
				{
					((TLine *)cur)->updateMultiplicity();
				}
				break;
			}
		}
	}

	/*while (lines.peek() != nullptr)
	{
		cur = lines.pop();
		while (cur->getMultiplicity() != 1)
		{
			((TLine *)cur)->updateMultiplicity();
		}
	}*/

	return res;
}

TPoint* TPlex::findPoint(int x, int y)
{
	TPoint *res = nullptr;
	TBase *cur = start;
	TStack<TLine *> lines(100);
	//lines.push(nullptr);

	while (cur != nullptr)
	{
		if (cur->getType() == POINT)
		{
			if (res == nullptr)
			{
				if (((TPoint *)cur)->distance(x, y) == 1)
				{
					res = (TPoint *)cur;
				}
			}

			cur = lines.pop();
			if (cur != nullptr)
			{
				((TLine *)cur)->updateMultiplicity();
			}
		}
		else
		{
			switch (cur->getMultiplicity())
			{
			case 1:
				lines.push((TLine *)cur);
				cur = ((TLine *)cur)->getLeft();
				break;
			case 2:
				lines.push((TLine *)cur);
				cur = ((TLine *)cur)->getRight();
				break;
			case 3:
				((TLine *)cur)->updateMultiplicity();

			
				cur = lines.pop();

				if (cur != nullptr)
				{
					((TLine *)cur)->updateMultiplicity();
				}
				break;
			}
		}
	}

	/*while (lines.peek() != nullptr)
	{
		cur = lines.pop();
		while (cur->getMultiplicity() != 1)
		{
			((TLine *)cur)->updateMultiplicity();
		}
	}*/

	return res;
}

void TPlex::movePlex(int dx, int dy)
{
	TBase *cur = start;
	TStack<TPoint *> points(100);
	TStack<TLine *> lines(100);
	lines.push(nullptr);
	points.push(nullptr);

	while (cur != nullptr)
	{
		if (cur->getType() == POINT)
		{
			if (((TPoint*)cur)->getMultiplicity() == 1)
			{
				((TPoint*)cur)->updateMultiplicity(1);
				((TPoint*)cur)->move(dx, dy);
				points.push((TPoint *)cur);
			}

			cur = lines.pop();
			if (cur != nullptr)
			{
				((TLine *)cur)->updateMultiplicity();
			}
		}
		else
		{
			switch (cur->getMultiplicity())
			{
			case 1:
				lines.push((TLine *)cur);
				cur = ((TLine *)cur)->getLeft();
				break;
			case 2:
				lines.push((TLine *)cur);
				cur = ((TLine *)cur)->getRight();
				break;
			case 3:
				((TLine *)cur)->updateMultiplicity();

				cur = lines.pop();
				if (cur != nullptr)
				{
					((TLine *)cur)->updateMultiplicity();
				}
				break;
			}
		}
	}

	while (points.peek() != nullptr)
	{
		TPoint* p = points.pop();
		while (p->getMultiplicity() != 1)
		{
			p->updateMultiplicity(-1);
		}
	}
}

void TPlex::movePoint(int x, int y, int dx, int dy)
{
	TBase *cur = start;
	TStack<TLine *> lines(100);
	lines.push(nullptr);
	TPoint *res = nullptr;

	while (res == nullptr && cur != nullptr)
	{
		if (cur->getType() == POINT)
		{
			if (((TPoint*)cur)->distance(x, y) == 1)
			{
				res = (TPoint*)cur;
				res->move(dx, dy);

				while (lines.peek() != nullptr)
				{
					cur = lines.pop();
					while (cur->getMultiplicity() != 1)
					{
						((TLine *)cur)->updateMultiplicity();
					}
				}
			}

			cur = lines.pop();
			if (cur != nullptr)
			{
				((TLine *)cur)->updateMultiplicity();
			}
		}
		else
		{
			switch (cur->getMultiplicity())
			{
			case 1:
				lines.push((TLine *)cur);
				cur = ((TLine *)cur)->getLeft();
				break;
			case 2:
				lines.push((TLine *)cur);
				cur = ((TLine *)cur)->getRight();
				break;
			case 3:
				((TLine *)cur)->updateMultiplicity();

				cur = lines.pop();
				if (cur != nullptr)
				{
					((TLine *)cur)->updateMultiplicity();
				}
				break;
			}
		}
	}

	while (lines.peek() != nullptr)
	{
		cur = lines.pop();
		while (cur->getMultiplicity() != 1)
		{
			((TLine *)cur)->updateMultiplicity();
		}
	}
}

void TPlex::draw(System::Drawing::Graphics^ g)
{
	TBase *cur = start;
	TStack<TPoint*> points(100);
	TStack<TLine*> lines(100);
	lines.push(nullptr);
	TPoint *left, *right;

	while (cur != nullptr)
	{
		if (cur->getType() == POINT)
		{
			points.push((TPoint *)cur);
			cur = lines.pop();

			if (cur != nullptr)
			{
				((TLine*)cur)->updateMultiplicity();
			}
		}
		else
		{
			switch (cur->getMultiplicity())
			{
			case 1:
				lines.push((TLine *)cur);
				cur = ((TLine *)cur)->getLeft();
				break;
			case 2:
				lines.push((TLine *)cur);
				cur = ((TLine *)cur)->getRight();
				break;
			case 3:
				((TLine *)cur)->updateMultiplicity();

				TLine *nLine = new TLine(*((TLine *)cur));
				right = points.pop();
				left = points.peek();
				nLine->setLeft(left);
				nLine->setRight(right);

				nLine->show(g);
				right->show(g);
				left->show(g);

				cur = lines.pop();
				if (cur != nullptr)
				{
					((TLine *)cur)->updateMultiplicity();
				}
				break;
			}
		}
	}
}

void TPlex::recolor(int color)
{
	TBase *cur = start;
	//TStack<TPoint *> points(100);
	TStack<TLine *> lines(100);
	lines.push(nullptr);

	while (cur != nullptr)
	{
		if (cur->getType() == POINT)
		{
			((TPoint *)cur)->setColor(color);
			//points.push((TPoint *)cur);
			cur = lines.pop();

			if (cur != nullptr)
			{
				((TLine*)cur)->updateMultiplicity();
			}
		}
		else
		{
			switch (cur->getMultiplicity())
			{
			case 1:
				lines.push((TLine *)cur);
				cur = ((TLine *)cur)->getLeft();
				break;
			case 2:
				lines.push((TLine *)cur);
				cur = ((TLine *)cur)->getRight();
				break;
			case 3:
				((TLine*)cur)->updateMultiplicity();
				((TLine*)cur)->setColor(color);

				cur = lines.pop();
				if (cur != nullptr)
				{
					((TLine *)cur)->updateMultiplicity();
				}
				break;
			}
		}
	}
}

void TPlex::save(std::string path)
{
	if (!path.empty())
	{
		TBase *cur = start;
		TStack<TLine*> lines(100);
		lines.push(nullptr);
		std::ofstream outfile;
		outfile.open(path);

		while (cur != nullptr)
		{
			if (cur->getType() == POINT)
			{
				outfile << ((TPoint*)cur)->toString() << std::endl;

				cur = lines.pop();
				((TLine*)cur)->updateMultiplicity();
			}
			else
			{
				switch (cur->getMultiplicity())
				{
				case 1:
					lines.push((TLine*)cur);
					cur = ((TLine*)cur)->getLeft();
					break;
				case 2:
					lines.push((TLine*)cur);
					cur = ((TLine*)cur)->getRight();
					break;
				case 3:
					((TLine*)cur)->updateMultiplicity();

					outfile << ((TLine*)cur)->toString() << std::endl;
					cur = lines.pop();
					if (cur != nullptr)
					{
						((TLine*)cur)->updateMultiplicity();
					}
					break;
				}
			}
		}

		outfile.close();
	}
}

void TPlex::open(std::string path)
{
	if (!path.empty())
	{
		std::string item;
		std::ifstream infile;
		infile.open(path);
		TStack<TBase*> stack(100);
		TPoint* points[100];
		int lastp = -1;
		int pID = -1;
		TLine* lines[100];
		int lastl = -1;
		int lID = -1;

		while (!infile.eof())
		{
			getline(infile, item);
			if(item.find("|") == std::string::npos){ break; }
			if (item.find("POINT") != std::string::npos)
			{

				TPoint* point = new TPoint(item);
				for (int i = 0; i <= lastp && pID == -1; i++)
				{
					if (points[i]->getName() == point->getName())
					{
						pID = i;
					}
				}

				if (pID != -1)
				{
					stack.push(points[pID]);
					pID = -1;
				} else 
				{
					points[++lastp] = point;
					stack.push(point);
				}
			}
			else if (item.find("LINE") != std::string::npos)
			{
				TLine *line = new TLine(item);
				for (int i = 0; i <= lastl && lID == -1; i++)
				{
					if (lines[i]->getName() == line->getName())
					{
						lID = i;
					}
				}
				if (lID != -1)
				{
					line = lines[lID];
					lID = -1;
				}
				line->setRight(stack.pop());
				line->setLeft(stack.pop());
				stack.push(line);
			}
		}

		infile.close();
		start = (TLine*)stack.pop();
	}
}

void TPlex::showPointNames(System::Drawing::Graphics^ g)
{
	TBase *cur = start;
	TStack<TLine*> lines(100);
	lines.push(nullptr);

	while (cur != nullptr)
	{
		if (cur->getType() == POINT)
		{
			g->DrawString(
				gcnew System::String(cur->getName().c_str()),
				gcnew System::Drawing::Font(gcnew System::Drawing::FontFamily("Arial"), 16),
				gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black),
				(float)((TPoint*)cur)->getX() - 15,
				(float)((TPoint*)cur)->getY() - 30
			);

			cur = lines.pop();
			if (cur != nullptr)
			{
				((TLine*)cur)->updateMultiplicity();
			}
		}
		else
		{
			switch (cur->getMultiplicity())
			{
			case 1:
				lines.push((TLine*)cur);
				cur = ((TLine*)cur)->getLeft();
				break;
			case 2:
				lines.push((TLine*)cur);
				cur = ((TLine*)cur)->getRight();
				break;
			case 3:
				((TLine*)cur)->updateMultiplicity();
				//TLine *l = lines.pop();
				//cur = l;
				cur = lines.pop();
				if (cur != nullptr)
				{
					((TLine*)cur)->updateMultiplicity();
				}
				break;
			}
		}
	}

}
void TPlex::showNearesPointNames(System::Drawing::Graphics^ g, int x, int y)
{
	TBase *cur = start;
	TStack<TLine*> lines(100);
	lines.push(nullptr);

	while (cur != nullptr)
	{
		if (cur->getType() == POINT)
		{
			if (((TPoint*)cur)->distance(x, y) == 1)
			{
				g->DrawString(
					gcnew System::String(cur->getName().c_str()),
					gcnew System::Drawing::Font(gcnew System::Drawing::FontFamily("TimesNewRoman"), 12),
					gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black),
					(float)((TPoint*)cur)->getX() - 15,
					(float)((TPoint*)cur)->getY() - 30
				);
			}

			cur = lines.pop();
			if (cur != nullptr)
			{
				((TLine*)cur)->updateMultiplicity();
			}
		}
		else
		{
			switch (cur->getMultiplicity())
			{
			case 1:
				lines.push((TLine*)cur);
				cur = ((TLine*)cur)->getLeft();
				break;
			case 2:
				lines.push((TLine*)cur);
				cur = ((TLine*)cur)->getRight();
				break;
			case 3:
				((TLine*)cur)->updateMultiplicity();
				//TLine *l = lines.pop();
				//cur = l;
				cur = lines.pop();
				if (cur != nullptr)
				{
					((TLine*)cur)->updateMultiplicity();
				}
				break;
			}
		}
	}

}