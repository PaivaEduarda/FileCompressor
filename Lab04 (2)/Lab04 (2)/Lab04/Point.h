using namespace std;

class Point
{
private:
	int x;
	int y;
	//questão A -
public:
	void Create(int ay, int ax, int bx, int by);
	void MoveTo(int px, int py);
	void Translate(int dx, int dy);
	int X();
	int Y();
};


