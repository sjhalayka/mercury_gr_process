

// Uncomment this to visualize the orbit using OpenGL/GLUT
#define USE_OPENGL


#include "main.h"

#include <string>
#include <iomanip>
#include <bitset>
using std::to_string;

int main(int argc, char** argv)
{
	cout << setprecision(20) << endl;




#ifndef USE_OPENGL

	while (1)
	{
		idle_func();
	}

	return 0;
#endif

#ifdef USE_OPENGL
	glutInit(&argc, argv);
	init_opengl(win_x, win_y);
	glutReshapeFunc(reshape_func);
	glutIdleFunc(idle_func);
	glutDisplayFunc(display_func);
	glutKeyboardFunc(keyboard_func);
	glutMouseFunc(mouse_func);
	glutMotionFunc(motion_func);
	glutPassiveMotionFunc(passive_motion_func);
	//glutIgnoreKeyRepeat(1);
	glutMainLoop();
	glutDestroyWindow(win_id);
#endif

	return 0;
}






custom_math::vector_3 grav_acceleration(const custom_math::vector_3& pos, const custom_math::vector_3& vel, const long double G)
{
	custom_math::vector_3 grav_dir = sun_pos - pos;

	const double distance = grav_dir.length();
	grav_dir.normalize();

	custom_math::vector_3 accel = grav_dir * G * sun_mass / (distance * distance);

	return accel;
}


//
//double truncate_normalized_double(const double d)
//{
//	float a = d - numeric_limits<float>::epsilon();
//	float b = d + numeric_limits<float>::epsilon();
//
//	float r1 = abs(d - a);
//	float r2 = abs(d - b);
//
//	if (r1 < r2)
//		return static_cast<double>(a);
//	else
//		return static_cast<double>(b);
//}
//

//
//double truncate_normalized_double(const double d)
//{
//	float num = 1;
//
//	while (num >= d)
//		num -= numeric_limits<float>::epsilon();
//
//	if (num < 0)
//		num = 0;
//
//	return num;
//}
//
//
//double round6(double x) {
//	return std::round(x * 1e4) / 1e4;
//}
//
//	
//double truncate_normalized_double(double d)
//{
//	if (d <= 0.0)
//		return 0.0f;
//	else if (d >= 1.0)
//		return 1.0f;
//
//	double result = 0;
//	int exponent = 0;
//	double s = signbit(d);
//
//	result = frexp(d, &exponent);
//
//	const double d_final = result * pow(2.0, static_cast<double>(exponent));
//
//	return copysign(d_final, s);
//}


#include <bitset>
#include <iostream>
#include <string>



//
//
//double truncate_normalized_double(double d)
//{
//	if (d <= 0.0)
//		return 0.0;
//	else if (d >= 1.0)
//		return 1.0;
//
//	//return static_cast<double>(static_cast<float>(d));
//
//	//string s;
//	//get_double_bit_string(d, s);
//	//cout << s << endl;
//
//	const int64_t mantissa_size = 52;
//	uint64_t max = static_cast<uint64_t>(-1); // 2^64 - 1
//
//	uint64_t bits = reinterpret_cast<uint64_t&>(d);
//	bits = bits & (max << 30);
//	double reduced = reinterpret_cast<double&>(bits);
//
//	//get_double_bit_string(reduced, s);
//	//cout << s << endl;
//
//	//double df = static_cast<double>(static_cast<float>(d));
//	//string sdf = "";
//	//get_double_bit_string(df, sdf);
//	//cout << sdf << endl;
//
//	return reduced;
//}



