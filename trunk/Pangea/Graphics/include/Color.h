/*
 * Color.h
 *
 *  Created on: Mar 10, 2011
 *      Author: mmerchan
 */

#include <SDL/SDL.h>
#include <GL/gl.h>

#ifndef COLOR_H_
#define COLOR_H_

class Color {

	private:

		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;

	public:

		Color() {
			r = g = b = a = 0;
		}

		Color(unsigned int r, unsigned int g, unsigned int b) {
			if (r < 256)
				this->r = r;
			else
				this->r = 255;
			if (b < 256)
				this->b = b;
			else
				this->b = 255;
			if (g < 256)
				this->g = g;
			else
				this->g = 255;

			a = 255; // default alpha
		}

		Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
			if (r < 256)
				this->r = r;
			else
				this->r = 255;
			if (b < 256)
				this->b = b;
			else
				this->b = 255;
			if (g < 256)
				this->g = g;
			else
				this->g = 255;
			if (a < 256)
				this->a = a;
			else
				this->a = 255;
		}

		unsigned char getAlpha() {
			return a;
		}

		unsigned char getR() {
			return r;
		}

		unsigned char getG() {
			return g;
		}

		unsigned char getB() {
			return b;
		}

		Color setAlpha(unsigned int alpha) {
			a = alpha > 255 ? 255 : alpha;
			return *this;
		}

		// Utilities
		void set_GLColor() {
			glColor4f(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
		}

		SDL_Color getSDL_Color() {
			SDL_Color tmp = { (Uint8) r, (Uint8) g, (Uint8) b };
			return tmp;
		}

		// Operators
		Color operator*(float param) {
			unsigned char tmpr = (r * param > 255) ? 255 : (unsigned char) (r
					* param);
			unsigned char tmpg = (g * param > 255) ? 255 : (unsigned char) (g
					* param);
			unsigned char tmpb = (b * param > 255) ? 255 : (unsigned char) (b
					* param);
			//unsigned char tmpa = (a*param > 255) ? 255 :  (unsigned char)(a*param);
			return Color(tmpr, tmpg, tmpb, a);
		}

		Color operator/(float param) {
			return (*this) * (1 / param);
		}

		Color operator-(Color& tmp) {
			return Color(this->r - tmp.r, this->g - tmp.g, this->b - tmp.b,
					this->a - tmp.a);
		}

		Color operator+(Color& tmp) {
			return Color(this->r + tmp.r, this->g + tmp.g, this->b + tmp.b,
					this->a + tmp.a);
		}

		bool operator==(Color& tmp) {
			if (this->r == tmp.r && this->g == tmp.g && this->b == tmp.b
					&& this->a == tmp.a)
				return true;
			else
				return false;
		}

		bool operator>(Color& tmp) {
			if (this->r > tmp.r || this->g > tmp.g || this->b > tmp.b
					|| this->a > tmp.a)
				return true;
			else
				return false;
		}

		bool operator<(Color& tmp) {
			return (tmp > *this);
		}
};

#endif /* COLOR_H_ */
