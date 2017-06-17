#ifndef RUBIK_H
#define RUBIK_H

extern GLuint cube_textures[6];

enum Color {
	black = 0,
	white,	// BACK   0
	red,	// FRONT  1
	green,	// LEFT   2
	blue,	// RIGHT  3
	yellow,	// BOTTOM 4
	orange	// TOP    5
};

class RubikCube {
	private:
		int cube_size;
		float rotationAngle;

		int highlight;
		int*** cube_color;

	public:
		RubikCube(int size=3);
		~RubikCube();

		void highlightNext()	{ highlight++; highlight %= 3*cube_size;  };

		void glRotate();
		void glDisplay();

	protected:
		void resetColors();
		void rotateColors();

		void glDrawCube(int x, int y, int z,
			int front, int left, int right, int back,
			int top, int bottom);
};

#endif