/*
size_t get_first_one_from_right(const string& s)
{
	bool found_one = false;

	signed long long int i = 0;

	signed long long int ssize = s.size() - 1;


	for (i = ssize; i >= 0; i--)
	{
		if (s[i] == '1')
		{
			return i;
		}
	}

	return i;

	//	cout << endl;

}


size_t get_last_one_from_right(const string& s)
{
	bool found_one = false;

	signed long long int i = 0;

	signed long long int ssize = s.size() - 1;


	for (i = ssize; i >= 0; i--)
	{
		if (found_one == false)
		{
			if (s[i] == '1')
			{
				if (i == ssize)
					return ssize;

				found_one = true;
			}
		}
		else
		{
			if (s[i] == '0')
			{
				i++;
				break;
			}
		}
	}

	return i;

	//	cout << endl;

}


void get_truncated_bit_string(double d, string& s)
{
	s = "";

	for (int i = 63; i >= 0; i--)
	{
		if (i <= 27)
			s += '0';
		else
			s += to_string((reinterpret_cast<uint64_t&>(d) >> i) & 1);
	}
}

void get_double_bit_string(double d, string& s)
{
	s = "";

	for (int i = 63; i >= 0; i--)
		s += to_string((reinterpret_cast<uint64_t&>(d) >> i) & 1);
}


double truncate_normalized_double(double d)
{
	if (d <= 0.0)
		return 0.0;
	else if (d >= 1.0)
		return 1.0;

	return static_cast<double>(static_cast<float>(d));

	string sd = "";
	get_double_bit_string(d, sd);
	//cout << sd << endl;

	std::bitset<64> Bitset64(sd);

	uint64_t value = Bitset64.to_ullong();

	double dv = reinterpret_cast<double&>(value);
	string sdv = "";
	get_truncated_bit_string(dv, sdv);

	size_t st = get_last_one_from_right(sdv) - 1;

	size_t st_first = get_first_one_from_right(sdv);

	if (st_first != st)
	{
		size_t st = get_last_one_from_right(sdv) - 1;

		sdv[st] = '1';

		for (size_t i = st + 1; i < sdv.size(); i++)
			sdv[i] = '0';
	}

	std::bitset<64> Bitset64sdv(sdv);
	value = Bitset64sdv.to_ullong();
	dv = reinterpret_cast<double&>(value);
	//cout << sdv << endl;




	//double df = static_cast<double>(static_cast<float>(d));
	//string sdf = "";
	//get_double_bit_string(df, sdf);
	////cout << sdf << endl;

	return dv;
}


*/






//
//double truncate_normalized_double(double d)
//{
//	//return static_cast<double>(static_cast<float>(d));
//
//	string s = "";
//
//	for (int i = 63; i >= 0; i--)
//	{
//		if (i <= 23)
//			s += "0";
//		else
//			s += to_string((reinterpret_cast<uint64_t&>(d) >> i) & 1);
//	}
//
//	std::bitset<64> Bitset64(s);
//
//	uint64_t value = Bitset64.to_ullong();
//
//	return reinterpret_cast<double&>(value);
//
////	std::cout << d << endl <<  << endl;
//
//
//	//cout << s << endl;
//
////	cout << endl;
////	cout << endl;
//
//
//
//	//const int64_t mantissa_size = 52;
//	//uint64_t max = static_cast<uint64_t>(-1); // 2^64 - 1
//
//	//uint64_t bits = reinterpret_cast<uint64_t&>(d);
//
//
//
//
//
//
//
//
//	//bits = bits & (max << 23);
//	//d = reinterpret_cast<double&>(bits);
//	////cout << d << endl;
//
//	//return d;
//}
//



//
//double truncate_normalized_double(const double d)
//{
//	//return static_cast<float>(round6(d));
//
//
//
////	return static_cast<double>(static_cast<float>(d));
//
//	if (d <= 0.0)
//		return 0.0f;
//	else if (d >= 1.0)
//		return 1.0f;
//
//	float df = static_cast<float>(d);
//
//	float tempf = nexttowardf(1.0f, df);
//
//	while (tempf > df)
//		tempf = nexttowardf(tempf, df);
//
//	return static_cast<double>(tempf);
//}









