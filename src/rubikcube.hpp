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
		float rotationHigh;

		Color*** face_color;

	public:
		RubikCube(int size=3);
		~RubikCube();

		void glRotate(int msdelay=250, int fps=20);
		void glDisplay();

	protected:
		void resetColors();
		void rotateColors();

		void glDrawCube(int x, int y, int z,
			Color front, Color left, Color right, Color back,
			Color top, Color bottom);

		void glSetColor(Color col); 
};

#endif