#ifndef RUBIK_H
#define RUBIK_H

enum Color {
	black = 0,
	white,
	red,
	green,
	blue,
	yellow,
	orange
};

class RubikCube {
	private:
		int cube_size;

		Color*** face_color;

	public:
		RubikCube(int size=3);
		~RubikCube();

		void glRotate();
		void glDisplay();

	protected:
		void reset();
		void rotateColors();

		void glDrawCube(int x, int y, int z,
			Color front, Color left, Color right, Color back,
			Color top, Color down);

		void glSetColor(Color col); 
};

#endif