//
//void get_truncated_bit_string(double d, string& s)
//{
//	s = "";
//
//	for (int i = 63; i >= 0; i--)
//	{
//		if (i <= 31)
//			s += '0';
//		else
//			s += to_string((reinterpret_cast<uint64_t&>(d) >> i) & 1);
//	}
//}
//
//void get_double_bit_string(double d, string& s)
//{
//	s = "";
//
//	for (int i = 63; i >= 0; i--)
//		s += to_string((reinterpret_cast<uint64_t&>(d) >> i) & 1);
//}
//
//
//double truncate_normalized_double(double d)
//{
//	//return static_cast<double>(static_cast<float>(d));
//
//	double value = d;
//	uint64_t bits = (uint64_t&)value;
//		bits = bits & 0b1111111111111111111111111111111110000000000000000000000000000000ull;
//
//	double truncated = (double&)bits;
//
//	return truncated;
//
//
//
//
//
//
////	string sd = "";
////	get_double_bit_string(truncated, sd);
////	cout << sd << endl;
//
//
//
//
//	//std::bitset<64> Bitset64(sd);
//
//	//uint64_t value = Bitset64.to_ullong();
//
//	//double dv = reinterpret_cast<double&>(value);
//	//string sdv = "";
//	//get_truncated_bit_string(dv, sdv);
//	//cout << sdv << endl;
//
//
//
//
////double df = static_cast<double>(static_cast<float>(d));
//	//string sdf = "";
//	//get_double_bit_string(df, sdf);
////	cout << sdf << endl;
//
//	return truncated;
//}
//
//
//









//
//
//
//void get_truncated_bit_string(double d, string& s)
//{
//	s = "";
//
//	for (int i = 63; i >= 0; i--)
//	{
//		if (i <= 30)
//		{
//			if (i == 30)
//				s += '1';
//			else
//				s += '0';
//		}
//		else
//			s += to_string((reinterpret_cast<uint64_t&>(d) >> i) & 1);
//	}
//}
//
//void get_double_bit_string(double d, string& s)
//{
//	s = "";
//
//	for (int i = 63; i >= 0; i--)
//		s += to_string((reinterpret_cast<uint64_t&>(d) >> i) & 1);
//}
//
//
//double truncate_normalized_double(double d)
//{
//	if (d <= 0)
//		return 0;
//	
//	if (d >= 1)
//		return 1;
//
//	//return static_cast<double>(static_cast<float>(d));
//
//	string sd = "";
//	get_double_bit_string(d, sd);
//	//cout << sd << endl;
//
//	std::bitset<64> Bitset64(sd);
//
//	uint64_t value = Bitset64.to_ullong();
//
//	double dv = reinterpret_cast<double&>(value);
//	string sdv = "";
//	get_truncated_bit_string(dv, sdv);
////	cout << sdv << endl;
//
//	//double df = static_cast<double>(static_cast<float>(d));
//	//string sdf = "";
//	//get_double_bit_string(df, sdf);
//	//cout << sdf << endl;
//
//	return dv;
//}
//
//
//









//
//
//double truncate_normalized_double(double d)
//{
//	if (d <= 0.0)
//		return 0.0;
//	else if (d >= 1.0)
//		return 1.0;
//
//	//////return static_cast<double>(static_cast<float>(d));
//
//
//
//	static int shift = 52 - 23;
//
//	//double ref = static_cast<double>(static_cast<float>(d));
//
////	cout << ref << endl;
//
//	//string s = "";
//	//get_double_bit_string(ref, s);
//	//cout << s << endl;
//
//	uint64_t max = -1;
//
//	uint64_t bits = (uint64_t&)d;
//	bits = bits & (uint64_t(max << shift));
//	double emu = (double&)bits;
//
//	//	cout << emu << endl;
//
//	//	s = "";
//	//	get_double_bit_string(emu, s);
//	//	cout << s << endl;
//
//	return emu;
//}







//
//double truncate_normalized_double(double d)
//{
//	if (d <= 0.0)
//		return 0.0;
//	else if (d >= 1.0)
//		return 1.0;
//
//	////return static_cast<double>(static_cast<float>(d));
//
//	uint64_t shift = static_cast<uint64_t>(52) - static_cast<uint64_t>(23);
//	uint64_t max = static_cast<uint64_t>(-1);
//
//	uint64_t bits = (uint64_t&)d;
//	bits = bits & (uint64_t(max << shift));
//	double emu = (double&)bits;
//
//	return emu;
//}




//
//double truncate_normalized_double(double d)
//{
//	if (d <= 0.0)
//		return 0.0;
//	else if (d >= 1.0)
//		return 1.0;
//
//	//////return static_cast<double>(static_cast<float>(d));
//
//	float f = static_cast<float>(d);
//
//	float tempf = nexttowardf(1.0f, f);
//
//	while (tempf > f)
//		tempf = nexttowardf(tempf, f);
//
//	return static_cast<double>(tempf);
//}
//
//
//
//
//






