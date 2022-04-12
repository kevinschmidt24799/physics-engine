//
// Created by Kevin Schmidt on 3/31/22.
//

#include <unistd.h>
#include "simulation.hpp"

const int timer_ms = 1000/60;

void Simulation::reset()
{
    particles_.clear();
    bonds_.clear();



    for(int x = -100; x <= 100; x+=20)
    {
        for(int y = 800; y <= 1000; y+=20)
        {
            for(int z = -100; z <= 100; z+=20)
            {
                auto r = sqrtf(x*x + (y-900)*(y-900) + z*z);
                if(r < 85 && r > 0)
                {
                    particle(2*x, 2*y, 2*z);
                }
            }
        }
    }

    for(int i = 1; i <= particles_.size(); ++i)
    {
        for(int j = i+1; j <= particles_.size(); ++j)
        {
            if(distance(particles_[i-1], particles_[j-1]) < 120)
            {
                bond(i, j);
            }
        }
    }
}

void Simulation::run()
{
    for(auto & j : bonds_)
    {
        j.set_forces();
    }

    for(auto & j : particles_)
    {
        j.f.y() -= 0.5;
        j.move();
    }

}

void Simulation::run(int cycles)
{
    for (int i = 0; i < cycles; ++i)
    {
        run();
    }
}

int Simulation::particle(float x, float y, float z)
{
    particles_.emplace_back(Point {{x}, {y}, {z}});
    return particles_.size();
}

void Simulation::bond(int p1, int p2)
{
    bonds_.emplace_back(&particles_[p1 - 1], &particles_[p2 - 1]);
}


void Simulation::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, static_cast<float>(glutGet(GLUT_WINDOW_WIDTH))/glutGet(GLUT_WINDOW_HEIGHT),  0.01, 100);
    auto e = eye_ * Matrix<3,1>{{0},{0},{2}};
    auto up = Matrix<3,1>{{0},{1},{0}};
    gluLookAt(e.data_[0][0], e.data_[1][0], e.data_[2][0], 0, 0, 0, up.data_[0][0], up.data_[1][0], up.data_[2][0]);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    draw();

    glutSwapBuffers();
}

void Simulation::draw()
{
    for(auto const & i : bonds_)
    {
        glPushMatrix();
        glColor3f(0, 0, 1);
        glBegin(GL_LINES);
            glVertex3f(i.p1_->p.x()/500, i.p1_->p.y()/500, i.p1_->p.z()/500);
            glVertex3f(i.p2_->p.x()/500, i.p2_->p.y()/500, i.p2_->p.z()/500);
        glEnd();
        glPopMatrix();
    }

    glPushMatrix();
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
        glVertex3f(5, 0, 5);
        glVertex3f(-5, 0, 5);
        glVertex3f(-5, 0, -5);
        glVertex3f(5, 0, -5);
    glEnd();
    glPopMatrix();

    for (int i = -50; i <= 50; i += 1)
    {
        glPushMatrix();
        glColor3f(1, 0, 0);
        glBegin(GL_LINES);
        glVertex3f(i/10.0f, 0, -5);
        glVertex3f(i/10.0f, 0, 5);
        glEnd();
        glPopMatrix();
    }

    for (int i = -50; i <= 50; i += 1)
    {
        glPushMatrix();
        glColor3f(1, 0, 0);
        glBegin(GL_LINES);
        glVertex3f(-5, 0, i/10.0f);
        glVertex3f(5, 0, i/10.0f);
        glEnd();
        glPopMatrix();
    }
}

void Simulation::mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        left = (state == GLUT_DOWN);
        leftx = x;
        lefty = y;
    }
}

void Simulation::motion(int x, int y)
{
    if(left)
    {
        float rotate = 0.5;
        eye_ = rotate_na(rotate*(leftx-x), 0, 1, 0) * eye_;
        leftx = x;
        eye_ = rotate_na(rotate*(lefty-y), 1, 0, 0) * eye_;
        lefty = y;
        //glutGet(GLUT_WINDOW_WIDTH)
    }
    glutPostRedisplay();
}

void Simulation::keys(unsigned char c, int x, int y)
{
    if(c=='-')
    {
        eye_ = eye_ * 1.1;
    }
    if(c=='+' || c=='=')
    {
        eye_ = eye_ / 1.1;
    }
    if(c=='r')
    {
        reset();
    }
    glutPostRedisplay();
}

void Simulation::keysup(unsigned char c, int x, int y)
{

}


static Simulation * s;
void s_display(){s->display();}
void s_mouse(int button, int state, int x, int y) {s->mouse(button, state, x, y); }
void s_motion(int x, int y) {s->motion(x, y);}
void s_keys(unsigned char c, int x, int y) { s->keys(c, x, y); }
void s_keysup(unsigned char c, int x, int y) { s->keysup(c, x, y); }
void s_update(int i){ s->update(i);}

void Simulation::update(int i)
{
    glutTimerFunc(timer_ms, s_update, 0);

    run(10);

    glutPostRedisplay();
}

void Simulation::start(int argc, char **argv)
{
    s = this;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("test");

    glutDisplayFunc(s_display);

    glutMouseFunc(s_mouse);
    glutMotionFunc(s_motion);

    glutKeyboardFunc(s_keys);
    glutKeyboardUpFunc(s_keysup);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
    glClearColor(0.7, 0.7, 0.7, 1);
    eye_ = rotate_na(-2, 1, 0, 0) * eye_;
    eye_ = rotate_na(2, 0, 0, 1) * eye_;

    eye_ = eye_ * 3;

    update(0);

    glutMainLoop();
}