double truncate_normalized_double(double d)
{
	if (d <= 0.0)
		return 0.0;
	else if (d >= 1.0)
		return 1.0;


	float f = static_cast<float>(d);

	return f;

	static const long long signed int mantissa_bits = 23;

	static const double epsilon = pow(2, -mantissa_bits);
	const double remainder = fmod(d, epsilon);

	d = nexttowardf(d, d - remainder);

	return d;
}





void proceed_symplectic4(custom_math::vector_3& pos, custom_math::vector_3& vel, long double G, long double dt)
{
	static double const cr2 = pow(2.0, 1.0 / 3.0);

	static const double c[4] =
	{
		1.0 / (2.0 * (2.0 - cr2)),
		(1.0 - cr2) / (2.0 * (2.0 - cr2)),
		(1.0 - cr2) / (2.0 * (2.0 - cr2)),
		1.0 / (2.0 * (2.0 - cr2))
	};

	static const double d[4] =
	{
		1.0 / (2.0 - cr2),
		-cr2 / (2.0 - cr2),
		1.0 / (2.0 - cr2),
		0.0
	};

	{
		const custom_math::vector_3 grav_dir = sun_pos - pos;
		const double distance = grav_dir.length();
		const double Rs = 2 * grav_constant * sun_mass / (speed_of_light * speed_of_light);

		const double alpha = 2.0 - sqrt(1 - (vel.length() * vel.length()) / (speed_of_light * speed_of_light));

		const double beta = sqrt(1.0 - Rs / distance);
		const double beta_truncated = truncate_normalized_double(beta);

		pos += vel * c[0] * dt * beta_truncated;
		vel += grav_acceleration(pos, vel, G) * d[0] * dt * alpha;
	}

	{
		const custom_math::vector_3 grav_dir = sun_pos - pos;
		const double distance = grav_dir.length();
		const double Rs = 2 * grav_constant * sun_mass / (speed_of_light * speed_of_light);

		const double alpha = 2.0 - sqrt(1 - (vel.length() * vel.length()) / (speed_of_light * speed_of_light));

		const double beta = sqrt(1.0 - Rs / distance);
		const double beta_truncated = truncate_normalized_double(beta);

		pos += vel * c[1] * dt * beta_truncated;
		vel += grav_acceleration(pos, vel, G) * d[1] * dt * alpha;
	}

	{
		const custom_math::vector_3 grav_dir = sun_pos - pos;
		const double distance = grav_dir.length();
		const double Rs = 2 * grav_constant * sun_mass / (speed_of_light * speed_of_light);

		const double alpha = 2.0 - sqrt(1 - (vel.length() * vel.length()) / (speed_of_light * speed_of_light));

		const double beta = sqrt(1.0 - Rs / distance);
		const double beta_truncated = truncate_normalized_double(beta);

		pos += vel * c[2] * dt * beta_truncated;
		vel += grav_acceleration(pos, vel, G) * d[2] * dt * alpha;
	}

	{
		const custom_math::vector_3 grav_dir = sun_pos - pos;
		const double distance = grav_dir.length();
		const double Rs = 2 * grav_constant * sun_mass / (speed_of_light * speed_of_light);

		const double alpha = 2.0 - sqrt(1 - (vel.length() * vel.length()) / (speed_of_light * speed_of_light));

		const double beta = sqrt(1.0 - Rs / distance);
		const double beta_truncated = truncate_normalized_double(beta);

		pos += vel * c[3] * dt * beta_truncated;
		//	vel += grav_acceleration(pos, vel, G) * d[3] * dt * alpha; // last element d[3] is always 0
	}
}






void proceed_Euler(custom_math::vector_3& pos, custom_math::vector_3& vel, const long double G, const long double dt)
{
	const custom_math::vector_3 grav_dir = sun_pos - pos;
	const double distance = grav_dir.length();
	const double Rs = 2 * grav_constant * sun_mass / (speed_of_light * speed_of_light);

	double alpha = 2.0 - sqrt(1 - (vel.length() * vel.length()) / (speed_of_light * speed_of_light));

	const double beta = sqrt(1.0 - Rs / distance);

	const double beta_truncated = truncate_normalized_double(beta);

	custom_math::vector_3 accel = grav_acceleration(pos, vel, G);

	vel += accel * dt * alpha;
	pos += vel * dt * beta_truncated;
}


long unsigned int frame_count = 0;

void idle_func(void)
{
	frame_count++;

	custom_math::vector_3 last_pos = mercury_pos;

	//proceed_Euler(mercury_pos, mercury_vel, grav_constant, dt);
	proceed_symplectic4(mercury_pos, mercury_vel, grav_constant, dt);
	
	const long double radial_vel = mercury_pos.dot(mercury_vel);

	if (decreasing)
	{
		if (radial_vel > 0)
		{
			// hit perihelion
			cout << "hit perihelion" << endl;
			decreasing = false;
			return;
		}
	}
	else
	{
		if (radial_vel < 0 && frame_count > 1)
		{
			// hit aphelion
			cout << "hit aphelion" << endl;

			orbit_count++;

			custom_math::vector_3 current_dir = last_pos;
			current_dir.normalize();

			const long double d = current_dir.dot(previous_dir);

			const long double angle = acos(d);

			if (isnan(angle))
				cout << "nan" << endl;

			previous_dir = current_dir;

			static const long double num_orbits_per_earth_century = 365.0 / 88.0 * 100;
			static const long double to_arcseconds = 1.0 / (pi / (180.0 * 3600.0));

			cout << "orbit " << orbit_count << endl;
			cout << "dot   " << d << endl;
			cout << "angle " << angle * num_orbits_per_earth_century * to_arcseconds << endl;
			cout << "delta " << delta * num_orbits_per_earth_century * to_arcseconds << endl;
			cout << "delta_earth " << delta_earth * 100 * to_arcseconds << endl;


			cout << endl;

#ifdef USE_OPENGL
			positions.clear();
#endif
			decreasing = true;

			exit(0);
		}
	}

#ifdef USE_OPENGL

	if (frame_count % 100000 == 0)
	{
		positions.push_back(mercury_pos);

		glutPostRedisplay();
	}

#endif
}


#ifdef USE_OPENGL

void init_opengl(const int& width, const int& height)
{
	win_x = width;
	win_y = height;

	if (win_x < 1)
		win_x = 1;

	if (win_y < 1)
		win_y = 1;

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(win_x, win_y);
	win_id = glutCreateWindow("orbit");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glClearColor(background_colour.x, background_colour.y, background_colour.z, 1);
	glClearDepth(1.0f);

	main_camera.Set(0, 0, camera_w, camera_fov, win_x, win_y, camera_near, camera_far);
}

void reshape_func(int width, int height)
{
	win_x = width;
	win_y = height;

	if (win_x < 1)
		win_x = 1;

	if (win_y < 1)
		win_y = 1;

	glutSetWindow(win_id);
	glutReshapeWindow(win_x, win_y);
	glViewport(0, 0, win_x, win_y);

	main_camera.Set(main_camera.u, main_camera.v, main_camera.w, main_camera.fov, win_x, win_y, camera_near, camera_far);
}

// Text drawing code originally from "GLUT Tutorial -- Bitmap Fonts and Orthogonal Projections" by A R Fernandes
void render_string(int x, const int y, void* font, const string& text)
{
	for (size_t i = 0; i < text.length(); i++)
	{
		glRasterPos2i(x, y);
		glutBitmapCharacter(font, text[i]);
		x += glutBitmapWidth(font, text[i]) + 1;
	}
}
// End text drawing code.

void draw_objects(void)
{
	glDisable(GL_LIGHTING);

	glPushMatrix();


	glPointSize(1.0);
	glLineWidth(1.0);


	glBegin(GL_POINTS);
	glVertex3f(sun_pos.x, sun_pos.y, sun_pos.z);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(1.0, 1.0, 1.0);

	for (size_t i = 0; i < positions.size(); i++)
		glVertex3d(positions[i].x, positions[i].y, positions[i].z);

	glEnd();





	glLineWidth(1.0f);


	// If we do draw the axis at all, make sure not to draw its outline.
	if (true == draw_axis)
	{
		glBegin(GL_LINES);

		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(1, 0, 0);
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1, 0);
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 1);

		glColor3f(0.5, 0.5, 0.5);
		glVertex3f(0, 0, 0);
		glVertex3f(-1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, -1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, -1);

		glEnd();
	}

	glPopMatrix();
}




void display_func(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw the model's components using OpenGL/GLUT primitives.
	draw_objects();

	if (true == draw_control_list)
	{
		// Text drawing code originally from "GLUT Tutorial -- Bitmap Fonts and Orthogonal Projections" by A R Fernandes
		// http://www.lighthouse3d.com/opengl/glut/index.php?bmpfontortho
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, win_x, 0, win_y);
		glScalef(1, -1, 1); // Neat. :)
		glTranslatef(0, -win_y, 0); // Neat. :)
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glColor3f(control_list_colour.x, control_list_colour.y, control_list_colour.z);

		size_t break_size = 22;
		size_t start = 20;
		ostringstream oss;

		render_string(10, start, GLUT_BITMAP_HELVETICA_18, string("Mouse controls:"));
		render_string(10, start + 1 * break_size, GLUT_BITMAP_HELVETICA_18, string("  LMB + drag: Rotate camera"));
		render_string(10, start + 2 * break_size, GLUT_BITMAP_HELVETICA_18, string("  RMB + drag: Zoom camera"));

		render_string(10, start + 4 * break_size, GLUT_BITMAP_HELVETICA_18, string("Keyboard controls:"));
		render_string(10, start + 5 * break_size, GLUT_BITMAP_HELVETICA_18, string("  w: Draw axis"));
		render_string(10, start + 6 * break_size, GLUT_BITMAP_HELVETICA_18, string("  e: Draw text"));


		custom_math::vector_3 eye = main_camera.eye;
		custom_math::vector_3 eye_norm = eye;
		eye_norm.normalize();

		oss.clear();
		oss.str("");
		oss << "Camera position: " << eye.x << ' ' << eye.y << ' ' << eye.z;
		render_string(10, win_y - 2 * break_size, GLUT_BITMAP_HELVETICA_18, oss.str());

		oss.clear();
		oss.str("");
		oss << "Camera position (normalized): " << eye_norm.x << ' ' << eye_norm.y << ' ' << eye_norm.z;
		render_string(10, win_y - break_size, GLUT_BITMAP_HELVETICA_18, oss.str());

		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		// End text drawing code.
	}

	glFlush();
	glutSwapBuffers();
}

void keyboard_func(unsigned char key, int x, int y)
{
	switch (tolower(key))
	{
	case 'w':
	{
		draw_axis = !draw_axis;
		break;
	}
	case 'e':
	{
		draw_control_list = !draw_control_list;
		break;
	}

	default:
		break;
	}
}

void mouse_func(int button, int state, int x, int y)
{
	if (GLUT_LEFT_BUTTON == button)
	{
		if (GLUT_DOWN == state)
			lmb_down = true;
		else
			lmb_down = false;
	}
	else if (GLUT_MIDDLE_BUTTON == button)
	{
		if (GLUT_DOWN == state)
			mmb_down = true;
		else
			mmb_down = false;
	}
	else if (GLUT_RIGHT_BUTTON == button)
	{
		if (GLUT_DOWN == state)
			rmb_down = true;
		else
			rmb_down = false;
	}
}

void motion_func(int x, int y)
{
	int prev_mouse_x = mouse_x;
	int prev_mouse_y = mouse_y;

	mouse_x = x;
	mouse_y = y;

	int mouse_delta_x = mouse_x - prev_mouse_x;
	int mouse_delta_y = prev_mouse_y - mouse_y;

	if (true == lmb_down && (0 != mouse_delta_x || 0 != mouse_delta_y))
	{
		main_camera.u -= static_cast<float>(mouse_delta_y) * u_spacer;
		main_camera.v += static_cast<float>(mouse_delta_x) * v_spacer;
	}
	else if (true == rmb_down && (0 != mouse_delta_y))
	{
		main_camera.w -= static_cast<float>(mouse_delta_y) * w_spacer;

		if (main_camera.w < 1.1f)
			main_camera.w = 1.1f;

	}

	main_camera.Set(); // Calculate new camera vectors.
}

void passive_motion_func(int x, int y)
{
	mouse_x = x;
	mouse_y = y;
}

#endif